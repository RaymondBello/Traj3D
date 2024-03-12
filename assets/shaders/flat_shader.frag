#version 100
precision mediump float;


varying vec3 v_Position;

uniform vec3 u_Color;


void main()
{
	gl_FragColor = vec4(u_Color, 1.0);
}