#include "ScreenElements.h"
#include "TextureManager.h"
#include "Rendering.h"

void	ScreenElement::SetPosition(float x,float y, float z)
{
	pos.x=x;
	pos.y=y;
	pos.z=z;
}

void	ScreenElement::SetRotation(float rotation)
{
	rot=rotation;
	UpdateTransform();
}

void	ScreenElement::SetScale(float x, float y)
{
	scale.x=x;
	scale.y=y;
	UpdateTransform();
}

void	ScreenElement::UpdateTransform(void)
{
	D3DXMATRIX TempScale, TempRot;
	D3DXMatrixScaling(&TempScale, scale.x, scale.y, 1);
	D3DXMatrixRotationZ(&TempRot, rot);
	transform=TempScale*TempRot;
}

void	ScreenElement::SetColor(float red, float green, float blue)
{
	if(red<0||red>1||green<0||green>1||blue<0||blue>1) {
		_MESSAGE("Tried to set a hud element to an invalid colour");
		return;
	}
	float alpha=((D3DXCOLOR)color).a;
	color=(DWORD)D3DXCOLOR(red,green,blue,alpha);
}

void	ScreenElement::SetAlpha(float alpha)
{
	if (alpha<0||alpha>1)
	{
		_MESSAGE("Tried to set a hud element to an invalid colour");
		return;
	}

	float red=((D3DXCOLOR)color).r;
	float green=((D3DXCOLOR)color).g;
	float blue=((D3DXCOLOR)color).b;
	color=(DWORD)D3DXCOLOR(red,green,blue,alpha);
}

bool	Sprite::SetTexture(int texture)
{
	tex=texture;
	return(true);
}

int		Sprite::GetTexture()
{
	return(tex);
}

void	Sprite::Render(ID3DXSprite *sprite)
{
	TextureManager	*TexMan=TextureManager::GetSingleton();

	if (enabled&&TexMan->IsValidTexture(tex))
	{
		sprite->SetTransform(&transform);
		sprite->Draw(TexMan->GetTexture(tex),0,0,&pos,color);
	}
}

HUDManager::HUDManager()
{
	NextElementIndex=0;
	sprite=NULL;
	Singleton=this;
	
}

HUDManager	*HUDManager::Singleton=NULL;

HUDManager	*HUDManager::GetSingleton()
{
	if (Singleton)
		return(Singleton);
	else
		return(new(HUDManager));
}

int		HUDManager::AddScreenElement(Sprite *data)
{
	ScreenElementList.push_back(data);
	NextElementIndex++;
	return(NextElementIndex);
}

Sprite	*HUDManager::index(int ind)
{
	return(ScreenElementList[ind]);
}

void	HUDManager::PurgeTexture(int TextureIndex)
{
	for(int i=0; i<ScreenElementList.size()-1; i++)
	{
		if(ScreenElementList[i]->GetTexture()==TextureIndex)
		{
			ScreenElementList[i]->SetTexture(-1);
			//ScreenElementList[i]->enabled=false;
		}
	}
}

void	HUDManager::Render()
{
	HRESULT hr;
	IDirect3DDevice9 *Device;

	Device = GetD3DDevice();

	if (!Device)
	{
		_MESSAGE("No valid D3D Device.");
		return;
	}

	if(!sprite)
	{
		hr=D3DXCreateSprite(Device,&sprite);
		if (FAILED(hr)||!sprite)
		{
			_MESSAGE("Create sprite failed.");
			return;
		}
	}

	sprite->Begin(0);
	
	for(::std::vector<Sprite*>::iterator i=ScreenElementList.begin(); i!=ScreenElementList.end(); i++)
	{
		(*i)->Render(sprite);
	}

	sprite->End();
	return;
}

void HUDManager::DeviceLost()
{
	if(sprite)
	{
		sprite->OnLostDevice();
	}
}

void HUDManager::DeviceReset()
{
	if(sprite)
	{
		sprite->OnResetDevice();
	}
}

