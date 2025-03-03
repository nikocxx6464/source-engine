//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//
#include "OptionsSubGamepad.h"
//#include "CommandCheckButton.h"
#include "KeyToggleCheckButton.h"
#include "CvarNegateCheckButton.h"
#include "CvarToggleCheckButton.h"
#include "cvarslider.h"

#include "EngineInterface.h"

#include <KeyValues.h>
#include <vgui/IScheme.h>
#include "tier1/convar.h"
#include <stdio.h>
#include <vgui_controls/TextEntry.h>
// memdbgon must be the last include file in a .cpp file!!!
#include <tier0/memdbgon.h>

using namespace vgui;

COptionsSubGamepad::COptionsSubGamepad(vgui::Panel *parent) : PropertyPage(parent, NULL)
{
/*	m_pJoystickCheckBox = new CCvarToggleCheckButton( 
		this, 
		"Joystick", 
		"#GameUI_Joystick", 
		"joystick" );

	m_pJoystickSouthpawCheckBox = new CCvarToggleCheckButton( 
		this, 
		"JoystickSouthpaw", 
		"#GameUI_JoystickSouthpaw", 
		"joy_movement_stick" );

	m_pReverseJoystickCheckBox = new CCvarToggleCheckButton( 
		this, 
		"ReverseJoystick", 
		"#GameUI_ReverseJoystick", 
		"joy_inverty" );

	m_pQuickInfoCheckBox = new CCvarToggleCheckButton(
		this,
		"HudQuickInfo",
		"#GameUI_HudQuickInfo",
		"hud_quickinfo" );

	m_pJoyYawSensitivitySlider = new CCvarSlider( this, "JoystickYawSlider", "#GameUI_JoystickYawSensitivity",
		-0.5f, -7.0f, "joy_yawsensitivity", true );
	m_pJoyYawSensitivityPreLabel = new Label(this, "JoystickYawSensitivityPreLabel", "#GameUI_JoystickLookSpeedYaw" );

	m_pJoyPitchSensitivitySlider = new CCvarSlider( this, "JoystickPitchSlider", "#GameUI_JoystickPitchSensitivity",
		0.5f, 7.0f, "joy_pitchsensitivity", true );
	m_pJoyPitchSensitivityPreLabel = new Label(this, "JoystickPitchSensitivityPreLabel", "#GameUI_JoystickLookSpeedPitch" );*/

	LoadControlSettings("Resource\\OptionsSubGamepad.res");

	UpdateJoystickPanels();
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
COptionsSubGamepad::~COptionsSubGamepad()
{
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void COptionsSubGamepad::OnResetData()
{
	// m_pJoystickCheckBox->Reset();
	// m_pJoystickSouthpawCheckBox->Reset();
	// m_pQuickInfoCheckBox->Reset();
	// m_pReverseJoystickCheckBox->Reset();
	// m_pJoyYawSensitivitySlider->Reset();
	// m_pJoyPitchSensitivitySlider->Reset();
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void COptionsSubGamepad::OnApplyChanges()
{
	// m_pJoystickCheckBox->ApplyChanges();
	// m_pJoystickSouthpawCheckBox->ApplyChanges();
	// m_pQuickInfoCheckBox->ApplyChanges();
	// m_pReverseJoystickCheckBox->ApplyChanges();
	// m_pJoyYawSensitivitySlider->ApplyChanges();
	// m_pJoyPitchSensitivitySlider->ApplyChanges();

	engine->ClientCmd_Unrestricted( "joyadvancedupdate" );
}

//-----------------------------------------------------------------------------
// Purpose: sets background color & border
//-----------------------------------------------------------------------------
void COptionsSubGamepad::ApplySchemeSettings(IScheme *pScheme)
{
	BaseClass::ApplySchemeSettings(pScheme);
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void COptionsSubGamepad::OnControlModified(Panel *panel)
{
	PostActionSignal(new KeyValues("ApplyButtonEnable"));

	if (panel == m_pJoystickCheckBox)
	{
		UpdateJoystickPanels();
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void COptionsSubGamepad::OnTextChanged(Panel *panel)
{
}


//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void COptionsSubGamepad::UpdateJoystickPanels()
{
	// bool bEnabled = m_pJoystickCheckBox->IsSelected();

/*	m_pReverseJoystickCheckBox->SetEnabled( bEnabled );
	m_pJoystickSouthpawCheckBox->SetEnabled( bEnabled );
	m_pJoyYawSensitivitySlider->SetEnabled( bEnabled );
	m_pJoyYawSensitivityPreLabel->SetEnabled( bEnabled );
	m_pJoyPitchSensitivitySlider->SetEnabled( bEnabled );
	m_pJoyPitchSensitivityPreLabel->SetEnabled( bEnabled );*/
}