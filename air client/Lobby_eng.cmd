echo off
IF [%1] NEQ [] (
	set base=%~1
) ELSE (
	set base=%cd%
)
mklink /H "%base%\GameData\Apps\LoLTW\Air\css\fonts_en_US.swf" "%base%\GameData\Apps\LoLTW\Air\css\fonts_zh_TW.swf"
xcopy /K /Y "%~dp0locale.properties" "%base%\GameData\Apps\LoLTW\Air\locale.properties"*