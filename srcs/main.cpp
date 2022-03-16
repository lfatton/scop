#include <scop.h>

void render_loop(GLFWwindow* window) {
    while(!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

int main() {
    Environment environment;

    GLFWwindow* window = environment.init_glfw();
    environment.init_glad();
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    render_loop(window);

    environment.quit();
    return 0;
}