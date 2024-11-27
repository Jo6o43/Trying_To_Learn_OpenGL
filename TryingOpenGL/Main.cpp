#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
	glfwInit();

	//especifica a versão que será usada
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	//criar a janela
	GLFWwindow* window = glfwCreateWindow(800, 800, "Trying to Learn OPENGL", NULL, NULL);
	//verifica erros ao abrir a janela
	if (window == NULL) {
		std::cout << "Failed to Create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//dar cor à janela
	gladLoadGL();
	glViewport(0,0,800,800);
	glClearColor(0.5f, 1.0f, 1.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	//adiciona a condição de que o programa irá continuar caso a janela seja fechada
	while (!glfwWindowShouldClose(window))
	{
		//processar eventos, impede que a janela fique eternamente em estado "Não Responder"
		glfwPollEvents();
	}

	//apaga a janela ao fechar o programa 
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

