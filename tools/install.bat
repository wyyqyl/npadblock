@echo off
reg add "HKLM\SOFTWARE\Wow6432Node\MozillaPlugins\@anvisoft.com/npadblock" /f /v Path /t REG_SZ /d "%~dp0npadblock.dll"
reg add "HKLM\SOFTWARE\Wow6432Node\MozillaPlugins\@anvisoft.com/npadblock\MimeTypes\application/x-adblock" /f
