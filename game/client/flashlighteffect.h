//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
// Other: Heavily edited by Team Gear for City17: Episode 1.
//
//=============================================================================//

#ifndef FLASHLIGHTEFFECT_H
#define FLASHLIGHTEFFECT_H
#ifdef _WIN32
#pragma once
#endif

struct dlight_t;

class CFlashlightEffect
{
public:

	CFlashlightEffect(int nEntIndex = 0);
	~CFlashlightEffect();

	virtual void UpdateLight(const Vector &vecPos, const Vector &vecDir, const Vector &vecRight, const Vector &vecUp, int nDistance, bool bMuzzleFlash);
	void TurnOn();
	void TurnOff();
	//Allow anyone to execute this.
	//void RefreshFlashlight( void );
	bool IsOn( void ) { return m_bIsOn;	}

	ClientShadowHandle_t GetFlashlightHandle( void ) { return m_FlashlightHandle; }
	void SetFlashlightHandle( ClientShadowHandle_t Handle ) { m_FlashlightHandle = Handle;	}
	
protected:

	void LightOff();
	void LightOffOld();
	void LightOffNew();

	void UpdateLightNew(const Vector &vecPos, const Vector &vecDir, const Vector &vecRight, const Vector &vecUp, bool bMuzzleFlash);
	void UpdateLightOld(const Vector &vecPos, const Vector &vecDir, int nDistance);

	bool m_bIsOn;
	bool m_bUseShadows;
	int m_nEntIndex;

	ClientShadowHandle_t m_FlashlightHandle;

	// Vehicle headlight dynamic light pointer
	dlight_t *m_pPointLight;
	float m_flDistMod;

	// Texture for flashlight
	CTextureReference m_FlashlightTexture;
	CTextureReference m_MuzzlelightTexture;
	CTextureReference m_ARMuzzlelightTexture;
	CTextureReference m_ShotgunMuzzlelightTexture;
	CTextureReference m_PistolMuzzlelightTexture;
	CTextureReference m_SilenserMuzzlelightTexture;
};

class CHeadlightEffect : public CFlashlightEffect
{
public:
	
	CHeadlightEffect();
	~CHeadlightEffect();

	virtual void UpdateLight(const Vector &vecPos, const Vector &vecDir, const Vector &vecRight, const Vector &vecUp, int nDistance);
};



#endif // FLASHLIGHTEFFECT_H
