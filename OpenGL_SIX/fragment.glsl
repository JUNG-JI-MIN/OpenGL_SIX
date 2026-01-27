#version 330 core

struct LIGHT{
    vec3 position;  // pos → position으로 변경
    vec3 dir;
    vec3 color;
    int type;
};


in vec4 out_Color;
in vec3 out_Normal;
in vec3 out_FragPos;
in vec2 out_Texcord;

out vec4 FragColor;

uniform LIGHT light;
uniform sampler2D texture1;
uniform vec3 viewPos;
uniform int useTexture;


void main()
{
    vec4 selectColor = out_Color;
    if (useTexture == 1){
        selectColor = texture(texture1, out_Texcord);
    }
    else{
        selectColor = out_Color;
    }

    vec3 resultlight = vec3(0.0f);
    vec3 norm = normalize(out_Normal);

    // 1. Ambient
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * light.color;

    // 2. Diffuse (확산광)
    vec3 lightDir;
    float attenuation = 1.0;
        
    if (light.type == 0){    
        // 방향광: dir을 반대로 (빛이 오는 방향)
        lightDir = normalize(-light.dir);
    }
    else{
        // 점광원: 위치에서 fragment로의 방향 + 감쇠 계산
        lightDir = normalize(light.position - out_FragPos);
        float distance = length(light.position - out_FragPos);
        attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * distance * distance);
    }
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.color * attenuation;
        
    // ambient에도 점광원이면 감쇠 적용
    vec3 finalAmbient = ambient;
    if (light.type == 1) {
        finalAmbient *= attenuation;
    }
        
    resultlight += finalAmbient + diffuse;

    vec3 result = resultlight * selectColor.rgb;
    FragColor = vec4(result, selectColor.a);
}