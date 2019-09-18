
#include <matrixKeyboard.h>

// this config is for the big black keyboard 4x4
int rows[] = {3, 4, 5, 6};
int columns[] = {7, 8, 9, 2};
char codes[] = "123A456B789C*0#D";
#define NB_COLUMNS (sizeof(columns) / sizeof(int))
#define NB_ROWS (sizeof(rows) / sizeof(int))

MATRIX_KEYBOARD keyboard = MATRIX_KEYBOARD(columns, NB_COLUMNS, rows, NB_ROWS, codes);

const char PROGMEM title[] = "test of matrixKeyboard v. " MATRIX_KEYBOARD_VERSION;
const char PROGMEM callbackMessage[] = "Press '#' to use callback's way";
const char PROGMEM timestamp[] = __DATE__ " " __TIME__;

byte activeCallback = 0;

#define CONSOLE_OUT_DEV Serial

void cPrint(const char* address)
{
    while(pgm_read_byte(address))
        CONSOLE_OUT_DEV.write(pgm_read_byte(address++));
}

void cPrintLn(const char* address)
{
    cPrint(address);
    CONSOLE_OUT_DEV.write('\n');
}

void pollingPrint(byte key)
{
    Serial.write(key);
}

void callbackPrint(byte key)
{
    CONSOLE_OUT_DEV.print(F("callback "));
    Serial.write(key);
    Serial.write('\n');
}

void setup()
{
    keyboard.begin();
    CONSOLE_OUT_DEV.begin(9600);
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
        // let's read the buffer
        if(keyboard.available())
        {
            char key = keyboard.read();
            pollingPrint(key);
            if(key == '#')
            {
                // user want to install callback
                CONSOLE_OUT_DEV.println(F("\ncallback installed"));
                activeCallback = 1;
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


