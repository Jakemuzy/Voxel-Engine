#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 TexCoords;

vec3 lightDir = vec3(-0.5, -0.5, -0.5);
uniform sampler2DArray myTexture;

void main()
{

    float diff = max(dot(Normal, lightDir), 0.0);

	FragColor = texture(myTexture, TexCoords) + (diff * 0.2);
    //FragColor = vec4(1.0f, 0.3f, 0.3f, 1.0f);
}