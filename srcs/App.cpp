#include "App.hpp"

App::App() {
    Environment glEnvironment;
    Shader shader("../shaders/shader.vert", "../shaders/shader.frag");
    Vertex vertex;
    mSpeed = 0.5f;
    mCanChangeSpeed = true;
    glEnable(GL_DEPTH_TEST);

    renderLoop(glEnvironment.window, shader.shaderProgram, vertex);
}

App::~App() {
    quit();
}

void App::renderLoop(GLFWwindow* window, unsigned int shaderProgram, const Vertex& vertex) {
    Matrix model;

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) {
       camera.rotate((float)xPos, (float)yPos);
    });

    glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset)
    {
        camera.zoom((float)yOffset);
    });


//    int i = 0;
//    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
//    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        Matrix view = Matrix::getLookAtMatrix(camera.xAxis, camera.yAxis, camera.zAxis, camera.position);
        Matrix projection = Matrix::getPerspectiveMatrix(camera.zoomValue, (float)WINDOW_W / (float)WINDOW_H, 0.1f, 100.f);

//        glm::mat4 lookAt = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
//        if (i == 0) {
//            std::cout << "MODEL   " << glm::to_string(lookAt) << std::endl;
//
//            view.printToConsole();
//
//            i++;
//        }

        if (mSpeedVariation != 0.f && mCanChangeSpeed) {
            mSpeed = std::clamp(mSpeed + mSpeedVariation, -3.f, 3.f);
            mCanChangeSpeed = false;
        }

        glClearColor(0.576f, 0.439f, 0.859f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);

        auto timeValue = static_cast<float>(glfwGetTime());
        float damage = 1.f;
        
        auto variatorValue = std::modf(timeValue * mSpeed, &damage);
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "variator");
        glUniform1f(vertexColorLocation, variatorValue);

        Matrix mvp = projection * view * model;

        int mvpLoc = glGetUniformLocation(shaderProgram, "mvp");

        glUniformMatrix4fv(mvpLoc, 1, GL_TRUE, mvp.getArrayReference());

        glBindVertexArray(vertex.vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);

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
        mSpeedVariation = 0.1f;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        mSpeedVariation = -0.1f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE) {
        mCanChangeSpeed = true;
        mSpeedVariation = 0.f;
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera.move(FORWARD, mSpeed);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.move(BACKWARD, mSpeed);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camera.move(LEFT, mSpeed);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera.move(RIGHT, mSpeed);
}

void App::quit() {
    glfwTerminate();
    exit(EXIT_SUCCESS);
}