#include "ducc-par/fft/fftnd_impl.h"

namespace ducc::par{
namespace detail_fft {
#define T float
#include "ducc-par/fft/fft_inst_inc.h"
#undef T
}
}
