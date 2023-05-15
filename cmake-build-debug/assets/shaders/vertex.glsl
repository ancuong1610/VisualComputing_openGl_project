#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 colorRGB;

out vec3 colorVS;

uniform mat4 mm;

void main(){
    colorVS = colorRGB;
    gl_Position = mm * vec4(pos.x, pos.y, pos.z, 1.0);

}
