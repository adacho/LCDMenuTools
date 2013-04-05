#include <WString.h>
#include <RTClib.h>
#include <LiquidCrystal.h>


class editObject {
private:
	int X, Y, Value, minValue, maxValue;
	LiquidCrystal* LCD;
	String leadingChar, ValueAsString;
    editObject *Next, *Prev;
	bool readOnly, editMode;
public:
	void setXY(int x, int y);
	void setLeadingChar(String c);
	void setLCD (LiquidCrystal* newLCD);
	void setValue(int newValue);
	void incrementValue(int increment);
	void decrementValue(int decrement);
	void setNext(editObject* next);
	void setPrev(editObject* prev);
	void print();
	editObject* getPrev();
	editObject* getNext();
	editObject(int x, int y, int minval, int maxval, LiquidCrystal* newLCD, editObject* next, editObject* prev);
	void setReadOnly(bool mode);
	void setEditMode(bool mode);
	bool getEditMode();
};
