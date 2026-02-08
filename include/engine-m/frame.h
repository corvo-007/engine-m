#pragma once

#include "engine-m/core.h"
#include "engine-m/vector/vector.h"

namespace EngineM {

    class ENGINE_M_API Frame {
    public:
        vec3f origin;
        vec3f tangent;
        vec3f normal;
        vec3f rotationAxis;

        Frame() = default;
        Frame(const vec3f &, const vec3f &, const vec3f &, const vec3f &);
        Frame(const Frame &) = default;

        Frame& operator=(const Frame &) = default;

        ~Frame() = default;
    };
}