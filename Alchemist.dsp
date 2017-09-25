# Microsoft Developer Studio Project File - Name="Alchemist" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Alchemist - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Alchemist.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Alchemist.mak" CFG="Alchemist - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Alchemist - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Alchemist - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Alchemist - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(QTDIR)\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib wsock32.lib winspool.lib winmm.lib $(QTDIR)\lib\qt-mtnc321.lib $(QTDIR)\lib\qtmain.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Alchemist - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(QTDIR)\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib imm32.lib wsock32.lib winspool.lib winmm.lib $(QTDIR)\lib\qt-mtnc321.lib $(QTDIR)\lib\qtmain.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"msvcrt.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Alchemist - Win32 Release"
# Name "Alchemist - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\src\alchemist.cpp
# End Source File
# Begin Source File

SOURCE=.\src\alchemistbase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\docinfodialog.cpp
# End Source File
# Begin Source File

SOURCE=.\src\docinfodialogbase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\general.cpp
# End Source File
# Begin Source File

SOURCE=.\src\helpaboutdialog.cpp
# End Source File
# Begin Source File

SOURCE=.\src\helpaboutdialogbase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\main.cpp
# End Source File
# Begin Source File

SOURCE=.\src\moc_alchemist.cpp
# End Source File
# Begin Source File

SOURCE=.\src\moc_alchemistbase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\moc_docinfodialog.cpp
# End Source File
# Begin Source File

SOURCE=.\src\moc_docinfodialogbase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\moc_helpaboutdialog.cpp
# End Source File
# Begin Source File

SOURCE=.\src\moc_helpaboutdialogbase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\moc_preferencesdialog.cpp
# End Source File
# Begin Source File

SOURCE=.\src\moc_preferencesdialogbase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\moc_verifydialog.cpp
# End Source File
# Begin Source File

SOURCE=.\src\moc_verifydialogbase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\parse.cpp
# End Source File
# Begin Source File

SOURCE=.\src\preferencesdialog.cpp
# End Source File
# Begin Source File

SOURCE=.\src\preferencesdialogbase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\verifydialog.cpp
# End Source File
# Begin Source File

SOURCE=.\src\verifydialogbase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\wordcollection.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\src\alchemist.h

!IF  "$(CFG)" == "Alchemist - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing alchemist.h...
InputDir=.\src
InputPath=.\src\alchemist.h
InputName=alchemist

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"%qtdir%\bin\moc.exe" "$(InputDir)\$(InputName).h" -o "$(InputDir)\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "Alchemist - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing alchemist.h...
InputDir=.\src
InputPath=.\src\alchemist.h
InputName=alchemist

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"%qtdir%\bin\moc.exe" "$(InputDir)\$(InputName).h" -o "$(InputDir)\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\alchemistbase.h
# End Source File
# Begin Source File

SOURCE=.\src\docinfodialog.h

!IF  "$(CFG)" == "Alchemist - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing docinfodialog.h...
InputDir=.\src
InputPath=.\src\docinfodialog.h
InputName=docinfodialog

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"%qtdir%\bin\moc.exe" "$(InputDir)\$(InputName).h" -o "$(InputDir)\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "Alchemist - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing docinfodialog.h...
InputDir=.\src
InputPath=.\src\docinfodialog.h
InputName=docinfodialog

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"%qtdir%\bin\moc.exe" "$(InputDir)\$(InputName).h" -o "$(InputDir)\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\docinfodialogbase.h
# End Source File
# Begin Source File

SOURCE=.\src\general.h
# End Source File
# Begin Source File

SOURCE=.\src\helpaboutdialog.h

!IF  "$(CFG)" == "Alchemist - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing helpaboutdialog.h...
InputDir=.\src
InputPath=.\src\helpaboutdialog.h
InputName=helpaboutdialog

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"%qtdir%\bin\moc.exe" "$(InputDir)\$(InputName).h" -o "$(InputDir)\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "Alchemist - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing helpaboutdialog.h...
InputDir=.\src
InputPath=.\src\helpaboutdialog.h
InputName=helpaboutdialog

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"%qtdir%\bin\moc.exe" "$(InputDir)\$(InputName).h" -o "$(InputDir)\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\helpaboutdialogbase.h
# End Source File
# Begin Source File

SOURCE=.\src\parse.h
# End Source File
# Begin Source File

SOURCE=.\src\preferencesdialog.h

!IF  "$(CFG)" == "Alchemist - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing preferencesdialog.h...
InputDir=.\src
InputPath=.\src\preferencesdialog.h
InputName=preferencesdialog

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"%qtdir%\bin\moc.exe" "$(InputDir)\$(InputName).h" -o "$(InputDir)\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "Alchemist - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing preferencesdialog.h...
InputDir=.\src
InputPath=.\src\preferencesdialog.h
InputName=preferencesdialog

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"%qtdir%\bin\moc.exe" "$(InputDir)\$(InputName).h" -o "$(InputDir)\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\preferencesdialogbase.h
# End Source File
# Begin Source File

SOURCE=.\src\verifydialog.h

!IF  "$(CFG)" == "Alchemist - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing verifydialog.h...
InputDir=.\src
InputPath=.\src\verifydialog.h
InputName=verifydialog

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"%qtdir%\bin\moc.exe" "$(InputDir)\$(InputName).h" -o "$(InputDir)\moc_$(InputName).cpp"

# End Custom Build

!ELSEIF  "$(CFG)" == "Alchemist - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - MOCing verifydialog.h...
InputDir=.\src
InputPath=.\src\verifydialog.h
InputName=verifydialog

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"%qtdir%\bin\moc.exe" "$(InputDir)\$(InputName).h" -o "$(InputDir)\moc_$(InputName).cpp"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\verifydialogbase.h
# End Source File
# Begin Source File

SOURCE=.\src\wordcollection.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\src\alchemistbase.ui

!IF  "$(CFG)" == "Alchemist - Win32 Release"

!ELSEIF  "$(CFG)" == "Alchemist - Win32 Debug"

# Begin Custom Build - UICing $(InputName).ui...
InputDir=.\src
InputPath=.\src\alchemistbase.ui
InputName=alchemistbase

BuildCmds= \
	"%qtdir%\bin\uic.exe" $(InputPath) -o $(InputDir)\$(InputName).h \
	"%qtdir%\bin\uic.exe" $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	"%qtdir%\bin\moc.exe" $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\docinfodialogbase.ui

!IF  "$(CFG)" == "Alchemist - Win32 Release"

!ELSEIF  "$(CFG)" == "Alchemist - Win32 Debug"

# Begin Custom Build - UICing $(InputName).ui...
InputDir=.\src
InputPath=.\src\docinfodialogbase.ui
InputName=docinfodialogbase

BuildCmds= \
	"%qtdir%\bin\uic.exe" $(InputPath) -o $(InputDir)\$(InputName).h \
	"%qtdir%\bin\uic.exe" $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	"%qtdir%\bin\moc.exe" $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\helpaboutdialogbase.ui

!IF  "$(CFG)" == "Alchemist - Win32 Release"

!ELSEIF  "$(CFG)" == "Alchemist - Win32 Debug"

# Begin Custom Build - UICing $(InputName).ui...
InputDir=.\src
InputPath=.\src\helpaboutdialogbase.ui
InputName=helpaboutdialogbase

BuildCmds= \
	"%qtdir%\bin\uic.exe" $(InputPath) -o $(InputDir)\$(InputName).h \
	"%qtdir%\bin\uic.exe" $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	"%qtdir%\bin\moc.exe" $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\preferencesdialogbase.ui

!IF  "$(CFG)" == "Alchemist - Win32 Release"

!ELSEIF  "$(CFG)" == "Alchemist - Win32 Debug"

# Begin Custom Build - UICing $(InputName).ui...
InputDir=.\src
InputPath=.\src\preferencesdialogbase.ui
InputName=preferencesdialogbase

BuildCmds= \
	"%qtdir%\bin\uic.exe" $(InputPath) -o $(InputDir)\$(InputName).h \
	"%qtdir%\bin\uic.exe" $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	"%qtdir%\bin\moc.exe" $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\readme.txt
# End Source File
# Begin Source File

SOURCE=.\src\verifydialogbase.ui

!IF  "$(CFG)" == "Alchemist - Win32 Release"

!ELSEIF  "$(CFG)" == "Alchemist - Win32 Debug"

# Begin Custom Build - UICing $(InputName).ui...
InputDir=.\src
InputPath=.\src\verifydialogbase.ui
InputName=verifydialogbase

BuildCmds= \
	"%qtdir%\bin\uic.exe" $(InputPath) -o $(InputDir)\$(InputName).h \
	"%qtdir%\bin\uic.exe" $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	"%qtdir%\bin\moc.exe" $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
