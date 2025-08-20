#include "Renderer.hpp"
#include <glm/glm.hpp>
#include "Camera.hpp"
#include "Shaders.hpp"
#include "Buffers.hpp"
#include "WindowManager.hpp"

namespace Renderer {
	void Update() {
		//TODO DRAW A BASIC TRIANGLE SO I CAN CHECK IF I FUCKED MY BUFFERS UP
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glm::mat4 view = Camera::getCurrentCamera().getViewMatrix();//please work
		glm::vec3 objColor = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(
			glm::radians(Camera::getCurrentCamera().zoom),
			(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
			0.1f,
			100.0f);
		
		auto& BasicLighting = Shaders::g_Shaders["basic_lighting"]; 
		BasicLighting->use();
		unsigned int modelLoc = glGetUniformLocation(BasicLighting->ID, "model");
		unsigned int viewLoc = glGetUniformLocation(BasicLighting->ID, "view");
		unsigned int projectionLoc = glGetUniformLocation(BasicLighting->ID, "projection"); //doesnt need to be called every frame but leaving here for now
		BasicLighting->setMat4("model", model);
		BasicLighting->setMat4("view", view);
		BasicLighting->setVec3("objColor", objColor);
		BasicLighting->setVec3("lightColor", lightColor);
		BasicLighting->setMat4("projection", projection);
		//BasicLighting.setMat4("projection", projection);

		glBindVertexArray(Buffers::g_buffers["VAO"]);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
}