#include "MainGame.h"

int main(int argc, char ** argv) {
    MainGame mainGame;
    mainGame.run();

    return 0;
}
//
//
//  main.cpp
//  openGL
//
//  Created by Sergey Timoshkin on 31.08.17.
//  Copyright © 2017 Sergey Timoshkin. All rights reserved.
//

//#include <iostream>
//#include <GL/glew.h>
//#include "GLFW/glfw3.h"
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//    // Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true,
//    // и приложение после этого закроется
//    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, GL_TRUE);
//}
//
//int main(int argc, const char * argv[]) {
//    // insert code here...
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    //Минорная
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    //Установка профайла для которого создается контекст
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    //Выключение возможности изменения размера окна
//
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//
//    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
//    if (window == nullptr)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//
//    glewExperimental = GL_TRUE;
//    if (glewInit() != GLEW_OK)
//    {
//        std::cout << "Failed to initialize GLEW" << std::endl;
//        return -1;
//    }
//
//    int width, height;
//    glfwGetFramebufferSize(window, &width, &height);
//
//    glViewport(0, 0, width, height);
//
//    glfwSetKeyCallback(window, key_callback);
//
//    while(!glfwWindowShouldClose(window))
//    {
//        glfwPollEvents();
//        glfwSwapBuffers(window);
//
//
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//    }
//    glfwTerminate();
//
//    std::cout << "Hello, World!\n";
//    return 0;
//}
