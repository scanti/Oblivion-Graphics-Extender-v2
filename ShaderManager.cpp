#include "ShaderManager.h"
#include "TextureManager.h"

ShaderRecord::ShaderRecord()
{
	Name[0]=0;
	Effect=NULL;
	Enabled=false;
}

ShaderRecord::~ShaderRecord()
{
	if(Effect)
		while(Effect->Release()){};
}

void ShaderRecord::Render(IDirect3DDevice9*	D3DDevice,IDirect3DSurface9 *RenderTo)
{
	if(!Enabled)
		return;
	UINT passes;

	Effect->Begin(&passes,0);
	UINT pass=0;
	while(true)
	{
		Effect->BeginPass(pass);
		D3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		Effect->EndPass();
		if(++pass>=passes)
			break;
		D3DDevice->StretchRect(RenderTo,0,TextureManager::GetSingleton()->lastpassSurf,0,D3DTEXF_NONE);  
	}
	Effect->End();
	return;
}

void ShaderRecord::OnLostDevice(void)
{
	Effect->OnLostDevice();
	return;
}

void ShaderRecord::OnResetDevice(void)
{
	Effect->OnResetDevice();
	return;
}

void ShaderRecord::ApplyConstants(Constants *ConstList)
{
	Effect->SetMatrix("m44world",&ConstList->world);
	Effect->SetMatrix("m44view",&ConstList->view);
	Effect->SetMatrix("m44proj",&ConstList->proj);
	Effect->SetVector("f4Time",&ConstList->time);
	Effect->SetVector("f4SunDir",&ConstList->SunDir);
	Effect->SetFloatArray("f3EyeForward",&ConstList->EyeForward.x,3);
	return;
}

bool ShaderRecord::IsEnabled()
{
	return(Enabled);
}

bool ShaderRecord::LoadShader(char *Filename)
{
	if(Effect)
	{
		while(Effect->Release()){};
		Name[0]=0;
	}
	
	if(strlen(Filename)>240)
		return(false);

	char NewPath[260];
	strcpy(NewPath,"data\\shaders\\");
	strcat(NewPath,Filename);

	_MESSAGE("Loading shader (%s)",NewPath);

	LPD3DXBUFFER pCompilationErrors=0;
	HRESULT hr=D3DXCreateEffectFromFileA(GetD3DDevice(),NewPath,0,0,D3DXFX_NOT_CLONEABLE,0,&Effect,&pCompilationErrors);
	if(hr!=D3D_OK) 
	{
		if(pCompilationErrors) 
		{
			_MESSAGE("Shader compilation errors occured");
			_MESSAGE(Filename);
			_MESSAGE((char*)pCompilationErrors->GetBufferPointer());
			pCompilationErrors->Release();
		}
		else
		{
			_MESSAGE("Failed to load.");
		}
		return(false);
	}
	ApplyCompileDirectives();
	strcpy(Filepath,NewPath);
	Enabled=true;
	return(true);
}

void ShaderRecord::ApplyCompileDirectives()
{
	LPCSTR	pName=NULL;
	Effect->GetString("Name",&pName);
	if (pName)
		strcpy(Name,(char *)pName);

	D3DXEFFECT_DESC Description;
	StaticTextureRecord	*Tex;

	Effect->GetDesc(&Description);
	for (int par=0;par<Description.Parameters;par++)
	{
		D3DXHANDLE	handle;
		handle=Effect->GetParameter(NULL,par);
		if(handle)
		{
			D3DXPARAMETER_DESC Description;
			Effect->GetParameterDesc(handle,&Description);
			if(Description.Type=D3DXPT_TEXTURE)
			{
				D3DXHANDLE handle2;
				handle2=Effect->GetAnnotationByName(handle,"filename");
				if(handle2)
				{
					LPCSTR	pString=NULL;
					Effect->GetString(handle2,&pString);
					_MESSAGE("Found filename : %s",pString);
					Tex=TextureManager::GetSingleton()->LoadStaticTexture((char *)pString);
					if(Tex)
						Effect->SetTexture(handle,Tex->texture);
				}
			}
		}
	}
}

bool ShaderRecord::SetShaderInt(char *name, int value)
{
	HRESULT hr=Effect->SetInt(name,value);
	return(hr==D3D_OK);
}

bool ShaderRecord::SetShaderFloat(char *name, float value)
{
	HRESULT hr=Effect->SetFloat(name,value);
	return(hr==D3D_OK);
}

bool ShaderRecord::SetShaderVector(char *name,v1_2_416::NiVector4 *value)
{
	HRESULT hr=Effect->SetVector(name,value);
	return(hr==D3D_OK);
}

bool ShaderRecord::SetShaderTexture(char *name, int TextureNum)
{
	IDirect3DTexture9* texture;
	IDirect3DTexture9* OldTexture=NULL;

	texture=TextureManager::GetSingleton()->GetTexture(TextureNum);
	
	Effect->GetTexture(name,(LPDIRECT3DBASETEXTURE9 *)&OldTexture);
	if(OldTexture)
		TextureManager::GetSingleton()->ReleaseTexture(OldTexture);
	HRESULT hr=Effect->SetTexture(name,texture);
	return(hr==D3D_OK);
}

// *********************************************************************************************************

ShaderManager *ShaderManager::Singleton=NULL;

ShaderManager::ShaderManager()
{
	DynamicShaderStart=0;
}

ShaderManager::~ShaderManager()
{
	Singleton=NULL;
	if(D3D_ShaderBuffer)
		while(D3D_ShaderBuffer->Release()){};
}

ShaderManager*	ShaderManager::GetSingleton()
{
	if(!ShaderManager::Singleton)
		ShaderManager::Singleton=new(ShaderManager);
	return(ShaderManager::Singleton);
}

void ShaderManager::UpdateFrameConstants()
{
	v1_2_416::NiDX9Renderer *Renderer = v1_2_416::GetRenderer();

	OBGEfork::Sun	*pSun=OBGEfork::Sky::GetSingleton()->sun;
	float (_cdecl *GetTimer)(bool, bool)=(float(*)(bool, bool))0x0043F490; // (TimePassed,GameTime)
	v1_2_416::NiCamera	**pMainCamera = (v1_2_416::NiCamera **)0x00B43124;
	char		*CamName;

	Renderer->SetCameraViewProj(*pMainCamera);
	D3DXMatrixTranslation(&ShaderConst.world,-(*pMainCamera)->m_worldTranslate.x,-(*pMainCamera)->m_worldTranslate.y,-(*pMainCamera)->m_worldTranslate.z);
	ShaderConst.view=(D3DXMATRIX)Renderer->m44View;
	ShaderConst.proj=(D3DXMATRIX)Renderer->m44Projection;
	
	CamName=(*pMainCamera)->m_pcName;
	(*pMainCamera)->m_worldRotate.GetForwardVector(&ShaderConst.EyeForward);

	ShaderConst.time.x=GetTimer(0,1);
	ShaderConst.time.w=(int)ShaderConst.time.x%60;
	ShaderConst.time.z=(int)(ShaderConst.time.x/60)%60;
	ShaderConst.time.y=(int)(ShaderConst.time.x/60)/60;

	ShaderConst.SunDir.x=pSun->SunBillboard.Get()->ParentNode->m_localTranslate.x;
	ShaderConst.SunDir.y=pSun->SunBillboard.Get()->ParentNode->m_localTranslate.y;
	ShaderConst.SunDir.z=pSun->SunBillboard.Get()->ParentNode->m_localTranslate.z;
	ShaderConst.SunDir.Normalize3();
}

void ShaderManager::Render(IDirect3DDevice9 *D3DDevice,IDirect3DSurface9 *RenderTo, IDirect3DSurface9 *RenderFrom)
{
	v1_2_416::NiDX9Renderer *Renderer = v1_2_416::GetRenderer();

	D3DDevice->SetStreamSource(0,D3D_ShaderBuffer,0,sizeof(D3D_sShaderVertex));
	Renderer->RenderStateManager->SetFVF(MYVERTEXFORMAT,false);

	float test[4];
	test[0]=0.0;
	test[1]=1.0;
	test[2]=1.0;
	test[3]=0.0;
	Renderer->func_51(test); // Sets up the viewport.

	Renderer->RenderStateManager->SetRenderState(D3DRS_COLORWRITEENABLE,0xF,false);
	Renderer->RenderStateManager->SetRenderState(D3DRS_ALPHABLENDENABLE,false,false);
	Renderer->RenderStateManager->SetRenderState(D3DRS_ZENABLE,D3DZB_FALSE,false);

	UpdateFrameConstants();

	TextureManager* TexMan=TextureManager::GetSingleton();

	if(TexMan->RAWZflag)
	{
		D3DDevice->EndScene();
		D3DDevice->SetRenderTarget(0,TexMan->depthSurface);
		D3DDevice->BeginScene();
		RenderRAWZfix(D3DDevice,RenderTo);
		D3DDevice->EndScene();
		D3DDevice->SetRenderTarget(0,RenderTo);
		D3DDevice->BeginScene();
	}


	D3DDevice->StretchRect(RenderFrom,0,TexMan->thisframeSurf,0,D3DTEXF_NONE);
	D3DDevice->StretchRect(RenderFrom,0,RenderTo,0,D3DTEXF_NONE); // Blank screen fix when ShaderList is empty.
	
	ShaderList::iterator Shader=Shaders.begin();

	while(Shader!=Shaders.end())
	{
		if((*Shader)->IsEnabled())
		{
			(*Shader)->ApplyConstants(&ShaderConst);
			(*Shader)->Render(D3DDevice,RenderTo);
			D3DDevice->StretchRect(RenderTo,0,TexMan->thisframeSurf,0,D3DTEXF_NONE);
		}
		Shader++;
	}
	
	D3DDevice->StretchRect(RenderTo,0,TexMan->lastframeSurf,0,D3DTEXF_NONE);
	return;
}

void ShaderManager::RenderRAWZfix(IDirect3DDevice9* D3DDevice,IDirect3DSurface9 *RenderTo)
{
	if(!DepthShader)
	{
		DepthShader=new(ShaderRecord);
		DepthShader->LoadShader("RAWZfix.fx");
		DepthShader->Effect->SetTexture("RAWZdepth",TextureManager::GetSingleton()->depthRAWZ);
	}
	DepthShader->Render(D3DDevice,RenderTo);
	return;
}

int ShaderManager::AddShader(char *Filename, bool AllowDuplicates)
{
	int pos;

	if (!AllowDuplicates)
	{
		for(pos=DynamicShaderStart;pos<Shaders.size();pos++)
		{
			if(Shaders.at(pos)->Effect)
			{
				if(!_stricmp(Shaders.at(pos)->Filepath,Filename))
				{
					_MESSAGE("Loading shader that already exists. Returning index of existing shader.");
					return(pos-DynamicShaderStart);
				}
			}
		}
	}
	
	ShaderRecord	*NewShader=NULL;
	bool AddToEnd=true;

	for(pos=0;pos<Shaders.size();pos++)
	{
		if(!Shaders.at(pos)->Effect)
		{
			NewShader=Shaders.at(pos);
			AddToEnd=false;
			break;
		}
	}

	if(AddToEnd)
		NewShader=new(ShaderRecord);
	
	if(!NewShader->LoadShader(Filename))
	{
		if(AddToEnd)
			delete(NewShader);
		else
			if(NewShader->Effect)
			{
				NewShader->Effect->Release();
				NewShader->Effect=NULL;
			}
		return(-1);
	}
	
	_MESSAGE("Setting effects screen texture.");
	TextureManager	*TexMan=TextureManager::GetSingleton();
	NewShader->Effect->SetTexture("thisframe",TexMan->thisframeTex);
	NewShader->Effect->SetTexture("lastpass",TexMan->lastpassTex);
	NewShader->Effect->SetTexture("lastframe",TexMan->lastframeTex);
	NewShader->Effect->SetTexture("Depth",TexMan->depth);

	NewShader->Effect->SetFloatArray("rcpres",(float*)&ShaderConst.rcpres,2);
	NewShader->Effect->SetBool("bHasDepth",ShaderConst.bHasDepth);
	
	if(AddToEnd)
		Shaders.push_back(NewShader);

	Console_Print("Loaded shader number %i",pos-DynamicShaderStart);
	return(pos-DynamicShaderStart);
}

bool ShaderManager::RemoveShader(int ShaderNum)
{
	if((ShaderNum+DynamicShaderStart)>=Shaders.size())
		return(false);
	if(Shaders.at(ShaderNum+DynamicShaderStart)->Effect)
	{
		while(Shaders.at(ShaderNum+DynamicShaderStart)->Effect->Release()){};
		Shaders.at(ShaderNum+DynamicShaderStart)->Effect=NULL;
		if ((ShaderNum+DynamicShaderStart)==(Shaders.size()-1))
			PurgeShaderList();
		return(true);
	}
	return(false);
}

void ShaderManager::PurgeShaderList()
{
	for (int i=Shaders.size()-1;i<=0;i--)
	{
		if(Shaders.at(i)->Effect=NULL)
		{
			delete(Shaders.at(i));
			Shaders.pop_back();
		}
		else
			break;
	}
}

void ShaderManager::InitialiseBuffers()
{
	D3D_sShaderVertex ShaderVertices[] = 
	{
		{-0.5,-0.5,0,1,0,0},
		{-0.5,+5.0,0,1,0,1},
		{+5.0,-0.5,0,1,1,0},
		{+5.0,+5.0,0,1,1,1}
	};

	_MESSAGE("Creating vertex buffers.");
	GetD3DDevice()->CreateVertexBuffer(4*sizeof(D3D_sShaderVertex),D3DUSAGE_WRITEONLY,MYVERTEXFORMAT,D3DPOOL_DEFAULT,&D3D_ShaderBuffer,0);
	void* VertexPointer;
	ShaderVertices[3].x=ShaderVertices[2].x=(float)(v1_2_416::GetRenderer()->SizeWidth)-.5f;
	ShaderVertices[3].y=ShaderVertices[1].y=(float)(v1_2_416::GetRenderer()->SizeHeight)-.5f;
	D3D_ShaderBuffer->Lock(0,0,&VertexPointer,0);
	CopyMemory(VertexPointer,ShaderVertices,sizeof(ShaderVertices));
	D3D_ShaderBuffer->Unlock();
	
	ShaderConst.rcpres[0]=1.0f/(float)v1_2_416::GetRenderer()->SizeWidth;
	ShaderConst.rcpres[1]=1.0f/(float)v1_2_416::GetRenderer()->SizeHeight;
	ShaderConst.bHasDepth=HasDepth();

	return;
}

void ShaderManager::DeviceRelease()
{
	if(D3D_ShaderBuffer)
	{
		_MESSAGE("Releasing shader vertex buffer.");
		if(D3D_ShaderBuffer)
		{
			while(D3D_ShaderBuffer->Release()){}
			D3D_ShaderBuffer=NULL;
		}
	}

	ShaderList::iterator Shader=Shaders.begin();

	while(Shader!=Shaders.end())
	{
		while((*Shader)->Effect->Release()){}
		(*Shader)->Effect=NULL;
		Shader++;
	}
	Shaders.clear();
}

void ShaderManager::OnLostDevice()
{
	if(D3D_ShaderBuffer)
	{
		_MESSAGE("Releasing shader vertex buffer.");
		if(D3D_ShaderBuffer)
		{
			while(D3D_ShaderBuffer->Release()){}
			D3D_ShaderBuffer=NULL;
		}
	}

	ShaderList::iterator Shader=Shaders.begin();

	while(Shader!=Shaders.end())
	{
		(*Shader)->OnLostDevice();
		Shader++;
	}
}

void ShaderManager::OnResetDevice()
{
	TextureManager	*TexMan=TextureManager::GetSingleton();
	
	InitialiseBuffers();

	ShaderList::iterator Shader=Shaders.begin();
	while(Shader!=Shaders.end())
	{
		(*Shader)->OnResetDevice();
		(*Shader)->Effect->SetTexture("thisframe",TexMan->thisframeTex);
		(*Shader)->Effect->SetTexture("lastpass",TexMan->lastpassTex);
		(*Shader)->Effect->SetTexture("lastframe",TexMan->lastframeTex);
		(*Shader)->Effect->SetTexture("Depth",TexMan->depth);

		(*Shader)->Effect->SetFloatArray("rcpres",(float*)&ShaderConst.rcpres,2);
		(*Shader)->Effect->SetBool("bHasDepth",ShaderConst.bHasDepth);
		Shader++;
	}
}

void ShaderManager::LoadShaderList()
{
	FILE *ShaderFile;
	char ShaderBuffer[260];
	int lastpos;

	_MESSAGE("Loading the shaders.");
	if(!fopen_s(&ShaderFile,"data\\shaders\\shaderlist.txt","rt"))
	{
		while(!feof(ShaderFile))
		{
			if(fgets(ShaderBuffer,260,ShaderFile))
			{
				lastpos=strlen(ShaderBuffer)-1;
				if (ShaderBuffer[lastpos]==10||ShaderBuffer[lastpos]==13)
					ShaderBuffer[lastpos]=0;
				AddShader(ShaderBuffer,true);
			}
		}
		fclose(ShaderFile);
		DynamicShaderStart=Shaders.size();
	}
	else
	{
		_MESSAGE("Error opening shaderlist.txt file.");
		DynamicShaderStart=0;
	}
}

void ShaderManager::NewGame()
{
	ShaderList::iterator Shader=Shaders.begin();

	while(Shader!=Shaders.end())
	{
		while((*Shader)->Effect->Release()){}
		(*Shader)->Effect=NULL;
		Shader++;
	}
	Shaders.clear();
}

bool ShaderManager::IsShaderValid(int ShaderNum)
{
	if((ShaderNum+DynamicShaderStart)>=Shaders.size())
		return(false);
	if(!Shaders.at(ShaderNum+DynamicShaderStart)->Effect)
		return(false);
	return(true);
}

bool ShaderManager::EnableShader(int ShaderNum, bool State)
{
	if(!IsShaderValid(ShaderNum))
		return(false);
	Shaders.at(ShaderNum+DynamicShaderStart)->Enabled=State;
	return(true);
}

bool ShaderManager::SetShaderInt(int ShaderNum, char *name, int value)
{
	if(!IsShaderValid(ShaderNum))
		return(false);
	return(Shaders.at(ShaderNum+DynamicShaderStart)->SetShaderInt(name,value));
}

bool ShaderManager::SetShaderFloat(int ShaderNum, char *name, float value)
{
	if(!IsShaderValid(ShaderNum))
		return(false);
	return(Shaders.at(ShaderNum+DynamicShaderStart)->SetShaderFloat(name,value));
}

bool ShaderManager::SetShaderVector(int ShaderNum, char *name, v1_2_416::NiVector4 *value)
{
	if(!IsShaderValid(ShaderNum))
		return(false);
	return(Shaders.at(ShaderNum+DynamicShaderStart)->SetShaderVector(name,value));
}

bool ShaderManager::SetShaderTexture(int ShaderNum, char *name, int TextureNum)
{
	if(!IsShaderValid(ShaderNum))
		return(false);
	return(Shaders.at(ShaderNum+DynamicShaderStart)->SetShaderTexture(name,TextureNum));
}

void ShaderManager::PurgeTexture(IDirect3DTexture9 *texture)
{
	for(int i=DynamicShaderStart;i<Shaders.size();i++)
	{
		D3DXEFFECT_DESC Description;
		Shaders[i]->Effect->GetDesc(&Description);
		for (int par=0;par<Description.Parameters;par++)
		{
			D3DXHANDLE	handle;
			handle=Shaders[i]->Effect->GetParameter(NULL,par);
			if(handle)
			{
				D3DXPARAMETER_DESC Description;
				Shaders[i]->Effect->GetParameterDesc(handle,&Description);
				if(Description.Type=D3DXPT_TEXTURE)
				{
					IDirect3DBaseTexture9 *ShaderTexture=NULL;				// NB must set to NULL otherwise strange things happen
					Shaders[i]->Effect->GetTexture(handle,&ShaderTexture);
					if(ShaderTexture==texture)
					{
						Shaders[i]->Effect->SetTexture(handle,NULL);
						_MESSAGE("Removing texture %s from shader %i",Description.Name,i-DynamicShaderStart);
					}
					
				}
			}
		}
	}
}