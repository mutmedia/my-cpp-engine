// Custom headers
#include "common.h"
#include "glutils.h"
#include "window.h"
//#include "events.h"
#include "input.h"

// STD
#include <functional>

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
    glm::vec3 position;
    //GLfloat color[4];
  };

  struct Camera {
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 up;
  } ;
}


using namespace std;
function<void()> game_loop;
void main_loop() { 
  game_loop(); 
}

int main() {
  if(SDL_Init(SDL_INIT_VIDEO) < 0) { FAIL("SDL Init"); }
  SDL_GL_SetSwapInterval(0);

  // Camera stuff
  
  Camera camera;
  camera.position = glm::vec3(0, 0, 3);
  camera.up = glm::vec3(0, 1, 0);
  camera.direction = glm::vec3(0, 0, -1);

  // Initialize events
  SDL_KeyMapping km[4] = {
      {SDLK_w, "up"},
      {SDLK_s, "down"},
      {SDLK_a, "left"},
      {SDLK_d, "right"},
  };
  InputHandler *playerInput = new InputHandler(km, 4);

  playerInput->BindAction("up", INPUT_HOLD, [&](){
      camera.position += glm::vec3(0, 0, -0.1);
  });
  playerInput->BindAction("down", INPUT_HOLD, [&](){
      camera.position += glm::vec3(0, 0, +0.1);
  });
  playerInput->BindAction("left", INPUT_HOLD, [&](){
      camera.position += glm::vec3(-0.1, 0, 0);
  });
  playerInput->BindAction("right", INPUT_HOLD, [&](){
      camera.position += glm::vec3(+0.1, 0, 0);
  });

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
  GLint uniform_mvp = glGetUniformLocation(shaderProgram->id, "u_mvp");
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
        case SDL_KEYDOWN: 
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
      playerInput->ProcessEvent(&event);
    }

    playerInput->Update();

    if(window->visible) {

      function<void()> renderFunc = [&] {
        // Set Shapes

        VertexAttributes vertices[6];
        int vertices_size = 6;
        vertices[0].position = glm::vec3( -1.0f, -1.0f, 0.0f);
        vertices[1].position = glm::vec3( -1.0f,  1.0f, 0.0f);
        vertices[2].position = glm::vec3(  1.0f,  1.0f, 0.0f);
        vertices[3].position = glm::vec3(  1.0f,  1.0f, 0.0f);
        vertices[4].position = glm::vec3( -1.0f, -1.0f, 0.0f);
        vertices[5].position = glm::vec3(  1.0f, -1.0f, 0.0f);

        // Creating MVP matrix
        glm::mat4 Projection = glm::perspective(
            glm::radians(45.0f),
            (float) window->width / (float) window->height,
            0.1f,
            100.0f);

        glm::mat4 View = glm::lookAt(
            camera.position,
            camera.position + camera.direction,
            camera.up);

        glm::mat4 Model = glm::mat4(1.0f);

        glm::mat4 MVP = Projection * View * Model;

        // Render Shapes
        glUseProgram(shaderProgram->id);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        GLERRORS("use program");

        glBindBuffer(GL_ARRAY_BUFFER, vbo.id);
        glBufferData(GL_ARRAY_BUFFER, 
            sizeof(VertexAttributes) * vertices_size,
            vertices,
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
        glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, &MVP[0][0]);
        GLERRORS("glUniformMatrix4fv");

        GLfloat screenSize[] = {
          static_cast<GLfloat>(window->width),
          static_cast<GLfloat>(window->height)
        };
        glUniform2fv(uniform_screenSize, 1, screenSize);
        GLERRORS("glUniform2fv");

        glUniform1f(uniform_time, (float)window->FRAME);
        glEnableVertexAttribArray(attribute_position);
        //glEnableVertexAttribArray(attribute_color);

        glDrawArrays(GL_TRIANGLES, 0, vertices_size);
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

