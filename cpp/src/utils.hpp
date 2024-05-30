#pragma once

#include <algorithm>
#include <array>
#include <chrono>
#include <numeric>
#include <print>

#include "types.hpp"

namespace utils
{
    inline auto print_stats(std::array<u8, RUNS>& reboots) -> void
    {
        const auto total_reboots = std::accumulate(reboots.begin(), reboots.end(), 0);
        const auto avg_reboots = total_reboots / reboots.size();
        const auto min_reboots = *std::ranges::min_element(reboots.begin(), reboots.end());
        const auto max_reboots = *std::ranges::max_element(reboots.begin(), reboots.end());

        std::println("\n=====================================");
        std::println("||           STATISTICS            ||");
        std::println("=====================================");
        std::println("|| Total number of reboots: {:6} ||", total_reboots);
        std::println("|| Average number of reboots: {:4} ||", avg_reboots);
        std::println("|| Maximum number of reboots: {:4} ||", max_reboots);
        std::println("|| Minimum number of reboots: {:4} ||", min_reboots);
        std::println("=====================================");
    }

    inline auto getTimeMs() -> long
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::steady_clock::now().time_since_epoch())
                .count();
    }
}
