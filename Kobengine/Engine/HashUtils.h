#pragma once
#include <cstdint>

namespace kob
{
	template <int Length>
	struct SDBMHash
	{
		consteval static uint32_t _calculate(const char* const text, uint32_t& value)
		{
			const uint32_t character = SDBMHash<Length - 1>::_calculate(text, value);
			value = character + (value << 6) + (value << 16) - value;
			return text[Length - 1];
		}
		consteval static uint32_t Calculate(const char* const text)
		{
			uint32_t value = 0;
			const auto character = _calculate(text, value);
			return character + (value << 6) + (value << 16) - value;
		}
	};
	template<>
	struct SDBMHash<1>
	{
		consteval static int _calculate(const char* const text, uint32_t&) { return text[0]; }
	};
	template <size_t N>
	consteval uint32_t MakeSDBMHash(const char(&text)[N])
	{
		return SDBMHash<N - 1>::Calculate(text);
	}
}
