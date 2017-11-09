@ECHO off
set compiler=em++
set files=main.cpp events.cpp glutils.cpp input.cpp camera.cpp mesh.cpp renderer.cpp meshRenderer.cpp time.cpp window.cpp game.cpp 
set std=-std=c++11
set opt=-Oz
set flags=-s USE_SDL=2 --use-preload-plugins -s USE_SDL_IMAGE=2 --preload-file assets
set output=build\index.html

@ECHO on
%compiler% %files% %std% %opt% %flags% -o %output%
