//##################################################################################################
//## Keyboard software for the A500Mini. It is created for an Arduino Leonardo, using it pinout.  ##
//## The final implementation is for 32U4 micro directly, to the RetroWiki's keyboard design.     ##
//## The mechanical part was created between Kikems_retro and Lince (ea4gge).                     ##
//## Soft and Electronic design was made by Lince.                                                ##
//## This soft was inspired on the soft of the project "Armapad36v2". I has it as example for this##
//## Many thanks to the creator of the software, it was esential for my own one                   ## 
//## You are free to use this code under GNU General Public License. You can use, distribute and  ##
//## modify  ONLY for free. Read the License's Document for details.                              ##
//##################################################################################################

#include <Keypad.h>
#include <Keyboard.h>
const byte ROWS = 8; // rows
const byte COLS = 12; // columns
byte colPins[COLS] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; //row pinouts of the keypad
byte rowPins[ROWS] = {12, 13, 18, 19, 20, 21, 22, 23}; //column pinouts of the keypad
//
//define the keys of the keyboard as American Amiga layout, one for normal
//
char directKeys[ROWS][COLS] = {
  
  {KEY_ESC, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_BACKSPACE},
  {39, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-'},
  {KEY_TAB, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '['},
  {KEY_LEFT_CTRL, KEY_CAPS_LOCK,'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';'},
  {KEY_LEFT_SHIFT, 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', KEY_RIGHT_SHIFT},
  {KEY_LEFT_ALT, KEY_LEFT_GUI, ' ', KEY_RIGHT_GUI, KEY_RIGHT_ALT, KEY_DELETE, KEY_PAGE_DOWN, KEY_LEFT_ARROW, KEY_UP_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW, KEY_RETURN},
  {'=', '\\', ']', '#', 219, ')', 220, 221, 222, 223, 224, 235},
  {234, 225, 226, 227, 228, 229, 230, 231, 232, 233, ' ', ' ', }
 
};

byte Layout = 0;
char Key = 0;
byte State = 0;
const bool KeybInit = true;

Keypad kpd = Keypad( makeKeymap(directKeys), rowPins, colPins, ROWS, COLS );
unsigned long loopCount;
unsigned long startTime;

void setup() {
  Keyboard.begin();
    loopCount = 0;
    startTime = millis();

  // KeybInit
  if (KeybInit) {
 
  }
}

void loop() {
    loopCount++;
    if ( (millis()-startTime)>5000 ) {
        startTime = millis();
        loopCount = 0;
    }
    
    // Fills kpd.key[ ] array with up-to 10 active keys.
    // Returns true if there are ANY active keys.
    if (kpd.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
        {
            if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
            {
                switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED:
               Keyboard.press(kpd.key[i].kchar);
               break;

                    case HOLD:
                Keyboard.press(kpd.key[i].kchar);
                break;

                    case RELEASED:
               Keyboard.releaseAll();
               for (int i=0; i<LIST_MAX; i++){
                if (kpd.key[i].kchar == char(KEY_LEFT_SHIFT)) {
               
               Keyboard.press(KEY_LEFT_SHIFT);
               switch (kpd.key[i].kstate) {
                      case RELEASED:
               Keyboard.releaseAll();
               }
               }
                if (kpd.key[i].kchar == char(KEY_RIGHT_SHIFT)) {
               
               Keyboard.press(KEY_RIGHT_SHIFT);
               switch (kpd.key[i].kstate) {
                      case RELEASED:
               Keyboard.releaseAll();
               }
               }
                if (kpd.key[i].kchar == char(KEY_LEFT_CTRL)) {
               
               Keyboard.press(KEY_LEFT_CTRL);
               switch (kpd.key[i].kstate) {
                      case RELEASED:
               Keyboard.releaseAll();
               }
               }
                if (kpd.key[i].kchar == char(KEY_LEFT_CTRL)) {
               
               Keyboard.press(KEY_LEFT_CTRL);
               switch (kpd.key[i].kstate) {
                      case RELEASED:
               Keyboard.releaseAll();
               }
               }
/*                if (kpd.key[i].kchar == char(KEY_LEFT_GUI)) {
               
               Keyboard.press(KEY_LEFT_GUI);
               switch (kpd.key[i].kstate) {
                      case RELEASED:
               Keyboard.releaseAll();
               }
               }
                if (kpd.key[i].kchar == char(KEY_RIGHT_GUI)) {
               
               Keyboard.press(KEY_RIGHT_GUI);
               switch (kpd.key[i].kstate) {
                      case RELEASED:
               Keyboard.releaseAll();
               }
               }*/
                if (kpd.key[i].kchar == char(KEY_LEFT_ALT)) {
               
               Keyboard.press(KEY_LEFT_ALT);
               switch (kpd.key[i].kstate) {
                      case RELEASED:
               Keyboard.releaseAll();
               }
               }
                if (kpd.key[i].kchar == char(KEY_RIGHT_ALT)) {
               
               Keyboard.press(KEY_RIGHT_ALT);
               switch (kpd.key[i].kstate) {
                      case RELEASED:
               Keyboard.releaseAll();
               }
               }

              }
                break;
                  
               
                    case IDLE:
 //               Keyboard.releaseAll();        
                  break;
                   
                }
                
            }
        }
    }
}
