#version 150

uniform mat4 worldViewMatrix;
in vec4 position;
in vec2 coord;
out vec2  texCoord;

void main()                    
{
    gl_Position = worldViewMatrix  * position;
    texCoord = coord;
}
 
