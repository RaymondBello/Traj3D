#version 100
precision mediump float;


// Uniforms
uniform sampler2D u_ScreenTexture;

// Varyings
varying vec2 TexCoords;


void main()
{
    gl_FragColor = vec4(texture2D(u_ScreenTexture, TexCoords).rgb, 1.0);
}