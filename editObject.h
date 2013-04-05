#include <WString.h>
#include <RTClib.h>
#include <LiquidCrystal.h>


class editObject {
private:
	int X, Y, Value, minVal, maxVal;
	LiquidCrystal* LCD;
	String leadingChar, ValueAsString;
    editObject *Next, *Prev;
	bool editMode;
public:
	void setXY(int x, int y);
	void setLeadingChar(String c);
	void setLCD (LiquidCrystal* newLCD);
	void setValue(int newValue);
	void setNext(editObject* next);
	void setPrev(editObject* prev);
	void print();
	editObject* getPrev();
	editObject* getNext();
	editObject(int x, int y, int minval, int maxval, LiquidCrystal* newLCD, editObject* next, editObject* prev);
	
};
