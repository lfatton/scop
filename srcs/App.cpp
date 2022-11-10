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
    Vector rotationAxis(0.5f, 1.0f, 0.0f);
    Vector position;
    Vector target(0.0f, 0.0f, -1.0f);

    Matrix view;
    Matrix projection = Matrix::getPerspectiveMatrix(45.0f, (float)WINDOW_W / (float)WINDOW_H, 0.1f, 100.0f);
    Matrix model;
    Matrix mvp;

    const float radius = 5.0f;

    position = Vector(0.0f, 0.0f, 3.0f);
    Camera camera(position, target);

    while(!glfwWindowShouldClose(window)) {
        glEnable(GL_DEPTH_TEST);
        // input
        // -----
        processInput(window, camera);
        Camera updatedCam(camera.position, camera.target);
        camera = updatedCam;

        view = Matrix::getLookAtMatrix(camera.xAxis, camera.yAxis, camera.zAxis, position);

        if (mSpeedVariation != 0 && mCanChangeSpeed) {
            mSpeed = std::clamp(mSpeed + mSpeedVariation, -3.0f, 3.0f);
            mCanChangeSpeed = false;
        }
        // render
        // ------
        glClearColor(0.576f, 0.439f, 0.859f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);

        // update shader uniform
        auto timeValue = static_cast<float>(glfwGetTime());
        float damage = 1.0f;
        
        auto variatorValue = std::modf(timeValue * mSpeed, &damage);
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "variator");
        glUniform1f(vertexColorLocation, variatorValue);

        //rotate object
       // model = Matrix::getRotationMatrix((float)glfwGetTime() * 50.0f, rotationAxis);

//       //rotate view
//        position = Vector(sinf(timeValue) * radius, 0.0f, cosf(timeValue) * radius);
//        Camera camera(position, target);
//        view = Matrix::getLookAtMatrix(camera.xAxis, camera.yAxis, camera.zAxis, position);

        mvp = projection * view * model;

        int mvpLoc = glGetUniformLocation(shaderProgram, "mvp");
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, mvp.getArrayReference());

        // render the box
        glBindVertexArray(vertex.vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
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
        mSpeedVariation = 0.1;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        mSpeedVariation = -0.1;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE) {
        mCanChangeSpeed = true;
        mSpeedVariation = 0;
    }

    //move camera
    const float cameraSpeed = 0.05f;
    Vector y = Vector::getCrossProduct(camera.target, camera.yAxis);
    y.getUnitVector();

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