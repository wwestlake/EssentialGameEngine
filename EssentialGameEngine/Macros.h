#pragma once

#if defined(ESSENTIAL_API_EXPORT)
#    define ESSENTIAL_API __declspec(dllexport)
#else
#    define ESSENTIAL_API __declspec(dllimport)
#endif

