#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time; 

void main()
{
    float amplitude = 0.5; 
    float speed = 2.0;      

    float pulse = sin(time * speed);
    if(pulse <0){
        pulse = -pulse;
    }
    float displacement = pulse * amplitude;
    
    vec3 perturbedPos = aPos + aNormal * displacement;
    

    FragPos = vec3(model * vec4(perturbedPos, 1.0));

    Normal = mat3(transpose(inverse(model))) * aNormal;

    gl_Position = projection * view * model * vec4(perturbedPos, 1.0);
}