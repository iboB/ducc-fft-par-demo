// Copyright (c) Borislav Stanimirov
// SPDX-License-Identifier: MIT
//
#include <ducc0/fft/fft.h>

#include <iostream>
#include <atomic>
#include <random>
#include <numeric>
#include <bit>
#include <thread>

#define PICOBENCH_IMPLEMENT
#include <picobench/picobench.hpp>

static constexpr uint32_t NUM_THREADS = 8;
void bench(picobench::state& s) {
    std::mt19937 rng(s.iterations());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    std::vector<std::complex<float>> data;
    data.reserve(s.iterations());
    for (int i = 0; i < s.iterations(); ++i) {
        data.push_back(dist(rng));
    }

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
PICOBENCH(bench);

void warmup();

int main(int argc, char* argv[]) {
    picobench::runner r;
    r.set_default_samples(10);
    r.set_default_state_iterations({10'000, 100'000, 1'000'000});
    r.set_compare_results_across_samples(true);
    r.parse_cmd_line(argc, argv);

    warmup();

    return r.run();
}
