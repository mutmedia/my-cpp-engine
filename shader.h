#ifndef SHADER_H
#define SHADER_H

#include <SDL_opengles2.h>

#include "common.h"

class Shader : nocopy {
    public:
        Shader(const char* vert, const char* frag);
        ~Shader();

        GLint uniform_time() { return uniform_time_; } 
        GLint uniform_screenSize() { return uniform_screenSize_; } 
        GLint uniform_mvp() { return uniform_mvp_; }
        GLuint id() { return id_; }

    private:
        GLuint id_;

        // default uniforms
        GLint uniform_time_;
        GLint uniform_screenSize_;
        GLint uniform_mvp_;
};

#endif
