#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time; // Required for animation

void main()
{
    float amplitude = 0.5; // Max displacement strength
    float speed = 2.0;      // Speed of the breathing motion

    float pulse = sin(time * speed);
    if(pulse <0){
        pulse = -pulse;
    }
    float displacement = pulse * amplitude;
    
    // Apply displacement along the vertex's local normal for pure in/out motion
    vec3 perturbedPos = aPos + aNormal * displacement;
    
    // --------------------------------------------------

    // 2. Pass the World Position of the perturbed vertex to the Fragment Shader
    FragPos = vec3(model * vec4(perturbedPos, 1.0));

    // 3. Transform the Normal
    // The original normal is still used, which is appropriate for uniform displacement.
    Normal = mat3(transpose(inverse(model))) * aNormal;

    // 4. Calculate the Clip Position using the perturbed vertex
    gl_Position = projection * view * model * vec4(perturbedPos, 1.0);
}