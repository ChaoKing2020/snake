@echo off

cd %~dp0

@rem windres -i ico.rc -o ico-out.o # 将ico.rc目录下的资源文件转为二进制

IF "%1"=="pkg" (
	g++ src/*.cpp -shared -fPIC -olibsnake.dll -leasyx -lole32 -lgdi32
    g++ -L. -lsnake main.cpp -osnake2 && snake2
)

IF "%1"=="run" (
	g++ src/*.cpp -Iheader -Llib -leasyx -lole32 -lgdi32 -o build/snake
)

IF "%1"=="static" (
	g++ src/*.cpp static/favicon.o -Iheader -Llib -leasyx -lole32 -lgdi32 -o build/snake -static
)


IF "%1"=="git" (
    git add .
    git commit -m '#'
    git push origin master
)

IF "%1"=="clean" (
    git rm -r --cached .
)
