#include "cbase.h"
#include "gunmod_core.h"
#include "tier0/icommandline.h"
#include "filesystem.h"

#include "tier0/memdbgon.h"

ConVar gm_disable_replace("gm_disable_replace", "0", FCVAR_ARCHIVE, "Disable entity replacing from file" );

extern int gEvilImpulse101;

const char *CGMCore::ReplaceEntity( const char *classname )
{	
	if ( CommandLine()->CheckParm( "-noreplace" ) )
		return classname;

	if ( gm_disable_replace.GetBool() )
		return classname;

	if ( gEvilImpulse101 )
		return classname;

	if ( ( !Q_strncmp( gpGlobals->mapname.ToCStr(), "c1", 2 ) == 0 ) || 
	   ( !Q_strncmp( gpGlobals->mapname.ToCStr(), "c2", 2 ) == 0 ) 	 || 
	   ( !Q_strncmp( gpGlobals->mapname.ToCStr(), "c3", 2 ) == 0 )   || 
	   ( !Q_strncmp( gpGlobals->mapname.ToCStr(), "c4", 2 ) == 0 ) )
	{
		KeyValues *kv = new KeyValues( "ReplaceEntity" );
		if ( kv )
		{
			if ( kv->LoadFromFile(g_pFullFileSystem, "addons/menu/replace_entity.txt") )
			{
				for ( KeyValues *control = kv->GetFirstSubKey(); control != NULL; control = control->GetNextKey() )
				{	
					if ( FStrEq( control->GetName(), classname ))
					{	
						printf( "ReplaceEntity: %10s=>%s\n", classname, control->GetString() );
						return control->GetString();
					}
				}
			}
			kv->deleteThis();
		}
	}
	return classname;
}
