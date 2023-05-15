#version 330 core

in vec3 colorVS;

uniform vec3 colorAdjustment;
//fragment shader output
out vec4 color;

void main(){

    color = vec4(colorVS.x + colorAdjustment.x,
        colorVS.y + colorAdjustment.y,
        colorVS.z + colorAdjustment.z,
        1.0);

}
