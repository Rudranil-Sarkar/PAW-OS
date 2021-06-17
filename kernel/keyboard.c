#include "keyboard.h"

static u8 _CAPS_LOCK_STATUS = 0;
static u8 _SHIFT_STATUS = 0;
static u8 _CTRLSTATUS = 0;
static u8 _ALT_STATUS = 0;

char decode_scancode(u8 scancode)
{
     /**********************************************************************************************/
     /* TODO: This the most useless and bad implementation in the wold for keyboard special events */
     /* but this will do for now I will fix this later                                             */
     /**********************************************************************************************/

    if(scancode == 0x3A) { _CAPS_LOCK_STATUS = !_CAPS_LOCK_STATUS; return -0x02; }
    if(scancode == 0x2A) { _SHIFT_STATUS = 1; return -0x02; }

    if(scancode >= 0x58) {
        /********************/
        /* Release keys set */
        /********************/

        if(scancode == 0xAA) { _SHIFT_STATUS = 0; }

        return -0x03;
    }

    char keycode = *keycode_table[scancode];
    if(_CAPS_LOCK_STATUS)
    {
        if(keycode >= 'a' && keycode <= 'z')
            keycode = keycode - 32;
    }

    if (_SHIFT_STATUS)
    {
        if(keycode >= 'a' && keycode <= 'z')
            keycode = keycode - 32;

        if(keycode == '1') keycode = '!';
        if(keycode == '2') keycode = '@';
        if(keycode == '3') keycode = '#';
        if(keycode == '4') keycode = '$';
        if(keycode == '5') keycode = '%';
        if(keycode == '6') keycode = '^';
        if(keycode == '7') keycode = '&';
        if(keycode == '8') keycode = '*';
        if(keycode == '9') keycode = '(';
        if(keycode == '0') keycode = ')';

        if(keycode == '-') keycode = '_';
        if(keycode == '=') keycode = '+';

        if(keycode == '[') keycode = '{';
        if(keycode == ']') keycode = '}';
        if(keycode == '\\') keycode = '|';

        if(keycode == ';') keycode = ':';
        if(keycode == '\'') keycode = '"';

        if(keycode == ',') keycode = '<';
        if(keycode == '.') keycode = '>';
        if(keycode == '/') keycode = '?';
    }

    return keycode;
}
