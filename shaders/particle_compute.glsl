#version 450

// Define the buffer block for the particle data
layout(std430, binding = 0) buffer ParticleBuffer {
    vec4 positions[]; // x, y, z, unused
    vec4 velocities[]; // x, y, z, unused
} particles;

uniform float deltaTime; // Time step for simulation

void main() {
    // Get the global invocation ID
    uint index = gl_GlobalInvocationID.x;

    // Update the position based on the velocity
    particles.positions[index] += particles.velocities[index] * deltaTime;
}