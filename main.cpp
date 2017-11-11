// Custom headers
#include "common.h"
#include "glutils.h"
#include "window.h"
//#include "events.h"
#include "time.h"
#include "game.h"
#include "input.h"
#include "mesh.h"
#include "shader.h"
#include "graphics.h"


// STD
#include <functional>
#include <math.h>

// System libraries
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <SDL.h>
#include <SDL_image.h>

#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4, glm::ivec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr
#include "glm/gtc/quaternion.hpp" // Quaternioon
#include "glm/gtx/quaternion.hpp"

#define GL_GLEXT_PROTOTYPES 1
#include <SDL_opengles2.h>

namespace {
  struct VertexAttributes {
    glm::vec3 position;
    //GLfloat color[4];
  };
}


using namespace std;
function<void()> game_loop;
void main_loop() { 
  game_loop(); 
}

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    FAIL("SDL Init");
  }
  SDL_GL_SetSwapInterval(0);
  Window::Initialize("test", 800, 600);

  Time::Init(SDL_GetTicks());

  // External shader data
  // Shader implementation
  auto fileToSource = [](const char *path) {
    // Converts file to char *
    FILE *fp;
    long lSize;
    char *buffer;

    fp = fopen(path, "rb");
    if (!fp)
    {
      FAIL("open file");
    }

    fseek(fp, 0L, SEEK_END);
    lSize = ftell(fp);
    rewind(fp);

    buffer = static_cast<char *>(calloc(1, lSize + 1));
    if (!buffer)
    {
      fclose(fp);
      FAIL("file memory allocation");
    }

    if (fread(buffer, lSize, 1, fp) != 1)
    {
      fclose(fp);
      FAIL("entire read failed");
    }

    fclose(fp);
    return buffer;
  };

  auto shaderProgram = new Shader(
      fileToSource("assets/shaders/base.vert"),
      fileToSource("assets/shaders/base.frag"));
      
  // Initialize graphics lib
  Graphics::camera = new Camera(45, 1, 0.1f, 100.0f);
  Graphics::shader = shaderProgram;

  bool main_loop_running = true;

  Game * game = new Game();

  // Proper Game initialization
  game->Load();

  game_loop = [&] {
    // Main loop implementation
    Time::Update(SDL_GetTicks());

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
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

      Window::Instance()->ProcessEvent(&event);
      Input::ProcessEvent(&event);
    }

    Input::Update();
    game->Update();

    if (Window::Instance()->visible)
    {

      function<void()> renderFunc = [&] {

        // Setting shader
        glUseProgram(shaderProgram->id());
        GLERRORS("use program");

        // Setting configuration
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        //glEnable(GL_CULL_FACE);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Uniforms
        GLfloat screenSize[] = {
          static_cast<GLfloat>(Window::Instance()->width),
          static_cast<GLfloat>(Window::Instance()->height)};
        glUniform2fv(shaderProgram->uniform_screenSize(), 1, screenSize);
        GLERRORS("glUniform2fv");

        glUniform1f(shaderProgram->uniform_time(), (float)Window::Instance()->FRAME);

        game->Draw();
        glDisable(GL_BLEND);
      };

      Window::Instance()->Render(renderFunc);
    }
  };

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(main_loop, 0, true);
#else
  while (main_loop_running)
  {
    main_loop();
  }
#endif

printf("exiting...\n");
  SDL_Quit();
}

