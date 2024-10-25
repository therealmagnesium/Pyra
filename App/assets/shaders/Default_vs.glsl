#version 450 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 vertexTexCoord;
layout (location = 2) in vec3 vertexNormal;

out vec3 fragPosition;
out vec2 fragTexCoords;
out vec3 fragNormal;

uniform mat4 matModel;
uniform mat4 matView;
uniform mat4 matProjection;
uniform mat4 matNormal;
uniform mat4 mvp;

void main()
{
    fragPosition = vertexPosition;
    fragTexCoords = vertexTexCoord;
    fragNormal = mat3(matNormal) * vertexNormal;
    gl_Position = mvp * vec4(vertexPosition, 1.f);
}
