#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

float screenWidth = 800.0f;
float screenHeight = 600.0f;

GLFWwindow* StartGLFW();

int main() {
    GLFWwindow* window = StartGLFW();
    float centerX = screenWidth / 2.0f;
    float centerY = screenHeight / 2.0f;
    float radius = 50.0f;
    int res = 100;
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2d(centerX, centerY);
        for (int i=0;i<=res;++i) {
            float angle = 2.0f * 3.141592653589 * (static_cast<float>(i) / res);
            float x = centerX + cos(angle) * radius;
            float y = centerY + sin(angle) * radius;
            glVertex2d(x, y);
        }
        glEnd();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    return 0;
}

GLFWwindow* StartGLFW() {
    if (!glfwInit()) {
        std::cerr << "failed to initialize glfw, panic!" << std::endl;
        return nullptr;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    GLFWwindow* window = glfwCreateWindow(800, 600, "gravity_sim", NULL, NULL);
    glfwMakeContextCurrent(window);
    glOrtho(0, screenWidth, 0, screenHeight, -1, 1);
    return window;
}