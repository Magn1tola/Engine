#version 430 core

layout (location = 0) in vec3 pos;

uniform mat4 vp;
uniform mat4 model;

out vec3 out_pos;

void main()
{
    gl_Position = vp * model * vec4(pos, 1.0);
    out_pos = pos;
}