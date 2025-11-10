add_library(ducc-fft-par STATIC)
add_library(ducc::fft-par ALIAS ducc-fft-par)

target_sources(ducc-fft-par
    PUBLIC FILE_SET HEADERS FILES
        ducc0/fft/fft.h
        ducc0/infra/mav.h
        ducc0/infra/string_utils.h
    PRIVATE
        ducc0/fft/fft_inst1.cc # float
        ducc0/fft/fft_inst2.cc # double and long double
        ducc0/infra/mav.cc
        ducc0/infra/string_utils.cc
)

set_target_properties(ducc-fft-par PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

target_link_libraries(ducc-fft-par PUBLIC par::par)
optimize_target_for_numeric_compute(ducc-fft-par)
