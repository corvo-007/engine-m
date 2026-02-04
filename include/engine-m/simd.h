#pragma once

namespace EngineM::SIMD {
    enum class Level {
        Scalar,
        SSE2,
        AVX,
        AVX2
    };

    Level get_simd_level();
}
