#include "box.hpp"
#include "utils.hpp"

inline auto run(std::array<u8, RUNS>& reboots) -> void
{
    for (usize i = 0; i < RUNS; ++i)
    {
        while (!box::select<false>(box::init()))
            ++reboots[i];
    }

    utils::print_stats(reboots);
}

int main()
{
    std::array<u8, RUNS> reboots{};
    const auto start = utils::getTimeMs();

    run(reboots);

    std::println("\nElapsed time: {} ms", utils::getTimeMs() - start);

    return 0;
}
