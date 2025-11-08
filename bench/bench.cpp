// Copyright (c) Borislav Stanimirov
// SPDX-License-Identifier: MIT
//
#include <ducc0/infra/threading.h>
#include <ducc0/fft/fft.h>

#include <iostream>
#include <atomic>
#include <random>
#include <numeric>
#include <bit>
#include <map>

#define PICOBENCH_IMPLEMENT
#include <picobench/picobench.hpp>

std::map<int, std::vector<std::complex<float>>> random_data_for_iterations;

static constexpr uint32_t NUM_THREADS = 8;

void warmup() {
    std::atomic_uint32_t counter = 0;
    ducc0::execStatic(NUM_THREADS, NUM_THREADS, 1, [&](ducc0::Scheduler&) {
        ++counter;
    });
}

void orig(picobench::state& s) {
    auto& data = random_data_for_iterations[s.iterations()];
    std::vector<std::complex<float>> result(data.size());

    std::vector<size_t> axes = {0};
    std::vector<size_t> dims = {data.size()};
    ducc0::vfmav<std::complex<float>> in(data.data(), dims);
    ducc0::vfmav<std::complex<float>> out(result.data(), dims);

    {
        picobench::scope scope(s);
        ducc0::c2c(in, out, axes, true, 1.f, NUM_THREADS);
    }

    auto sum = std::accumulate(result.begin(), result.end(), std::complex<float>{0});
    s.set_result(std::bit_cast<uint32_t>(std::abs(sum)));
}

PICOBENCH(orig);

int main(int argc, char* argv[]) {
    picobench::runner r;
    r.set_default_state_iterations({1000, 10'000});
    r.set_compare_results_across_samples(true);
    r.set_compare_results_across_benchmarks(true);
    r.parse_cmd_line(argc, argv);

    std::mt19937 rng(42);
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    auto& iters = r.default_state_iterations();
    for (auto i : iters) {
        auto& data = random_data_for_iterations[i];
        data.reserve(i);
        for (int j = 0; j < i; ++j) {
            data.push_back(dist(rng));
        }
    }

    warmup();

    return r.run();
}
