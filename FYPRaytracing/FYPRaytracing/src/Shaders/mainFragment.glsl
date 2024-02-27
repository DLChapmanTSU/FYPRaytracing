#version 330

//uniform sampler2D sampler_tex;

uniform vec4 diffuse_colour;
//uniform sampler2D sampler_tex;

in vec3 varying_colour;
//in vec2 varying_coord;

out vec4 fragment_colour;

void main(void)
{
	fragment_colour = vec4(1.0f,0.0f,0.0f,1.0f);
}