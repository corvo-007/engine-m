#include "engine-m/simd.h"

#if defined(_MSC_VER)
#include <intrin.h>
#elif defined(__GNUC__) || defined(__clang__)
#include <cpuid.h>
#include <immintrin.h>
#endif

namespace EngineM::SIMD {
#if defined(__GNUC__) || defined(__clang__)
    __attribute__((target("xsave")))
#endif
    Level get_simd_level() {
#if !defined(__i386__) && !defined(__x86_64__) && !defined(_M_IX86) && !defined(_M_X64)
        return Level::Scalar;
#else
        int cpu_info[4];

        auto call_cpuid = [&](int leaf, int subleaf, int *info) {
#if defined(_MSC_VER)
            __cpuidex(info, leaf, subleaf);
#else
            __cpuid_count(leaf, subleaf, info[0], info[1], info[2], info[3]);
#endif
        };

        call_cpuid(0, 0, cpu_info);

        int nIds = cpu_info[0];
        if (nIds < 1) {
            return Level::Scalar;
        }

        call_cpuid(1, 0, cpu_info);
        bool has_sse2 = (cpu_info[3] & (1 << 26)) != 0;
        bool has_osxsave = (cpu_info[2] & (1 << 27)) != 0;
        bool has_avx = (cpu_info[2] & (1 << 28)) != 0;

        bool os_avx_support = false;
        bool os_avx512_support = false;

        if (has_osxsave) {
#if defined(_MSC_VER)
            unsigned __int64 xcr0 = _xgetbv(0);
#else
            unsigned long long xcr0 = _xgetbv(0);
#endif

            os_avx_support = (xcr0 & 0x6) == 0x6;

            os_avx512_support = os_avx_support && ((xcr0 & 0xE0) == 0xE0);
        }

        if (nIds >= 7 && os_avx_support) {
            call_cpuid(7, 0, cpu_info);
            bool has_avx2 = (cpu_info[1] & (1 << 5)) != 0;
            bool has_avx512f = (cpu_info[1] & (1 << 16)) != 0;

            // TODO: for future support
            // if (has_avx512f && os_avx512_support) {
            //     return Level::AVX512;
            // }
            if (has_avx2) {
                return Level::AVX2;
            }
            if (has_avx) {
                return Level::AVX;
            }
        }

        if (has_sse2) {
            return Level::SSE2;
        }
        return Level::Scalar;
#endif
    }
}