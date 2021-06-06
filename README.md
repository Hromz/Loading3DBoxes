# Loading2DBoxes
Loading boxes into container.
This is my pet project that still in development.
Requires user to input quantity and box dimensions. After that calculates optimal box loading and print graphical representation of loading in the container.
Right now i'm using coordinates system for collision detection and box representation inside container.

First, programm placing very first box in far left corner and after that start loading boxes by right handside -> on top -> infront.
Right now i'm using binary search for choosing coordinates on which box should be placed new one.

Basically i want to make cheap and much simplier version of this https://www.searates.com/reference/stuffing/
