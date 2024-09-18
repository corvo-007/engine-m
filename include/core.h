#pragma once

#ifdef BUILD_DLL
    #define MATH_ENGINE_API __declspec(dllexport)
#else
    #define MATH_ENGINE_API __declspec(dllimport)
#endif