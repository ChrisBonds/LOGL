namespace Renderer {
	void Update() {
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = Camera::getCurrentCamera().getViewMatrix();//please work
		glm::mat4 projection = glm::mat4(1.0f);

		projection = glm::perspective(
			glm::radians(Camera::getCurrentCamera().zoom),
			(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
			0.1f,
			100.0f);

		unsigned int modelLoc = glGetUniformLocation(BasicLighting.ID, "model");
		unsigned int viewLoc = glGetUniformLocation(BasicLighting.ID, "view");
		unsigned int projectionLoc = glGetUniformLocation(BasicLighting.ID, "projection"); //doesnt need to be called every frame but leaving here for now
		BasicLighting.setMat4("model", model);
		BasicLighting.setMat4("view", view);
		BasicLighting.setMat4("projection", projection);
	}
}