#version 100
precision mediump float;


// Uniforms
uniform sampler2D u_Texture1;

// Varyings
varying vec2 TexCoords;



void main()
{
    gl_FragColor = texture2D(u_Texture1, TexCoords);
}