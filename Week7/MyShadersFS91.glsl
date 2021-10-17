#version 150

uniform sampler2D RT;
uniform float numpixels;
out vec4 fragColour;
in vec2 oUv0;
in vec2 oUv1;

void main()
{

    //means each axis, x and y, will have 50 pixels.        
    //float num = 50.0;

    // stepsize, which is 1 divided by the number of pixels. We need this value to
    //calculate the texture coordinates.
    float stepsize = 1.0/numpixels;
    
    vec2 fragment = vec2(stepsize * floor(oUv0.x * numpixels),stepsize *  floor(oUv0.y * numpixels));
    fragColour = texture(RT,fragment);  
}
