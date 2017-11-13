@ECHO off
set compiler=em++
set files=^
camera.cpp ^
events.cpp ^
game-mario.cpp ^
glutils.cpp ^
glm_extensions.cpp ^
graphics.cpp ^
input_manager.cpp ^
keyboard_input.cpp ^
mouse_input.cpp ^
main.cpp ^
mesh.cpp ^
shader.cpp ^
scheduler.cpp ^
time.cpp ^
window.cpp 
set std=-std=c++11
set opt=-Oz
set flags=-s USE_SDL=2 --use-preload-plugins -s USE_SDL_IMAGE=2 --preload-file assets
set output=build\index.html

@ECHO on
%compiler% %files% %std% %opt% %flags% -o %output%
