#ifndef XXWEAKPTREXPORT_H
#define XXWEAKPTREXPORT_H

#if defined(_WIN32) || defined(_WIN64)
    #ifdef XXWEAKPTR_EXPORTS
        #define XXWEAKPTR_API __declspec(dllexport)
    #else
        #define XXWEAKPTR_API __declspec(dllimport) 
    #endif
#else
    #define XXWEAKPTR_API
#endif

#endif // XXWEAKPTREXPORT_H

