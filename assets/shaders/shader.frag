#version 460 core

in vec3 out_pos;

out vec3 color;

void main()
{
    color = out_pos * 2;
}