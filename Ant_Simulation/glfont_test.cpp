#include <string>
#include <utility>

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>

#include "glfont2.h"
using namespace glfont;

//glFont
GLFont myfont;

//Out OpenGL initialization function
bool TestBedInit (void)
{
	//Initialize OpenGL
	//Texture mapping and blending must be enabled for glFont to work
	glClearColor(0.0, 0.0, 0.0, 1.0);	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Create our glFont from verdana.glf, using texture 1
	if (!myfont.Create("verdana.glf", 1))
		return false;

	//Return successfully
	return true;
}