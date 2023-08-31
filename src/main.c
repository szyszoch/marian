#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <stdio.h>
#include <texture.h>
#include <renderer.h>

void input(GLFWwindow* window) 
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(512, 480, "Marian", NULL, NULL);

    if (window == NULL) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize glad\n");
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 512, 480);

    renderer_init();

    sprite_t sprite = sprite_get(SPRITE_GROUND, PALETTE_OVERWORLD_GROUND_AND_STONE);
    texture_t texture1 = texture_load_image(&sprite);
    sprite_destroy(sprite);

    sprite = sprite_get(SPRITE_GROUND, PALETTE_UNDERGROUND_GROUND_AND_STONE);
    texture_t texture2 = texture_load_image(&sprite);
    sprite_destroy(sprite);

    vec2 pos1 = {128.0f,128.0f};
    vec2 size1 = {128.0f, 128.0f};

    vec2 pos2 = {256.0f,128.0f};
    vec2 size2 = {128.0f, 128.0f};

    while(!glfwWindowShouldClose(window)) {
        input(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        renderer_render(texture1, pos1, size1);
        renderer_render(texture2, pos2, size2);
    }

    glfwTerminate();
    return 0;
}