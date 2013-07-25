//#version 330

//layout (location = 0) in vec3 Position;
//layout (location = 1) in vec2 TexCoord; // texture info recieved

//uniform mat4 gWVP; // WVP stands for World-View-Projection

//out vec2 TexCoord0; // texture info passed down the pipeline

//void main()
//{
	// gl_Position is the final position of the vertex
	//gl_Position = gWVP * vec4(Position, 1.0);
	
	//TexCoord0 = TexCoord; // dont do anything to the texel, just send down the pipeline
//}

#version 330

layout (location = 0) in vec3 Position;

uniform mat4 gWVP;

out vec4 Color;

void main()
{
	gl_Position = gWVP * vec4(Position, 1.0);
	Color = vec4(clamp(Position, 0.0, 1.0), 1.0);
}
