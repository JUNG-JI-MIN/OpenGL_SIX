#version 330 core

layout (location = 0) out vec4 FragColor;   // 원래 색상 (Scene)
layout (location = 1) out vec4 BrightColor; // 밝은 영역 (Bloom용)

#define MAX_WAVES 10

struct ScanWave {
    vec3 center;
    float radius;
    float range;
    float MaxRadius;
};

in vec4                     out_Color;
in vec3                     out_Normal;
in vec3                     out_FragPos;
in vec2                     out_Texcord;

uniform sampler2D           texture1;
uniform int                 useTexture;

// 파동 배열
uniform ScanWave            waves[MAX_WAVES];
uniform int                 waveCount;

float CalDistance(vec3 position1, vec3 position2){
    return length(position1 - position2);
}

float CalcWaveBrightness(vec3 fragPos, ScanWave wave) {
    float dist = CalDistance(fragPos, wave.center);
    float canMax = wave.radius + wave.range;
    float canMin = wave.radius - wave.range;

    if (dist <= canMax && dist >= canMin) {
        float distFromWave = abs(dist - wave.radius);
        float brightness = 1.0 - smoothstep(0.0, wave.range, distFromWave);
        brightness = brightness * brightness;
        
        float fadeStart = wave.MaxRadius * 0.7;  // 70% 지점부터 페이드 시작
        float fadeOut = 1.0 - smoothstep(fadeStart, wave.MaxRadius, wave.radius);
        
        return brightness * fadeOut;
    }
    return 0.0;
}

void main()
{
    // 기본 색상 선택
    vec4 selectColor = out_Color;
    if (useTexture == 1){
        selectColor = texture(texture1, out_Texcord);
    }

    // 모든 파동의 밝기 합산 (최대값 사용)
    float totalBrightness = 0.0;
    for (int i = 0; i < waveCount && i < MAX_WAVES; ++i) {
        float waveBrightness = CalcWaveBrightness(out_FragPos, waves[i]);
        totalBrightness = max(totalBrightness, waveBrightness);  // 가장 밝은 값 사용
    }

    vec3 result = selectColor.rgb * totalBrightness;
    FragColor = vec4(result, selectColor.a);

    float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722)); // 휘도 계산
    if(brightness > 0.5) // 임계값 조절 가능
        BrightColor = vec4(result, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
}