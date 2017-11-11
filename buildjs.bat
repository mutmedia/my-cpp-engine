@ECHO off
set compiler=em++
set files=^
camera.cpp ^
events.cpp ^
game.cpp ^
glutils.cpp ^
graphics.cpp ^
input.cpp ^
main.cpp ^
mesh.cpp ^
shader.cpp ^
time.cpp ^
window.cpp 
set std=-std=c++11
set opt=-Oz
set flags=-s USE_SDL=2 --use-preload-plugins -s USE_SDL_IMAGE=2 --preload-file assets
set output=build\index.html

@ECHO on
%compiler% %files% %std% %opt% %flags% -o %output%
