#include <scop.h>

void render_loop(GLFWwindow* window) {
    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        glfwSwapBuffers(window);

        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
    }
}

int main() {
    Environment environment;

    GLFWwindow* window = environment.init_glfw();
    environment.init_glad();
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glClearColor(0.576, 0.439, 0.859, 1);

    render_loop(window);

    environment.quit();
    return 0;
}