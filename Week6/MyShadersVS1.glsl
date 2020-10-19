#version 150

uniform mat4 worldViewMatrix;
uniform float pulseTime;
in vec4 position;

void main()                    
{
    gl_Position = worldViewMatrix  * position;
    gl_Position.x *= (2+sin(pulseTime));
}
 
