#version 330

in vec3 pos;
in vec3 normal;

out vec3 fragPos;
out vec3 fragNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void) {
    gl_Position = projection * view * model * vec4(pos, 1.0);

    fragPos = vec3(model * vec4(pos, 1.0));
    fragNormal = normal;
}
