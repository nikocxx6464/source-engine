//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//
#include "OptionsSubMouse.h"
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
#include <vgui_controls/ComboBox.h>
// memdbgon must be the last include file in a .cpp file!!!
#include <tier0/memdbgon.h>

using namespace vgui;

COptionsSubMouse::COptionsSubMouse(vgui::Panel *parent) : PropertyPage(parent, NULL)
{
	m_pReverseMouseCheckBox = new CCvarNegateCheckButton( 
		this, 
		"ReverseMouse", 
		"#GameUI_ReverseMouse", 
		"m_pitch" );
	
	m_pMouseFilterCheckBox = new CCvarToggleCheckButton( 
		this, 
		"MouseFilter", 
		"#GameUI_MouseFilter", 
		"m_filter" );

	m_pMouseRawCheckBox = new CCvarToggleCheckButton( 
		this, 
		"MouseRaw", 
		"#GameUI_MouseRaw", 
		"m_rawinput" );

	m_pMouseAccelerationCheckBox = new CheckButton( 
		this, 
		"MouseAccelerationCheckbox", 
		"#GameUI_MouseCustomAccel" );

	m_pQuickInfoCheckBox = new CCvarToggleCheckButton(
		this,
		"HudQuickInfo",
		"#GameUI_HudQuickInfo",
		"hud_quickinfo" );

	m_pMouseAutoAimLabel = new Label( this, "AutoaimLabel", "#GameUI_AimAssist" );
	m_pMouseAutoAimLabel->AddActionSignalTarget(this);
	
	m_pMouseAutoAim = new ComboBox( this, "Autoaim", 3, false );
	
	m_pMouseAutoAim->AddItem( "#GameUI_SettingOff", NULL );
	m_pMouseAutoAim->AddItem( "#GameUI_SettingBasic", NULL );
	m_pMouseAutoAim->AddItem( "#GameUI_SettingEnhanced", NULL );


	m_pMouseAutoAimSensitivityLabel = new Label( this, "AutoaimScaleLabel", "#GameUI_AimAssistScale" );
	m_pMouseAutoAimSensitivity = new CCvarSlider(this, "AutoaimScale", "#GameUI_AimAssistScale",
		0.1f, 2.0f, "m_autoaim_scale", true );

	m_pMouseSensitivitySlider = new CCvarSlider( this, "Slider", "#GameUI_MouseSensitivity",
		0.1f, 6.0f, "sensitivity", true );

    m_pMouseSensitivityLabel = new TextEntry(this, "SensitivityLabel");
    m_pMouseSensitivityLabel->AddActionSignalTarget(this);

	m_pMouseAccelExponentSlider = new CCvarSlider( this, "MouseAccelerationSlider", "#GameUI_MouseAcceleration",
		1.0f, 1.4f, "m_customaccel_exponent", true );

	m_pMouseAccelExponentLabel = new TextEntry(this, "MouseAccelerationLabel");
	m_pMouseAccelExponentLabel->AddActionSignalTarget(this);

	LoadControlSettings("Resource\\OptionsSubMouse.res");

	m_pMouseAutoAim->SetEnabled( false );

	UpdateSensitivityLabel();
	UpdateAccelerationLabel();
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
COptionsSubMouse::~COptionsSubMouse()
{
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void COptionsSubMouse::OnResetData()
{
	m_pReverseMouseCheckBox->Reset();
	m_pMouseFilterCheckBox->Reset();
	m_pMouseRawCheckBox->Reset();
	m_pMouseSensitivitySlider->Reset();
	m_pMouseAccelExponentSlider->Reset();
	m_pQuickInfoCheckBox->Reset();
	m_pMouseAutoAimSensitivity->Reset();

	ConVarRef m_autoaim_mode("m_autoaim_mode");
	
	m_pMouseAutoAim->ActivateItem( m_autoaim_mode.GetInt() );

	ConVarRef m_customacel("m_customaccel");
	if ( m_customacel.IsValid() )
		m_pMouseAccelerationCheckBox->SetSelected( m_customacel.GetBool() );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void COptionsSubMouse::OnApplyChanges()
{
	m_pReverseMouseCheckBox->ApplyChanges();
	m_pMouseFilterCheckBox->ApplyChanges();
	m_pMouseRawCheckBox->ApplyChanges();
	m_pMouseSensitivitySlider->ApplyChanges();
	m_pMouseAccelExponentSlider->ApplyChanges();
	m_pQuickInfoCheckBox->ApplyChanges();
	m_pMouseAutoAimSensitivity->ApplyChanges();

	ConVarRef m_autoaim_mode("m_autoaim_mode");

	m_autoaim_mode.SetValue( m_pMouseAutoAim->GetActiveItem() );

	ConVarRef m_customacel("m_customaccel");
	if ( m_customacel.IsValid() )
		m_customacel.SetValue(m_pMouseAccelerationCheckBox->IsSelected() ? 3 : 0);
}

//-----------------------------------------------------------------------------
// Purpose: sets background color & border
//-----------------------------------------------------------------------------
void COptionsSubMouse::ApplySchemeSettings(IScheme *pScheme)
{
	BaseClass::ApplySchemeSettings(pScheme);
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void COptionsSubMouse::OnControlModified(Panel *panel)
{
	PostActionSignal(new KeyValues("ApplyButtonEnable"));

    // the HasBeenModified() check is so that if the value is outside of the range of the
    // slider, it won't use the slider to determine the display value but leave the
    // real value that we determined in the constructor
    if (panel == m_pMouseSensitivitySlider && m_pMouseSensitivitySlider->HasBeenModified())
    {
        UpdateSensitivityLabel();
    }
	else if (panel == m_pMouseAccelExponentSlider && m_pMouseAccelExponentSlider->HasBeenModified())
	{
		UpdateAccelerationLabel();
	}
	else if (panel == m_pMouseAccelerationCheckBox)
	{
		m_pMouseAccelExponentSlider->SetEnabled(m_pMouseAccelerationCheckBox->IsSelected());
		m_pMouseAccelExponentLabel->SetEnabled(m_pMouseAccelerationCheckBox->IsSelected());
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void COptionsSubMouse::OnTextChanged(Panel *panel)
{
    if ( panel == m_pMouseSensitivityLabel )
    {
        char buf[64];
        m_pMouseSensitivityLabel->GetText(buf, 64);

        float fValue;
		int numParsed = sscanf(buf, "%f", &fValue);
		if ( ( numParsed == 1 ) && ( fValue >= 0.0f ) )
        {
            m_pMouseSensitivitySlider->SetSliderValue(fValue);
            PostActionSignal(new KeyValues("ApplyButtonEnable"));
        }
		return;
    }

	if ( panel == m_pMouseAccelExponentLabel )
	{
		char buf[64];
		m_pMouseAccelExponentLabel->GetText(buf, 64);

		float fValue = (float) atof(buf);
		if (fValue >= 1.0)
		{
			m_pMouseAccelExponentSlider->SetSliderValue(fValue);
			PostActionSignal(new KeyValues("ApplyButtonEnable"));
		}
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void COptionsSubMouse::UpdateSensitivityLabel()
{
    char buf[64];
    Q_snprintf(buf, sizeof( buf ), " %.2f", m_pMouseSensitivitySlider->GetSliderValue());
    m_pMouseSensitivityLabel->SetText(buf);
}


void COptionsSubMouse::UpdateAccelerationLabel()
{
	char buf[64];
	Q_snprintf(buf, sizeof( buf ), " %.2f", m_pMouseAccelExponentSlider->GetSliderValue());
	m_pMouseAccelExponentLabel->SetText(buf);
}