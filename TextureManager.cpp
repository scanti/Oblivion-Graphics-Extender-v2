#include "TextureManager.h"

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
}

TextureManager::~TextureManager()
{
	if(thisframeSurf)
		while(thisframeSurf->Release()){};
	if(lastframeSurf)
		while(lastframeSurf->Release()){};
	if(lastpassSurf)
		while(lastpassSurf->Release()){};
	if(thisframeTex)
		while(thisframeTex->Release()){};
	if(lastframeTex)
		while(lastframeTex->Release()){};
	if(lastpassTex)
		while(lastpassTex->Release()){};
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
	_MESSAGE("Creating screen texture.");
	_MESSAGE("Width = %i, Height = %i",v1_2_416::GetRenderer()->SizeWidth,v1_2_416::GetRenderer()->SizeHeight);
	GetD3DDevice()->CreateTexture(v1_2_416::GetRenderer()->SizeWidth,v1_2_416::GetRenderer()->SizeHeight,1,D3DUSAGE_RENDERTARGET,D3DFMT_X8R8G8B8,D3DPOOL_DEFAULT,&thisframeTex,0);
	GetD3DDevice()->CreateTexture(v1_2_416::GetRenderer()->SizeWidth,v1_2_416::GetRenderer()->SizeHeight,1,D3DUSAGE_RENDERTARGET,D3DFMT_X8R8G8B8,D3DPOOL_DEFAULT,&lastpassTex,0);
	GetD3DDevice()->CreateTexture(v1_2_416::GetRenderer()->SizeWidth,v1_2_416::GetRenderer()->SizeHeight,1,D3DUSAGE_RENDERTARGET,D3DFMT_X8R8G8B8,D3DPOOL_DEFAULT,&lastframeTex,0);
	
	//GetD3DDevice()->CreateTexture(v1_2_416::GetRenderer()->SizeWidth,v1_2_416::GetRenderer()->SizeHeight,1,D3DUSAGE_RENDERTARGET,D3DFMT_A16B16G16R16F,D3DPOOL_DEFAULT,&thisframeTex,0);
	//GetD3DDevice()->CreateTexture(v1_2_416::GetRenderer()->SizeWidth,v1_2_416::GetRenderer()->SizeHeight,1,D3DUSAGE_RENDERTARGET,D3DFMT_A16B16G16R16F,D3DPOOL_DEFAULT,&lastpassTex,0);
	//GetD3DDevice()->CreateTexture(v1_2_416::GetRenderer()->SizeWidth,v1_2_416::GetRenderer()->SizeHeight,1,D3DUSAGE_RENDERTARGET,D3DFMT_A16B16G16R16F,D3DPOOL_DEFAULT,&lastframeTex,0);
	

	_MESSAGE("Setting screen surface.");
	thisframeTex->GetSurfaceLevel(0,&thisframeSurf);
	lastpassTex->GetSurfaceLevel(0,&lastpassSurf);
	lastframeTex->GetSurfaceLevel(0,&lastframeSurf);

	_MESSAGE("Setting depth texture.");
	depth=GetDepthBufferTexture();
}

void	TextureManager::DeviceRelease()
{
	if(thisframeSurf)
	{
		_MESSAGE("Releasing thisframe surface.");
		while(thisframeSurf->Release()){}
		thisframeSurf=NULL;
	}

	if(lastpassSurf)
	{
		_MESSAGE("Releasing lastpass surface.");
		while(lastpassSurf->Release()){}
		lastpassSurf=NULL;
	}

	if(lastframeSurf)
	{
		_MESSAGE("Releasing lastframe surface.");
		while(lastframeSurf->Release()){}
		lastframeSurf=NULL;
	}

	if (thisframeTex)
	{
		_MESSAGE("Releasing thisframe texture.");
		while(thisframeTex->Release()){}
		thisframeTex=NULL;
	}

	if (lastpassTex)
	{
		_MESSAGE("Releasing lastpass texture.");
		while(lastpassTex->Release()){}
		lastpassTex=NULL;
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
			Textures[i]->FromFile=FromFile;
			return i;
		}
	}
	TextureRecord	*TextureElement=new(TextureRecord);
	TextureElement->texture=tex;
	strcpy_s(TextureElement->Filepath,256,NewPath);
	TextureElement->FromFile=FromFile;
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
		//HUDManager::GetSingleton()->PurgeTexture(index);
		ShaderManager::GetSingleton()->PurgeTexture(Textures[index]->texture);
		while(Textures[index]->texture->Release()){};
		Textures[index]->texture=NULL;
		Textures[index]->Filepath[0]=0;
	}
	
}



	