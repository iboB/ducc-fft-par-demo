#include <ducc0/fft/fft.h>
#include <complex>
#include <iostream>

int main() {
    std::vector<std::complex<float>> in = {
        0.123f, 0.234f, 0.345f, 0.456f,
        0.567f, 0.678f, 0.789f, 0.890f,
        0.765f, 0.654f, 0.543f, 0.432f,
        0.321f, 0.210f, 0.109f, 0.012f
    };

    std::vector<std::complex<float>> out(in.size());
    ducc0::vfmav<std::complex<float>> vin(in.data(), { in.size() });
    ducc0::vfmav<std::complex<float>> vout(out.data(), { out.size() });
    std::vector<size_t> axes = {0};
    ducc0::c2c(vin, vout, axes, true, 1.f, 4);

    for (auto& c : out) {
        std::cout << c << "\n";
    }

    return 0;
}
