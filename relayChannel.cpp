#include "relayChannel.h"

void relayChannel::enableModule(bool newState)
{
  if (Enabled != newState) Enabled = newState;
}

void relayChannel::setActive(bool newState)
{
  if (Enabled && Active != newState)
  {
    Active = newState;
    (newState)?digitalWrite(Pin, HIGH):digitalWrite(Pin, LOW);
  }
}

void relayChannel::setMode(rcMode mode)
{
  Mode = mode;
}

bool relayChannel::setActivationValue(int newValue)
{
  if (newValue < DeactivationValue) ActivationValue = newValue;
  return (newValue < DeactivationValue);
}

bool relayChannel::setDeactivationValue(int newValue)
{
  if (newValue > ActivationValue) DeactivationValue = newValue;
  return (newValue > ActivationValue);
}

bool relayChannel::isActive()
{
  return Active;
}

bool relayChannel::isEnabled()
{
  return Enabled;
}

relayChannel::relayChannel(int newPin, bool enabled, bool active, rcMode mode, int activationvalue, int deactivationvalue)
{
  Pin = newPin;
  Enabled = enabled;
  Active = active;
  Mode = mode;
  if (activationvalue < deactivationvalue)
  {
    ActivationValue = activationvalue;
    DeactivationValue = deactivationvalue;
  }
  else
  {
    ActivationValue = deactivationvalue;
    DeactivationValue = activationvalue;
  }
}