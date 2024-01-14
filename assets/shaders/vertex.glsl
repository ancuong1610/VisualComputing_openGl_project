#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 colorRGB;

out vec3 ColorVS;

out vec3 PositionVS;
out vec3 NormalVS;

uniform mat4 mm;
uniform mat4 projection;
uniform mat4 views;

void main(){

    //lighting
    NormalVS = mat3(transpose(inverse(mm))) * normal;
    PositionVS = vec3(mm* vec4(pos, 1.0)); // Convert position to world space

    //diagonal
    gl_Position = projection * views * mm * vec4(pos.x, pos.y, pos.z, 1.0);

    //gl_Position = mm * vec4(pos.x, pos.y, pos.z, 1.0);
    ColorVS = colorRGB*0.2;

}
