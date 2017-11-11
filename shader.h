#ifndef SHADER_H
#define SHADER_H

#include <SDL_opengles2.h>

class Shader {
    // default uniforms

    public:
    GLint uniform_time() { return uniform_time_;} 
    GLint uniform_screenSize() { return uniform_screenSize_;} 
    GLint uniform_mvp() { return uniform_mvp_; }

    private:
    GLint uniform_time_ = 2;
    GLint uniform_screenSize_ = 1;
    GLint uniform_mvp_ = 0;

}

#endif
