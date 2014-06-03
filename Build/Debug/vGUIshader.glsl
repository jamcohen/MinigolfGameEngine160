#version 150

in  vec4 vPosition;
out vec2 uv;

uniform mat4 model;
uniform mat4 projection;
void main()
{
    gl_Position = projection * model * vPosition;
    uv = vPosition.xy;
}