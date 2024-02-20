#version 100
precision mediump float;

varying vec3 v_Position;
varying vec4 v_Color;

void main()
{
	// gl_FragColor = vec4(v_Position, 1.0);
	gl_FragColor = v_Color;
}