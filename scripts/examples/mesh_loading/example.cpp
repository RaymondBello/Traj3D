#include <glad/glad.h> // GLAD: https://github.com/Dav1dde/glad ... GLAD 2 also works via the web-service: https://gen.glad.sh/ (leaving all checkbox options unchecked)
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// OpenGL Mathematics(GLM) ... https://github.com/g-truc/glm/blob/master/manual.md
// ------------------------------------
// GLM Headers
// ------------------
#include <glm/glm.hpp>                  // Include all GLM core.
                                        // #include <glm/ext.hpp> // Include all GLM extensions.
#include <glm/gtc/matrix_transform.hpp> // Specific extensions.
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>main
#include <iostream>
#include <fstream> // Used in "shader_configure.h" to read the shader text files.

#include "load_model_meshes.h"
#include "shader_configure.h" // Used to create the shaders.

int main()
{
    // (1) GLFW: Initialise & Configure
    // -----------------------------------------
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_SAMPLES, 4); // Anti-aliasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    int monitor_width = mode->width; // Monitor's width.
    int monitor_height = mode->height;

    int window_width = (int)(monitor_width * 0.75f);   // Window size will be 50% the monitor's size...
    int window_height = (int)(monitor_height * 0.75f); // ... Cast is simply to silence the compiler warning.

    GLFWwindow *window = glfwCreateWindow(window_width, window_height, "Assimp Model Loading - Blender Object Files", NULL, NULL);
    // GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Assimp Model Loading - Blender Object Files", glfwGetPrimaryMonitor(), NULL); // Full Screen Mode ("Alt" + "F4" to Exit!)

    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window); // Set the window to be used and then centre that window on the monitor.
    glfwSetWindowPos(window, (monitor_width - window_width) / 2, (monitor_height - window_height) / 2);

    glfwSwapInterval(1); // Set VSync rate 1:1 with monitor's refresh rate.

    // (2) GLAD: Load OpenGL Function Pointers
    // -------------------------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // For GLAD 2 use the following instead: gladLoadGL(glfwGetProcAddress)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glEnable(GL_DEPTH_TEST);  // Enabling depth testing allows rear faces of 3D objects to be hidden behind front faces.
    glEnable(GL_MULTISAMPLE); // Anti-aliasing
    glEnable(GL_BLEND);       // GL_BLEND for OpenGL transparency which is further set within the fragment shader.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // (3) Compile Shaders Read from Text Files
    // ------------------------------------------------------
    const char *vert_shader = "../../Shaders/shader_glsl.vert";
    const char *frag_shader = "../../Shaders/shader_glsl.frag";

    Shader main_shader(vert_shader, frag_shader);
    main_shader.use();

    unsigned int view_matrix_loc = glGetUniformLocation(main_shader.ID, "view");
    unsigned int projection_matrix_loc = glGetUniformLocation(main_shader.ID, "projection");
    unsigned int camera_position_loc = glGetUniformLocation(main_shader.ID, "camera_position");

    glm::vec3 camera_position(0.0f, 0.0f, 3.0f); // -Z is into the screen.
    glm::vec3 camera_target(0.0f, 0.0f, 0.0f);
    glm::vec3 camera_up(0.0f, 1.0f, 0.0f);

    glUniform3f(camera_position_loc, camera_position.x, camera_position.y, camera_position.z);

    glm::mat4 view = glm::lookAt(camera_position, camera_target, camera_up);
    glUniformMatrix4fv(view_matrix_loc, 1, GL_FALSE, glm::value_ptr(view)); // Uniform: Transfer view matrix to vertex shader.

    glm::mat4 projection = glm::perspective(glm::radians(55.0f), (float)window_width / (float)window_height, 0.1f, 100.0f);
    glUniformMatrix4fv(projection_matrix_loc, 1, GL_FALSE, glm::value_ptr(projection));

    // (4) Enter the Main-Loop
    // --------------------------------
    srand((unsigned)time(NULL)); // Initialise random seed.

    float x_spin = 1.0f / (rand() % 10 + 1); // Generate random number between 1 and 10
    float y_spin = 1.0f / (rand() % 10 + 1);
    float z_spin = 1.0f / (rand() % 10 + 1);
    float spin_speed = (float)(rand() % 5 + 1); // Cast is simply to silence the compiler warning.

    float spin_vary = 0.0f;
    int spin_dir = 1;

    glm::mat4 spinning_mat(1.0f);

    unsigned int animate_loc = glGetUniformLocation(main_shader.ID, "animate");

    // https://www.turbosquid.com/Search/3D-Models/free/commercial (Free Models)
    // ----------------------------------------------------------------------------------------
    Model model_testing("model_testing.obj");
    Model black_smith("black_smith.obj");
    // Model model("The_Beast_Helicopter.obj");
    // Model model("Plane_CAP_232.obj");

    glActiveTexture(GL_TEXTURE0); // Reusing the same texture unit for each model mesh.
    unsigned int image_sampler_loc = glGetUniformLocation(main_shader.ID, "image");
    glUniform1i(image_sampler_loc, 0);

    while (!glfwWindowShouldClose(window)) // Main-Loop
    {
        // (5) Randomise the Model's Spinning Speed & Axis
        // ------------------------------------------------------------------
        spin_vary += 0.05f * spin_dir;

        if (spin_vary > 6 || spin_vary < 0)
        {
            spin_dir = -spin_dir; // Reverse the spinning direction.

            x_spin = 1.0f / (rand() % 10 + 1);
            y_spin = 1.0f / (rand() % 10 + 1);
            z_spin = 1.0f / (rand() % 10 + 1);
            spin_speed = (float)(rand() % 50 + 1) / 20;
            // std::cout << "\n   Spin speed: " << spin_speed;
        }

        spinning_mat = glm::rotate(spinning_mat, glm::radians(spin_speed), glm::normalize(glm::vec3(x_spin, y_spin, z_spin)));
        glUniformMatrix4fv(animate_loc, 1, GL_FALSE, glm::value_ptr(spinning_mat)); // Pass rotation matrix to vertex shader.

        // (6) Clear the Screen & Draw Model Meshes
        // ---------------------------------------------------------
        glClearColor(0.30f, 0.55f, 0.65f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (unsigned int i = 0; i < model_testing.num_meshes; ++i)
        {
            glBindTexture(GL_TEXTURE_2D, model_testing.mesh_list[i].tex_handle); // Bind texture for the current mesh.

            glBindVertexArray(model_testing.mesh_list[i].VAO);
            glDrawElements(GL_TRIANGLES, (GLsizei)model_testing.mesh_list[i].vert_indices.size(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
        for (unsigned int i = 0; i < black_smith.num_meshes; ++i)
        {
            glBindTexture(GL_TEXTURE_2D, black_smith.mesh_list[i].tex_handle); // Bind texture for the current mesh.

            glBindVertexArray(black_smith.mesh_list[i].VAO);
            glDrawElements(GL_TRIANGLES, (GLsizei)black_smith.mesh_list[i].vert_indices.size(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // (7) Exit the Application
    // ------------------------------
    glDeleteProgram(main_shader.ID); // This OpenGL function call is talked about in: shader_configure.h

    /* glfwDestroyWindow(window) // Call this function to destroy a specific window */
    glfwTerminate(); // Destroys all remaining windows and cursors, restores modified gamma ramps, and frees resources.

    exit(EXIT_SUCCESS); // Function call: exit() is a C/C++ function that performs various tasks to help clean up resources.
}