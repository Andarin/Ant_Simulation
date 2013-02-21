Project Description
-------------------

Ant Simulation Project by Guillaume Martinet and Lucas Tittmann under
GNU GPL v3 is a project to simulate a colony of ants, represented in simple OpenGL 3D.

Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation  
Operating system: Tested under Windows XP, Linux (Ubuntu 64bit), Windows 7 64bit

The aim of the simulation is to gather as much food as possible (solid and liquid) in order
to spread a lot new queens and drones in the new generation.
More ants can gather more food but also consume food themselves. The colony needs larvae to
transform solid food into liquid food. Adult ants can only eat liquid food and must therefore
return to the colony from time to time. They age and die eventually, so keep an eye
on the ant count if you reduce egg production.

You can change the parameters of the simulation as well as the display resolution in the  
"Ant_Simulation_parameters.txt" file in the Ant_Simulation folder.
  
Controls  
--------  
  
PRESSING LEFT MOUSE BUTTON: look around  
WASD: while looking around, use W for flying forward, A for flying leftward, etc.  
LEFT SHIFT (while wasd pressed): accelerate camera  
Q: better graphics on / off  
F: fog on / off ("on" increases performance)  
M: increase simulation precision  
N: decrease simulation precision  
P: print camera position to console  
ESC: exit programme  