#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


int main()
{
	glfwInit();

	//especifica a versão que será usada
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//criar a janela
	GLFWwindow* window = glfwCreateWindow(800, 800, "Trying to Learn OPENGL", NULL, NULL);
	//verifica erros ao abrir a janela
	if (window == NULL) {
		std::cout << "Failed to Create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	gladLoadGL();
	//seleciona a area da janela a ser usada
	glViewport(0, 0, 800, 800);


	//criar referencia aos shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//coordenadas dos vetices
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //canto esquerdo inferior
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //canto direito inferior
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, //canto superior
		-0.5f / 2,0.5f * float(sqrt(3)) / 6,0.0f, //vertice esquerdo
		0.5f / 2,0.5 * float(sqrt(3)) / 6, 0.0f, //vertice direito
		0.0f,-0.5f * float(sqrt(3)) / 3, 0.0f //vertice de baixo
	};

	GLuint indices[] =
	{
		0,3,5, //triangulo esquerdo inferior 
		3,2,4, //triangulo direito inferior
		5,4,1 //triangulo superior
	};


	//criar buffers
	GLuint VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	//adiciona a condição de que o programa irá continuar caso a janela seja fechada
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3); (desenha o triangulo com os tres vertices)
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		//processar eventos, impede que a janela fique eternamente em estado "Não Responder"
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	//apaga a janela ao fechar o programa 
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

