@echo off
rem =========================================================
rem  MSVC ビルド例（"x64 Native Tools Command Prompt" で実行）
rem  リリースDLLとテスト用staticを同一ソース・同一最適化で作る
rem =========================================================

rem --- 1) リリース配布物: mylib.dll + mylib.lib(インポートlib) ---
cl /nologo /EHsc /MD /O2 /DNDEBUG /DMYLIB_BUILD ^
   /I include /c src\MyClass1.cpp /Fo:MyClass1_dll.obj
link /nologo /DLL /OUT:mylib.dll MyClass1_dll.obj

rem --- 2) テスト用 static lib（フラグは 1) と同一 + MYLIB_STATIC）---
cl /nologo /EHsc /MD /O2 /DNDEBUG /DMYLIB_STATIC ^
   /I include /c src\MyClass1.cpp /Fo:MyClass1_static.obj
lib /nologo /OUT:mylib_static.lib MyClass1_static.obj

rem --- 3) テスト実行ファイル（配布しない）---
cl /nologo /EHsc /MD /O2 /DNDEBUG /DMYLIB_STATIC ^
   /I include tests\test_myclass1.cpp mylib_static.lib ^
   /Fe:tests.exe
tests.exe

rem 配布するのは include\ と mylib.lib と mylib.dll のみ。
rem src\MyClass1_impl.h と tests\ は配布物に含めない。
