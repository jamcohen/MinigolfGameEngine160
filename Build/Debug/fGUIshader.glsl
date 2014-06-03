#version 150

// Interpolated values from the vertex shaders
in vec2 uv;

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;
uniform vec3 textColor;

void main(){
    
	color = texture( myTextureSampler, vec2(uv.x,-uv.y) );
    if(color == vec4(0,0,0,1)){
        discard;
    }
    color = vec4(textColor.xyz,1);
}