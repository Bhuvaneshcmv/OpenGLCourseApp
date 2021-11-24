//linking libraries
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//Setting window width
const GLint WIDTH = 800, HEIGHT = 600;

int main() {

    //Checking if glfw is working
    if (!glfwInit())
    {
        printf("GLFW Initialisation failed");
        glfwTerminate();
        return 1;
    }

    // Setup GLFW window properties
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR , 3);
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR , 3);
    
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    //Creating Window Variables
    GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);

    //Checking if main Window is created
    if (!mainWindow)
    {
        printf("GLFW window creation failed");
        glfwTerminate();
        return 1;
    }

    //Get Buffer size information
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // set context for GLEW to use
    glfwMakeContextCurrent(mainWindow);

    // Allow modern extensio features 
    glewExperimental = GL_TRUE;

    glewInit();

    if (glewInit() != GLEW_OK)
    {
        printf("GLEW init failed");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }
    glViewport(0, 0, bufferWidth, bufferHeight);
   
    while (!glfwWindowShouldClose(mainWindow))
    {
        glfwPollEvents();
        //Clear Window
        glClearColor(0,0,1,0.8f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(mainWindow);

    }
    return 0;
}