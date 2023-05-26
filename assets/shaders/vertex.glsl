#version 330 core

layout (location = 1) in vec3 colorRGB;
layout (location = 0) in vec3 vertex;

uniform mat4 mm;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 colorVS;

void main(){
    colorVS = colorRGB;
    gl_Position = projectionMatrix * viewMatrix * mm * vec4(vertex, 1.0);

}
