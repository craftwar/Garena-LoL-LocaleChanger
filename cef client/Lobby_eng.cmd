echo off
IF [%1] NEQ [] (
	set base=%~1
) ELSE (
	set base=%cd%
)
md "%base%\backup_zh_TW"
move "%base%\GameData\Apps\LoLTW\LeagueClient\Plugins\rcp-be-lol-game-data\zh_TW-assets.wad" "%base%\backup_zh_TW"