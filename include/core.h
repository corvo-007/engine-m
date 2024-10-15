#pragma once

#if defined(_WIN32) && defined(DYNAMIC_LINK)
    #ifdef BUILD_DLL
        #define MATH_ENGINE_API __declspec(dllexport)
    #else
        #define MATH_ENGINE_API __declspec(dllimport)
    #endif
#else
    #define MATH_ENGINE_API
#endif
