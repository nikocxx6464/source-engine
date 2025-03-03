#include "cbase.h"
#include "schemeeditor.h"
#include <vgui/IVGui.h>

#include "tier0/memdbgon.h"


SMEditor::SMEditor( vgui::Panel * panel, const char *panelName ) : BaseClass( panel, panelName )
{
	SetParent( panel );
	vgui::ivgui()->AddTickSignal( GetVPanel(), 250 );
	LoadControlSettings( "resource/ui/smeditor.res" );
}