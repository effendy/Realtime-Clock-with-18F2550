#ifndef BUTTON_H
#define BUTTON_H
//
// Written by: Tony DeRose, August 2010
// Updated: Feburary 2012
// 
#include "Arduino.h"

//
// Represents a button attached to a pin. The pin can either be an analog or digital
// pin as specified by the third argument to the constructor.
//
// The button can store a keyboard equivalent character for keyboard emulation applications.
//
// Debouncing is done to make the results of isPressed() and wasPressed() more reliable.
//
class Button
{
  public:
    Button(uint8_t buttonPin, bool isPinAnalog, bool pressedWhenLOW = false);
	
    Button();
	
    void Initialize(uint8_t buttonPin, bool isPinAnalog, bool pressedWhenLOW = false);

    // For keyboard emulation
    void SetKey( char key);

    char GetKey() {
        return key;
    }

    // Call this immediately prior to calling the other accessors.
    void Update();
    
    // Return true if the debounced state of the button is pressed.
    bool IsPressed();

    // Return true if the debounced state of the button was pressed since the last time it was queried.
    bool WasPressed();
    
    // Return true if the debounced state of the button was released since the last time it was quieried.
    bool WasReleased();
    
    // Return the instantaneous (non-debounced) state of the pin attached to the button
    uint8_t ReadState();
    
    
  private:
    char    key;
    bool    isAnalogPin;
    uint8_t pin;
    uint8_t pressedState;
    uint8_t prevState;
    uint8_t openState;
    uint8_t state;
    long int time;             // The time at which the button was last pressed
};
#endif

