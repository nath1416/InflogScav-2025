#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 firstColor;
uniform vec3 secondColor;

void main()
{
    vec3 colorA = firstColor; 
    vec3 colorB = secondColor;

    float mixFactor = smoothstep(0.4, 0.6, normalize(Normal).y); 

    vec3 finalfirstColor = mix(colorA, colorB, mixFactor);


    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * finalfirstColor;

    vec3 ambient = 0.2 * finalfirstColor; 

    float shininess = 32.0;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = vec3(1.0) * spec; // Specular color remains white (or adjust if needed)

    vec3 result = ambient + diffuse + specular;
    result = clamp(result, 0.0, 1.0); 

    FragColor = vec4(result, 1.0);
}