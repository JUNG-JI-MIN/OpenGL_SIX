#version 330 core

#define MAX_WAVES 10

struct ScanWave {
    vec3 center;
    float radius;
    float range;
};

in vec4                     out_Color;
in vec3                     out_Normal;
in vec3                     out_FragPos;
in vec2                     out_Texcord;

out vec4                    FragColor;

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
        return brightness * brightness;
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
}