add_executable(bench bench.cpp)
target_link_libraries(bench PRIVATE
    ducc::original
    ducc::fft-par
    picobench::picobench
)
optimize_target_for_numeric_compute(bench)
