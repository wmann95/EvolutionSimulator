#include "Shader.h"

void Shader::checkCompileErrors(GLuint shader, std::string type) {
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR:SHADER_COMPILATION_ERROR of type: " << type << std::endl << infoLog << std::endl << "----------------------------------------------------------------------------" << std::endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR:PROGRAM_LINKING_ERROR of type: " << type << std::endl << infoLog << std::endl << "----------------------------------------------------------------------------" << std::endl;
		}
	}
}

Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath) {
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	std::ifstream gShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		// open the files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		// initialize string streams for files that should definitely be defined for the shader
		std::stringstream vShaderStream, fShaderStream;

		// read each file buffer into the string stream
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// close the files
		vShaderFile.close();
		fShaderFile.close();

		//Convert from stream to string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

		//Optional code if geometry is included
		if (geometryPath != nullptr) {
			gShaderFile.open(geometryPath);
			std::stringstream gShaderStream;
			gShaderStream << gShaderFile.rdbuf();
			gShaderFile.close();
			geometryCode = gShaderStream.str();
		}

	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// Compile shaders
	unsigned int vertex, fragment, geometry;

	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");

	// fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");

	// geometry shader
	if (geometryPath != nullptr) {
		const char* gShaderCode = geometryCode.c_str();
		geometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometry, 1, &vShaderCode, NULL);
		glCompileShader(geometry);
		checkCompileErrors(geometry, "GEOMETRY");
	}

	// shader program
	ID = glCreateProgram();

	glAttachShader(ID, fragment);
	glAttachShader(ID, vertex);
	if (geometryPath != nullptr) glAttachShader(ID, geometry);

	glLinkProgram(ID);

	checkCompileErrors(ID, "PROGRAM");

	// delete the shaders as they are already linked to the program
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	if (geometryPath != nullptr) glDeleteShader(geometry);
}


void Shader::Delete() {
	glDeleteProgram(ID);
}

void Shader::use() {
	//std::cout << "ID: " << ID << std::endl;
	glUseProgram(ID);
}


void Shader::setMat4(std::string name, glm::mat4 matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

