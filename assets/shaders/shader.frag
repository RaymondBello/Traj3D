// #version 100
// precision mediump float;

// varying vec2 TexCoord;

// void main(){
//   gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
// }

#version 330

out vec4 color;

void main()
{
	color = vec4(0.05, 0.86, 0.95, 1.0);
}