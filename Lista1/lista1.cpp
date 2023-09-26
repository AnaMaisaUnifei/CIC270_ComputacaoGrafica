// Ana Maísa do Nascimento Santos - 2021002575
// CIC270 - Computação Gráfica
// Prof. Elisa de Cássia Silva Rodrigues

// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/freeglut.h>


/* Globals */
/** Window width. */
int win_width  = 800;
/** Window height. */
int win_height = 600;

// Variáveis globais para a resolução da lista
int triangles_number = 1;
int type_primitive = GL_TRIANGLES;
int type_polygon = GL_FILL;

/** Program variable. */
int program;
/** Vertex array object. */
unsigned int VAO;
/** Vertex buffer object. */
unsigned int VBO;

/** Vertex shader. */
const char *vertex_code = "\n"
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";

/** Fragment shader. */
const char *fragment_code = "\n"
"#version 330 core\n"
"out vec4 FragColor;\n"
"\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
"}\0";

/* Functions. */
void display(void);
void reshape(int, int);
void keyboard(unsigned char, int, int);
void initData(void);
void initShaders(void);

/** 
 * Drawing function.
 *
 * Draws a triangle.
 */
void display()
{
    	glClearColor(0.3, 0.5, 0.9, 1.0);
    	glClear(GL_COLOR_BUFFER_BIT);

    	glUseProgram(program);
    	glBindVertexArray(VAO);

    	// Draws the triangle.
    	glDrawArrays(type_primitive, 0, triangles_number*3);

    	glutSwapBuffers();
}

/**
 * Reshape function.
 *
 * Called when window is resized.
 *
 * @param width New window width.
 * @param height New window height.
 */
void reshape(int width, int height)
{
    win_width = width;
    win_height = height;
    glViewport(0, 0, width, height);
    glutPostRedisplay();
}


/** 
 * Keyboard function.
 *
 * Called to treat pressed keys.
 *
 * @param key Pressed key.
 * @param x Mouse x coordinate when key pressed.
 * @param y Mouse y coordinate when key pressed.
 */
void keyboard(unsigned char key, int x, int y)
{
        switch (key)
        {
                case 27:
                    exit(0);
                case 'q':
                case 'Q':
                    exit(0);
                case 'o':  
                case 'O':
                    if(triangles_number == 1){
                        triangles_number = 2;
                    }
                    else{
                        triangles_number = 1;
                    }
                    break;
                case 'v':
                case 'V':
                    if(type_primitive == GL_TRIANGLES){
                        type_primitive = GL_POINTS;
                    }else{
                        type_primitive = GL_TRIANGLES;
                    }
                    break;
                case 'f':
                case 'F':
                    if(type_polygon == GL_FILL){
                        type_polygon = GL_LINE;
                    }else{
                        type_polygon = GL_FILL;
                    }
                    glPolygonMode(GL_FRONT_AND_BACK, type_polygon);
                    break;

        }
    glutPostRedisplay();
}

/**
 * Init vertex data.
 *
 * Defines the coordinates for vertices, creates the arrays for OpenGL.
 */
void initData()
{

    // Set triangle vertices.
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
         0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    };

    glPointSize(5.0f);
    
    // Vertex array.
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Vertex buffer
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Set attributes.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    
	// Desabilita VAO	
	glEnableVertexAttribArray(0);

    // Unbind Vertex Array Object.
    glBindVertexArray(0);
}

/** Create program (shaders).
 * 
 * Compile shaders and create the program.
 */
void initShaders()
{
    // Request a program and shader slots from GPU
    program  = glCreateProgram();
    int vertex   = glCreateShader(GL_VERTEX_SHADER);
    int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    
    // Set shaders source
    glShaderSource(vertex, 1, &vertex_code, NULL);
    glShaderSource(fragment, 1, &fragment_code, NULL);

    // Compile shaders
    glCompileShader(vertex);
    glCompileShader(fragment);

    // Attach shader objects to the program
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    // Link the program
    glLinkProgram(program);

    // Get rid of shaders (not needed anymore)
    glDetachShader(program, vertex);
    glDetachShader(program, fragment);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    
    // Set the program to be used.
    glUseProgram(program);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(win_width,win_height);
	glutCreateWindow(argv[0]);
	glewExperimental = GL_TRUE; 
	glewInit();

	// Init vertex data for the triangle.
	initData();

	// Create shaders.
	initShaders();

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
}
