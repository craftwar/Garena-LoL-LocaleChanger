echo off
IF [%1] NEQ [] (
	set base=%~1
) ELSE (
	set base=%cd%
)
move "%base%\backup_zh_TW\zh_TW-assets.wad" "%base%\GameData\Apps\LoLTW\LeagueClient\Plugins\rcp-be-lol-game-data\zh_TW-assets.wad"
move "%base%\backup_zh_TW\LogitechGkey.dll" "%base%\GameData\Apps\LoLTW\Game\LogitechGkey.dll" 
move "%base%\backup_zh_TW\LogitechLed.dll" "%base%\GameData\Apps\LoLTW\Game\LogitechLed.dll"