#version 100
precision mediump float;


// Attributes
attribute vec3 a_Position;
attribute vec2 a_TexCoords;

// Uniforms
uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

varying vec2 TexCoords;

void main()
{
    TexCoords = a_TexCoords;    
    gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vec4(a_Position, 1.0);
}