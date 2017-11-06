// Custom headers
#include "common.h"
#include "glutils.h"
#include "window.h"

// STD
#include <functional>
#include <vector>

// System libraries
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4, glm::ivec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

#define GL_GLEXT_PROTOTYPES 1
#include <SDL2/SDL_opengles2.h>

namespace {
  struct VertexAttributes {
    GLfloat position[3];
    //GLfloat color[4];
  };
}


using namespace std;
function<void()> game_loop;
void main_loop() { 
  game_loop(); 
}

int main() {
  if(SDL_Init(SDL_INIT_VIDEO) < 0) { FAIL("SDL Init"); }
  SDL_GL_SetSwapInterval(0);

  auto window = std::unique_ptr<Window>(new Window("test", 800, 600));

  // External shader data
  // Shader implementation
  auto fileToSource = [](const char* path) {
    // Converts file to char *
    FILE *fp;
    long lSize;
    char *buffer;

    fp = fopen(path, "rb");
    if(!fp) {FAIL("open file");}

    fseek(fp, 0L, SEEK_END);
    lSize = ftell(fp);
    rewind(fp);

    buffer = static_cast<char*>(calloc(1, lSize+1));
    if(!buffer) {
      fclose(fp);
      FAIL("file memory allocation");
    }

    if( fread(buffer, lSize, 1, fp) != 1) 
    {
      fclose(fp);
      FAIL("entire read failed");
    }

    fclose(fp);
    return buffer;
  };

  auto shaderProgram = new ShaderProgram(
      fileToSource("assets/shaders/base.vert"), 
      fileToSource("assets/shaders/base.frag")
      );

  GLint attribute_position = glGetAttribLocation(shaderProgram->id, "a_position");
  GLint attribute_color = glGetAttribLocation(shaderProgram->id, "a_color");
  GLint uniform_screenSize = glGetUniformLocation(shaderProgram->id, "u_screenSize");
  GLint uniform_time = glGetUniformLocation(shaderProgram->id, "u_time");

  VertexBuffer vbo;

  bool main_loop_running = true;

  game_loop = [&] {
    // Main loop implementation
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
      switch(event.type) {
        case SDL_QUIT: 
          {
            main_loop_running = false;
            break;
          }
        case SDL_KEYUP: 
          {
            int sym = event.key.keysym.sym;
            switch (sym) 
            {
              case (SDLK_ESCAPE):
              {
                main_loop_running = false;
                break;
              }
            }
          }
      }

      window->ProcessEvent(&event);
    }

    if(window->visible) {

      function<void()> renderFunc = [&] {
        // Set Shapes

        vector<VertexAttributes> vertices;
        vertices.resize(6);
        vertices[0].position[0] = -1.0f;
        vertices[0].position[1] = -1.0f;
        vertices[0].position[2] =  0.0f;

        vertices[1].position[0] = -1.0f;
        vertices[1].position[1] =  1.0f;
        vertices[1].position[2] =  0.0f;

        vertices[2].position[0] =  1.0f;
        vertices[2].position[1] =  1.0f;
        vertices[2].position[2] =  0.0f;

        vertices[3].position[0] =  1.0f;
        vertices[3].position[1] =  1.0f;
        vertices[3].position[2] =  0.0f;

        vertices[4].position[0] = -1.0f;
        vertices[4].position[1] = -1.0f;
        vertices[4].position[2] =  0.0f;

        vertices[5].position[0] =  1.0f;
        vertices[5].position[1] = -1.0f;
        vertices[5].position[2] =  0.0f;

        // Render Shapes
        glUseProgram(shaderProgram->id);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        GLERRORS("use program");

        glBindBuffer(GL_ARRAY_BUFFER, vbo.id);
        glBufferData(GL_ARRAY_BUFFER, 
            sizeof(VertexAttributes) * vertices.size(),
            vertices.data(),
            GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, vbo.id);

        // Attributes
        glVertexAttribPointer(attribute_position,
            3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributes),
            (GLvoid *) offsetof(VertexAttributes, position));
        /*
        glVertexAttribPointer(attribute_color,
            4, GL_FLOAT, GL_FALSE, sizeof(VertexAttributes),
            (GLvoid *) offsetof(VertexAttributes, color));
        */
        GLERRORS("glVertexAttribPointer");

        // Uniforms
        GLfloat screenSize[] = {
          static_cast<GLfloat>(window->width),
          static_cast<GLfloat>(window->height)
        };
        glUniform2fv(uniform_screenSize, 1, screenSize);
        GLERRORS("glUniform2fv");

        glUniform1f(uniform_time, (float)window->FRAME);
        glEnableVertexAttribArray(attribute_position);
        //glEnableVertexAttribArray(attribute_color);

        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        glEnableVertexAttribArray(attribute_position);
        GLERRORS("draw arrays");
        glDisableVertexAttribArray(attribute_position);
        glDisable(GL_BLEND);
      };

      window->Render(renderFunc);
    }
  };

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(main_loop, 0, true);
#else 
  while(main_loop_running)
  {
    main_loop();
  }
#endif

  window = nullptr;
  SDL_Quit();
}

