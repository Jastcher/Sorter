#shader vertex
#version 330 core

uniform int uHeight;
uniform int uIndex;

uniform int uN;

uniform vec3 uColor;

out vec3 color;

void main()
{

  color = uColor;

  float x = 2.0 * (uIndex / float(uN)) - 1.00;
  float height = -1.00;

	if(gl_VertexID == 1) { height = 2.00 * (uHeight / float(uN)) - 1.00; }

	gl_Position = vec4(x, height, 0.0f, 1.0f);
}

#shader fragment
#version 330 core

out vec4 FragColor;

in vec3 color;


void main()
{
	gl_FragColor = vec4(color, 1.0f);
}

