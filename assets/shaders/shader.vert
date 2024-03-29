#version 100
precision mediump float;

attribute vec3 a_Position;
attribute vec4 a_Color;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

varying vec3 v_Position;
varying vec4 v_Color;

void main()
{
	v_Position = a_Position;
	v_Color = a_Color;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
}
