#version 100
precision mediump float;


// Varyings
varying vec3 v_VertexColor;


void main()
{
	gl_FragColor = vec4(v_VertexColor, 1.0);
}
