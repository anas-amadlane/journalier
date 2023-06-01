Name "Journalier"
Outfile "Journalier_setup.exe"
InstallDir "$PROGRAMFILES\Journalier"
VIProductVersion "1.0.0"

!include LogicLib.nsh

Function CheckGTKInstalled
    ReadRegStr $0 HKLM "SOFTWARE\Gtk" ""
    ReadRegStr $1 HKLM "SOFTWARE\Wow6432Node\Gtk" ""

    ${If} $0 != ""
        StrCpy $1 1
    ${ElseIf} $1 != ""
        StrCpy $1 1
    ${Else}
        StrCpy $1 0
    ${EndIf}
FunctionEnd

Section
    Call CheckGTKInstalled

    ${If} $1 == 0
        DetailPrint "GTK3 not found. Installing GTK3..."
        SetOutPath "$INSTDIR\dep"
        File "dep\gtk3-runtime-3.24.31-2022-01-04-ts-win64.exe"
        ExecWait "$INSTDIR\dep\gtk3-runtime-3.24.31-2022-01-04-ts-win64.exe"
    ${Else}
        DetailPrint "GTK3 is already installed."
    ${EndIf}

    CreateDirectory "$APPDATA\journalier"
    SetOutPath "$INSTDIR"
    File "journalier.exe"
    File "DLLs\libxlsxio_read.dll"
    File "DLLs\libxlsxio_write.dll"
    File "DLLs\libzip.dll"
    File "DLLs\libzstd.dll"

    CreateDirectory "$INSTDIR\output"

    SetOutPath "$INSTDIR\data\table"
    File "data\table\BL.xlsx"
    File "data\table\BL1.xlsx"
    File "data\table\CLT.xlsx"
    File "data\table\MAT.xlsx"

    SetOutPath "$INSTDIR\data\logo"
    File "data\logo\srm.png"

    CreateShortcut "$SMPROGRAMS\Journalier.lnk" "$INSTDIR\journalier.exe" "" "$INSTDIR\journalier.exe"

    ExecWait 'cmd.exe /C mklink /J "$DOCUMENTS\Journalier" "$INSTDIR\output"'

    WriteUninstaller "$INSTDIR\Uninstall.exe"
SectionEnd

Section "Uninstall"
    Delete "$INSTDIR\journalier.exe"
    Delete "$SMPROGRAMS\Journalier.lnk"
    Delete "$INSTDIR\Uninstall.exe"

    ExecWait 'cmd.exe /C rmdir /s /q "$DOCUMENTS\Journalier"'

    RMDir /r "$INSTDIR"
SectionEnd
