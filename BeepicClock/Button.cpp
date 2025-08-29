#include "Button.h"

#define INDETERMINANT    4            // Indicates an indeterminant state
#define DEBOUNCE         5            // # of milliseconds to wait for state to settle

Button::Button(uint8_t buttonPin, bool isPinAnalog, bool pressedWhenLOW)
{
  pin = buttonPin;
  isAnalogPin = isPinAnalog;
  if (!isAnalogPin) pinMode( buttonPin, INPUT);

  if (pressedWhenLOW) {
      pressedState = LOW;
      openState    = HIGH;
  } else {
      pressedState = HIGH;
      openState    = LOW;
  }
  state = openState;                   // Debounced current state/
  prevState = openState;               // Debounced previous state
}

Button::Button()
{
}

void Button::Initialize( uint8_t buttonPin, bool isPinAnalog, bool pressedWhenLOW )
{
  pin = buttonPin;
  isAnalogPin = isPinAnalog;
  if (pressedWhenLOW) {
      pressedState = LOW;
      openState    = HIGH;
  } else {
      pressedState = HIGH;
      openState    = LOW;
  }
  state = openState;                   // Debounced current state/
  prevState = openState;  	
}

bool Button::IsPressed()
{
  return (ReadState() == pressedState);
}

bool Button::WasPressed()
{
  if (state == pressedState && prevState == openState) return true;
  return false;
}

bool Button::WasReleased()
{
  if (state == openState && prevState == pressedState) return true;
  return false;
}

uint8_t Button::ReadState()
{
  if (isAnalogPin) {
    if (analogRead(pin) > 1000) {
      return HIGH;
    } else {
      return LOW;
    }
  }
  return digitalRead(pin);
}

void Button::SetKey( char aKey)
{
    key = aKey;
}

void Button::Update()
{
    if (state == INDETERMINANT) {
        // If we're still in the settling period, keep waiting
        if (millis() - time < DEBOUNCE) {
            // Serial.println("W");
            return;
        }
        
        // State should be reliable now
        // Serial.println("D");
        state = ReadState();
        return;
    }

    uint8_t instantaneousState = ReadState();
  
    if (instantaneousState != state) {          // We're moving into indeterminant state
        prevState = state;
        state = INDETERMINANT;
        time = millis();
        // Serial.println("I");
        return;
    }

    if (instantaneousState == state && state == prevState) { // We're in an constant state
        return;
    }

    prevState = state;
    state = instantaneousState;
}

