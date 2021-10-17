#version 150

uniform sampler2D RT;
uniform vec4 factors;
out vec4 fragColour;
in vec2 oUv0;
in vec2 oUv1;

void main()
{
    
    fragColour = texture(RT,oUv0);  
    fragColour *= factors;
}
