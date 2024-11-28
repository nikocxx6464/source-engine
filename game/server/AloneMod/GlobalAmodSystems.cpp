//a shitty little system for the skybox changer
#include "cbase.h"
#include "cdll_int.h"
#include "fmtstr.h"
#include <filesystem.h>
#include "AloneMod/Amod_SharedDefs.h"

extern IVEngineClient* clientengine;

void AmodSkyCallback(IConVar* var, const char*, float);

ConVar amod_sky_override("amod_sky_override", "1");
ConVar amod_sky("amod_sky", "sky_borealis01", 0, "", AmodSkyCallback);

//im not even kidding i tinkered around with this for like an hour to get it to work
void AmodSkyCallback(IConVar* var, const char*, float)
{
	if (!amod_sky_override.GetBool())
		return;

	static ConVar* day = cvar->FindVar("amod_day");
	if (!day)
		return;

	if (day->GetBool() && Q_strcmp(amod_sky.GetString(), "sky_day02_09") && IsCityMap(gpGlobals->mapname.ToCStr()))
		return;

	if (gpGlobals->eLoadType == MapLoad_Background)
		clientengine->ExecuteClientCmd(CFmtStr("map_background %s", gpGlobals->mapname.ToCStr()));
	else
		clientengine->ExecuteClientCmd("save quick001_sky; load quick001_sky");
}

KeyValues* KvSkyes = nullptr;

void DefaultFogOverride()
{
	clientengine->ClientCmd_Unrestricted("fog_override 1");

	clientengine->ClientCmd_Unrestricted("fog_enable 1");
	clientengine->ClientCmd_Unrestricted("fog_enableskybox 1");
	
	clientengine->ClientCmd_Unrestricted("fog_start 1500");
	clientengine->ClientCmd_Unrestricted("fog_end 2750");

	clientengine->ClientCmd_Unrestricted("fog_startskybox 1500");
	clientengine->ClientCmd_Unrestricted("fog_endskybox 3000");

	clientengine->ClientCmd_Unrestricted("fog_maxdensity 0.95");
	clientengine->ClientCmd_Unrestricted("fog_maxdensityskybox 0.8");

	clientengine->ClientCmd_Unrestricted("fog_color 55 55 70");
	clientengine->ClientCmd_Unrestricted("fog_colorskybox 55 55 70");

	clientengine->ClientCmd_Unrestricted("r_farz -1");
	clientengine->ClientCmd_Unrestricted("r_pixelfog 1");
}

void DoFogOverride(KeyValues* kv, const char* str = nullptr)
{
	KeyValues* mapkv = kv->FindKey(str ? str : gpGlobals->mapname.ToCStr());
	if (!mapkv)
	{
		DefaultFogOverride();
		return;
	}

	clientengine->ClientCmd_Unrestricted(CFmtStr("fog_override %d", mapkv->GetBool("fog_override", true)));

	clientengine->ClientCmd_Unrestricted(CFmtStr("fog_enable %d", mapkv->GetBool("fog_enable", true)));
	clientengine->ClientCmd_Unrestricted(CFmtStr("fog_enableskybox %d", mapkv->GetBool("fog_enableskybox", true)));

	clientengine->ClientCmd_Unrestricted(CFmtStr("fog_start %d", mapkv->GetInt("fog_start", 1500)));
	clientengine->ClientCmd_Unrestricted(CFmtStr("fog_end %d", mapkv->GetInt("fog_end", 2750)));

	clientengine->ClientCmd_Unrestricted(CFmtStr("fog_startskybox %d", mapkv->GetInt("fog_startskybox", true)));
	clientengine->ClientCmd_Unrestricted(CFmtStr("fog_endskybox %d", mapkv->GetInt("fog_endskybox", true)));

	clientengine->ClientCmd_Unrestricted(CFmtStr("fog_maxdensity %f", mapkv->GetFloat("fog_maxdensity", 0.95)));
	clientengine->ClientCmd_Unrestricted(CFmtStr("fog_maxdensityskybox %f", mapkv->GetFloat("fog_maxdensityskybox", 0.7)));

	clientengine->ClientCmd_Unrestricted(CFmtStr("fog_color %s", mapkv->GetString("fog_color", "55 55 70")));
	clientengine->ClientCmd_Unrestricted(CFmtStr("fog_colorskybox %s", mapkv->GetString("fog_colorskybox", "55 55 70")));

	clientengine->ClientCmd_Unrestricted(CFmtStr("r_farz %s", mapkv->GetString("r_farz", "-1")));
	clientengine->ClientCmd_Unrestricted(CFmtStr("r_pixelfog %d", mapkv->GetBool("r_pixelfog", true)));
}

CON_COMMAND(amod_fog_reset, "")
{
	ConVar* day = cvar->FindVar("amod_day");
	if (!day)
		return;

	if (!day->GetBool())
		return;

	if (KvSkyes)
		KvSkyes->deleteThis();

	KvSkyes = nullptr;

	KvSkyes = new KeyValues("");
	if (!KvSkyes->LoadFromFile(filesystem, "resource\\amod_city_fogs.txt", "MOD"))
	{
		ConWarning("Failed To Load amod_city_fog.txt Day Time Section Use Default Fog\n");
		KvSkyes->deleteThis();
		KvSkyes = nullptr;

		DefaultFogOverride();

		return;
	}
	else
	{

		if (day->GetBool())
		{
			if (IsCityMap(gpGlobals->mapname.ToCStr()))
			{
				DoFogOverride(KvSkyes);
			}
		}
	}
}

static bool bDidFilterOn = false;

//TODO: MAKE ALGORITHM SO I CAN USE MORE SKYBOXES
class CAmodAutoGameSystem : public CAutoGameSystem
{
public:
	void LevelInitPreEntity()
	{
		if (!KvSkyes)
		{
			KvSkyes = new KeyValues("");
			if (!KvSkyes->LoadFromFile(filesystem, "resource\\amod_city_fogs.txt", "MOD"))
			{
				ConWarning("Failed To Load amod_city_fog.txt Day Time Section Use Default Fog\n");
				KvSkyes->deleteThis();
				KvSkyes = nullptr;
			}
		}

		clientengine->ClientCmd_Unrestricted("r_pixelfog 1");

		if (!amod_sky_override.GetBool())
			return;

		static ConVar* sname = cvar->FindVar("sv_skyname");
		if (!sname)
			return;

		static ConVar* day = cvar->FindVar("amod_day");
		if (!day)
			return;

		static ConVar* fog_override = cvar->FindVar("fog_override");
		if (!fog_override)
			return;

		if (day->GetBool())
		{
			if (IsCityMap(gpGlobals->mapname.ToCStr()))
			{
				if (!bDidFilterOn)
				{
					clientengine->ClientCmd_Unrestricted("tf2");
					clientengine->ClientCmd_Unrestricted("alias Amod_ToggleFilter");
				}
				bDidFilterOn = true;

				sname->SetValue("sky_day02_09");

				if (KvSkyes)
					DoFogOverride(KvSkyes);
				else
					DefaultFogOverride();

				return;
			}
			else
			{
				if (bDidFilterOn)
				{
					clientengine->ClientCmd_Unrestricted("alias Amod_ToggleFilter tf2; tf1");
					bDidFilterOn = false;
				}

				fog_override->SetValue(false);

				if ((!Q_strcmp(sname->GetString(), "sky_day02_09") && Q_strcmp(amod_sky.GetString(), "sky_day02_09")) || (Q_strcmp(sname->GetString(), "sky_day02_09") && Q_strcmp(amod_sky.GetString(), "sky_day02_09")))
					sname->SetValue(amod_sky.GetString());
				else
					sname->SetValue("sky_borealis01");
			}
		}
		else
		{
			if (bDidFilterOn)
			{
				clientengine->ClientCmd_Unrestricted("alias Amod_ToggleFilter tf2; tf1");
				bDidFilterOn = false;
			}

			fog_override->SetValue(false);

			if ((!Q_strcmp(sname->GetString(), "sky_day02_09") && Q_strcmp(amod_sky.GetString(), "sky_day02_09")) || (Q_strcmp(sname->GetString(), "sky_day02_09") && Q_strcmp(amod_sky.GetString(), "sky_day02_09")))
				sname->SetValue(amod_sky.GetString());
			else
				sname->SetValue("sky_borealis01");
		}
	}

	void LevelInitPostEntity()
	{
		if (gpGlobals->eLoadType == MapLoad_Transition)
			clientengine->ClientCmd_Unrestricted("amod_songpanel_changelevel");
		else
			clientengine->ClientCmd_Unrestricted("amod_songpanel_newlevel");

		//i made these so the self esteem fund song from the start will go througth the 1st and 2nd map (continue playing)
		static ConCommand* cmd_stop = cvar->FindCommand("Amod_SefStop");
		static ConCommand* cmd_start = cvar->FindCommand("Amod_SefStart");
		static ConCommand* cmd_start01 = cvar->FindCommand("Amod_SefStart_01");
		if (gpGlobals->eLoadType != MapLoad_NewGame && !Q_strcmp(gpGlobals->mapname.ToCStr(), "d1_trainstation_01_d"))
		{
			if (cmd_stop)
				cmd_stop->Dispatch(CCommand{});
			else
				clientengine->ClientCmd_Unrestricted("Amod_SefStop");
		}
		else if (gpGlobals->eLoadType == MapLoad_NewGame && !Q_strcmp(gpGlobals->mapname.ToCStr(), "d1_trainstation_01_d"))
		{
			if (cmd_start01)
				cmd_start01->Dispatch(CCommand{});
			else
				clientengine->ClientCmd_Unrestricted("Amod_SefStart_01");
		}
		else if (gpGlobals->eLoadType == MapLoad_Transition && !Q_strcmp(gpGlobals->mapname.ToCStr(), "d1_trainstation_02_d"))
		{
			if (cmd_start)
				cmd_start->Dispatch(CCommand{});
			else
				clientengine->ClientCmd_Unrestricted("Amod_SefStart");
		}
	}
};
CAmodAutoGameSystem g_AmodAGS;

//simple entity for background06_d
class CAmodFogSetter : public CBaseEntity
{
public:
	DECLARE_CLASS(CAmodFogSetter, CBaseEntity);
	DECLARE_DATADESC();

	void InputSetFog(inputdata_t& input);
	void OnRestore();
private:
	string_t m_szFogName;
};

LINK_ENTITY_TO_CLASS(amod_fog_setter, CAmodFogSetter);

BEGIN_DATADESC(CAmodFogSetter)
DEFINE_KEYFIELD(m_szFogName, FIELD_STRING, "fogname"),
DEFINE_INPUTFUNC(FIELD_STRING, "SetFog", InputSetFog)
END_DATADESC()

void CAmodFogSetter::InputSetFog(inputdata_t& input)
{
	static ConVarRef amod_day("amod_day");
	if (!amod_day.GetBool())
		return;

	m_szFogName = AllocPooledString(input.value.String());
	DoFogOverride(KvSkyes, m_szFogName.ToCStr());
}

void CAmodFogSetter::OnRestore()
{
	static ConVarRef amod_day("amod_day");
	if (!amod_day.GetBool())
		return;

	DoFogOverride(KvSkyes, m_szFogName.ToCStr());
	BaseClass::OnRestore();
}