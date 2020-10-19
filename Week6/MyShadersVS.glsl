#version 150

uniform mat4 worldViewMatrix;
in vec4 position;

void main()                    
{
    gl_Position = worldViewMatrix  * position;
}
 
