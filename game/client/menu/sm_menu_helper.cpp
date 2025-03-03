#include "cbase.h"
#include "sm_menu_helper.h"

#include "tier0/memdbgon.h"

ConVar sm_menu_theme( "sm_menu_theme", "0", FCVAR_ARCHIVE, "SMenu theme" );

void SMHelper::ReloadScheme( vgui::Panel *panel )
{
	vgui::Panel *parent = panel->GetParent()->GetParent();
	const char *theme = sm_menu_theme.GetBool() ? "resource/SourceScheme_Dark.res" : "resource/SourceScheme.res";
	parent->SetScheme(vgui::scheme()->LoadSchemeFromFile(theme, "SourceScheme"));
	parent->InvalidateLayout(true, true);
}

void SMHelper::CheckVar( const char *cvarName )
{
	ConVarRef convar(cvarName);
	convar.SetValue(!convar.GetBool());
}

void SMHelper::SetVar( vgui::TextEntry *pEntry, const char *cvarName )
{
	char buf[64];
	ConVarRef convar( cvarName );
	pEntry->GetText( buf, 64 );
	convar.SetValue( buf );
}

void SMHelper::SetText( vgui::TextEntry *panel, char *value )
{
	char buf[64];
  	Q_snprintf(buf, sizeof( buf ), "%s", value );
	panel->SetText(buf);
}