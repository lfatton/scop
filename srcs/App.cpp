#include "App.hpp"

App::App() {
    this->glEnvironment.init();
    this->mSpeed = 0.5f;
    this->mCanChangeSpeed = true;
    glEnable(GL_DEPTH_TEST);
}

App::~App() {
    App::quit();
}

void App::renderLoop() {
    Shader shader;
    Matrix model;

    glfwSetCursorPosCallback(this->glEnvironment.window, [](GLFWwindow* window, double xPos, double yPos) {
       camera.rotate((float)xPos, (float)yPos);
    });

    glfwSetScrollCallback(this->glEnvironment.window, [](GLFWwindow* window, double xOffset, double yOffset){
        camera.zoom((float)yOffset);
    });

    while(!glfwWindowShouldClose(this->glEnvironment.window)) {

        processInput(this->glEnvironment.window);
        Matrix view = Matrix::getLookAtMatrix(camera.xAxis, camera.yAxis, camera.zAxis, camera.position);
        Matrix projection = Matrix::getPerspectiveMatrix(camera.zoomValue,
                                                         (float)WINDOW_W / (float)WINDOW_H,
                                                         0.1f,
                                                         100.f);

        if (this->mSpeedVariation != 0.f && this->mCanChangeSpeed) {
            this->mSpeed = std::clamp(this->mSpeed + this->mSpeedVariation, -3.f, 3.f);
            this->mCanChangeSpeed = false;
        }

        glClearColor(0.576f, 0.439f, 0.859f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader.shaderProgram);

        auto timeValue = static_cast<float>(glfwGetTime());
        float damage = 1.f;
        
        auto variatorValue = std::modf(timeValue * mSpeed, &damage);
        int vertexColorLocation = glGetUniformLocation(shader.shaderProgram, "variator");
        glUniform1f(vertexColorLocation, variatorValue);

        Matrix mvp = projection * view * model;

        int mvpLoc = glGetUniformLocation(shader.shaderProgram, "mvp");

        glUniformMatrix4fv(mvpLoc, 1, GL_TRUE, mvp.getArrayReference());

        this->obj.draw();
        glfwSwapBuffers(this->glEnvironment.window);
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
        this->mSpeedVariation = 0.1f;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        this-> mSpeedVariation = -0.1f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE) {
        this-> mCanChangeSpeed = true;
        this->mSpeedVariation = 0.f;
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera.move(FORWARD, this->mSpeed);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.move(BACKWARD, this->mSpeed);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camera.move(LEFT, this->mSpeed);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera.move(RIGHT, this->mSpeed);
}

void App::quit() {
    glfwTerminate();
    exit(EXIT_SUCCESS);
}