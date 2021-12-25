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
        switch (keycode) {
            case 'a' ... 'z': keycode = keycode - 32; break;
            case '1'  : keycode = '!'; break;
            case '2'  : keycode = '@'; break;
            case '3'  : keycode = '#'; break;
            case '4'  : keycode = '$'; break;
            case '5'  : keycode = '%'; break;
            case '6'  : keycode = '^'; break;
            case '7'  : keycode = '&'; break;
            case '8'  : keycode = '*'; break;
            case '9'  : keycode = '('; break;
            case '0'  : keycode = ')'; break;
            case '-'  : keycode = '_'; break;
            case '='  : keycode = '+'; break;
            case '['  : keycode = '{'; break;
            case ']'  : keycode = '}'; break;
            case '\\' : keycode = '|'; break;
            case ';'  : keycode = ':'; break;
            case '\'' : keycode = '"'; break;
            case ','  : keycode = '<'; break;
            case '.'  : keycode = '>'; break;
            case '/'  : keycode = '?'; break;
        }
    }

    return keycode;
}
