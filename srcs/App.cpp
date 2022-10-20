#include "App.hpp"

App::App() {
    Environment glEnvironment;
    Shader shader;
    Vertex vertex;

    renderLoop(glEnvironment.getWindow(), shader.getShaderProgram(), vertex.getVAO());
}

App::~App() {
    quit();
}

void App::renderLoop(GLFWwindow* window, unsigned int shaderProgram, unsigned int VAO) {
    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        glfwSwapBuffers(window);

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();
    }
}

void App::processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void App::quit() {
    glfwTerminate();
    exit(EXIT_SUCCESS);
}