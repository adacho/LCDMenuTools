#ifndef RELAYCHANNEL_H
#define RELAYCHANNEL_H
#include <Arduino.h>

enum rcMode {timer, event, schedule};

class  relayChannel {
private:
	bool Enabled; //is channel active
	bool Active; //is channel working now
	rcMode Mode; // is channel set to work in timer mode, schedule (user defined) or eventMode
	int ActivationValue, DeactivationValue; //used in event mode to activate/deactivate module
	int Pin; // Channel is attached to this pin
public:
	void enableModule(bool newState);
	void setActive(bool newState);
	void setMode(rcMode mode);
	bool setActivationValue(int newValue);
	bool setDeactivationValue(int newValue);
	bool isActive();
	bool isEnabled();
	relayChannel(int newPin, bool enabled, bool active, rcMode mode, int activationvalue, int deactivationvalue);
};
	
#endif
