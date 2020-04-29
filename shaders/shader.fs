#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

// Mode choice
uniform bool drawTex2;
uniform bool drawTex1;
uniform bool color;

uniform vec4 ourColor;
uniform vec4 lightColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float opacity;

// Fragment shader, deal with textures and colors
void main()
{
	// Combine 2 textures
	if (drawTex2)
		FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), opacity);
	// Apply 1 texture
	else if (drawTex1)
		FragColor = texture(texture1, TexCoord);
	// Apply a color
	else if (color)
		FragColor = lightColor*ourColor;
	// Default color is black
	else
		FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}