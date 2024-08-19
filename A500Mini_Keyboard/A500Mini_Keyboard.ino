//####################################################################################################
//## Keyboard software for the A500Mini. It is created for an Arduino Leonardo, using it pinout.    ##
//## The final implementation is for 32U4 micro directly, to the RetroWiki's keyboard design.       ##
//## The project was created between Kikems_retro and Lince (ea4gge).                               ##
//## This soft was inspired on the soft of the project "Armapad36v2". I has it as example for       ##
//## this project. Actually here are nothing about that but it was my oun inspiration for the start ##
//## Many thanks to the creator of the software, it was esential for my own one.                    ##
//## Keypad by Community https://github.com/Chris--A/Keypad version 3.1.1                           ##
//## HID-Project by NicoHood https://github.com/NicoHood/HID version 2.8.2                          ##
//## Spetial TNANKS to Miguel Angel Vallejo, EA4EOZ. He gave us a great help during the Project     ##
//## You are free to use this code under GNU General Public License. You can use, distribute and    ##
//## modify  ONLY sharing all the changes for free. Read the License's Document for details.        ##
//####################################################################################################


//Keypad by Community https://github.com/Chris--A/Keypad version 3.1.1
#include <Keypad.h>

// HID-Project by NicoHood https://github.com/NicoHood/HID version 2.8.2
#include "HID-Project.h"

const byte capsLed = LED_BUILTIN_RX;
const byte ROWS = 8;
const byte COLS = 12;
byte colPins[COLS] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,  11};
byte rowPins[ROWS] = {12, 13, 18, 19, 20, 21, 22, 23};

// American Amiga layout
byte directKeys[ROWS][COLS] = {
//    0 (COL 1)       1 (COL 2)      2 (COL 3)        3 (COL 4)       4 (COL 5)      5 (COL 6)         6 (COL 7)      7 (COL 8)       8 (COL 9)       9 (COL 10)      10 (COL 11)       11  (COL 12)
// ==============  =============  ===============  ==============  ==============  ===============  =============  ===============  ===============  ==============  ===============  ===============  
  {KEY_ESC,        KEY_F1,        KEY_F2,          KEY_F3,         KEY_F4,         KEY_F5,          KEY_F6,        KEY_F7,          KEY_F8,          KEY_F9,         KEY_F10,         KEY_BACKSPACE   }, // 12     (ROW 1)
  {KEY_QUOTE,      KEY_1,         KEY_2,           KEY_3,          KEY_4,          KEY_5,           KEY_6,         KEY_7,           KEY_8,           KEY_9,          KEY_0,           KEY_MINUS       }, // 13     (ROW 2)
  {KEY_TAB,        KEY_Q,         KEY_W,           KEY_E,          KEY_R,          KEY_T,           KEY_Y,         KEY_U,           KEY_I,           KEY_O,          KEY_P,           KEY_LEFT_BRACE  }, // A0 (18)(ROW 3)
  {KEY_LEFT_CTRL,  KEY_CAPS_LOCK, KEY_A,           KEY_S,          KEY_D,          KEY_F,           KEY_G,         KEY_H,           KEY_J,           KEY_K,          KEY_L,           KEY_SEMICOLON   }, // A1 (19)(ROW 4)
  {KEY_LEFT_SHIFT, KEY_Z,         KEY_X,           KEY_C,          KEY_V,          KEY_B,           KEY_N,         KEY_M,           KEY_COMMA,       KEY_PERIOD,     KEY_SLASH,       KEY_RIGHT_SHIFT }, // A2 (20)(ROW 5)
  {KEY_LEFT_ALT,   KEY_LEFT_GUI,  KEY_SPACE,       KEY_RIGHT_GUI,  KEY_RIGHT_ALT,  KEY_DELETE,      KEY_PAGE_DOWN, KEY_LEFT_ARROW,  KEY_UP_ARROW,    KEY_DOWN_ARROW, KEY_RIGHT_ARROW, KEY_RETURN      }, // A3 (21)(ROW 6)
  {KEY_EQUAL,      KEY_BACKSLASH, KEY_RIGHT_BRACE, KEY_QUOTE,      KEY_LEFT_BRACE, KEY_RIGHT_BRACE, KEYPAD_DIVIDE, KEYPAD_MULTIPLY, KEYPAD_SUBTRACT, KEYPAD_ADD,     KEYPAD_ENTER,    KEY_F11         }, // A4 (22)(ROW 7)
  {KEYPAD_0,       KEYPAD_1,      KEYPAD_2,        KEYPAD_3,       KEYPAD_4,       KEYPAD_5,        KEYPAD_6,      KEYPAD_7,        KEYPAD_8,        KEYPAD_9,       KEYPAD_DOT,      KEY_F12         }  // A5 (23)(ROW 8)
};

Keypad kpd = Keypad(makeKeymap(directKeys), rowPins, colPins, ROWS, COLS);



void setup() {
  pinMode(capsLed, OUTPUT);

  // Sends a clean report to the host. This is important on any Arduino type.
  BootKeyboard.begin();
}


void loop() {
  //
  // Update CapsLock Led
  //
  if (BootKeyboard.getLeds() & LED_CAPS_LOCK)
    digitalWrite(capsLed, HIGH);
  else
    digitalWrite(capsLed, LOW);



  //
  // Process keys
  //
  if (kpd.getKeys()) {
    for (int i=0; i<LIST_MAX; i++){  // Scan the whole key list.
      if (kpd.key[i].stateChanged){  // Only find keys that have changed state.
        switch (kpd.key[i].kstate){  // Report changes to host

          case PRESSED:
            BootKeyboard.press(KeyboardKeycode(kpd.key[i].kchar));
            break;

          case HOLD:
            break;
                    
          case RELEASED:
            BootKeyboard.release(KeyboardKeycode(kpd.key[i].kchar));
            break;
                    
          case IDLE:
            break;
        }
      }
    }
  }
}
