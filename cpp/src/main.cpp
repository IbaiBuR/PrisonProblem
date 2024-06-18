#include "run.hpp"

int main()
{
    run::single_threaded();
    run::multi_threaded::manual();
    run::multi_threaded::thread_pool();

    return 0;
}
