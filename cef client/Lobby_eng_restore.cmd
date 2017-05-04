echo off
IF [%1] NEQ [] (
	set base=%~1
) ELSE (
	set base=%cd%
)
move "%base%\backup_zh_TW" "%base%\GameData\Apps\LoLTW\LeagueClient\Plugins\rcp-be-lol-game-data\zh_TW-assets.wad"