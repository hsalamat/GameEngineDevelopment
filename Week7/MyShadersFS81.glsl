#version 150

uniform sampler2D RT;
out vec4 fragColour;
in vec2 oUv0;
in vec2 oUv1;

void main()
{

    //means each axis, x and y, will have 50 pixels.        
    float num = 50.0;

    // stepsize, which is 1 divided by the number of pixels. We need this value to
    //calculate the texture coordinates.
    float stepsize = 1.0/num;
    
    vec2 fragment = vec2(stepsize * floor(oUv0.x * num),stepsize *  floor(oUv0.y * num));
    fragColour = texture(RT,fragment);  
}
