#version 150

uniform sampler2D RT;
out vec4 fragColour;
in vec2 oUv0;
in vec2 oUv1;

void main()
{
    vec4 temp_color = texture(RT, oUv0);
    fragColour = vec4(1.0-temp_color.r,1.0-temp_color.g,1.0-temp_color.b,0);   
    //fragColour = vec4(1.0-temp_color.g,1.0-temp_color.r,1.0-temp_color.b,0);   
    //fragColour = vec4(1,0,0,0); 
}
