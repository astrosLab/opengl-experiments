#version 330 core
out vec4 FragColor;

in vec3 vColor;
in vec2 vTexCoord;

uniform sampler2D ourTexture;

void main() {
	FragColor = texture(ourTexture, vTexCoord) * vec4(vColor, 1.0);
}
