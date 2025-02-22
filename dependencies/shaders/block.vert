#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in int side;
layout (location = 2) in vec3 aTex;

float normals[18] = float[](
    1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f,
    0.0f,-1.0f, 0.0f, 
    0.0f, 0.0f,-1.0f,
   -1.0f, 0.0f, 0.0f
);


out vec3 Normal;
out vec3 TexCoords;

uniform mat4 model; //transformations
uniform mat4 view;  //camera
uniform mat4 projection;    //Ortho or perspective camera


void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    Normal = vec3(normals[side * 3], normals[side * 3 + 1], normals[side * 3 + 2]);
    //TexCoords = vec3(textures[side * 3], textures[side * 3 + 1], textures[side * 3 + 2]);
    TexCoords = aTex;
}