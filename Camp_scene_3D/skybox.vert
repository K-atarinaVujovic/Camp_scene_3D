#version 330 core
layout(location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 uVP; // view-projection

void main()
{
    vec4 pos = uVP * vec4(aPos, 1.0);
    gl_Position = pos.xyww; // keep depth = 1.0
    TexCoords = aPos;
}
