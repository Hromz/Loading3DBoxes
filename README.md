# Loading3DBoxes, container loading problem
Loading 3D boxes into container.
This is my pet project that still in development. Right know it's only console and i'm trying to figure out best solution for this problem, after im gonna add GUI and 3d visualisation of loaded boxes.

Requires user to input quantity and box dimensions. After that calculates optimal box loading and print graphical representation of loading in the container.
Right now i'm using coordinates system for collision detection and box representation inside container.

First, programm placing very first box in far left corner and after that starts loading boxes by right handside -> top -> infront.
Right now i'm using binary search for choosing best coordinates on which box should be placed new one.

Basically i want to make cheap and much simplier version of this https://www.searates.com/reference/stuffing/
