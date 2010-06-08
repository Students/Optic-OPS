
@echo off
set QTDIR=D:\Program_Files\Qt\2009.05-rc1\qt
set PATH=D:\Program_Files\Qt\2009.05-rc1\qt\bin
set PATH=%PATH%;D:\Program_Files\Qt\2009.05-rc1\bin;D:\Program_Files\Qt\2009.05-rc1\mingw\bin
set PATH=%PATH%;%SystemRoot%\System32
set QMAKESPEC=win32-g++

qmake WV.pro
D:\Program_Files\Qt\2009.05-rc1\mingw\bin\mingw32-make.exe
pause

