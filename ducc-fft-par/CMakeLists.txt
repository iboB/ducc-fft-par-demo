add_library(ducc-fft-par STATIC)
add_library(ducc::fft-par ALIAS ducc-fft-par)

target_sources(ducc-fft-par
    PUBLIC FILE_SET HEADERS FILES
        ducc-par/fft/fft.h
        ducc-par/infra/mav.h
        ducc-par/infra/string_utils.h
    PRIVATE
        ducc-par/fft/fft_inst1.cc # float
        ducc-par/fft/fft_inst2.cc # double and long double
        ducc-par/infra/mav.cc
        ducc-par/infra/string_utils.cc
)

set_target_properties(ducc-fft-par PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

target_link_libraries(ducc-fft-par PUBLIC par::par)

optimize_target_for_numeric_compute(ducc-fft-par)
