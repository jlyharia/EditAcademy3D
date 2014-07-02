#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;
static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
int main(int argc, const char ** argv)
{
    
    
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    window = glfwCreateWindow(640, 480, "Edit Academy 3D", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    
// glewInit();
    cout<< glGetString(GL_VERSION)<<endl;
    glClear(GL_COLOR_BUFFER_BIT);
    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        
        //	glMatrixMode(GL_PROJECTION);
        //	glLoadIdentity();
        //	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        //	glMatrixMode(GL_MODELVIEW);
        //	glLoadIdentity();
        //	glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
        //	glBegin(GL_TRIANGLES);
        //	glColor3f(1.f, 0.f, 0.f);
        //	glVertex3f(-0.6f, -0.4f, 0.f);
        //	glColor3f(0.f, 1.f, 0.f);
        //	glVertex3f(0.6f, -0.4f, 0.f);
        //	glColor3f(0.f, 0.f, 1.f);
        //	glVertex3f(0.f, 0.6f, 0.f);
        //	glEnd();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
