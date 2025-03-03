#include "cbase.h"
#include <vgui_controls/TextEntry.h>

class SMHelper
{
	DECLARE_CLASS_NOBASE( SMHelper );	
public:	
	void ReloadScheme( vgui::Panel *panel );
	void CheckVar( const char *cvarName );
	void SetVar( vgui::TextEntry *pEntry, const char *cvarName );
	void SetText( vgui::TextEntry *panel, char *value );
};