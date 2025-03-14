#include "SteamAchievements.h"
#include "SDL_syswm.h"

//--------------------------------------------------
//    Constructor
//--------------------------------------------------
SteamAchievements::SteamAchievements(Achievement_t* achievements, int numAchievements)
	: m_CallbackUserStatsReceived{ this, &SteamAchievements::OnUserStatsReceived }
	, m_CallbackUserStatsStored{ this, &SteamAchievements::OnUserStatsStored }
	, m_CallbackAchievementStored{ this, &SteamAchievements::OnAchievementStored }
	, m_AppID{ 0 }
	, m_IsInitialized{ false }
{
	m_AppID = SteamUtils()->GetAppID();
	m_pAchievements = achievements;
	m_NumAchievements = numAchievements;
	RequestStats();
}


//--------------------------------------------------
//    Achievement
//--------------------------------------------------
bool SteamAchievements::RequestStats()
{
	// Check if steam is loaded
	if (SteamUserStats() == NULL || SteamUser() == NULL)
		return false;

	// Check if the user is logged on
	if (!SteamUser()->BLoggedOn())
		return false;

	// Request user stats
	return SteamUserStats()->RequestCurrentStats();
}
bool SteamAchievements::SetAchievement(const char* id)
{
	// Have we received a call back from Steam yet
	if (m_IsInitialized)
	{
		SteamUserStats()->SetAchievement(id);
		return SteamUserStats()->StoreStats();
	}
	// If not then we can't set achievements yet
	return false;
}
void SteamAchievements::ResetAllAchievements() const
{
	bool bStatsChanged = false;  // Flag to check if any stats were modified

	// Iterate through all achievements
	for (int achIdx = 0; achIdx < m_NumAchievements; ++achIdx)
	{
		Achievement_t& achievement = m_pAchievements[achIdx];

		// Reset the achievement if it's unlocked
		if (SteamUserStats()->ClearAchievement(achievement.achievementIDName))
		{
			bStatsChanged = true;  // If any achievement is cleared, mark stats as changed
		}
	}

	// Store stats if any achievements were reset
	if (bStatsChanged)
	{
		SteamUserStats()->StoreStats();
	}
}


//--------------------------------------------------
//    Callbacks
//--------------------------------------------------
void SteamAchievements::OnUserStatsReceived(UserStatsReceived_t* pCallback)
{
	if (m_AppID == pCallback->m_nGameID)
	{
		if (pCallback->m_eResult == k_EResultOK)
		{
			OutputDebugString("Received stats and achievements from Steam\n");
			m_IsInitialized = true;

			// Load Achievements
			for (int achIdx = 0; achIdx < m_NumAchievements; ++achIdx)
			{
				Achievement_t& achievement = m_pAchievements[achIdx];

				SteamUserStats()->GetAchievement(achievement.achievementIDName, &achievement.achieved);
				_snprintf_s(achievement.name, sizeof(achievement.name), "%s", SteamUserStats()->GetAchievementDisplayAttribute(achievement.achievementIDName, "name"));
				_snprintf_s(achievement.description, sizeof(achievement.description), "%s", SteamUserStats()->GetAchievementDisplayAttribute(achievement.achievementIDName, "desc"));
			}
		}
		else
		{
			char buffer[128];
			_snprintf_s(buffer, 128, "RequestStats - failed, %d\n", pCallback->m_eResult);
			OutputDebugString(buffer);
		}
	}
}
void SteamAchievements::OnUserStatsStored(UserStatsStored_t* pCallback)
{
	if (m_AppID == pCallback->m_nGameID)
	{
		if (k_EResultOK == pCallback->m_eResult)
		{
			OutputDebugString("Stored stats for Steam\n");
		}
		else
		{
			char buffer[128];
			_snprintf_s(buffer, 128, "StatsStored - failed, %d\n", pCallback->m_eResult);
			OutputDebugString(buffer);
		}
	}
}
void SteamAchievements::OnAchievementStored(UserAchievementStored_t* pCallback)
{
	if (m_AppID == pCallback->m_nGameID)
	{
		OutputDebugString("Stored Achievement for Steam\n");
	}
}
