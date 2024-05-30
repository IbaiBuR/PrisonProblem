#include "box.hpp"
#include "utils.hpp"

inline auto run(std::array<u8, RUNS>& reboots) -> void
{
    for (usize i = 0; i < RUNS; ++i)
    {
        while (!box::select<false>(box::init()))
            ++reboots[i];
    }
}

int main()
{
    std::array<u8, RUNS> reboots{};

    const auto start = utils::getTimeMs();
    run(reboots);
    const auto elapsed = utils::getTimeMs() - start;

    utils::print_stats(reboots);
    std::println("\n\033[32mElapsed time: {} ms\033[0m", elapsed);

    return 0;
}
