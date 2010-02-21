#include "ShaderManager.h"
#include "TextureManager.h"
#include "GlobalSettings.h"

static global<bool> UseShaderList(true,NULL,"Shaders","bUseShaderList");
static global<char*> ShaderListFile("data\\shaders\\shaderlist.txt",NULL,"Shaders","sShaderListFile");
static global<bool> UseLegacyCompiler(false,NULL,"Shaders","bUseLegacyCompiler");

ShaderRecord::ShaderRecord()
{
	Name[0]=0;
	Effect=NULL;
	Enabled=false;
	ParentRefID = 0xFF000000;
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

	Effect->Begin(&passes,D3DXFX_DONOTSAVESTATE);
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
	HRESULT hr;

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
	if(UseLegacyCompiler.data)
		hr=D3DXCreateEffectFromFileA(GetD3DDevice(),NewPath,0,0,D3DXFX_NOT_CLONEABLE|D3DXSHADER_USE_LEGACY_D3DX9_31_DLL,0,&Effect,&pCompilationErrors);
	else
		hr=D3DXCreateEffectFromFileA(GetD3DDevice(),NewPath,0,0,D3DXFX_NOT_CLONEABLE,0,&Effect,&pCompilationErrors);
	
	if(hr!=D3D_OK && pCompilationErrors && !UseLegacyCompiler.data) 
	{
		pCompilationErrors->Release();
		pCompilationErrors=NULL;
		_MESSAGE("Shader compilation errors occured - trying legacy compiler.");
		hr=D3DXCreateEffectFromFileA(GetD3DDevice(),NewPath,0,0,D3DXFX_NOT_CLONEABLE|D3DXSHADER_USE_LEGACY_D3DX9_31_DLL,0,&Effect,&pCompilationErrors);
	}

	if (hr!=D3D_OK)
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
	strcpy(Filepath,Filename);
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

void ShaderRecord::SaveVars(OBSESerializationInterface *Interface)
{
	D3DXEFFECT_DESC Description;
	IDirect3DTexture9 *Texture;

	Effect->GetDesc(&Description);
	_MESSAGE("Shader %s has %i parameters.",Filepath,Description.Parameters);
	for (int par=0;par<Description.Parameters;par++)
	{
		D3DXHANDLE	handle;
		handle=Effect->GetParameter(NULL,par);
		if(handle)
		{
			D3DXPARAMETER_DESC Description;
			Effect->GetParameterDesc(handle,&Description);
			switch (Description.Type)
			{
			case D3DXPT_TEXTURE:
				
				int tex;
				Texture=NULL;
				
				TextureType TextureData;

				Effect->GetTexture(handle,(LPDIRECT3DBASETEXTURE9 *)&Texture);
				tex=TextureManager::GetSingleton()->FindTexture(Texture);
				strcpy(TextureData.Name,Description.Name);
				if(tex>0)
				{
					TextureData.tex=tex;
					Interface->WriteRecord('STEX',SHADERVERSION,&TextureData,sizeof(TextureData));
					_MESSAGE("Found texture: name - %s, texnum - %n",TextureData.Name,tex);
				}
				else
				{
					_MESSAGE("Found texture: name - %s - not in texture list.",TextureData.Name);
				}
				break;
			case D3DXPT_INT:
				
				IntType IntData;

				IntData.size=Description.Elements;
				if (IntData.size==0)
					IntData.size=1;
				Effect->GetIntArray(handle,(int *)&IntData.data,IntData.size);
				strcpy(IntData.Name,Description.Name);
				Interface->WriteRecord('SINT',SHADERVERSION,&IntData,sizeof(IntData));
				_MESSAGE("Found int: name - %s, size - %i, data[0] - %i",IntData.Name,IntData.size, IntData.data[0]);
				break;
			case D3DXPT_FLOAT:

				FloatType FloatData;

				FloatData.size=Description.Elements;
				if(FloatData.size==0)
					FloatData.size=1;
				Effect->GetFloatArray(handle,(float *)&FloatData.data,FloatData.size);
				strcpy(FloatData.Name,Description.Name);
				Interface->WriteRecord('SFLT',SHADERVERSION,&FloatData,sizeof(FloatData));
				_MESSAGE("Found float: name - %s, size - %i, data[0] - %f",FloatData.Name,FloatData.size, FloatData.data[0]);
				break;
			}
		}
	}
}

// *********************************************************************************************************

ShaderManager *ShaderManager::Singleton=NULL;

ShaderManager::ShaderManager()
{
	ShaderIndex=0;
	MaxShaderIndex=0;
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
	
	if(UseShaderList.data)
	{
		StaticShaderList::iterator SShader=StaticShaders.begin();

		while(SShader!=StaticShaders.end())
		{
			if((*SShader)->IsEnabled())
			{
				(*SShader)->ApplyConstants(&ShaderConst);
				(*SShader)->Render(D3DDevice,RenderTo);
				D3DDevice->StretchRect(RenderTo,0,TexMan->thisframeSurf,0,D3DTEXF_NONE);
			}
			SShader++;
		}
	}

	ShaderList::iterator Shader=Shaders.begin();

	while(Shader!=Shaders.end())
	{
		if(Shader->second->IsEnabled())
		{
			Shader->second->ApplyConstants(&ShaderConst);
			Shader->second->Render(D3DDevice,RenderTo);
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

int ShaderManager::AddShader(char *Filename, bool AllowDuplicates, UINT32 refID)
{
	ShaderList::iterator Shader=Shaders.begin();

	if (!AllowDuplicates)
	{
		while(Shader!=Shaders.end())
		{
			if(!_stricmp(Shader->second->Filepath,Filename)&&((Shader->second->ParentRefID&0xff000000)==(refID&0xff000000)))
			{
				_MESSAGE("Loading shader that already exists. Returning index of existing shader.");
				return(Shader->first);
			}
			Shader++;
		}
	}
	
	ShaderRecord	*NewShader=new(ShaderRecord);

	while(1)
	{
		Shader=Shaders.find(ShaderIndex);
		if (Shader==Shaders.end())
			break;
		ShaderIndex++;
	} 

	if(!NewShader->LoadShader(Filename))
	{
		delete(NewShader);
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

	NewShader->ParentRefID=refID;
	
	Shaders.insert(std::make_pair(ShaderIndex,NewShader));

	Console_Print("Loaded shader number %i",ShaderIndex);
	return(ShaderIndex++);
}

bool ShaderManager::AddStaticShader(char *Filename)
{
	ShaderRecord	*NewShader=NULL;
	
	NewShader=new(ShaderRecord);
	
	if(!NewShader->LoadShader(Filename))
	{
		delete(NewShader);
		return(false);
	}
	
	_MESSAGE("Setting effects screen texture.");
	TextureManager	*TexMan=TextureManager::GetSingleton();
	NewShader->Effect->SetTexture("thisframe",TexMan->thisframeTex);
	NewShader->Effect->SetTexture("lastpass",TexMan->lastpassTex);
	NewShader->Effect->SetTexture("lastframe",TexMan->lastframeTex);
	NewShader->Effect->SetTexture("Depth",TexMan->depth);

	NewShader->Effect->SetFloatArray("rcpres",(float*)&ShaderConst.rcpres,2);
	NewShader->Effect->SetBool("bHasDepth",ShaderConst.bHasDepth);
	
	StaticShaders.push_back(NewShader);

	return(true);
}

bool ShaderManager::RemoveShader(int ShaderNum)
{
	if(Shaders.erase(ShaderNum))
	{
		return(true);
	}
	return(false);
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

	StaticShaderList::iterator SShader=StaticShaders.begin();
	while(SShader!=StaticShaders.end())
	{
		while((*SShader)->Effect->Release()){}
		(*SShader)->Effect=NULL;
		SShader++;
	}
	StaticShaders.clear();

	ShaderList::iterator Shader=Shaders.begin();
	while(Shader!=Shaders.end())
	{
		while(Shader->second->Effect->Release()){}
		Shader->second->Effect=NULL;
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

	StaticShaderList::iterator SShader=StaticShaders.begin();

	while(SShader!=StaticShaders.end())
	{
		(*SShader)->OnLostDevice();
		SShader++;
	}

	ShaderList::iterator Shader=Shaders.begin();

	while(Shader!=Shaders.end())
	{
		Shader->second->OnLostDevice();
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
		Shader->second->OnResetDevice();
		Shader->second->Effect->SetTexture("thisframe",TexMan->thisframeTex);
		Shader->second->Effect->SetTexture("lastpass",TexMan->lastpassTex);
		Shader->second->Effect->SetTexture("lastframe",TexMan->lastframeTex);
		Shader->second->Effect->SetTexture("Depth",TexMan->depth);

		Shader->second->Effect->SetFloatArray("rcpres",(float*)&ShaderConst.rcpres,2);
		Shader->second->Effect->SetBool("bHasDepth",ShaderConst.bHasDepth);
		Shader++;
	}
}

void ShaderManager::LoadShaderList()
{
	FILE *ShaderFile;
	char ShaderBuffer[260];
	int lastpos;

	if(UseShaderList.data)
	{
		_MESSAGE("Loading the shaders.");
		if(!fopen_s(&ShaderFile,ShaderListFile.Get(),"rt"))
		{
			while(!feof(ShaderFile))
			{
				if(fgets(ShaderBuffer,260,ShaderFile))
				{
					lastpos=strlen(ShaderBuffer)-1;
					if (ShaderBuffer[lastpos]==10||ShaderBuffer[lastpos]==13)
						ShaderBuffer[lastpos]=0;
					AddStaticShader(ShaderBuffer);
				}
			}
			fclose(ShaderFile);
		}
		else
		{
			_MESSAGE("Error opening shaderlist.txt file.");
		}
	}
	else
	{
		_MESSAGE("ShaderList has been disabled by the INI file.");
	}
}

void ShaderManager::NewGame()
{
	StaticShaderList::iterator SShader=StaticShaders.begin();

	while(SShader!=StaticShaders.end())
	{
		while((*SShader)->Effect->Release()){}
		(*SShader)->Effect=NULL;
		SShader++;
	}

	StaticShaders.clear();

	ShaderList::iterator Shader=Shaders.begin();

	while(Shader!=Shaders.end())
	{
		while(Shader->second->Effect->Release()){}
		Shader->second->Effect=NULL;
		Shader++;
	}

	Shaders.clear();
}

void ShaderManager::SaveGame(OBSESerializationInterface *Interface)
{
	int temp;

	_MESSAGE("ShaderManager::SaveGame");

	ShaderList::iterator Shader=Shaders.begin();

	Interface->WriteRecord('SIDX',SHADERVERSION,&ShaderIndex,sizeof(ShaderIndex));
	_MESSAGE("Shader index = %i",ShaderIndex);

	while(Shader!=Shaders.end())
	{
		if(Shader->second->Effect)
		{
			Interface->WriteRecord('SNUM',SHADERVERSION,&Shader->first,sizeof(Shader->first));
			Interface->WriteRecord('SPAT',SHADERVERSION,Shader->second->Filepath,strlen(Shader->second->Filepath)+1);
			Interface->WriteRecord('SENB',SHADERVERSION,&Shader->second->Enabled,sizeof(Shader->second->Enabled));
			Interface->WriteRecord('SREF',SHADERVERSION,&Shader->second->ParentRefID,sizeof(Shader->second->ParentRefID));
			Shader->second->SaveVars(Interface);
			Interface->WriteRecord('SEOD',SHADERVERSION,&temp,1);
		}
		Shader++;
	}
	Interface->WriteRecord('SEOF',SHADERVERSION,&temp,1);
}

void ShaderManager::LoadGame(OBSESerializationInterface *Interface)
{
	UInt32	type, version, length;
	int LoadShaderNum;
	char LoadFilepath[260];
	bool LoadEnabled;
	UInt32 LoadRefID;
	bool InUse;

	Interface->GetNextRecordInfo(&type, &version, &length);

	if (type=='SIDX')
	{
		Interface->ReadRecordData(&ShaderIndex,length);
		_MESSAGE("Shader Index = %i",ShaderIndex);
	}
	else
	{
		_MESSAGE("No shader data in save file.");
		return;
	}

	Interface->GetNextRecordInfo(&type, &version, &length);

	while(type!='SEOF')
	{
		if(type=='SNUM')
		{
			Interface->ReadRecordData(&LoadShaderNum,length);
			_MESSAGE("Shader num = %i",LoadShaderNum);
		}
		else
		{
			_MESSAGE("Error loading shader list. type!=SNUM");
			return;
		}

		Interface->GetNextRecordInfo(&type, &version, &length);

		if(type=='SPAT')
		{
			Interface->ReadRecordData(LoadFilepath,length);
			_MESSAGE("Filename = %s",LoadFilepath);
		}
		else
		{
			_MESSAGE("Error loading shader list. type!=SPAT");
			return;
		}

		Interface->GetNextRecordInfo(&type, &version, &length);

		if(type=='SENB')
		{
			Interface->ReadRecordData(&LoadEnabled,length);
			_MESSAGE("Enabled = %i",LoadEnabled);
		}
		else
		{
			_MESSAGE("Error loading shader list. type!=SENB");
			return;
		}

		Interface->GetNextRecordInfo(&type, &version, &length);

		if(type=='SREF')
		{
			Interface->ReadRecordData(&LoadRefID,length);
			_MESSAGE("RefID = %X",LoadRefID);
			if (LoadRefID==0)
			{
				_MESSAGE("NULL refID. Will load shader as I can't resolve it's state.");
				InUse=true;
			}
			else
			{
				InUse=Interface->ResolveRefID(LoadRefID,&LoadRefID);
				_MESSAGE("Is in use = %i",InUse);
			}
		}
		else
		{
			_MESSAGE("Error loading shader list. type!=SREF");
			return;
		}

		ShaderRecord *NewShader=new(ShaderRecord);

		if(InUse && NewShader->LoadShader(LoadFilepath))
		{
			NewShader->Enabled=LoadEnabled;
			NewShader->ParentRefID=LoadRefID;

		_MESSAGE("Setting effects screen texture.");
		TextureManager	*TexMan=TextureManager::GetSingleton();
		NewShader->Effect->SetTexture("thisframe",TexMan->thisframeTex);
		NewShader->Effect->SetTexture("lastpass",TexMan->lastpassTex);
		NewShader->Effect->SetTexture("lastframe",TexMan->lastframeTex);
		NewShader->Effect->SetTexture("Depth",TexMan->depth);

		NewShader->Effect->SetFloatArray("rcpres",(float*)&ShaderConst.rcpres,2);
		NewShader->Effect->SetBool("bHasDepth",ShaderConst.bHasDepth);

	
			Interface->GetNextRecordInfo(&type, &version, &length);

			while(type!='SEOD')
			{
				switch(type)
				{
				case 'STEX':
					TextureType TextureData;

					Interface->ReadRecordData(&TextureData,length);

					NewShader->SetShaderTexture(TextureData.Name,TextureData.tex);
					_MESSAGE("Texture %s = %i",TextureData.Name,TextureData.tex);
					break;
				case 'SINT':
					IntType IntData;

					Interface->ReadRecordData(&IntData,length);

					NewShader->Effect->SetIntArray(IntData.Name,(int *)&IntData.data,IntData.size);
					_MESSAGE("Int %s = %i(%i)",IntData.Name,IntData.data[0],IntData.size);
					break;
				case 'SFLT':
					FloatType FloatData;

					Interface->ReadRecordData(&FloatData,length);

					NewShader->Effect->SetFloatArray(FloatData.Name, (float *)&FloatData.data, FloatData.size);
					_MESSAGE("Float %s = %f(%i)",FloatData.Name, FloatData.data[0], FloatData.size);
					break;
				}
				Interface->GetNextRecordInfo(&type, &version, &length);
			}
			Shaders.insert(std::make_pair(LoadShaderNum,NewShader));
			_MESSAGE("Inserting the shader into the list.");
		}
		else
		{
			delete(NewShader);
			
			Interface->GetNextRecordInfo(&type, &version, &length);

			while(type!='SEOD')
			{
				Interface->ReadRecordData(&LoadFilepath,length);
				Interface->GetNextRecordInfo(&type, &version, &length);
			}
		}
		Interface->GetNextRecordInfo(&type,&version,&length);
	}
}
		
bool ShaderManager::IsShaderValid(int ShaderNum)
{
	if(Shaders.find(ShaderNum)==Shaders.end())
		return(false);
	return(true);
}

bool ShaderManager::EnableShader(int ShaderNum, bool State)
{
	ShaderList::iterator Shader;
	
	Shader=Shaders.find(ShaderNum);
	if(Shader!=Shaders.end())
	{
		Shader->second->Enabled=State;
		return(true);
	}
	return(false);
}

bool ShaderManager::SetShaderInt(int ShaderNum, char *name, int value)
{
	ShaderList::iterator Shader;
	
	Shader=Shaders.find(ShaderNum);
	if(Shader!=Shaders.end())
	{
		return(Shader->second->SetShaderInt(name,value));
	}
	return(false);
}

bool ShaderManager::SetShaderFloat(int ShaderNum, char *name, float value)
{
	ShaderList::iterator Shader;
	
	Shader=Shaders.find(ShaderNum);
	if(Shader!=Shaders.end())
	{
		return(Shader->second->SetShaderFloat(name,value));
	}
	return(false);
}

bool ShaderManager::SetShaderVector(int ShaderNum, char *name, v1_2_416::NiVector4 *value)
{
	ShaderList::iterator Shader;
	
	Shader=Shaders.find(ShaderNum);
	if(Shader!=Shaders.end())
	{
		return(Shader->second->SetShaderVector(name,value));
	}
	return(false);
}

bool ShaderManager::SetShaderTexture(int ShaderNum, char *name, int TextureNum)
{
	ShaderList::iterator Shader;
	
	Shader=Shaders.find(ShaderNum);
	if(Shader!=Shaders.end())
	{
		return(Shader->second->SetShaderTexture(name,TextureNum));
	}
	return(false);
}

void ShaderManager::PurgeTexture(IDirect3DTexture9 *texture)
{
	ShaderList::iterator Shader=Shaders.begin();

	while(Shader!=Shaders.end())
	{
		D3DXEFFECT_DESC Description;
		Shader->second->Effect->GetDesc(&Description);
		for (int par=0;par<Description.Parameters;par++)
		{
			D3DXHANDLE	handle;
			handle=Shader->second->Effect->GetParameter(NULL,par);
			if(handle)
			{
				D3DXPARAMETER_DESC Description;
				Shader->second->Effect->GetParameterDesc(handle,&Description);
				if(Description.Type=D3DXPT_TEXTURE)
				{
					IDirect3DBaseTexture9 *ShaderTexture=NULL;				// NB must set to NULL otherwise strange things happen
					Shader->second->Effect->GetTexture(handle,&ShaderTexture);
					if(ShaderTexture==texture)
					{
						Shader->second->Effect->SetTexture(handle,NULL);
						_MESSAGE("Removing texture %s from shader %i",Description.Name,Shader->first);
					}
					
				}
			}
		}
		Shader++;
	}
}