#pragma once
#include <memory>
#include <unordered_set>
#include <string>
#include "Singleton.h"
#include "Event.h"
#include "SteamAchievements.h"

namespace kob
{
	class AchievementManager : public Singleton<AchievementManager>
	{
	public:
        template <typename... Args>
        void RegisterAchievement(Event<Args...>& eventRef, std::function<bool(Args...)> condition, const std::string& achievementID)
		{
            // Link event to achievement logic
            auto result = m_Callbacks.insert(std::make_unique<EventCallback<Args...>>
                (
                    [this, achievementID, condition](Args... args)
                    {
                        if (condition(args...)) {
                            UnlockAchievement(achievementID);
                        }
                    }
                )
            );

            if (result.second)
            {
                eventRef += static_cast<EventListener<Args...>*>((*result.first).get());
            }
        }

        SteamAchievements* GetSteamAchievementsPtr()
        {
            return m_SteamAchievements.get();
        }

	private:
        void UnlockAchievement(const std::string& achievementID)
		{
            m_SteamAchievements->SetAchievement(achievementID.c_str());
        }

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
        const char* to_string(Achievements e)
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
        Achievement_t m_Achievements[4] =
        {
            _ACH_ID(static_cast<int>(Achievements::ACH_WIN_ONE_GAME), to_string(Achievements::ACH_WIN_ONE_GAME), "Winner"),
            _ACH_ID(static_cast<int>(Achievements::ACH_WIN_100_GAMES), to_string(Achievements::ACH_WIN_100_GAMES),"Champion"),
            _ACH_ID(static_cast<int>(Achievements::ACH_TRAVEL_FAR_ACCUM), to_string(Achievements::ACH_TRAVEL_FAR_ACCUM),"Interstellar"),
            _ACH_ID(static_cast<int>(Achievements::ACH_TRAVEL_FAR_SINGLE), to_string(Achievements::ACH_TRAVEL_FAR_SINGLE),"Orbiter"),
        };

        std::unordered_set<std::unique_ptr<BaseListener>> m_Callbacks;
		std::unique_ptr<SteamAchievements> m_SteamAchievements = std::make_unique<SteamAchievements>(m_Achievements, 4);
    };
}
