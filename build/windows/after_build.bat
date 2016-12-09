@ECHO OFF

MKDIR ..\..\bin
MKDIR ..\..\bin\include

XCOPY /D  ..\..\include                                     ..\..\bin\include       /Y /Q
XCOPY /D  ..\..\kernel\include\config_default.h             ..\..\bin\include       /Y /Q
XCOPY /D  ..\..\porting\windows\config_user.h               ..\..\bin\include       /Y /Q

:QUIT
@ECHO ON