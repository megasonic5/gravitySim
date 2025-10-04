#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <vector>
#ifndef M_PI
#define M_PI 3.141592653589
#endif

float screenWidth = 800.0f;
float screenHeight = 600.0f;

GLFWwindow* StartGLFW();
void DrawCircle(float centerX, float centerY, float radius, int res);

class Object {
    public:
    std::vector<float> position;
    std::vector<float> velocity;
    float radius;
    Object(std::vector<float> position, std::vector<float> velocity, float radius = 15.0f) {
        this->position = position;
        this->velocity = velocity;
        this->radius = radius;
    }

    void accelerate(float x, float y) {
        this->velocity[0] += x;
        this->velocity[1] += y;
    }

    void updatePos() {
        this->position[0] += this->velocity[0];
        this->position[1] += this->velocity[1];
    }

    void DrawCircle(float centerX, float centerY, float radius, int res) {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2d(centerX, centerY);
        for (int i=0;i<=res;++i) {
            float angle = 2.0f * M_PI * (static_cast<float>(i) / res);
            float x = centerX + cos(angle) * radius;
            float y = centerY + sin(angle) * radius;
            glVertex2d(x, y);
        }
        glEnd();
    }
};

int main() {
    GLFWwindow* window = StartGLFW();
    float centerX = screenWidth / 2.0f;
    float centerY = screenHeight / 2.0f;
    float radius = 50.0f;
    int res = 100;
    std::vector<Object> objs = {
        Object(std::vector<float>{200.0f, 500.0f}, std::vector<float>{5.0f, 0.0f}),
        Object(std::vector<float>{700.0f, 500.0f}, std::vector<float>{5.0f, 0.0f})
    };
    std::vector<float> position = {400.0f, 300.0f};
    std::vector<float> velocity = {0.0f, 0.0f};
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        for (auto& obj : objs) {
            obj.accelerate(0.0f, -9.81);
            obj.updatePos();
            obj.DrawCircle(obj.position[0], obj.position[1], obj.radius, res);
            if (obj.position[1] < -obj.radius) {
                obj.velocity[1] *= -0.95;
            }
            if (obj.position[0] < -obj.radius || (obj.position[0] + obj.radius) > screenWidth) {
                obj.velocity[0] *= -0.95;
            }
        }
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