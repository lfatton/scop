#include "App.hpp"
#include <cmath>
#include <algorithm>

App::App() {
    Environment glEnvironment;
    Shader shader("../shaders/shader.vert", "../shaders/shader.frag");
    Vertex vertex;
    speed = 0.5;
    can_change_speed = true;

    renderLoop(glEnvironment.getWindow(), shader.getShaderProgram(), vertex);
}

App::~App() {
    quit();
}

void App::renderLoop(GLFWwindow* window, unsigned int shaderProgram, const Vertex& vertex) {
    Vector rotationAxis(0.5f, 1.0f, 0.0f);
    Matrix view;
    Matrix projection;
    Matrix model;
    Matrix mvp;

    view.getTranslationMatrix(0.0f, 0.0f, -3.0f);
    projection.getPerspectiveMatrix(45.0f, (float)WINDOW_W / (float)WINDOW_H, 0.1f, 100.0f);

    while(!glfwWindowShouldClose(window)) {
        glEnable(GL_DEPTH_TEST);
        // input
        // -----
        processInput(window);
        if (speed_variation != 0 && can_change_speed) {
            speed = std::clamp(speed + speed_variation, -3.0, 3.0);
            can_change_speed = false;
        }
        // render
        // ------
        glClearColor(0.576, 0.439, 0.859, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);

        // update shader uniform
        double timeValue = glfwGetTime();
        double dommage = 1.0;
        auto variatorValue = static_cast<float>(std::modf(timeValue * speed, &dommage));
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "variator");
        glUniform1f(vertexColorLocation, variatorValue);

        model.getRotationMatrix((float)glfwGetTime() * 50.0f, rotationAxis);
        mvp = projection * view * model;

        int mvpLoc = glGetUniformLocation(shaderProgram, "mvp");
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, mvp.getArrayReference());

        // render the box
        glBindVertexArray(vertex.getVAO());
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void App::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        speed_variation = 0.1;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        speed_variation = -0.1;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE) {
        can_change_speed = true;
        speed_variation = 0;
    }

}

void App::quit() {
    glfwTerminate();
    exit(EXIT_SUCCESS);
}