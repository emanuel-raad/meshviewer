// Make sure glad include comes before glfw
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// screen size settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

const char *fragmentShaderSourceRed = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
    "}\n\0";

int main() {
    // glfw: initialize and configure
    glfwInit();
    // Sets version to major.minor = 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // Creates a window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Mesh Viewer", NULL, NULL);

    // Check if creating the window was a success
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad boilerplate to load all the needed OpenGL pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Create, then compile the shaders
    // Shader code is in the string at the top of this file
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

	unsigned int fragmentShaderRed;
	fragmentShaderRed = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderRed, 1, &fragmentShaderSourceRed, NULL);
	glCompileShader(fragmentShaderRed);

	// Now, link the shaders in a shader program
    unsigned int shaderProgram, shaderProgramRed;
    shaderProgram = glCreateProgram();
	shaderProgramRed = glCreateProgram();
    
	glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

	glAttachShader(shaderProgramRed, vertexShader);
	glAttachShader(shaderProgramRed, fragmentShaderRed);
	glLinkProgram(shaderProgramRed);
    // Setup every following render call to use the shaderProgram
    // Delete vertex and fragment since we're done with those
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
	glDeleteShader(fragmentShaderRed);

    // triangle points
    float vertices[] = {
         0.5f,  0.5f, 0.0f, //0, index number
         0.5f, -0.5f, 0.0f, //1
        -0.5f, -0.5f, 0.0f, //2
        -0.5f,  0.5f, 0.0f, //3
         0.0f, 0.0f, 0.0f   //4
    };

	float verticesOrange[] = {
		 0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.0f, 0.0f
	};

	float verticesRed[] = {
		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, 0.0f, 0.0f
	};

	/*
    unsigned int indices[] = {
        0, 1, 3, // triangle 1, made from the indices above
        1, 2, 4, // triangle 2
        4, 2, 3  // triangle 3
    };
	*/

    // Vertex buffer object
    // Manages what data gets sent to the GPU
    // Position, color, normal...
    unsigned int VBO, VBORed; // buffer ID
    glGenBuffers(1, &VBO); // 1 buffer generated with ID stored in VBO
	glGenBuffers(1, &VBORed);

    // Vertex array object
    // Tells the gpu how to read the data in the VBO
    // Example: position 1 is a float
    unsigned int VAO, VAORed;
    glGenVertexArrays(1, &VAO);
	glGenVertexArrays(1, &VAORed);

    // Element buffer object
    // Stores indices that define a triangle
    // See indices array
    //unsigned int EBO;
    //glGenBuffers(1, &EBO);

    // 1. Bind VAO
    // Any following VBO and EBO and glVertexAttribPointer calls will reference back to this VAO
    glBindVertexArray(VAO);

    // 2. Bind buffer to GL_ARRAY_BUFFER type. you can only have 1 buffer for each type
    // specify which VBO to use, since its possible to have more than one
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesOrange), verticesOrange, GL_STATIC_DRAW);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 3. Configure vertex attributes (in this case, xyz pos). Uses whatever VBO is currently bound to GL_ARRAY_BUFFER
    // in vertexShader, location = 0. first para means to use location
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind. Not exactly needed
    glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Red
	glBindVertexArray(VAORed);
	glBindBuffer(GL_ARRAY_BUFFER, VBORed);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesRed), verticesRed, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Wireframe mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // main render loop
    while (!glfwWindowShouldClose(window)) {
        // process any user input
        processInput(window);

        // render window. This changes the color to greenish
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw triangles
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glBindVertexArray(0);

		glUseProgram(shaderProgramRed);
		glBindVertexArray(VAORed);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glBindVertexArray(0);

		// Drawing with an EBO
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate. cleans up ressources
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
