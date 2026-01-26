#version 330 core
layout(location = 0) in vec3 inPos;   // VBO에서 위치 입력
layout(location = 1) in vec4 inColor; // VBO에서 색상 입력
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inTexcord;

out vec4 out_Color;                   // 프래그먼트 셰이더로 색상 전달
out vec3 out_Normal;
out vec3 out_FragPos;
out vec2 out_Texcord;

uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
uniform mat3 n; // normal matrix

void main()
{
    vec4 worldPos = m * vec4(inPos, 1.0);
    gl_Position = p * v * worldPos;

    out_Color = inColor;
    out_FragPos = worldPos.xyz;
    out_Normal = normalize(n * inNormal);   // 법선 변환
    out_Texcord = inTexcord;
}