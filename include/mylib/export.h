#pragma once

// DLL / static lib の切り替え（DLL機能の一部であり、テストの痕跡ではない）
#if defined(_WIN32) && !defined(MYLIB_STATIC)
#  if defined(MYLIB_BUILD)
#    define MYLIB_API __declspec(dllexport)
#  else
#    define MYLIB_API __declspec(dllimport)
#  endif
#else
#  define MYLIB_API
#endif
