
cd %~dp0
cd ../
set destination=%cd%\x64\Debug

cd %~dp0

if not exist %destination%\metro\ (md %destination%\metro\)
xcopy metro %destination%\metro\ /Y /E
if not exist %destination%\platforms\ (md %destination%\platforms\)
xcopy platforms %destination%\platforms\ /Y /E
if not exist %destination%\qss\ (md %destination%\qss\)
xcopy qss %destination%\qss\ /Y /E
if not exist %destination%\resource\ (md %destination%\resource\)
xcopy resource %destination%\resource\ /Y /E
xcopy qt5dll %destination%\ /Y /E
xcopy CostMangement.VisualElementsManifest.xml %destination% /Y