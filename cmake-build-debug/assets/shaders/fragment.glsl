#version 330 core

in vec3 ColorVS;

in vec3 PositionVS;
in vec3 NormalVS;
uniform vec3 viewPosition;
uniform vec3 colorAdjustment;

// Fragment shader output
out vec4 color;

struct Light {
    vec3 position;
    vec3 color;
    float intensity;
};

struct Spotlight {
    float intensity;
    float constant;
    float linear;
    float quadratic;
    vec3 position;
    vec3 direction;
    float cutoff;
    float outerCone;
    vec3 color;
};


struct Material {
    vec3 specular;
    float shininess;
};

uniform Light light;
uniform Material material;
uniform Spotlight spotlight;
uniform vec3 globalAmbient;

void main() {
    vec3 adjustedColor = clamp(ColorVS + colorAdjustment, 0.0, 1.0); // Adjust color and clamp

    vec3 norm = normalize(NormalVS);
    vec3 lightDir = normalize(spotlight.position - PositionVS);
    vec3 viewDir = normalize(viewPosition - PositionVS);

    // Ensure angle between normal and light direction is not greater than 90 degrees
    float cosTheta = dot(norm, lightDir);
    float clampedCosTheta = max(cosTheta, 0.0);

    // Diffuse
    vec3 diffuse = spotlight.intensity * clampedCosTheta * spotlight.color * adjustedColor;

    // Calculate reflection direction
    vec3 reflectDir = reflect(-lightDir, norm);

    // Ensure angle between view direction and reflection direction is not greater than 90 degrees
    float cosAlpha = dot(viewDir, reflectDir);
    float clampedCosAlpha = max(cosAlpha, 0.0);

    // Specular
    float spec = pow(clampedCosAlpha, material.shininess);
    vec3 specular = material.specular * spec * spotlight.color * spotlight.intensity;

    // Ambient
    vec3 ambient = globalAmbient * adjustedColor;

    // Calculate the Attenuation and Spotlight
    float theta = acos(dot(-spotlight.direction,lightDir));
    float cosPhi = cos(spotlight.cutoff);
    float cosGamma = cos(spotlight.outerCone);
    float intensity = (cos(theta) - cosGamma) / (cosPhi - cosGamma);

    vec3 spotlightColor = intensity * spotlight.intensity * spotlight.color;

    float distance = length(spotlight.position - PositionVS);
    float attenuation = 1.0 / (spotlight.constant + spotlight.linear * distance + spotlight.quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 result = (ambient + diffuse + specular + spotlightColor);
    color = vec4(result, 1.0);
}
