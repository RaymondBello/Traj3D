#version 100
precision mediump float;

attribute vec3 a_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

varying vec3 v_Position;

void main()
{
	v_Position = a_Position;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
}
