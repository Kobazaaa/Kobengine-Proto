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
	bool HasAchievement(const char* id) const;

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