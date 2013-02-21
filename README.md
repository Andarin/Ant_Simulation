Ant Simulation Project by Guillaume Martinet and Lucas Tittmann
under GNU GPL v3
is a project to simulate a colony of ants, represented in simple OpenGL 3D.

Check out the latest version at Github: https://github.com/Andarin/Ant_Simulation
Operating system: Tested under Windows XP, Linux (Ubuntu 64bit), Windows 7 64bit

The aim of the simulation is to have at the end as much food as possible (solid and liquid)
to spread a lot new queens and drones in the new generation.
More ants can dig more food but also consum some food themselves. The colony needs larvas to
transform solid food into liquid food. Adult ants can only eat liquid food and must therefore
return to the colony from time to time. They age and die at a certain age, so keep an eye
on the ant count if you reduce egg production.

CONTROLS:

PRESSING LEFT MOUSE BUTTON: look around
WASD: while looking around, use W for flying forward, A for flying leftward, etc.
LEFT SHIFT (while wasd pressed): accelerate camera
Q: better graphics on / off
F: fog on / off ("on" increases performance)
M: increase simulation precision
N: decrease simulation precision
P: print camera position to console
ESC: exit programme