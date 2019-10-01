
#include <matrixKeyboard.h>

//~ int rows[] = {3, 4, 5, 6};
//~ int columns[] = {7, 8, 9, 2};
int  columns[] = {26, 24, 22, 36};
int  rows[]    = {34, 32, 30, 28};
const char codes[] PROGMEM = {'1', '2', '3', 'u', '4', '5', '6', 'r', '7', '8', '9', 'l', '*', '0', '#', 'd'};
MATRIX_KEYBOARD keyboard = MATRIX_KEYBOARD(columns, sizeof(columns) / sizeof(int), rows, sizeof(rows) / sizeof(int), codes);

const char PROGMEM title[] = "test of matrixKeyboard v. " MATRIX_KEYBOARD_VERSION;
const char PROGMEM callbackMessage[] = "Press '#' to use callback's way";
const char PROGMEM timestamp[] = __DATE__ " " __TIME__;

bool activeCallback = false;

void getKeyboardChar(byte index)
{
    return pgm_read_byte(codes + index);
}

void cPrint(const char* address)
{
    while(pgm_read_byte(address))
        Serial.write(pgm_read_byte(address++));
}

void cPrintLn(const char* address)
{
    cPrint(address);
    Serial.write('\n');
}

void pollingPrint(byte key)
{
    Serial.write(key);
}

void callbackPrint(byte key)
{
    if(key == '#')
    {
        activeCallback = false;
        keyboard.setPushHandler(NULL);
        Serial.print(F("callback removed!"));
    }
    else
    {
        Serial.print(F("callback "));
        Serial.write(key);
        Serial.write('\n');
    }
}

void setup()
{
    keyboard.begin();
    Serial.begin(9600);
    cPrintLn(title);
    cPrintLn(timestamp);
    cPrintLn(callbackMessage);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    keyboard.sequencer();
    
    if(!activeCallback)
    {
        // there is no callback installed,
        // let's use the usual way with available() and read()
        if(keyboard.available())
        {
            char key = keyboard.read();
            pollingPrint(key);
            if(key == '#')
            {
                //Let's install callback, no more usual way.
                Serial.println(F("\ncallback installed"));
                activeCallback = true;
                keyboard.setPushHandler(callbackPrint);
            }
        }
    }

        // let's blink status led
    if(millis() & 0x200)
        digitalWrite(LED_BUILTIN, 0);
    else
        digitalWrite(LED_BUILTIN, 1);
}


