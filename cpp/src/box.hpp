#pragma once

#include <algorithm>
#include <array>
#include <numeric>
#include <print>
#include <random>
#include <span>

#include "types.hpp"

namespace box
{
    inline auto init() -> std::array<u8, 100>
    {
        static std::mt19937 rng(std::random_device{}());
        std::array<u8, 100> box{};

        std::iota(box.begin(), box.end(), 0);
        std::ranges::shuffle(box.begin(), box.end(), rng);

        return box;
    }

    inline auto init(std::mt19937& rng) -> std::array<u8, 100>
    {
        std::array<u8, 100> box{};

        std::iota(box.begin(), box.end(), 0);
        std::ranges::shuffle(box.begin(), box.end(), rng);

        return box;
    }

    template<bool verbose>
    auto select(const std::span<const u8> box) -> bool
    {
        for (int prisoner = 0; prisoner < 100; ++prisoner)
        {
            if constexpr (verbose)
                std::println("Prisoner: {}", prisoner);

            int current_index = prisoner;
            int count = 0;
            bool found = false;

            do
            {
                const auto value = box[current_index];

                if constexpr (verbose)
                    std::println("Box: {:02} - Number: {:02}", current_index, value);

                if (prisoner == value)
                    found = true;
                else
                    current_index = value;

                ++count;
            } while (count < 50 && !found);

            if (!found)
            {
                if constexpr (verbose)
                    std::println("Failed!");

                return false;
            }
        }

        return true;
    }
}
