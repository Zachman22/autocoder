; AutoCoder Windows Installer Script
; NSIS Script for creating Windows installer

;--------------------------------
; Includes
!include "MUI2.nsh"
!include "FileFunc.nsh"

;--------------------------------
; General Settings
!define PRODUCT_NAME "AutoCoder"
!define PRODUCT_VERSION "1.0.1"
!define PRODUCT_PUBLISHER "AutoCoder Team"
!define PRODUCT_WEB_SITE "https://github.com/Zachman22/autocoder"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

; Installer name and output file
Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "AutoCoder-${PRODUCT_VERSION}-Setup.exe"

; Default installation directory
InstallDir "$PROGRAMFILES64\AutoCoder"

; Request application privileges
RequestExecutionLevel admin

; Modern UI Configuration
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; Welcome page
!insertmacro MUI_PAGE_WELCOME

; License page
!insertmacro MUI_PAGE_LICENSE "LICENSE"

; Components page
!insertmacro MUI_PAGE_COMPONENTS

; Directory page
!insertmacro MUI_PAGE_DIRECTORY

; Installation page
!insertmacro MUI_PAGE_INSTFILES

; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\autocoder.exe"
!define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\README.md"
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

; Languages
!insertmacro MUI_LANGUAGE "English"

;--------------------------------
; Version Information
VIProductVersion "${PRODUCT_VERSION}.0"
VIAddVersionKey "ProductName" "${PRODUCT_NAME}"
VIAddVersionKey "ProductVersion" "${PRODUCT_VERSION}"
VIAddVersionKey "CompanyName" "${PRODUCT_PUBLISHER}"
VIAddVersionKey "LegalCopyright" "Copyright © 2025 ${PRODUCT_PUBLISHER}"
VIAddVersionKey "FileDescription" "${PRODUCT_NAME} Installer"
VIAddVersionKey "FileVersion" "${PRODUCT_VERSION}"

;--------------------------------
; Installer Sections

Section "AutoCoder (Required)" SecCore
  SectionIn RO

  SetOutPath "$INSTDIR"

  ; Main executable (from Release build)
  File "build\Release\autocoder.exe"

  ; Documentation files
  File "README.md"
  File "LICENSE"
  File "PACKAGING.md"
  File "WINDOWS_BUILD.md"

  ; Resources directory
  SetOutPath "$INSTDIR\resources"
  File /r "resources\*.*"

  ; Qt6 DLLs and dependencies (these will be in the build/Release directory after building)
  SetOutPath "$INSTDIR"
  File /nonfatal "build\Release\Qt6Core.dll"
  File /nonfatal "build\Release\Qt6Gui.dll"
  File /nonfatal "build\Release\Qt6Widgets.dll"
  File /nonfatal "build\Release\Qt6Network.dll"
  File /nonfatal "build\Release\Qt6WebSockets.dll"

  ; OpenSSL DLLs
  File /nonfatal "build\Release\libssl*.dll"
  File /nonfatal "build\Release\libcrypto*.dll"

  ; CURL DLL
  File /nonfatal "build\Release\libcurl*.dll"

  ; Visual C++ Runtime (if not using static linking)
  File /nonfatal "build\Release\msvcp*.dll"
  File /nonfatal "build\Release\vcruntime*.dll"

  ; Qt6 plugins
  SetOutPath "$INSTDIR\plugins\platforms"
  File /nonfatal "build\Release\plugins\platforms\qwindows.dll"

  SetOutPath "$INSTDIR\plugins\styles"
  File /nonfatal "build\Release\plugins\styles\qwindowsvistastyle.dll"

  ; Create qt.conf to tell Qt where to find plugins
  SetOutPath "$INSTDIR"
  FileOpen $0 "$INSTDIR\qt.conf" w
  FileWrite $0 "[Paths]$\r$\n"
  FileWrite $0 "Plugins=plugins$\r$\n"
  FileClose $0

  ; Store installation folder
  WriteRegStr HKLM "Software\${PRODUCT_NAME}" "" $INSTDIR

  ; Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

  ; Write uninstall registry keys
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "${PRODUCT_NAME}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\Uninstall.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\autocoder.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
  WriteRegDWORD ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "NoModify" 1
  WriteRegDWORD ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "NoRepair" 1

  ; Calculate and store install size
  ${GetSize} "$INSTDIR" "/S=0K" $0 $1 $2
  IntFmt $0 "0x%08X" $0
  WriteRegDWORD ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "EstimatedSize" "$0"

SectionEnd

Section "Start Menu Shortcuts" SecStartMenu
  SetShellVarContext all
  CreateDirectory "$SMPROGRAMS\${PRODUCT_NAME}"
  CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\${PRODUCT_NAME}.lnk" "$INSTDIR\autocoder.exe" "" "$INSTDIR\autocoder.exe" 0
  CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Uninstall.lnk" "$INSTDIR\Uninstall.exe" "" "$INSTDIR\Uninstall.exe" 0
  CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\README.lnk" "$INSTDIR\README.md"
SectionEnd

Section "Desktop Shortcut" SecDesktop
  SetShellVarContext all
  CreateShortCut "$DESKTOP\${PRODUCT_NAME}.lnk" "$INSTDIR\autocoder.exe" "" "$INSTDIR\autocoder.exe" 0
SectionEnd

Section /o "Add to PATH" SecPath
  ; Add installation directory to system PATH
  EnVar::SetHKLM
  EnVar::AddValue "PATH" "$INSTDIR"
SectionEnd

;--------------------------------
; Section Descriptions

!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${SecCore} "Core AutoCoder application files (required)"
  !insertmacro MUI_DESCRIPTION_TEXT ${SecStartMenu} "Create shortcuts in Start Menu"
  !insertmacro MUI_DESCRIPTION_TEXT ${SecDesktop} "Create shortcut on Desktop"
  !insertmacro MUI_DESCRIPTION_TEXT ${SecPath} "Add AutoCoder to system PATH (allows running from command line)"
!insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
; Uninstaller Section

Section "Uninstall"
  ; Remove files
  Delete "$INSTDIR\autocoder.exe"
  Delete "$INSTDIR\README.md"
  Delete "$INSTDIR\LICENSE"
  Delete "$INSTDIR\PACKAGING.md"
  Delete "$INSTDIR\WINDOWS_BUILD.md"
  Delete "$INSTDIR\qt.conf"
  Delete "$INSTDIR\Uninstall.exe"

  ; Remove DLLs
  Delete "$INSTDIR\Qt6*.dll"
  Delete "$INSTDIR\libssl*.dll"
  Delete "$INSTDIR\libcrypto*.dll"
  Delete "$INSTDIR\libcurl*.dll"
  Delete "$INSTDIR\msvcp*.dll"
  Delete "$INSTDIR\vcruntime*.dll"

  ; Remove plugins
  Delete "$INSTDIR\plugins\platforms\qwindows.dll"
  Delete "$INSTDIR\plugins\styles\qwindowsvistastyle.dll"
  RMDir "$INSTDIR\plugins\platforms"
  RMDir "$INSTDIR\plugins\styles"
  RMDir "$INSTDIR\plugins"

  ; Remove resources
  RMDir /r "$INSTDIR\resources"

  ; Remove shortcuts
  SetShellVarContext all
  Delete "$SMPROGRAMS\${PRODUCT_NAME}\${PRODUCT_NAME}.lnk"
  Delete "$SMPROGRAMS\${PRODUCT_NAME}\Uninstall.lnk"
  Delete "$SMPROGRAMS\${PRODUCT_NAME}\README.lnk"
  RMDir "$SMPROGRAMS\${PRODUCT_NAME}"
  Delete "$DESKTOP\${PRODUCT_NAME}.lnk"

  ; Remove from PATH if it was added
  EnVar::SetHKLM
  EnVar::DeleteValue "PATH" "$INSTDIR"

  ; Remove registry keys
  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "Software\${PRODUCT_NAME}"

  ; Remove installation directory
  RMDir "$INSTDIR"

SectionEnd

;--------------------------------
; Installer Functions

Function .onInit
  ; Check if already installed
  ReadRegStr $R0 ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString"
  StrCmp $R0 "" done

  MessageBox MB_OKCANCEL|MB_ICONEXCLAMATION \
    "${PRODUCT_NAME} is already installed.$\n$\nClick OK to remove the previous version or Cancel to cancel this installation." \
    IDOK uninst
  Abort

uninst:
  ClearErrors
  ExecWait '$R0 _?=$INSTDIR'

done:
FunctionEnd

Function .onInstSuccess
  MessageBox MB_OK "${PRODUCT_NAME} has been successfully installed!"
FunctionEnd
