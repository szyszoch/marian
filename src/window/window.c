#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "window.h"

static GLFWwindow *window = NULL;

static void resize_callback(GLFWwindow* window, int width, int height)
{
    (void)window; // it is used to remove warnings about not using variable
    glViewport(0, 0, width, height);
}

int window_init(const char *t, int w, int h)
{
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(w, h, t, NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        glfwTerminate();
        return -1;
    }
    glViewport(0, 0, w, h);
    glfwSetWindowSizeCallback(window, resize_callback);
    glfwSwapInterval(1);
    return 0;
}

void window_destroy()
{
    glfwTerminate();
}

void window_update()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

int window_is_open()
{
    return !glfwWindowShouldClose(window);
}

int window_pressed_right_arrow()
{
    return glfwGetKey(window, GLFW_KEY_RIGHT);
}

int window_pressed_left_arrow()
{
    return glfwGetKey(window, GLFW_KEY_LEFT);
}

int window_pressed_down_arrow()
{
    return glfwGetKey(window, GLFW_KEY_DOWN);
}

int window_pressed_up_arrow()
{
    return glfwGetKey(window, GLFW_KEY_UP);
}

int window_pressed_escape()
{
    return glfwGetKey(window, GLFW_KEY_ESCAPE);
}