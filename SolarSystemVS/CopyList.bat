@echo off
echo 复制运行项目所需文件...
set sys="233"
echo %sys%
if %sys%=="x86" goto x86
if %sys%=="x64" goto x64
:x86
	echo x86
	for /f %%v in (CopyList_x86.txt) do xcopy "%%v" "%1" /d /y
	goto end
:x64
	echo x64
	for /f %%v in (CopyList_x64.txt) do xcopy "%%v" "%1" /d /y
	goto end
:end