@echo off
start /b node server.js
timeout /t 2
start chrome.exe "http://localhost:8080"