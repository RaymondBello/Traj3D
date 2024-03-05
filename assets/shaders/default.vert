#version 100
precision mediump float;


// Attributes
attribute vec3 a_Position;
attribute vec3 a_Color;

// Uniforms
uniform mat4 u_ModelMatrix;

uniform mat4 u_ViewMatrix;

uniform mat4 u_ProjectionMatrix;


// Varyings
varying vec3 v_VertexColor;


void main()
{
    v_VertexColor = a_Color;

    gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vec4(a_Position, 1.0);
}
