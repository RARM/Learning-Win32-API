#include <iostream>
#include <stdlib.h>

#include "glfw3.h"

void myOpenGL();

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(int argc, char* argv[]) {
    if (!glfwInit()) {
        std::cout << "There was an error initializing GLFW." << std::endl;
    }

    else {
        // std::cout << "Yay! GLFW was initialized correctly!" << std::endl;
        GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Window!", NULL, NULL);
        
        if (!window)
        {
            std::cout << "There was an error creating the Window." << std::endl;
        }

        else {
            glfwSetKeyCallback(window, key_callback);
            glfwMakeContextCurrent(window);
            glfwSwapInterval(2);

            // OpenGl
            myOpenGL();

            while (!glfwWindowShouldClose(window))
            {
                // Keep running
                myOpenGL();
                glfwSwapBuffers(window);
                glfwPollEvents();
            }
            
            glfwDestroyWindow(window);
        }

        glfwTerminate();
    }

    return EXIT_SUCCESS;
}

void myOpenGL() {
    glClearColor(0.0F, 0.0F, 0.5F, 0.0F);
    glClear(GL_COLOR_BUFFER_BIT);
}