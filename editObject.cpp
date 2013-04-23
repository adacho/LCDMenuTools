#include "editObject.h"

void editObject::setXY(int x, int y)
{
  X = x;
  Y = y;
}

void editObject::setLeadingChar(unsigned char c)
{
  leadingChar = c;
}

void editObject::setLCD (LiquidCrystal* newLCD)
{
  LCD = newLCD;
}

void editObject::setValue(int newValue)
{
  if (newValue >= minValue && newValue <= maxValue && newValue != Value)
  {
    Value=newValue;
    ValueAsString = String(Value);
    if (ValueAsString.length() <= 1)
      ValueAsString = '0' + ValueAsString;
  }
}

void editObject::print()
{
  LCD->setCursor(X,Y);
  if (editMode)
  {
    LCD->write(byte(0));
    LCD->print(ValueAsString);
    LCD->write(byte(0));
  }
  else if (Active)
  {
    LCD->write(byte(1));
    LCD->print(ValueAsString);
    LCD->write(byte(2));
  }
  else
  {
    LCD->write(leadingChar);
    LCD->print(ValueAsString);
  }
}

void editObject::setNext(editObject* next)
{
  Next = next;
}

void editObject::setPrev(editObject* prev)
{
  Prev = prev;
}

editObject* editObject::getPrev()
{
  return Prev;
}

editObject* editObject::getNext()
{
  return Next;
}
editObject::editObject(int x, int y, int minval, int maxval, LiquidCrystal* newLCD, editObject* next, editObject* prev)
{
  X = x;
  Y = y;
  minValue = minval;
  maxValue = maxval;
  Value = minval;
  ValueAsString = String(Value);
  if (ValueAsString.length() <= 1)
    ValueAsString = '0' + ValueAsString;
  LCD = newLCD;
  Next = next;
  Prev = prev;
  Active = false;
  if (Prev != NULL) Prev->setNext(this);
  //if (Next != NULL) Next->setPrev(this);
  readOnly = true;
  editMode = false;
  if (next == NULL)
    Next = this;
  if (prev == NULL)
    Prev = this;
}

void editObject::setReadOnly(bool mode)
{
  readOnly = mode;
}

void editObject::incrementValue(int increment = 1)
{
  setValue(Value + increment);
}

void editObject::decrementValue(int decrement = 1)
{
  setValue(Value - decrement);
}

void editObject::setEditMode(bool mode)
{
  editMode=readOnly?false:mode;
}

bool editObject::getEditMode()
{
  return editMode;
}

void editObject::setActive(bool active)
{
  Active = active;
}

bool editObject::isActive()
{
  return Active;
}

void displayTime(editObject* h, editObject* m, editObject* s)
{
  editObject* t[] = {h, m, s};
  int act = -1;
  for (int i = 0; i < 3; i++)
  {
    if (t[i]->isActive() || t[i]->getEditMode()) act = i;
    else t[i]->print();
  }
  if (act>=0) t[act]->print();
}