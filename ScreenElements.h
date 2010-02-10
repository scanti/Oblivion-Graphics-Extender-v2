#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

class ScreenElement
{
public:
	bool		enabled;
	D3DXVECTOR3	pos;
	D3DXVECTOR2	scale;
	float		rot;
	D3DXMATRIX	transform;
	DWORD		color;

	void			SetPosition(float x, float y, float z);
	void			SetScale(float x, float y);
	void			SetRotation(float rotation);
	void			UpdateTransform(void);
	void			SetColor(float red, float green, float blue);
	void			SetAlpha(float alpha);
	virtual void	Render(ID3DXSprite *sprite)=0;
};

class Sprite : public ScreenElement
{
public:
	int tex;

	bool			SetTexture(int texture);
	int				GetTexture(void);
	virtual void	Render(ID3DXSprite *sprite);
};

/*
class AnimatedSprite : public Sprite
{
public:

	float	fps;
	float	time;
	int		CurrentFrame;
	int		Width;
	int		Height;

	void	SetFramesPerSecond(float speed);
	void	SetCurrentFrame(int index);
	void	SetFilmStripDimensions(int width,int height);
	void	Render(ID3DXSprite *sprite);
};
*/

class HUDManager
{
public:
	static	HUDManager*				Singleton;
	::std::vector<Sprite*>			ScreenElementList;
	int								NextElementIndex;
	LPD3DXSPRITE					sprite;

private:
	HUDManager();									// Declare as private. Use GetSingleton to initialise HUDManager.
													// This is so we can't init multiple HUD managers.
public:
	static HUDManager	*GetSingleton(void);
	int					AddScreenElement(Sprite *data);
	Sprite				*index(int ind);
	void				PurgeTexture(int TextureIndex);
	void				Render(void);
	void				DeviceLost(void);
	void				DeviceReset(void);
	void				NewGame(void);
	void				LoadGame(void);
	void				SaveGame(void);
};