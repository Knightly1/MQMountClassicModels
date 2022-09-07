#include <mq/Plugin.h>

PreSetup("MQMountClassicModels");
PLUGIN_VERSION(0.1);

#ifdef ROF2EMU
#define RaceCannotMount_x 0x58DDE0
#endif

#ifdef RaceCannotMount_x
INITIALIZE_EQGAME_OFFSET(RaceCannotMount);
#endif


class RaceCannotMountHook
{
public:
	DETOUR_TRAMPOLINE_DEF(bool, RaceCannotMount_Trampoline, ())
	bool RaceCannotMount_Detour()
	{
		switch(pLocalPlayer->GetRace())
		{
		case EQR_HUMAN:
		case EQR_BARBARIAN:
		case EQR_ERUDITE:
		case EQR_ELF:
		case EQR_HIGH_ELF:
		case EQR_DARK_ELF:
		case EQR_HALF_ELF:
		case EQR_DWARF:
		case EQR_TROLL:
		case EQR_OGRE:
		case EQR_HALFLING:
		case EQR_GNOME:
		case EQR_IKSAR:
		case EQR_VAHSHIR:
			return false;
		default:
			return RaceCannotMount_Trampoline();
		}
	}
};

PLUGIN_API void InitializePlugin()
{
	DebugSpewAlways("MQMountClassicModels::Initializing version %f", MQ2Version);
#ifdef RaceCannotMount_x
	EzDetour(RaceCannotMount, &RaceCannotMountHook::RaceCannotMount_Detour, &RaceCannotMountHook::RaceCannotMount_Trampoline);
#else
	DebugSpewAlways("MQMountClassicModels::Not enabled for this client");
#endif
}

PLUGIN_API void ShutdownPlugin()
{
	DebugSpewAlways("MQMountClassicModels::Shutting down");
#ifdef RaceCannotMount_x
	RemoveDetour(RaceCannotMount);
#endif
}