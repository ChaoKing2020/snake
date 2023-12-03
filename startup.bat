@echo off
chcp 65001
title snake

cd %~dp0

IF "%1"=="pkg" (
	g++ src/*.cpp -shared -fPIC -osnake.dll -leasyx -lole32 -lgdi32
    g++ -L. -lsnake main.cpp -osnake && snake
)

IF "%1"=="run" (
	g++ src/*.cpp main.cpp -leasyx -lole32 -lgdi32 -osnake && snake
)

IF "%1"=="git" (
    git add .
    git commit -m '#'
    git push origin master
)

IF "%1"=="clean" (
    git rm -r --cached .
)