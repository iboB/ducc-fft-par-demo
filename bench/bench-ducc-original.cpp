#include <ducc0/infra/threading.h>
#include "bench-code.inl"

void warmup() {
    const auto num_threads = std::min(std::thread::hardware_concurrency(), NUM_THREADS);
    std::atomic_uint32_t counter = 0;
    ducc0::execStatic(NUM_THREADS, num_threads, 1, [&](ducc0::Scheduler&) {
        ++counter;
    });
}
