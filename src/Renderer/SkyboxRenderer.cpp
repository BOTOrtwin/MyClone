#include "SkyboxRenderer.h"

#include "defines.h"

#include <vector>

#include "Entity/Camera.h"

namespace {
	std::vector<GLfloat> vertecies{
		-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
		-SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
		SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
		SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
		SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
		-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,

		-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
		-SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
		-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
		-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
		-SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,

		SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
		SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
		SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
		SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,

		-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
		-SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
		-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,

		-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
		SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
		SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		-SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,

		-SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
		-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
		SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
		SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
		-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
		SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE
	};
}

SkyboxRenderer::SkyboxRenderer(const glm::mat4& proj, const std::string& path) :
	texture("Skybox/" + path)
{
	vao = Loader::get().GenVao();
	Loader::get().StoreData(0, 3, vertecies);
	GLCall(glBindVertexArray(0));

	shader.Start();
	shader.loadProjectionMatrix(proj);
	shader.Stop();
}

void SkyboxRenderer::Render(Camera& camera) {

	shader.Start();
	shader.loadViewMatrix(camera);

	texture.bind();

	GLCall(glBindVertexArray(vao));
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

	GLCall(glBindVertexArray(0));

	shader.Stop();
}