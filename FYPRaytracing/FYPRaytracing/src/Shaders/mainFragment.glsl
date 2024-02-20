#version 330 core

//layout(location = 0) in vec4 u_color;

uniform vec3 camera_direction;

in vec2 varying_coord;
in vec3 varying_normal;
in vec4 varying_position;

out vec4 fragment_colour;

void main()
{
	fragment_colour = vec4(1.0, 0.0, 0.0, 1.0);
}