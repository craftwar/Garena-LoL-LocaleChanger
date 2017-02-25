rem echo off
Setlocal EnableDelayedExpansion
IF [%1] NEQ [] (
	set base = %~1
) ELSE (
	set base = %cd%
)

rem dir "!base!\GameData\Apps\LoLTW\Air\css\fonts_en_US.swf"
mklink /H "%1\GameData\Apps\LoLTW\Air\css\fonts_en_US.swf" "%1\GameData\Apps\LoLTW\Air\css\fonts_zh_TW.swf"
copy /Y locale.properties "%1\GameData\Apps\LoLTW\Air\locale.properties"