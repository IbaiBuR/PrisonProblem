#pragma once

#include <array>
#include <thread>

#include "box.hpp"
#include "types.hpp"
#include "utils.hpp"

namespace run
{
    inline auto single_threaded() -> void
    {
        std::array<u8, RUNS> reboots{};
        const auto start_time = utils::get_time_ms();

        for (usize i = 0; i < RUNS; ++i)
        {
            while (!box::select<false>(box::init()))
                ++reboots[i];
        }

        const auto elapsed = utils::get_time_ms() - start_time;

        utils::print_stats(reboots);
        std::println("\n\033[32mElapsed time: {} ms\033[0m", elapsed);
    }

    inline auto multi_threaded() -> void
    {
        const auto num_threads = std::thread::hardware_concurrency();
        std::vector<std::atomic<u8>> reboots(RUNS);
        std::vector<std::thread> threads(num_threads);

        const auto start_time = utils::get_time_ms();

        for (auto i = 0; i < num_threads; ++i)
        {
            threads[i] = std::thread([&, i]() -> void
            {
                thread_local std::mt19937_64 rng{std::random_device{}()};

                for (auto j = i * RUNS / num_threads; j < (i + 1) * RUNS / num_threads; ++j)
                {
                    while (!box::select<false>(box::init(rng)))
                        ++reboots[j];
                }
            });
        }

        for (auto& thread: threads)
            thread.join();

        const auto elapsed = utils::get_time_ms() - start_time;

        std::array<u8, RUNS> copied_reboots{};

        for (usize i = 0; i < RUNS; ++i)
            copied_reboots[i] = reboots[i];

        utils::print_stats(copied_reboots);
        std::println("\n\033[32mElapsed time: {} ms\033[0m", elapsed);
    }
}
