<span style="align:center">
# Arduino Windows and Windows Manager
</span>

<span style="align:center">
## Abstract
</span>

A simple library to draw windows on TFT LCD with Arduino.<br>
This library relies on UTFT library by Henning Karlsen (http://www.rinkydinkelectronics.com/library.php?id=51) and modified by Damian Golda (https://github.com/dgolda/UTFT) for the low-level communications between Arduino and the TFT LCD.<br>
All the TFT LCD compatible with the UTFT library, should be compatible with this library too.

<span style="align:center">
## Window
</span>

Defines the drawable area of the window and draws the borders.

<span style="align:center">
### Window interface
</span>

**Constructor**
You can initialize the windows with two arrays for the size and the position or giving the dimentions, one by one (Size X, Size Y, Position X, Position Y)
>**window**(&tft,&size,&position)<br>
>**window**(&tft,sizeX,sizeY,positionX,positionY)

**Text**
This is for writing text in the window
>**text**(text)

<span style="align:center">
## Window Manager
</span>

It supersedes the creation of the Windows and checks for overlaps: if some windows overlaps the previous ones, it just doesn't create the overlapping one.

<span style="align:center">
[![Creative Commons License](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png "Creative Commons License")](http://creativecommons.org/licenses/by-nc-sa/4.0/)
</span>