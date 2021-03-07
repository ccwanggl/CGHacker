#version 460 core 

layout (location=0) out vec4 FragColor;

uniform vec4 ourColor;

int main()
{
    FragColor = ourColor;
}
