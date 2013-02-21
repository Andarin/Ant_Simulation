//Ant Simulation is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// Authors: Guillaume Martinet, Lucas Tittmann
// Date: 02/2013
//
// Some code is based on the tutorials from:
// http://www.youtube.com/user/thecplusplusguy
// If so it is stated in the header. The original files are distributed under LPGL.
//
// Furthermore, to display text, we use glfont2 from Brad Fisher:
// https://students.cs.byu.edu/~bfish/glfont2.php
//
// For displaying PNG-images, we use loadpng from Lode Vandevenne
// http://lodev.org/lodepng/
//
// To display the Blender models (*.obj) in our simulation, we used code from
// the site du zero:
// http://www.siteduzero.com/informatique/tutoriels/charger-des-fichiers-obj/parser-les-formats-obj-et-mtl
// http://www.siteduzero.com/informatique/tutoriels/creez-des-programmes-en-3d-avec-opengl/plaquage-de-texture
//
// The source files are also GPL v3.0 with 1 exception:
// grass.bmp is taken from
// http://www.public-domain-image.com/full-image/textures-and-patterns-public-domain-images-pictures/grass-texture-public-domain-images-pictures/buffalo-grass-texture.jpg-copyright-friendly-photo.html
// by Titus Tscharntke

#include "Ant_Sim.h"

int main(int argc, char** argv)
{
	// user changeable parameters
	int play_time = 600;

	Ant_Sim my_sim(play_time);
	my_sim.start();
	return 0;
}
