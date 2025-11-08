#include "ducc-par/fft/fftnd_impl.h"

namespace ducc_par{
namespace detail_fft {
#define T double
#include "ducc-par/fft/fft_inst_inc.h"
#undef T

// we don't need long double when nanobind is active
#ifndef DUCC_PAR_USE_NANOBIND
#define T long double
#include "ducc-par/fft/fft_inst_inc.h"
#undef T
#endif
}
}
