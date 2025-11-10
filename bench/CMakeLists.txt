add_executable(bench-ducc-original bench-ducc-original.cpp)
target_link_libraries(bench-ducc-original PRIVATE
    ducc::original
    picobench::picobench
)
optimize_target_for_numeric_compute(bench-ducc-original)

add_executable(bench-ducc-fft-par bench-ducc-fft-par.cpp)
target_link_libraries(bench-ducc-fft-par PRIVATE
    ducc::fft-par
    picobench::picobench
)
optimize_target_for_numeric_compute(bench-ducc-fft-par)
