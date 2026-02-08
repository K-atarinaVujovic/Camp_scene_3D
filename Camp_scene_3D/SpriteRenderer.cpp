#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Shader& shader) {
	this->shader = shader;
	initRenderData();
}

SpriteRenderer::~SpriteRenderer() {
	glDeleteVertexArrays(1, &this->quadVAO);
}


//void SpriteRenderer::DrawSprite(BasicTexture& texture, glm::vec3 position, glm::vec2 size, float rotate, glm::vec4 color, bool repeatX, bool repeatY, glm::vec2 scale) {
//	this->shader.use();
//	glm::mat4 model = glm::mat4(1.0f);
//
//	// Translate
//	model = glm::translate(model, glm::vec3(position));
//
//	// Rotate
//	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
//	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
//	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
//
//	// Scale
//	model = glm::scale(model, glm::vec3(scale.x * size.x, scale.y * size.y, 1.0f));
//
//	this->shader.setMat4("model", model);
//	this->shader.setVec4("spriteColor", color);
//
//	glActiveTexture(GL_TEXTURE0);
//	texture.Bind();
//
//	glm::vec2 repeatScale = glm::vec2(1.0f);
//	glm::vec2 texScale = size / glm::vec2(texture.TextureWidth, texture.TextureHeight);
//
//	if (repeatX) {
//		repeatScale.x = texScale.x;
//	}
//	if (repeatY) {
//		repeatScale.y = texScale.y;
//	}
//
//	this->shader.setVec2("repeatScale", repeatScale);
//
//
//	glBindVertexArray(this->quadVAO);
//	glDrawArrays(GL_TRIANGLES, 0, 6);
//	// Unbind
//	glBindVertexArray(0);
//}

void SpriteRenderer::DrawSprite(
    BasicTexture& texture,
    const glm::mat4& view,
    const glm::mat4& projection,
    glm::vec3 position,
    glm::vec2 size,
    float rotate,
    glm::vec4 color
) {
    shader.use();

    glm::mat4 model = glm::mat4(1.0f);

    // position in world
    model = glm::translate(model, position);

    // optional rotation (around Z, billboard-style)
    //model = glm::rotate(model, glm::radians(rotate), glm::vec3(0, 0, 1));

    // scale quad
    model = glm::scale(model, glm::vec3(size, 1.0f));

    shader.setMat4("uM", model);
    shader.setMat4("uV", view);
    shader.setMat4("uP", projection);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

}


void SpriteRenderer::initRenderData() {
	unsigned int VBO;
    float vertices[] = {
        // pos              // normal        // uv
        0.0f, 1.0f, 0.0f,   0, 0, 1,          0.0f, 1.0f, // top-left
        1.0f, 0.0f, 0.0f,   0, 0, 1,          1.0f, 0.0f, // bottom-right
        0.0f, 0.0f, 0.0f,   0, 0, 1,          0.0f, 0.0f, // bottom-left

        0.0f, 1.0f, 0.0f,   0, 0, 1,          0.0f, 1.0f, // top-left
        1.0f, 1.0f, 0.0f,   0, 0, 1,          1.0f, 1.0f, // top-right
        1.0f, 0.0f, 0.0f,   0, 0, 1,          1.0f, 0.0f  // bottom-right
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    glBindVertexArray(this->quadVAO);

    // position
    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE,
        8 * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(0);

    // normal
    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE,
        8 * sizeof(float),
        (void*)(3 * sizeof(float))
    );
    glEnableVertexAttribArray(1);

    // uv
    glVertexAttribPointer(
        2, 2, GL_FLOAT, GL_FALSE,
        8 * sizeof(float),
        (void*)(6 * sizeof(float))
    );
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

	//glGenVertexArrays(1, &this->quadVAO);
	//glGenBuffers(1, &VBO);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindVertexArray(this->quadVAO);
	//// Position
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	//// Unbind
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
}