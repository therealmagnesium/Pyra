#version 450 core
out vec4 finalColor;

in vec3 fragPosition;
in vec2 fragTexCoords;
in vec3 fragNormal;

const int LIGHT_DIRECTIONAL = 0;
const int LIGHT_POINT = 1;
const int LIGHT_SPOTLIGHT = 2;

struct DirectionalLight
{
    vec3 direction;
    vec3 color; 
    float intensity;
};

uniform vec3 viewPosition;
uniform vec4 colAmbient;
uniform vec4 colDiffuse;
uniform DirectionalLight directionalLight;

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 camPosition)
{
    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(-light.direction);

    float diffuseFactor = max(dot(normal, lightDir), 0.f);

    vec3 reflectDir = reflect(-lightDir, normal);
    float specularFactor = pow(max(dot(camPosition, reflectDir), 0.f), 8);

    vec3 ambient = light.color * colAmbient.xyz;
    vec3 diffuse = light.color * diffuseFactor * colDiffuse.xyz;
    vec3 specular = light.color * specularFactor;

    return light.intensity * colDiffuse.xyz * (ambient + diffuse + specular);
}

void main()
{
    vec3 result = CalculateDirectionalLight(directionalLight, viewPosition);
    finalColor = vec4(result, 1.f);
}
