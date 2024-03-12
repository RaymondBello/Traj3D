#version 100
precision mediump float;


// Attributes
attribute vec3 a_Position;
attribute vec2 a_TexCoords;

// Varyings
varying vec2 TexCoords;


void main()
{
    TexCoords = a_TexCoords;    
    gl_Position = vec4(a_Position.xy, 0.0, 1.0);
}