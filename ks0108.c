#include "ks0108.h"

void ks0108_init(volatile unsigned int *DATA_OR_INSTRUCTION, volatile unsigned int * READ_WRITE, volatile unsigned int *E, volatile unsigned int *CS1, volatile unsigned int *CS2, volatile unsigned int **DATA_BUS) {
    unsigned short int i;
    _ks0108_DI = DATA_OR_INSTRUCTION;
    _ks0108_DI_CLR = __SFR_PORTCLR(DATA_OR_INSTRUCTION);
    _ks0108_DI_SET = __SFR_PORTSET(DATA_OR_INSTRUCTION);
    *(__SFR_TRISCLR(DATA_OR_INSTRUCTION)) = _ks0108_DI_MASK; //clr tristate, set as output port [always]
    //set to low
    *_ks0108_DI_CLR = _ks0108_DI_MASK;

    _ks0108_RW = READ_WRITE;
    _ks0108_RW_CLR = __SFR_PORTCLR(READ_WRITE);
    _ks0108_RW_SET = __SFR_PORTSET(READ_WRITE);
    *(__SFR_TRISCLR(READ_WRITE)) = _ks0108_RW_MASK; //clr tristate, set as output port [always]
    //set to low
    *_ks0108_RW_CLR = _ks0108_RW_MASK;

    _ks0108_E = E;
    _ks0108_E_CLR = __SFR_PORTCLR(E);
    _ks0108_E_SET = __SFR_PORTSET(E);
    *(__SFR_TRISCLR(E)) = _ks0108_E_MASK; //clr tristate, set as output port [always]
    //set to low
    *_ks0108_E_CLR = _ks0108_E_MASK;

    _ks0108_CS1 = CS1;
    _ks0108_CS1_CLR = __SFR_PORTCLR(CS1);
    _ks0108_CS1_SET = __SFR_PORTSET(CS1);
    *(__SFR_TRISCLR(CS1)) = _ks0108_CS1_MASK; //clr tristate, set as output port [always]
    //set to low
    *_ks0108_CS1_CLR = _ks0108_CS1_MASK;

    _ks0108_CS2 = CS2;
    _ks0108_CS2_CLR = __SFR_PORTCLR(CS2);
    _ks0108_CS2_SET = __SFR_PORTSET(CS2);
    *(__SFR_TRISCLR(CS2)) = _ks0108_CS2_MASK; //clr tristate, set as output port [always]
    //set to low
    *_ks0108_CS2_CLR = _ks0108_CS2_MASK;

    for (i = 0; i < 8; ++i) {
        _ks0108_DB[i] = DATA_BUS[i];
        _ks0108_DB_CLR[i] = __SFR_PORTCLR(DATA_BUS[i]);
        _ks0108_DB_SET[i] = __SFR_PORTSET(DATA_BUS[i]);
        *(__SFR_TRISCLR(_ks0108_DB[i])) = _ks0108_DB_MASK[i]; //clr tristate, set as output
        //set to low
        *_ks0108_DB_CLR[i] = _ks0108_DB_MASK[i];
    }

    ks0108_set_side(ks0108_LEFT);
    ks0108_set_state(ks0108_ON); //left screen on
    ks0108_set_side(ks0108_RIGHT);
    ks0108_set_state(ks0108_ON); //right screen on
    ks0108_set_start_line(0);
    ks0108_cls(); //clear both
    _ks0108_X = _ks0108_Y = 0; //update global positions
}

void ks0108_set_state(ks0108_display_state state) {

    *(_ks0108_DI_CLR) = _ks0108_DI_MASK;
    *(_ks0108_RW_CLR) = _ks0108_RW_MASK;

    __ks0108_SET_DB_AS_OUTPUT();

    *(_ks0108_DB_CLR[7]) = _ks0108_DB_MASK[7];
    *(_ks0108_DB_CLR[6]) = _ks0108_DB_MASK[6];
    *(_ks0108_DB_SET[5]) = _ks0108_DB_MASK[5];
    *(_ks0108_DB_SET[4]) = _ks0108_DB_MASK[4];
    *(_ks0108_DB_SET[3]) = _ks0108_DB_MASK[3];
    *(_ks0108_DB_SET[2]) = _ks0108_DB_MASK[2];
    *(_ks0108_DB_SET[1]) = _ks0108_DB_MASK[1];

    switch (state) {
        case ks0108_OFF:
            *(_ks0108_DB_CLR[0]) = _ks0108_DB_MASK[0];
            break;

        case ks0108_ON:
            *(_ks0108_DB_SET[0]) = _ks0108_DB_MASK[0];
            break;
    }

    __ks0108_COMMIT();
}

void ks0108_set_address(unsigned short int data_bus_bitmask) {
    unsigned short int i;
    *(_ks0108_DI_CLR) = _ks0108_DI_MASK;
    *(_ks0108_RW_CLR) = _ks0108_RW_MASK;

    __ks0108_SET_DB_AS_OUTPUT();

    *(_ks0108_DB_CLR[7]) = _ks0108_DB_MASK[7];
    *(_ks0108_DB_SET[6]) = _ks0108_DB_MASK[6];

    //Y address 0-63 (6 bit in the bitmask)
    for (i = 0; i < 6; ++i) {
        if (1 & (data_bus_bitmask >> i))
            *(_ks0108_DB_SET[i]) = _ks0108_DB_MASK[i];
        else
            *(_ks0108_DB_CLR[i]) = _ks0108_DB_MASK[i];
    }

    _ks0108_Y = data_bus_bitmask; //update Y coord

    __ks0108_COMMIT();
}

void ks0108_set_page(unsigned short int data_bus_bitmask) {
    unsigned short int i;
    *(_ks0108_DI_CLR) = _ks0108_DI_MASK;
    *(_ks0108_RW_CLR) = _ks0108_RW_MASK;

    __ks0108_SET_DB_AS_OUTPUT();

    *(_ks0108_DB_SET[7]) = _ks0108_DB_MASK[7];
    *(_ks0108_DB_CLR[6]) = _ks0108_DB_MASK[6];
    *(_ks0108_DB_SET[5]) = _ks0108_DB_MASK[5];
    *(_ks0108_DB_SET[4]) = _ks0108_DB_MASK[4];
    *(_ks0108_DB_SET[3]) = _ks0108_DB_MASK[3];

    //X address 0-7 (3 bit in the bitmask)
    for (i = 0; i < 3; ++i) {
        if (1 & (data_bus_bitmask >> i))
            *(_ks0108_DB_SET[i]) = _ks0108_DB_MASK[i];
        else
            *(_ks0108_DB_CLR[i]) = _ks0108_DB_MASK[i];
    }

    _ks0108_X = data_bus_bitmask;

    __ks0108_COMMIT();
}

void ks0108_set_start_line(unsigned short int data_bus_bitmask) {
    unsigned short int i;
    *(_ks0108_DI_CLR) = _ks0108_DI_MASK;
    *(_ks0108_RW_CLR) = _ks0108_RW_MASK;

    __ks0108_SET_DB_AS_OUTPUT();

    *(_ks0108_DB_SET[7]) = _ks0108_DB_MASK[7];
    *(_ks0108_DB_SET[6]) = _ks0108_DB_MASK[6];

    //Y address 0-63 (6 bit in the bitmask)
    for (i = 0; i < 6; ++i) {
        if (1 & (data_bus_bitmask >> i))
            *(_ks0108_DB_SET[i]) = _ks0108_DB_MASK[i];
        else
            *(_ks0108_DB_CLR[i]) = _ks0108_DB_MASK[i];
    }
    __ks0108_COMMIT();
}

void ks0108_write_data(unsigned short int data_bus_bitmask) {
    unsigned short int i;

    *(_ks0108_DI_SET) = _ks0108_DI_MASK;
    *(_ks0108_RW_CLR) = _ks0108_RW_MASK;

    __ks0108_SET_DB_AS_OUTPUT();

    //8 bit buffer
    for (i = 0; i < 8; ++i) {
        if (1 & (data_bus_bitmask >> i))
            *(_ks0108_DB_SET[i]) = _ks0108_DB_MASK[i];
        else
            *(_ks0108_DB_CLR[i]) = _ks0108_DB_MASK[i];
    }

    __ks0108_COMMIT();
}

void ks0108_write_string(char *string) {
    short int i, s;

begin: //a label, yes. It's a label used by a goto. [OMG SPAGHETTI CODE!1! stfu]
    while (*string != 0) {

        //handling white space to the end of characters, i > 1, avoid to write it
        for (s = -1, i = 6; i > -1; --i) {
            if (_ks0108_ascii[*string][i]) {
                s = i;
                break;
            }
        }
        //if i == -1, all 0 -> space
        if (i == -1) // -> s = -1
            i = 2; //space is 2 px wide
        else if (!s) //no space, but 1 char found
            i = 1;

        if (_ks0108_Y + i + 1 > 127) //go on new line, or to start line
        {
            __ks0108_NEWLINE();
            if (*string == ' ' || *string == '\n') {
                ++string;
                goto begin;
            }
        }

        if (*string == '\n') {
            __ks0108_NEWLINE();
            ++string;
            goto begin;
        }

        if (s == -1) //space
        {
            ks0108_write_data(0);
            ks0108_write_data(0);
            _ks0108_Y += 2;
        } else {
            for (s = 0, ++i; s < i; ++s) { //foreach column in bitmap (with values)

                ks0108_write_data(_ks0108_ascii[*string][s]);

                ++_ks0108_Y;

                if (_ks0108_Y >= 64) //on write, Y always increment by 1
                {
                    //begin RIGHT display
                    ks0108_set_side(ks0108_RIGHT);
                    __ks0108_GOTO_XY(_ks0108_X, _ks0108_Y); //every time I change display side, I have to refresh memory with the correct addresses
                }
            }
            ks0108_write_data(0); //spacing after letter
            ++_ks0108_Y;
            if (_ks0108_Y >= 64) //on write, Y always increment by 1
            {
                //begin RIGHT display
                ks0108_set_side(ks0108_RIGHT);
                __ks0108_GOTO_XY(_ks0108_X, _ks0108_Y); //every time I change display side, I have to refresh memory with the correct addresses
            }
        }
        ++string;
    }
}

unsigned short int ks0108_read_data() {
    unsigned short int i, data = 0;

    *(_ks0108_DI_SET) = _ks0108_DI_MASK;
    *(_ks0108_RW_SET) = _ks0108_RW_MASK;

    ks0108_e_high();

    __ks0108_SET_DB_AS_INPUT();

    //8 bit buffer
    for (i = 0; i < 8; ++i) {
        data |= ((*(_ks0108_DB[i]) & _ks0108_DB_MASK[i]) != 0) << i;
    }

    ks0108_e_low();

    __ks0108_SET_DB_AS_OUTPUT();

    return data;
}

ks0108_status ks0108_status_read(void) {
    ks0108_status status;

    *(_ks0108_DI_SET) = _ks0108_DI_MASK;
    *(_ks0108_RW_SET) = _ks0108_RW_MASK;

    __ks0108_SET_DB_AS_OUTPUT();

    *(_ks0108_DB_CLR[6]) = _ks0108_DB_MASK[6];
    *(_ks0108_DB_CLR[3]) = _ks0108_DB_MASK[3];
    *(_ks0108_DB_CLR[2]) = _ks0108_DB_MASK[2];
    *(_ks0108_DB_CLR[1]) = _ks0108_DB_MASK[1];
    *(_ks0108_DB_CLR[0]) = _ks0108_DB_MASK[0];

    ks0108_e_high();

    __ks0108_SET_DB_AS_INPUT();

    status.busy = (*(_ks0108_DB[7]) & _ks0108_DB_MASK[7]) != 0;
    status.state = (*(_ks0108_DB[5]) & _ks0108_DB_MASK[5]) != 0 ? ks0108_OFF : ks0108_ON;
    status.reset = (*(_ks0108_DB[4]) & _ks0108_DB_MASK[4]) != 0;

    ks0108_e_low();

    __ks0108_SET_DB_AS_OUTPUT();

    return status;
}

void ks0108_e_high(void) {
    *(_ks0108_E_SET) = _ks0108_E_MASK;
    type_b_active_delay_us(1);
}

void ks0108_e_low(void) {
    *(_ks0108_E_CLR) = _ks0108_E_MASK;
    type_b_active_delay_us(1);
}

void ks0108_set_side(ks0108_side side) //negative logic
{
    if (side == ks0108_RIGHT) {
        *(_ks0108_CS1_CLR) = _ks0108_CS1_MASK;
        *(_ks0108_CS2_SET) = _ks0108_CS2_MASK;
    } else {
        *(_ks0108_CS1_SET) = _ks0108_CS1_MASK;
        *(_ks0108_CS2_CLR) = _ks0108_CS2_MASK;
    }
    //__ks0108_COMMIT();
}

void ks0108_cls(void) {
    unsigned short int x, y;
    for (x = 0; x < 8; ++x) {
        ks0108_set_side(ks0108_LEFT);
        __ks0108_GOTO_XY(x, 0);
        for (y = 0; y < 64; ++y) //first half
            ks0108_write_data(0); //clear

        ks0108_set_side(ks0108_RIGHT);
        __ks0108_GOTO_XY(x, y);
        for (y; y < 128; ++y) //2nd half
            ks0108_write_data(0); //clear
    }
    ks0108_set_side(ks0108_LEFT);
    __ks0108_GOTO_XY(0, 0);
}

//Mnemonic aliases
void ks0108_set_y_address(unsigned short int data_bus_bitmask) __attribute__((alias("ks0108_set_address")));
void ks0108_set_x_address(unsigned short int data_bus_bitmask) __attribute__((alias("ks0108_set_page")));

//Inline functions [http://gcc.gnu.org/onlinedocs/gcc/Inline.html : last line to understand why these functions are declared inline extern only in header file and not here]

void __ks0108_SET_DB_AS_OUTPUT(void) {
    *(__SFR_TRISCLR(_ks0108_DB[0])) = _ks0108_DB_MASK[0];
    *(__SFR_TRISCLR(_ks0108_DB[1])) = _ks0108_DB_MASK[1];
    *(__SFR_TRISCLR(_ks0108_DB[2])) = _ks0108_DB_MASK[2];
    *(__SFR_TRISCLR(_ks0108_DB[3])) = _ks0108_DB_MASK[3];
    *(__SFR_TRISCLR(_ks0108_DB[4])) = _ks0108_DB_MASK[4];
    *(__SFR_TRISCLR(_ks0108_DB[5])) = _ks0108_DB_MASK[5];
    *(__SFR_TRISCLR(_ks0108_DB[6])) = _ks0108_DB_MASK[6];
    *(__SFR_TRISCLR(_ks0108_DB[7])) = _ks0108_DB_MASK[7];
}

void __ks0108_SET_DB_AS_INPUT(void) {
    *(__SFR_TRISSET(_ks0108_DB[0])) = _ks0108_DB_MASK[0];
    *(__SFR_TRISSET(_ks0108_DB[1])) = _ks0108_DB_MASK[1];
    *(__SFR_TRISSET(_ks0108_DB[2])) = _ks0108_DB_MASK[2];
    *(__SFR_TRISSET(_ks0108_DB[3])) = _ks0108_DB_MASK[3];
    *(__SFR_TRISSET(_ks0108_DB[4])) = _ks0108_DB_MASK[4];
    *(__SFR_TRISSET(_ks0108_DB[5])) = _ks0108_DB_MASK[5];
    *(__SFR_TRISSET(_ks0108_DB[6])) = _ks0108_DB_MASK[6];
    *(__SFR_TRISSET(_ks0108_DB[7])) = _ks0108_DB_MASK[7];
}

void __ks0108_GOTO_XY(unsigned short X, unsigned short Y) {
    ks0108_set_page(X);
    ks0108_set_address(Y);
}

void __ks0108_COMMIT(void) {
    ks0108_e_high();
    ks0108_e_low();
}

void __ks0108_NEWLINE(void) {
    ks0108_set_side(ks0108_LEFT); //set side to left
    _ks0108_Y = 0; //reset y
    _ks0108_X = _ks0108_X < 7 ? ++_ks0108_X : 0; // go on new line if avaiable, else begin from 0
    __ks0108_GOTO_XY(_ks0108_X, _ks0108_Y); //set cursor to correct location
}

