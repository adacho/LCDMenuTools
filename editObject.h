#ifndef EDITOBJECT_H
#define EDITOBJECT_H

#include <WString.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

class editObject
{
  private:
    int X, Y, Value, minValue, maxValue;
    LiquidCrystal_I2C* LCD;
    String ValueAsString;
    unsigned char leadingChar;
    editObject *Next, *Prev;
    bool readOnly, editMode, Active;
  public:
    void setXY(int x, int y);
    void setLeadingChar(unsigned char c);
    void setActive(bool active);
    bool isActive();
    void setLCD (LiquidCrystal_I2C* newLCD);
    void setValue(int newValue);
    void incrementValue(int increment);
    void decrementValue(int decrement);
    void setNext(editObject* next);
    void setPrev(editObject* prev);
    void print();
    editObject* getPrev();
    editObject* getNext();
    editObject(int x, int y, int minval, int maxval, LiquidCrystal_I2C* newLCD, editObject* next, editObject* prev);
    void setReadOnly(bool mode);
    void setEditMode(bool mode);
    bool getEditMode();
};

void displayTime(editObject* h, editObject* m, editObject* s);

#endif
