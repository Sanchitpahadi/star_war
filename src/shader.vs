#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

layout (location = 2) in vec4 instanceModelCol0;
layout (location = 3) in vec4 instanceModelCol1;
layout (location = 4) in vec4 instanceModelCol2;
layout (location = 5) in vec4 instanceModelCol3;

uniform mat4 projection;
uniform mat4 view;

out vec2 TexCoord;

void main()
{
    mat4 instanceModel = mat4(instanceModelCol0, instanceModelCol1, instanceModelCol2, instanceModelCol3);
    gl_Position = projection * view * instanceModel * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}