#include "editObject.h"

void editObject::setXY(int x, int y){
	X = x;
	Y = y;
}

void editObject::setLeadingChar(String c){
	leadingChar = c;
}

void editObject::setLCD (LiquidCrystal* newLCD){
	LCD = newLCD;
}

void editObject::setValue(int newValue){
	if (newValue != Value){
		Value=newValue;
		ValueAsString = String(Value);
		if (ValueAsString.length() <= 1){
			ValueAsString = '0' + ValueAsString;
		}
	}
}

void editObject::print(){
	LCD->setCursor(X,Y);
	LCD->print(leadingChar);
	LCD->print(ValueAsString);
}

void editObject::setNext(editObject* next){
	Next = next;
}
void editObject::setPrev(editObject* prev){
	Prev = prev;
}

editObject* editObject::getPrev(){
	return Prev;
}

editObject* editObject::getNext(){
	return Next;
}
editObject::editObject(int x, int y, int minval, int maxval, LiquidCrystal* newLCD, editObject* next, editObject* prev){
	X = x;
	Y = y;
	minVal = minval;
	maxVal = maxval;
	LCD = newLCD;
	Next = next;
	Prev = prev;
	editMode = false;
	if (next == NULL) {
		next = this;
	}
	if (prev == NULL) {
		prev = this;
	}
	
}