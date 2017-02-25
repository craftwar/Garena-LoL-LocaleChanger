echo off
IF [%1] NEQ [] (
	set base=%~1
) ELSE (
	set base=%cd%
)
set base
mklink /H "%base%\GameData\Apps\LoLTW\Air\css\fonts_en_US.swf" "%base%\GameData\Apps\LoLTW\Air\css\fonts_zh_TW.swf"
copy /Y locale.properties "%base%\GameData\Apps\LoLTW\Air\locale.properties"