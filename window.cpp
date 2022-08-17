/*
 * window.cpp
 *
 *  Created on: 9 ago 2022
 *  Author: Francesco Antonetti Lamorgese Passeri
 *  Version: 1.0
 *  License: CC-BY-SA 4.0 (https://creativecommons.org/licenses/by-sa/4.0/)
 *  This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
 */

#ifndef WINDOW_HPP_
#include "window.hpp"
#endif

#include "Arduino.h"

//#define DEBUG

window::window(UTFT& tft,int* size,int* position) : tft{tft},position{position[0],position[1]},size{size[0],size[1]},fontSize{tft.getFontXsize(),tft.getFontYsize()}
{
	this->drawBorders();
}
window::window(UTFT& tft,int sizeX,int sizeY,int positionX,int positionY) : tft{tft},position{positionX,positionY},size{sizeX,sizeY},fontSize{tft.getFontXsize(),tft.getFontYsize()}
{
	this->drawBorders();
}
int* window::getSize()
{
	return this->size;
}
int* window::getPosition()
{
	return this->position;
}
void window::drawBorders()
{
	this->tft.drawRect(this->position[0],this->position[1],this->size[0]+this->position[0],this->size[1]+this->position[1]);
}
void window::clearWindow()
{
	int previousColor = tft.getColor();

	this->tft.setColor(0);
	this->tft.fillRect(this->position[0],this->position[1],this->size[0]+this->position[0],this->size[1]+this->position[1]);
	this->tft.setColor(previousColor);
	this->drawBorders();
}
void window::text(String text)
{
	int textLength;
	int textPositionX;
	int textPositionY;
	int fontSizeX = this->tft.getFontXsize();
	int maxLineChars = this->size[0]/fontSizeX;

	textLength = this->tft.getFontXsize()*text.length();
#ifdef DEBUG
	Serial.print("Text length: ");
	Serial.println(text.length());
#endif
	if((textLength < this->size[0]) && (text.indexOf("\n") < 0))
	{
		textPositionX = (this->position[0]+(this->size[0]-textLength)/2);
		textPositionY = (this->position[1]+(this->size[1]-this->tft.getFontYsize())/2);
		this->tft.print(text,textPositionX,textPositionY);
	}
	else
	{
		const int numLines = (this->size[1]-2)/this->tft.getFontYsize();
		String lines[numLines];

		for(int textIndex=0,lineNumber=0;lineNumber < numLines;++lineNumber)
		{
			String line = text.substring(textIndex,(textIndex+maxLineChars < text.length()) ? textIndex+maxLineChars : textIndex+text.length());
			int newLine = line.indexOf("\n");
#ifdef DEBUG
			Serial.print("textIndex: ");
			Serial.println(textIndex);
			Serial.print("line: ");
			Serial.println(line);
#endif
			if((newLine > -1) && (newLine <= text.length()))
			{
				line = line.substring(0,newLine);
				text.remove(text.indexOf("\n"),1);
				line.remove(line.indexOf("\n"),1);
#ifdef DEBUG
				Serial.print("text: ");
				Serial.println(text);
				Serial.print("line: ");
				Serial.println(line);
				Serial.println();
#endif
				if(line.length())
					lines[lineNumber] = line;
				else
					--lineNumber;
				if(textIndex < text.length())
					textIndex += newLine;
				else
					break;
				continue;
			}
#ifdef DEBUG
			Serial.print("text: ");
			Serial.println(text);
			Serial.print("line: ");
			Serial.println(line);
			Serial.println();
#endif
			lines[lineNumber] = line;
			if(textIndex < text.length())
				(textIndex+maxLineChars < text.length()) ? textIndex += maxLineChars : textIndex = text.length();
			else
				break;
		}
		for(int i=0;i<numLines;i++)
		{
			if(lines[i]!="")
			{
			  textPositionX = this->position[0]+1;
			  textPositionY = this->position[1]+i*this->tft.getFontYsize()+1;
			  this->tft.print(lines[i],textPositionX,textPositionY);
			}
			else
			  break;
		}
	}
}
