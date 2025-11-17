#version 330 core

in ATTRIB_VS_OUT {
    vec2 texCoords;
    vec3 normal;
    vec3 lightDir[3];
    vec3 spotDir[3];
    vec3 obsPos;
} attribIn;

struct Material {
    vec3 emission;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct UniversalLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
    vec3 spotDirection;
};

layout (std140) uniform LightingBlock {
    Material mat;
    UniversalLight lights[3];
    vec3 lightModelAmbient;
    bool useBlinn;
    bool useSpotlight;
    bool useDirect3D;
    float spotExponent;
    float spotOpeningAngle;
};

uniform sampler2D diffuseSampler;
uniform sampler2D specularSampler;

out vec4 FragColor;

vec3 getAmbientLight(Material mat, vec3 lightModelAmbient, sampler2D diffuseSampler, vec2 texCoords) {
    return mat.ambient * lightModelAmbient + texture(diffuseSampler, texCoords).rgb * mat.emission;
}

float getSpotLightFactor(bool useSpotlight, bool useDirect3D, float cosGamma, float cosThetaOuter, float cosThetaInner) {
    if (!useSpotlight || cosGamma < 0.0){ 
        return 1.0;
    }
    if (cosGamma > cosThetaInner) {
        return 1.0;
    }
    float spotFactor = pow((cosThetaInner - cosGamma) / (cosThetaOuter - cosThetaInner), spotExponent);
    if (useDirect3D && cosGamma < cosThetaOuter){ 
        spotFactor *= 0.5;
    }
    return spotFactor;
}

vec3 getDiffuseLight(vec3 diffuseColor, float diff, vec3 diffuseMat) {
    return diffuseMat * diffuseColor * diff;
}

vec3 getSpecularLight(bool useBlinn, vec3 lightDir, vec3 viewDirection, vec3 normal, vec3 specularColor, vec3 specularMat, float shininess) {
    vec3 halfway = normalize(lightDir + viewDirection);
    float specCoeff = pow(max(dot(normal, useBlinn ? halfway : lightDir), 0.0), shininess);
    return specularMat * specularColor * specCoeff;
}

void main() {
    vec3 result = getAmbientLight(mat, lightModelAmbient, diffuseSampler, attribIn.texCoords);

    for (int i = 0; i < 3; i++) {
        vec3 lightDir = normalize(attribIn.lightDir[i]);
        vec3 spotDir = normalize(attribIn.spotDir[i]);
        float cosGamma = dot(lightDir, spotDir);
        float cosThetaInner = cos(radians(spotOpeningAngle));
        float exponent = 1.01 + (spotExponent / 2.0);
        float cosThetaOuter = pow(cosThetaInner, exponent);

        float spotFactor = getSpotLightFactor(useSpotlight, useDirect3D, cosGamma, cosThetaOuter, cosThetaInner);

        vec4 texColor = texture(diffuseSampler, attribIn.texCoords);
        if (texColor.a < 0.3) {
            discard;
        }

        vec3 diffuseColor = lights[i].diffuse * texColor.rgb;
        float diff = max(dot(normalize(attribIn.normal), lightDir), 0.0);

        vec3 diffuse = getDiffuseLight(diffuseColor, diff, mat.diffuse);
        vec3 specularColor = lights[i].specular * texture(specularSampler, attribIn.texCoords).r;

        vec3 specular = getSpecularLight(useBlinn, lightDir, normalize(attribIn.obsPos), attribIn.normal, specularColor, mat.specular, mat.shininess);

        result += (useSpotlight ? spotFactor : 1.0) * (lights[i].ambient * mat.ambient + diffuse + specular);
    }

    FragColor = vec4(result, 1.0);
}
