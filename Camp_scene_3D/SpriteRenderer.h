#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "BasicTexture.h"
#include "shader.hpp"


class SpriteRenderer
{
public:
	SpriteRenderer(Shader& shader);
	~SpriteRenderer();
	/*void DrawSprite(BasicTexture& texture, glm::vec3 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec4 color = glm::vec4(1.0f), bool repeatX = false, bool repeatY = false, glm::vec2 scale = glm::vec2(1.0));*/
	void DrawSprite(
		BasicTexture& texture,
		const glm::mat4& view,
		const glm::mat4& projection,
		glm::vec3 position,
		glm::vec2 size,
		float rotate,
		glm::vec4 color = glm::vec4(1.0f)
	);
private:
	Shader shader;
	unsigned int quadVAO;
	void initRenderData();
};

#endif