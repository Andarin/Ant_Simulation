Project Description
-------------------

Ant Simulation Project by Guillaume Martinet and Lucas Tittmann under
GNU GPL v3 is a project to simulate a colony of ants, represented in simple OpenGL 3D.

Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation  
Operating system: Tested under Windows XP, Linux (Ubuntu 64bit), Windows 7 64bit

You find an executable as well as Visual Studio *.sln and *.vcxproj files in 
Ant_Simulation/bin.

How to play
-----------

The aim of the simulation is to gather as much food as possible (solid and liquid) in order
to spread a lot new queens and drones in the new generation.
More ants can gather more food but also consume food themselves. The colony needs larvae to
transform solid food into liquid food. Adult ants can only eat liquid food and must therefore
return to the colony from time to time. They age and die eventually, so keep an eye
on the ant count if you reduce egg production.

You can control your colony by changing the parameters of the simulation in the
"Ant_Simulation_parameters.txt" file in the Ant_Simulation folder. There you can change
the resolution of the application as well.
  
Controls  
--------  
  
PRESSING LEFT MOUSE BUTTON: look around  
WASD: while looking around, use W for flying forward, A for flying leftward, etc.  
LEFT SHIFT (while WASD pressed): accelerate camera  
Q: better graphics on / off  
F: fog on / off ("on" increases performance)  
M: increase simulation precision  
N: decrease simulation precision  
P: print camera position to console  
ESC: exit programme  

Compiling information
---------------------

Using the executable:  
In order to use Ant_Simulation.exe, copy it in the inner Ant_Simulation  
folder (with all the *.cpp) and double click it.

Visual Studio:  
To build with Visual Studio, copy the *.sln and *.vcxproj into the outer  
Ant_Simulation folder (where you found this README) and copy also the  
*.vcxproj in the inner Ant_Simulation folder. In Visual Studio choose  
"Open - Solution" and open Ant_Simulation.sln  
You should adapt your links of the project to SDL and SDL_image.

Linux/cygwin:  
Open the inner Ant_Simulation in the terminal and type "make" (there  
is a makefile inside the folder).