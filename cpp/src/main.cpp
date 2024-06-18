#include "run.hpp"

int main()
{
    run::single_threaded();

    run::multi_threaded::manual();
    run::multi_threaded::thread_pool();
    run::multi_threaded::parallel_std();

    return 0;
}
