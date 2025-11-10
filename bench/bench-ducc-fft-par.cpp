#include <par/prun.hpp>
#include "bench-code.inl"

void warmup() {
    par::thread_pool::init_global(std::min(std::thread::hardware_concurrency(), NUM_THREADS));

    // actual number of threads
    const auto num_threads = par::thread_pool::global().num_threads();

    std::atomic_uint32_t counter = 0;
    par::prun({.sched = par::schedule_static}, [&](uint32_t) {
        ++counter;
    });
}
