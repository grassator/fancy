@echo off

if not defined DevEnvDir (
    call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
)

rmdir /S /Q build
mkdir build

pushd build
cl /Fe:spec /Od /std:c++latest /nologo /WX /FC /Zo /Zi^
   /Wall /wd4711 /wd4068 /wd4710 /wd4204 /wd4200 /wd4221 /wd4057^
   /wd4255 /wd4505 /wd4201 /wd4668 /wd4820 /wd5045 /wd4100^
   /D UNICODE /D _UNICODE^
   ..\spec.c
if %errorlevel% neq 0 (
  popd
  exit /b 1
)
popd
