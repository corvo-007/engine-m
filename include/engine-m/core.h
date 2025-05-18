#pragma once

#if defined(_WIN32) && defined(DYNAMIC_LINK)
    #ifdef BUILD_DLL
        #define ENGINE_M_API __declspec(dllexport)
    #else
        #define ENGINE_M_API __declspec(dllimport)
    #endif
#else
    #define ENGINE_M_API
#endif
