// Custom headers
#include "common.h"
#include "glutils.h"
#include "window.h"
//#include "events.h"
#include "time.h"
#include "game.h"
#include "input.h"
#include "mesh.h"


// STD
#include <functional>
#include <math.h>

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
#include "glm/gtc/quaternion.hpp" // Quaternioon
#include "glm/gtx/quaternion.hpp"

#define GL_GLEXT_PROTOTYPES 1
#include <SDL2/SDL_opengles2.h>

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

static const Vertex vertex_data[] = {
  {{-1.0f, -1.0f, -1.0f,},	 {0.583f, 0.771f, 0.014f,}},
  {{-1.0f, -1.0f, +1.0f,},	 {0.609f, 0.115f, 0.436f,}},
  {{-1.0f, +1.0f, +1.0f,},	 {0.327f, 0.483f, 0.844f,}},
  {{+1.0f, +1.0f, -1.0f,},	 {0.822f, 0.569f, 0.201f,}},
  {{-1.0f, -1.0f, -1.0f,},	 {0.435f, 0.602f, 0.223f,}},
  {{-1.0f, +1.0f, -1.0f,},	 {0.310f, 0.747f, 0.185f,}},
  {{+1.0f, -1.0f, +1.0f,},	 {0.597f, 0.770f, 0.761f,}},
  {{-1.0f, -1.0f, -1.0f,},	 {0.559f, 0.436f, 0.730f,}},
  {{+1.0f, -1.0f, -1.0f,},	 {0.359f, 0.583f, 0.152f,}},
  {{+1.0f, +1.0f, -1.0f,},	 {0.483f, 0.596f, 0.789f,}},
  {{+1.0f, -1.0f, -1.0f,},	 {0.559f, 0.861f, 0.639f,}},
  {{-1.0f, -1.0f, -1.0f,},	 {0.195f, 0.548f, 0.859f,}},
  {{-1.0f, -1.0f, -1.0f,},	 {0.014f, 0.184f, 0.576f,}},
  {{-1.0f, +1.0f, +1.0f,},	 {0.771f, 0.328f, 0.970f,}},
  {{-1.0f, +1.0f, -1.0f,},	 {0.406f, 0.615f, 0.116f,}},
  {{+1.0f, -1.0f, +1.0f,},	 {0.676f, 0.977f, 0.133f,}},
  {{-1.0f, -1.0f, +1.0f,},	 {0.971f, 0.572f, 0.833f,}},
  {{-1.0f, -1.0f, -1.0f,},	 {0.140f, 0.616f, 0.489f,}},
  {{-1.0f, +1.0f, +1.0f,},	 {0.997f, 0.513f, 0.064f,}},
  {{-1.0f, -1.0f, +1.0f,},	 {0.945f, 0.719f, 0.592f,}},
  {{+1.0f, -1.0f, +1.0f,},	 {0.543f, 0.021f, 0.978f,}},
  {{+1.0f, +1.0f, +1.0f,},	 {0.279f, 0.317f, 0.505f,}},
  {{+1.0f, -1.0f, -1.0f,},	 {0.167f, 0.620f, 0.077f,}},
  {{+1.0f, +1.0f, -1.0f,},	 {0.347f, 0.857f, 0.137f,}},
  {{+1.0f, -1.0f, -1.0f,},	 {0.055f, 0.953f, 0.042f,}},
  {{+1.0f, +1.0f, +1.0f,},	 {0.714f, 0.505f, 0.345f,}},
  {{+1.0f, -1.0f, +1.0f,},	 {0.783f, 0.290f, 0.734f,}},
  {{+1.0f, +1.0f, +1.0f,},	 {0.722f, 0.645f, 0.174f,}},
  {{+1.0f, +1.0f, -1.0f,},	 {0.302f, 0.455f, 0.848f,}},
  {{-1.0f, +1.0f, -1.0f,},	 {0.225f, 0.587f, 0.040f,}},
  {{+1.0f, +1.0f, +1.0f,},	 {0.517f, 0.713f, 0.338f,}},
  {{-1.0f, +1.0f, -1.0f,},	 {0.053f, 0.959f, 0.120f,}},
  {{-1.0f, +1.0f, +1.0f,},	 {0.393f, 0.621f, 0.362f,}},
  {{+1.0f, +1.0f, +1.0f,},	 {0.673f, 0.211f, 0.457f,}},
  {{-1.0f, +1.0f, +1.0f,},	 {0.820f, 0.883f, 0.371f,}},
  {{+1.0f, -1.0f, +1.0f,},	 {0.982f, 0.099f, 0.879f}}
};
int vertices_size = 12 * 3;


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

  auto shaderProgram = new ShaderProgram(
      fileToSource("assets/shaders/base.vert"),
      fileToSource("assets/shaders/base.frag"));

  GLint attribute_position = glGetAttribLocation(shaderProgram->id, "a_position");
  GLint attribute_color = glGetAttribLocation(shaderProgram->id, "a_color");
  GLint uniform_mvp = glGetUniformLocation(shaderProgram->id, "u_mvp");
  GLint uniform_screenSize = glGetUniformLocation(shaderProgram->id, "u_screenSize");
  GLint uniform_time = glGetUniformLocation(shaderProgram->id, "u_time");

  bool main_loop_running = true;

  Game * game = new Game();


  // Proper Game initialization
  game->Initialize();
  Mesh cube(vertex_data, vertices_size);

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

        // Creating MVP matrix
        glm::mat4 ViewProjection = game->main_camera_->GetViewProjectionMatrix();

        glm::mat4 Model = glm::mat4(1.0f);

        glm::mat4 Translation = glm::translate(glm::mat4(), 3.0f* sin(glm::vec3(0.1f * (float)Window::Instance()->FRAME)));

        glm::mat4 MVP = ViewProjection * Model;

        // Setting shader
        glUseProgram(shaderProgram->id);
        GLERRORS("use program");

        // Setting configuration
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_CULL_FACE);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Uniforms
        glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, &MVP[0][0]);
        GLERRORS("glUniformMatrix4fv");

        GLfloat screenSize[] = {
          static_cast<GLfloat>(Window::Instance()->width),
          static_cast<GLfloat>(Window::Instance()->height)};
        glUniform2fv(uniform_screenSize, 1, screenSize);
        GLERRORS("glUniform2fv");

        glUniform1f(uniform_time, (float)Window::Instance()->FRAME);

        MVP = ViewProjection * Model;
        cube.Render();

        Model = Translation;
        MVP = ViewProjection * Model;
        glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, &MVP[0][0]);
        cube.Render();


        glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, &MVP[0][0]);
        GLERRORS("glUniformMatrix4fv");

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

  SDL_Quit();
}

