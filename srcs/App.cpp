#include "App.hpp"

App::App() {
    this->glEnvironment.init();
    this->mSpeed = 0.5f;
    this->mColourSpeed = 0.5f;
    this->mCanChangeColourSpeed = true;
    glEnable(GL_DEPTH_TEST);

    App::printHelpToConsole();
}

App::~App() {
    for (GLuint texture: this->mTexture) {
        glDeleteTextures(1, &texture);
    }
    App::quit();
}

void App::setCallbacks() const {
    glfwSetCursorPosCallback(this->glEnvironment.window, [](GLFWwindow* window, double xPos, double yPos) {
        camera.rotate((float)xPos, (float)yPos);
    });

    glfwSetScrollCallback(this->glEnvironment.window, [](GLFWwindow* window, double xOffset, double yOffset){
        camera.zoom((float)yOffset);
    });

    glfwSetKeyCallback(this->glEnvironment.window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        if (key == GLFW_KEY_1 && action == GLFW_PRESS)
            currentGlMode = GL_FILL;
        if (key == GLFW_KEY_2 && action == GLFW_PRESS)
            currentGlMode = GL_LINE;
        if (key == GLFW_KEY_3 && action == GLFW_PRESS)
            currentGlMode = GL_POINT;

        if (key == GLFW_KEY_T && action == GLFW_PRESS) {
            switch (textIndex) {
                case 0:
                    textIndex = 1;
                    break;
                case 1:
                    textIndex = 2;
                    break;
                case 2:
                    textIndex = 0;
                    break;
                default:
                    break;
            }
        }

        if (key == GLFW_KEY_F && action == GLFW_PRESS)
            flatMode = !flatMode;

        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
            colourMode = !colourMode;
            greyscaleMode = false;
        }

        if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
            greyscaleMode = !greyscaleMode;
            colourMode = false;
        }
    });
}

void App::renderLoop() {
    Shader shader;

    int mvpLoc = glGetUniformLocation(shader.shaderProgram, "mvp");
    int flatModeLocation = glGetUniformLocation(shader.shaderProgram, "flatMode");
    int colourSpeedLocation = glGetUniformLocation(shader.shaderProgram, "colourSpeed");
    int colourModeLocation = glGetUniformLocation(shader.shaderProgram, "colourMode");
    int greyscaleModeLocation = glGetUniformLocation(shader.shaderProgram, "greyscaleMode");
    GLint textureID  = glGetUniformLocation(shader.shaderProgram, "givenTexture");

    LoaderBMP kittenBMP("../assets/textures/kitten.bmp");
    LoaderBMP wallBMP("../assets/textures/wall.bmp");
    LoaderBMP uvBMP("../assets/textures/uvtemplate.bmp");

    GLuint kittenText = kittenBMP.bindTexture();
    GLuint wallText = wallBMP.bindTexture();
    GLuint uvText = uvBMP.bindTexture();

    this->mTexture[0] = kittenText;
    this->mTexture[1] = wallText;
    this->mTexture[2] = uvText;

    this->setCallbacks();
    while(!glfwWindowShouldClose(this->glEnvironment.window)) {
        glClearColor(0.1f, 0.1f, 0.2f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader.shaderProgram);

        Matrix view = Matrix::getLookAtMatrix(camera.xAxis, camera.yAxis, camera.zAxis, camera.position);
        Matrix projection = Matrix::getPerspectiveMatrix(camera.zoomValue,
                                                         (float)WINDOW_W / (float)WINDOW_H,
                                                         0.1f,
                                                         100.f);
        Matrix mvp = projection * view * this->mModel;
        glUniformMatrix4fv(mvpLoc, 1, GL_TRUE, mvp.getArrayReference());

        if (this->mColourSpeedVariation != 0.f && this->mCanChangeColourSpeed) {
            this->mColourSpeed = std::clamp(this->mColourSpeed + this->mColourSpeedVariation, -3.f, 3.f);
            this->mCanChangeColourSpeed = false;
        }

        auto timeValue = static_cast<float>(glfwGetTime());
        float damage = 1.f;
        auto colourSpeedValue = std::modf(timeValue * this->mColourSpeed, &damage);

        glUniform1f(flatModeLocation, flatMode);
        glUniform1f(colourModeLocation, colourMode);
        glUniform1f(colourSpeedLocation, colourSpeedValue);
        glUniform1f(greyscaleModeLocation, greyscaleMode);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->mTexture[textIndex]);
        glUniform1i(textureID, 0);

            glPolygonMode(GL_FRONT_AND_BACK, currentGlMode);

        this->processInput(this->glEnvironment.window);
        this->obj.draw();
        glfwSwapBuffers(this->glEnvironment.window);
        glfwPollEvents();
    }
}

void App::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS)
        this->mColourSpeedVariation = 0.1f;
    if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS)
        this->mColourSpeedVariation = -0.1f;
    if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_RELEASE &&
        glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_RELEASE) {
        this->mCanChangeColourSpeed = true;
        this->mColourSpeedVariation = 0.f;
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera.move(FORWARD, this->mSpeed);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.move(BACKWARD, this->mSpeed);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camera.move(LEFT, this->mSpeed);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera.move(RIGHT, this->mSpeed);

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        this->mModelRotationalAngle += 0.1f;
        this->mModelRotationalAxis = this->mModelRotationalAxis + Vector3(1.f, 0.f, 0.f);
        this->mModel.rotate(this->mModelRotationalAngle, this->mModelRotationalAxis);
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
        this->mModelRotationalAngle += 0.1f;
        this->mModelRotationalAxis = this->mModelRotationalAxis + Vector3(0.f, 1.f, 0.f);
        this->mModel.rotate(this->mModelRotationalAngle, this->mModelRotationalAxis);
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        this->mModelRotationalAngle += 0.1f;
        this->mModelRotationalAxis = this->mModelRotationalAxis + Vector3(0.f, 0.f, 1.f);
        this->mModel.rotate(this->mModelRotationalAngle, this->mModelRotationalAxis);
    }
}

void App::printHelpToConsole() {
    std::cout << "HELP" << std::endl;
    std::cout << "      Move camera: by using the keyboard ARROWS" << std::endl;
    std::cout << "      Zoom camera: with the mouse wheel" << std::endl;
    std::cout << "      Rotate model: by moving the mouse or press X or Y or Z" << std::endl;
    std::cout << "      Change texture: press T" << std::endl;
    std::cout << "      Toggle colour mode: press C" << std::endl;
    std::cout << "      Modify colour moving speed: press , or ." << std::endl;
    std::cout << "      Toggle greyscale mode: press G" << std::endl;
    std::cout << "      Toggle flat mode: press F" << std::endl;
    std::cout << "      Change to filled mode: press 1" << std::endl;
    std::cout << "      Change to lined mode: press 2" << std::endl;
    std::cout << "      Change to dotted mode: press 3" << std::endl;
    std::cout << "      Quit: press ESC" << std::endl;
}

void App::quit() {
    glfwTerminate();
    exit(EXIT_SUCCESS);
}