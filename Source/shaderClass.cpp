#include"../Header/shaderClass.h"

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename, const char* path)
{
	
	std::ifstream in;
	std::string fileName = filename;
	std::string filePath = path;
	fileName = filePath + fileName;
	in.open(fileName);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile, const char* path) {
	std::string vertexCode = get_file_contents(vertexFile, path);
	std::string fragmentCode = get_file_contents(fragmentFile, path);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//create shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	//create shader program
	ID = glCreateProgram(); //create shader program

	glAttachShader(ID, vertexShader); //add vertex shader to shader prog
	glAttachShader(ID, fragmentShader); // same but fragment
	glLinkProgram(ID); //wrap up

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

// Deletes the Shader Program
void Shader::Delete()
{
	glDeleteProgram(ID);
}