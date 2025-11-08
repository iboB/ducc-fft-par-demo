add_executable(demo demo.cpp)
target_link_libraries(demo PRIVATE
    ducc::original
    ducc::fft-par
)
