#include "Renderer.hpp"
#include <glm/glm.hpp>
#include "Camera.hpp"
#include "Shaders.hpp"
#include "Buffers.hpp"

namespace Renderer {
	void Update() {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glm::mat4 view = Camera::getCurrentCamera().getViewMatrix();//please work

		//glm::mat4 projection = glm::mat4(1.0f);
		//projection = glm::perspective(
		//	glm::radians(Camera::getCurrentCamera().zoom),
		//	(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
		//	0.1f,
		//	100.0f);
		
		Shader& BasicLighting = Shaders::getShader("basic_lighting"); //fuck this needs to return the object not a copy fuck 
		BasicLighting.use();
		unsigned int modelLoc = glGetUniformLocation(BasicLighting.ID, "model");
		unsigned int viewLoc = glGetUniformLocation(BasicLighting.ID, "view");
		//unsigned int projectionLoc = glGetUniformLocation(BasicLighting.ID, "projection"); //doesnt need to be called every frame but leaving here for now
		BasicLighting.setMat4("model", model);
		BasicLighting.setMat4("view", view);
		//BasicLighting.setMat4("projection", projection);
		//BasicLighting.setMat4("projection", projection);

		glBindVertexArray(Buffers::g_buffers["VAO"]);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
}