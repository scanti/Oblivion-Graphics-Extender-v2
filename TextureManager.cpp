#include "TextureManager.h"
#include "ShaderManager.h"
#include "ScreenElements.h"
#include "obse\pluginapi.h"
#include "GlobalSettings.h"

static global<int> BufferTexturesNumBits(8,NULL,"ScreenBuffers","iBufferTexturesNumBits");

TextureRecord::TextureRecord()
{
	texture=NULL;
	Filepath[0]=0;
}

TextureRecord::~TextureRecord()
{
	if(texture)
	{
		while(texture->Release()){}
	}
	texture=NULL;
}

StaticTextureRecord::StaticTextureRecord()
{
	RefCount=0;
}

StaticTextureRecord::~StaticTextureRecord()
{
}

int StaticTextureRecord::AddRef()
{
	RefCount++;
	return(RefCount);
}

int StaticTextureRecord::Release()
{
	if (RefCount)
		RefCount--;
	if(!RefCount)
	{
		delete(this);
		return(NULL);
	}
	return(RefCount);
}

TextureManager::TextureManager()
{
	thisframeTex=NULL;
	lastpassTex=NULL;
	lastframeTex=NULL;
	thisframeSurf=NULL;
	lastpassSurf=NULL;
	lastframeSurf=NULL;
	HasDepth=false;
	depth=NULL;
	depthSurface=NULL;
	depthRAWZ=NULL;
	RAWZflag=false;
}

TextureManager::~TextureManager()
{
	if(thisframeSurf)
		thisframeSurf->Release();
	if(lastframeSurf)
		lastframeSurf->Release();
	if(lastpassSurf)
		lastpassSurf->Release();
	if(thisframeTex)
		while(thisframeTex->Release()){};
	if(lastframeTex)
		while(lastframeTex->Release()){};
	if(lastpassTex)
		while(lastpassTex->Release()){};
	if(IsRAWZ()&&depth)
		while(depth->Release()){};
}

TextureManager*	TextureManager::Singleton=NULL;

TextureManager*	TextureManager::GetSingleton()
{
	if(!Singleton)
		Singleton=new(TextureManager);
	return(Singleton);
}

void	TextureManager::InitialiseFrameTextures()
{
	HRESULT hr;

	if(BufferTexturesNumBits.data>32 || BufferTexturesNumBits.data%8>0)
		BufferTexturesNumBits.data=8;

	UInt32 Width=v1_2_416::GetRenderer()->SizeWidth;
	UInt32 Height=v1_2_416::GetRenderer()->SizeHeight;

	_MESSAGE("Creating shader textures.");
	_MESSAGE("Width = %i, Height = %i",Width,Height);
	
	if(BufferTexturesNumBits.data==32)
	{
		hr=GetD3DDevice()->CreateTexture(Width,Height,1,D3DUSAGE_RENDERTARGET,D3DFMT_A32B32G32R32F,D3DPOOL_DEFAULT,&thisframeTex,0);
		if(FAILED(hr))
		{
			thisframeTex->Release();
			BufferTexturesNumBits.data=16;
		}
		else
		{
			GetD3DDevice()->CreateTexture(Width,Height,1,D3DUSAGE_RENDERTARGET,D3DFMT_A32B32G32R32F,D3DPOOL_DEFAULT,&lastpassTex,0);
			GetD3DDevice()->CreateTexture(Width,Height,1,D3DUSAGE_RENDERTARGET,D3DFMT_A32B32G32R32F,D3DPOOL_DEFAULT,&lastframeTex,0);
		}
	}

	if(BufferTexturesNumBits.data==16)
	{
		hr=GetD3DDevice()->CreateTexture(Width,Height,1,D3DUSAGE_RENDERTARGET,D3DFMT_A16B16G16R16F,D3DPOOL_DEFAULT,&thisframeTex,0);
		if(FAILED(hr))
		{
			thisframeTex->Release();
			BufferTexturesNumBits.data=8;
		}
		else
		{
			GetD3DDevice()->CreateTexture(Width,Height,1,D3DUSAGE_RENDERTARGET,D3DFMT_A16B16G16R16F,D3DPOOL_DEFAULT,&lastpassTex,0);
			GetD3DDevice()->CreateTexture(Width,Height,1,D3DUSAGE_RENDERTARGET,D3DFMT_A16B16G16R16F,D3DPOOL_DEFAULT,&lastframeTex,0);
		}
	}

	if(BufferTexturesNumBits.data==8)
	{
		GetD3DDevice()->CreateTexture(Width,Height,1,D3DUSAGE_RENDERTARGET,D3DFMT_X8R8G8B8,D3DPOOL_DEFAULT,&thisframeTex,0);
		GetD3DDevice()->CreateTexture(Width,Height,1,D3DUSAGE_RENDERTARGET,D3DFMT_X8R8G8B8,D3DPOOL_DEFAULT,&lastpassTex,0);
		GetD3DDevice()->CreateTexture(Width,Height,1,D3DUSAGE_RENDERTARGET,D3DFMT_X8R8G8B8,D3DPOOL_DEFAULT,&lastframeTex,0);
	}

	_MESSAGE("Setting shader surfaces.");
	thisframeTex->GetSurfaceLevel(0,&thisframeSurf);
	lastpassTex->GetSurfaceLevel(0,&lastpassSurf);
	lastframeTex->GetSurfaceLevel(0,&lastframeSurf);

	_MESSAGE("Setting depth texture.");
	if(IsRAWZ())
	{
		_MESSAGE("RAWZ depth texture - applying fix.");
		depthRAWZ=GetDepthBufferTexture();
		GetD3DDevice()->CreateTexture(v1_2_416::GetRenderer()->SizeWidth,v1_2_416::GetRenderer()->SizeHeight,1,D3DUSAGE_RENDERTARGET,D3DFMT_R32F,D3DPOOL_DEFAULT,&depth,0);
		depth->GetSurfaceLevel(0,&depthSurface);
		RAWZflag=true;
	}
	else
		depth=GetDepthBufferTexture();
}

void	TextureManager::DeviceRelease()
{
	if(thisframeSurf)
	{
		_MESSAGE("Releasing thisframe surface.");
		thisframeSurf->Release();
		thisframeSurf=NULL;
	}
	
	if (thisframeTex)
	{
		_MESSAGE("Releasing thisframe texture.");
		while(thisframeTex->Release()){}
		thisframeTex=NULL;
	}
	if(lastpassSurf)
	{
		_MESSAGE("Releasing lastpass surface.");
		lastpassSurf->Release();
		lastpassSurf=NULL;
	}

	if (lastpassTex)
	{
		_MESSAGE("Releasing lastpass texture.");
		while(lastpassTex->Release()){}
		lastpassTex=NULL;
	}

	if(lastframeSurf)
	{
		_MESSAGE("Releasing lastframe surface.");
		lastframeSurf->Release();
		lastframeSurf=NULL;
	}

	if (lastframeTex)
	{
		_MESSAGE("Releasing lastframe texture.");
		while(lastframeTex->Release()){}
		lastframeTex=NULL;
	}
}

int	TextureManager::LoadTexture(char *Filename, DWORD FromFile)
{
	if(strlen(Filename)>240) return NULL;
	
	char NewPath[256];
	strcpy_s(NewPath,256,"data\\textures\\");
	strcat_s(NewPath,256,Filename);

	_MESSAGE("Loading texture (%s)",NewPath);

	IDirect3DTexture9* tex=NULL;

	if(FromFile)
	{
		if(FAILED(D3DXCreateTextureFromFileEx(GetD3DDevice(),NewPath,D3DX_DEFAULT_NONPOW2,D3DX_DEFAULT_NONPOW2,D3DX_FROM_FILE,0,D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,0,0,0,&tex))||!tex)
			return -1;
	} 
	else 
	{
		if(FAILED(D3DXCreateTextureFromFile(GetD3DDevice(),NewPath,&tex))||!tex) 
			return -1;
	}

	for(int i=0;i<Textures.size();i++)
	{
		if(Textures[i]->texture==0)
		{
			Textures[i]->texture=tex;
			strcpy_s(Textures[i]->Filepath,256,NewPath);
			Textures[i]->FromFile=(FromFile!=0);
			return i;
		}
	}
	TextureRecord	*TextureElement=new(TextureRecord);
	TextureElement->texture=tex;
	strcpy_s(TextureElement->Filepath,256,Filename);
	TextureElement->FromFile=(FromFile!=0);
	Textures.push_back(TextureElement);
	return Textures.size()-1;
}

StaticTextureRecord*	TextureManager::LoadStaticTexture(char *Filename)
{
	if(strlen(Filename)>240) return NULL;
	
	char NewPath[256];
	strcpy_s(NewPath,256,"data\\textures\\");
	strcat_s(NewPath,256,Filename);

	_MESSAGE("Loading texture (%s)",NewPath);

	for (int i=0;i<StaticTextures.size();i++)
	{
		if(_stricmp(NewPath,StaticTextures.at(i)->Filepath)==0)
		{
			_MESSAGE("Linking to existing texture.");
			StaticTextures.at(i)->AddRef();
			return(StaticTextures.at(i));
		}
	}

	IDirect3DTexture9* tex=NULL;

	if(FAILED(D3DXCreateTextureFromFileEx(GetD3DDevice(),NewPath,D3DX_DEFAULT_NONPOW2,D3DX_DEFAULT_NONPOW2,D3DX_FROM_FILE,0,D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,0,0,0,&tex))||!tex)
		if(FAILED(D3DXCreateTextureFromFile(GetD3DDevice(),NewPath,&tex))||!tex) 
			return NULL;

	StaticTextureRecord*	NewTex = new(StaticTextureRecord);
	
	NewTex->texture=tex;
	NewTex->AddRef();

	strcpy_s(NewTex->Filepath,256,NewPath);
	StaticTextures.push_back(NewTex);
	return(NewTex);
}

void TextureManager::NewGame()
{
	TextureList::iterator Texture=Textures.begin();
	while(Texture!=Textures.end())
	{
		if((*Texture)->texture)
		{
			while((*Texture)->texture->Release()){}
			(*Texture)->texture=NULL;
		}
		Texture++;
	}
	Textures.clear();
	return;
}

bool TextureManager::IsValidTexture(int TextureNum)
{
	if (TextureNum>=Textures.size())
		return(false);
	if(!Textures.at(TextureNum))
		return(false);
	return(true);
}

IDirect3DTexture9 *TextureManager::GetTexture(int TextureNum)
{
	if(IsValidTexture(TextureNum))
		return(Textures.at(TextureNum)->texture);
	return(NULL);
}

void TextureManager::ReleaseTexture(IDirect3DTexture9 *texture)
{
	for(int pos=0;pos<StaticTextures.size();pos++)
	{
		if(StaticTextures.at(pos)->texture==texture)
		{
			_MESSAGE("Releasing static texture.");
			if(!StaticTextures.at(pos)->Release())
			{
				_MESSAGE("and removing it from memory.");
				StaticTextures.erase(StaticTextures.begin()+pos);
				break;
			}
		}
	}
	return;
}

 void TextureManager::FreeTexture(int index)
{
	if(index<0||index>=Textures.size()||!Textures[index]->texture)
	{
		_MESSAGE("Tried to free a non existant texture");
		return;
	}
	if(Textures[index]->texture)
	{
		_MESSAGE("Releasing %s",Textures[index]->Filepath);
		HUDManager::GetSingleton()->PurgeTexture(index);
		ShaderManager::GetSingleton()->PurgeTexture(Textures[index]->texture);
		while(Textures[index]->texture->Release()){};
		Textures[index]->texture=NULL;
		Textures[index]->Filepath[0]=0;
	}	
}

void TextureManager::LoadGame(OBSESerializationInterface *Interface)
{
	int maxtex=0;
	int i;
	UInt32	type, version, length;
	int OldTextureNum=-1;
	int TextureNum=-1;
	char TexturePath[260];
	bool TextureFromFile;

	Interface->GetNextRecordInfo(&type, &version, &length);

	if(type=='TIDX')
	{
		Interface->ReadRecordData(&maxtex,length);
		_MESSAGE("Save file links %i textures.",maxtex);
	}
	else
	{
		_MESSAGE("No texture data found in save file.");
		return;
	}

	while(TextureNum<(maxtex-1))
	{
		if((Interface->GetNextRecordInfo(&type,&version, &length))&&(type=='TNUM'))
		{
			OldTextureNum=TextureNum;
			Interface->ReadRecordData(&TextureNum,length);
			_MESSAGE("Found TNUM record = %i.",TextureNum);
			for(i=OldTextureNum;i<TextureNum;i++)
			{
				TextureRecord *tex = new(TextureRecord);
				tex->texture=NULL;
				tex->Filepath[0]=0;
				Textures.push_back(tex);
			}

			if((Interface->GetNextRecordInfo(&type,&version, &length))&&(type=='TPAT'))
			{
				Interface->ReadRecordData(TexturePath,length);
				_MESSAGE("Found TPAT record = %s",TexturePath);
			}
			else
			{
				_MESSAGE("Error loading texture list. type!=TPAT");
				return;
			}

			if((Interface->GetNextRecordInfo(&type, &version, &length)) && (type=='TFFL'))
			{
				Interface->ReadRecordData(&TextureFromFile,length);
				_MESSAGE("Found TFFL record = %i",TextureFromFile);
			}
			else
			{
				_MESSAGE("Error loading texture list. type!=TFFL");
				return;
			}

			if(LoadTexture(TexturePath,TextureFromFile)==-1)
			{
				_MESSAGE("Error loading texture list: texture (%s) no longer exists.",TexturePath);
				TextureRecord *tex = new(TextureRecord);
				tex->texture=NULL;
				tex->Filepath[0]=0;
				Textures.push_back(tex);
			}
		}
		else
		{
			_MESSAGE("Error loading texture list: too small.");
			return;
		}
	}
}	 

 void TextureManager::SaveGame(OBSESerializationInterface *Interface)
 {
	int i;
	int MaxTexture;

	MaxTexture=Textures.size();

	_MESSAGE("Calling TextureManager::SaveGame");

	Interface->WriteRecord('TIDX',TEXTUREVERSION,&MaxTexture,sizeof(MaxTexture));

	for (i=0;i<MaxTexture;i++)
	{
		if(Textures.at(i)->texture)
		{
			Interface->WriteRecord('TNUM',TEXTUREVERSION,&i,sizeof(i));
			Interface->WriteRecord('TPAT',TEXTUREVERSION,Textures.at(i)->Filepath,strlen(Textures.at(i)->Filepath)+1);
			Interface->WriteRecord('TFFL',TEXTUREVERSION,&Textures.at(i)->FromFile,sizeof(Textures.at(i)->FromFile));
		}
	}
 }

 int TextureManager::FindTexture(IDirect3DTexture9* texture)
 {
	for(int pos=0;pos<Textures.size();pos++)
	{
		if(Textures.at(pos)->texture==texture)
		{
			return(pos);
		}
	}
	return(-1);
 }



	