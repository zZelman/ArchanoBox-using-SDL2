//#version 330

//in vec2 TexCoord0; // texture info recieved

//out vec4 FragColor;

// the app must set the value of the texture unit into this var so the FS can use the texture
//uniform sampler2D gSampler;

//void main()
//{
	// * sample texture
	// * first param: sampeler uniform
	// * second param: texture coords
	// * output: pixel color rendered
	//FragColor = texture2D(gSampler, TexCoord0.xy);
//}


#version 330

in vec4 Color;

out vec4 FragColor;

void main()
{
	FragColor = Color;
}
