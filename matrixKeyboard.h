/*
 * file : matrixKeyboard.h
 * Copyright (c) pfeuh <ze.pfeuh@gmail>
 * All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef matrixKeyboard_h
#define matrixKeyboard_h

#include <Arduino.h>

#define MATRIX_KEYBOARD_VERSION "1.00"

typedef void (*MATRIX_KEYBOARD_type_callback)(byte bt_num);

class MATRIX_KEYBOARD
{
    public:
        MATRIX_KEYBOARD(int* column_pins, byte nb_columns, int* row_pins, byte nb_rows, const char* codes);
        void begin();
        void setPushHandler(MATRIX_KEYBOARD_type_callback callback);
        byte available();
        byte read();
        void sequencer();

    private:
        byte getState(byte column, byte row);
        void setState(byte column, byte row, byte state);
        byte getCode(byte column, byte row);
    
        int* columnPins;
        byte nbColumns;
        int* rowPins;
        byte nbRows;
        char* codes;
        MATRIX_KEYBOARD_type_callback pushHandler;
        byte _available;
        byte buffer;
};

#endif

