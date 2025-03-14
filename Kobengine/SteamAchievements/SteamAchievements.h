#pragma once
#include <steam_api.h>

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~	  Achievement Data	
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define _ACH_ID( id, idName, name ) { id, idName, name, "", false, 0 }
struct Achievement_t
{
	int achievementID;
	const char* achievementIDName;
	char name[128];
	char description[256];
	bool achieved;
	int iconImage;
};


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~	  Steam Achievement	
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class SteamAchievements
{
public:
	//--------------------------------------------------
	//    Constructor
	//--------------------------------------------------
	SteamAchievements(Achievement_t* achievements, int numAchievements);


	//--------------------------------------------------
	//    Achievement
	//--------------------------------------------------
	bool RequestStats();
	bool SetAchievement(const char* id);
	void ResetAllAchievements() const;

	//--------------------------------------------------
	//    Callbacks
	//--------------------------------------------------
	STEAM_CALLBACK(SteamAchievements, OnUserStatsReceived, UserStatsReceived_t, m_CallbackUserStatsReceived);
	STEAM_CALLBACK(SteamAchievements, OnUserStatsStored, UserStatsStored_t, m_CallbackUserStatsStored);
	STEAM_CALLBACK(SteamAchievements, OnAchievementStored, UserAchievementStored_t, m_CallbackAchievementStored);

private:
	uint64 m_AppID;
	Achievement_t* m_pAchievements;
	int m_NumAchievements;
	bool m_IsInitialized;
};


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~	  Game Achievements	
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
enum class Achievements
{
	ACH_WIN_ONE_GAME = 0,
	ACH_WIN_100_GAMES = 1,
	ACH_TRAVEL_FAR_ACCUM = 2,
	ACH_TRAVEL_FAR_SINGLE = 3
};
inline const char* to_string(Achievements e)
{
	switch (e)
	{
	case Achievements::ACH_WIN_ONE_GAME: return "ACH_WIN_ONE_GAME";
	case Achievements::ACH_WIN_100_GAMES: return "ACH_WIN_100_GAMES";
	case Achievements::ACH_TRAVEL_FAR_ACCUM: return "ACH_TRAVEL_FAR_ACCUM";
	case Achievements::ACH_TRAVEL_FAR_SINGLE: return "ACH_TRAVEL_FAR_SINGLE";
	default: return "unknown";
	}
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~	  Globals	
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
inline Achievement_t g_Achievements[] =
{
	_ACH_ID(static_cast<int>(Achievements::ACH_WIN_ONE_GAME), to_string(Achievements::ACH_WIN_ONE_GAME), "Winner"),
	_ACH_ID(static_cast<int>(Achievements::ACH_WIN_100_GAMES), to_string(Achievements::ACH_WIN_100_GAMES),"Champion"),
	_ACH_ID(static_cast<int>(Achievements::ACH_TRAVEL_FAR_ACCUM), to_string(Achievements::ACH_TRAVEL_FAR_ACCUM),"Interstellar"),
	_ACH_ID(static_cast<int>(Achievements::ACH_TRAVEL_FAR_SINGLE), to_string(Achievements::ACH_TRAVEL_FAR_SINGLE),"Orbiter"),
};

inline SteamAchievements* g_SteamAchievements = nullptr;