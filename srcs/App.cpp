#include "App.hpp"

App::App() {
    Environment glEnvironment;
    Shader shader("../shaders/shader.vert", "../shaders/shader.frag");
    Vertex vertex;
    mSpeed = 0.5f;
    mCanChangeSpeed = true;

    renderLoop(glEnvironment.window, shader.shaderProgram, vertex);
}

App::~App() {
    quit();
}

void App::renderLoop(GLFWwindow* window, unsigned int shaderProgram, const Vertex& vertex) {
    Vector position(0.f, 0.f, 3.f);
    Vector target(0.f, 0.f, -1.f);

    Matrix projection = Matrix::getPerspectiveMatrix(45.f, (float)WINDOW_W / (float)WINDOW_H, 0.1f, 100.f);
    Matrix model;

    Camera camera(position, target);

    while(!glfwWindowShouldClose(window)) {
        glEnable(GL_DEPTH_TEST);

        processInput(window, camera);
        Camera updatedCam(camera.position, camera.target);
        camera = updatedCam;

        Matrix view = Matrix::getLookAtMatrix(camera.xAxis, camera.yAxis, camera.zAxis, camera.position);

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

        float const *ref = mvp.getArrayReference();

        int mvpLoc = glGetUniformLocation(shaderProgram, "mvp");

        glUniformMatrix4fv(mvpLoc, 1, GL_TRUE, ref);

        glBindVertexArray(vertex.vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void App::processInput(GLFWwindow *window, Camera &camera) {
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

    const float cameraSpeed = 0.05f;
    Vector y = Vector::getCrossProduct(camera.target, camera.yAxis);
    y.normalise();

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera.position = camera.position + camera.target * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.position = camera.position - camera.target * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        camera.position = camera.position - y * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        camera.position = camera.position + y * cameraSpeed;
    }
}

void App::quit() {
    glfwTerminate();
    exit(EXIT_SUCCESS);
}