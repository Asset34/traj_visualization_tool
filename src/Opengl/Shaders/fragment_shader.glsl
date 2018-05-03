in vec3 fragPos;
in vec3 fragNormal;

out vec4 outcolor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform float lightAmbientStrength;

void main() {
    /* Ambient */
    vec3 ambient = lightAmbientStrength * lightColor;

    /* Diffuse */
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    /* Specular */
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 specular = specularStrength * spec * lightColor;

    /* Result */
    vec3 result = (ambient + diffuse + specular) * objectColor;

    outcolor = vec4(result, 1.0);
}
