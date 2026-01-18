#version 330 core
layout(location = 0) in vec3 inPos;   // VBO에서 위치 입력
layout(location = 1) in vec4 inColor; // VBO에서 색상 입력
out vec4 out_Color;                   // 프래그먼트 셰이더로 색상 전달

uniform mat4 u;   // 최종 행렬
uniform mat4 m;
uniform mat4 v;
uniform mat4 p;

void main()
{
    gl_Position =  p * v * m  * vec4(inPos, 1.0);
    out_Color = inColor;
}
