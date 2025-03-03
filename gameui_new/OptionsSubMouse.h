//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef OPTIONS_SUB_MOUSE_H
#define OPTIONS_SUB_MOUSE_H
#ifdef _WIN32
#pragma once
#endif

#include <vgui_controls/PropertyPage.h>

class CCvarNegateCheckButton;
class CKeyToggleCheckButton;
class CCvarToggleCheckButton;
class CCvarSlider;

namespace vgui
{
    class Label;
    class Panel;
}

//-----------------------------------------------------------------------------
// Purpose: Mouse Details, Part of OptionsDialog
//-----------------------------------------------------------------------------
class COptionsSubMouse : public vgui::PropertyPage
{
	DECLARE_CLASS_SIMPLE( COptionsSubMouse, vgui::PropertyPage );

public:
	COptionsSubMouse(vgui::Panel *parent);
	~COptionsSubMouse();

	virtual void OnResetData();
	virtual void OnApplyChanges();

protected:
    virtual void ApplySchemeSettings(vgui::IScheme *pScheme);

	MESSAGE_FUNC_PTR( OnControlModified, "ControlModified", panel );
	MESSAGE_FUNC_PTR( OnTextChanged, "TextChanged", panel );
	MESSAGE_FUNC_PTR( OnCheckButtonChecked, "CheckButtonChecked", panel )
	{
		OnControlModified( panel );
	}

	void UpdateSensitivityLabel();
	void UpdateAccelerationLabel();

private:
	CCvarNegateCheckButton		*m_pReverseMouseCheckBox;
	CCvarToggleCheckButton		*m_pMouseFilterCheckBox;
	CCvarToggleCheckButton		*m_pMouseRawCheckBox;
	vgui::CheckButton			*m_pMouseAccelerationCheckBox;

	CCvarToggleCheckButton		*m_pQuickInfoCheckBox;

	CCvarSlider					*m_pMouseSensitivitySlider;
    vgui::TextEntry             *m_pMouseSensitivityLabel;

    vgui::Label 				*m_pMouseAutoAimLabel;
    vgui::ComboBox 				*m_pMouseAutoAim;

    CCvarSlider					*m_pMouseAutoAimSensitivity;
    vgui::Label 				*m_pMouseAutoAimSensitivityLabel;

	CCvarSlider					*m_pMouseAccelExponentSlider;
	vgui::TextEntry             *m_pMouseAccelExponentLabel;
};



#endif // OPTIONS_SUB_MOUSE_H