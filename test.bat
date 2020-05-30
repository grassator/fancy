@echo off
call build
if %errorlevel% neq 0 (exit %errorlievel%)
build\spec
