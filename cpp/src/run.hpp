#pragma once

#include <thread>
#include <vector>

#include "box.hpp"
#include "types.hpp"
#include "utils.hpp"

#include "../external/BS_thread_pool.hpp"

namespace run
{
    inline auto single_threaded() -> void
    {
        std::vector<u8> reboots(default_runs);

        const auto start_time = utils::get_time_ms();

        for (usize i = 0; i < default_runs; ++i)
        {
            while (!box::select<false>(box::init()))
                ++reboots[i];
        }

        const auto elapsed = utils::get_time_ms() - start_time;

        utils::print_stats(reboots);
        std::println("\n\033[32mElapsed time: {} ms\033[0m", elapsed);
    }

    namespace multi_threaded
    {
        inline auto manual() -> void
        {
            const auto num_threads = std::thread::hardware_concurrency();

            std::vector<u8> reboots(default_runs);
            std::vector<std::thread> threads(num_threads);

            const auto start_time = utils::get_time_ms();

            for (unsigned i = 0; i < num_threads; ++i)
            {
                threads[i] = std::thread([&, i]() -> void
                {
                    thread_local std::mt19937 rng{std::random_device{}()};

                    for (auto j = i * default_runs / num_threads; j < (i + 1) * default_runs / num_threads; ++j)
                    {
                        while (!box::select<false>(box::init(rng)))
                            ++reboots[j];
                    }
                });
            }

            for (auto& thread: threads)
                thread.join();

            const auto elapsed = utils::get_time_ms() - start_time;

            utils::print_stats(reboots);
            std::println("\n\033[32mElapsed time: {} ms\033[0m", elapsed);
        }

        inline auto thread_pool() -> void
        {
            const auto num_threads = std::thread::hardware_concurrency();

            std::vector<u8> reboots(default_runs);
            BS::thread_pool pool(num_threads);

            const auto start_time = utils::get_time_ms();

            const auto loop_future = pool.submit_loop<usize>(0, default_runs, [&reboots](const usize i)
            {
                thread_local std::mt19937 rng{std::random_device{}()};

                while (!box::select<false>(box::init(rng)))
                    ++reboots[i];
            });

            loop_future.wait();

            const auto elapsed = utils::get_time_ms() - start_time;

            utils::print_stats(reboots);
            std::println("\n\033[32mElapsed time: {} ms\033[0m", elapsed);
        }
    }
}
