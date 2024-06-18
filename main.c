#include "ch559.h"
#include "sys.h"
#include "usb.h"

#define SHIFT 0x80
static uint8_c _asciimap[128] = {
    0x00,             // NUL
    0x00,             // SOH
    0x00,             // STX
    0x00,             // ETX
    0x00,             // EOT
    0x00,             // ENQ
    0x00,             // ACK  
    0x00,             // BEL
    0x2a,			  // BS	Backspace
    0x2b,			  // TAB ab
    0x28,			  // LF	Enter
    0x00,             // VT 
    0x00,             // FF 
    0x00,             // CR 
    0x00,             // SO 
    0x00,             // SI 
    0x00,             // DEL
    0x00,             // DC1
    0x00,             // DC2
    0x00,             // DC3
    0x00,             // DC4
    0x00,             // NAK
    0x00,             // SYN
    0x00,             // ETB
    0x00,             // CAN
    0x00,             // EM 
    0x00,             // SUB
    0x00,             // ESC
    0x00,             // FS 
    0x00,             // GS 
    0x00,             // RS 
    0x00,             // US 

    0x2c,		   //  ' '
    0x1e|SHIFT,	   // !
    0x34|SHIFT,	   // "
    0x20|SHIFT,    // #
    0x21|SHIFT,    // $
    0x22|SHIFT,    // %
    0x24|SHIFT,    // &
    0x34,          // '
    0x26|SHIFT,    // (
    0x27|SHIFT,    // )
    0x25|SHIFT,    // *
    0x2e|SHIFT,    // +
    0x36,          // ,
    0x2d,          // -
    0x37,          // .
    0x38,          // /
    0x27,          // 0
    0x1e,          // 1
    0x1f,          // 2
    0x20,          // 3
    0x21,          // 4
    0x22,          // 5
    0x23,          // 6
    0x24,          // 7
    0x25,          // 8
    0x26,          // 9
    0x33|SHIFT,    // :
    0x33,          // ;
    0x36|SHIFT,    // <
    0x2e,          // =
    0x37|SHIFT,      // >
    0x38|SHIFT,      // ?
    0x1f|SHIFT,      // @
    0x04|SHIFT,      // A
    0x05|SHIFT,      // B
    0x06|SHIFT,      // C
    0x07|SHIFT,      // D
    0x08|SHIFT,      // E
    0x09|SHIFT,      // F
    0x0a|SHIFT,      // G
    0x0b|SHIFT,      // H
    0x0c|SHIFT,      // I
    0x0d|SHIFT,      // J
    0x0e|SHIFT,      // K
    0x0f|SHIFT,      // L
    0x10|SHIFT,      // M
    0x11|SHIFT,      // N
    0x12|SHIFT,      // O
    0x13|SHIFT,      // P
    0x14|SHIFT,      // Q
    0x15|SHIFT,      // R
    0x16|SHIFT,      // S
    0x17|SHIFT,      // T
    0x18|SHIFT,      // U
    0x19|SHIFT,      // V
    0x1a|SHIFT,      // W
    0x1b|SHIFT,      // X
    0x1c|SHIFT,      // Y
    0x1d|SHIFT,      // Z
    0x2f,          // [
    0x31,          // bslash
    0x30,          // ]
    0x23|SHIFT,    // ^
    0x2d|SHIFT,    // _
    0x35,          // `
    0x04,          // a
    0x05,          // b
    0x06,          // c
    0x07,          // d
    0x08,          // e
    0x09,          // f
    0x0a,          // g
    0x0b,          // h
    0x0c,          // i
    0x0d,          // j
    0x0e,          // k
    0x0f,          // l
    0x10,          // m
    0x11,          // n
    0x12,          // o
    0x13,          // p
    0x14,          // q
    0x15,          // r
    0x16,          // s
    0x17,          // t
    0x18,          // u
    0x19,          // v
    0x1a,          // w
    0x1b,          // x
    0x1c,          // y
    0x1d,          // z
    0x2f|SHIFT,    // {
    0x31|SHIFT,    // |
    0x30|SHIFT,    // }
    0x35|SHIFT,    // ~
    0			   // DEL
};

void print(char* str) {
    uint8_t i = 0, c = 0;
    while (str[i] != '\0') {
        c = _asciimap[str[i]];
        usbSetKeycode(0, 1);
        usbSetKeycode(1, (c & SHIFT) ? 0x02 : 0x00);
        usbSetKeycode(2, c & ~SHIFT);
        usbPushKeydata();
        delay(50);
        usbSetKeycode(1, 0);
        usbSetKeycode(2, 0);
        usbPushKeydata();
        delay(100);
        i += 1;
    }
}

#include "music.h"

typedef struct {
    uint8_t tone;
    uint8_t len;
} MusicNote;

#define MUSIC_LEN (MID_MIKE_LENGTH / 2)
MusicNote* music = (MusicNote*) MID_MIKE;

/*
    0x24, 0x26, 0x28, 0x29, 0x2B, 0x2D, 0x2F,
    0x30, 0x32, 0x34, 0x35, 0x37, 0x39, 0x3B,
    0x3C, 0x3E, 0x40, 0x41, 0x43, 0x45, 0x47,
*/

uint8_t __conv(uint8_t tone) {
    switch (tone) {
    case 0x24:
        return 'z';
    case 0x26:
        return 'x';
    case 0x28:
        return 'c';
    case 0x29:
        return 'v';
    case 0x2B:
        return 'b';
    case 0x2D:
        return 'n';
    case 0x2F:
        return 'm';

    case 0x30:
        return 'a';
    case 0x32:
        return 's';
    case 0x34:
        return 'd';
    case 0x35:
        return 'f';
    case 0x37:
        return 'g';
    case 0x39:
        return 'h';
    case 0x3B:
        return 'j';

    case 0x3C:
        return 'q';
    case 0x3E:
        return 'w';
    case 0x40:
        return 'e';
    case 0x41:
        return 'r';
    case 0x43:
        return 't';
    case 0x45:
        return 'y';
    case 0x47:
        return 'u';

    default:
        return 0x00;
    }
}

void __usbDeviceInterrupt() __interrupt (INT_NO_USB) __using (1);
extern uint8_t FLAG;

#define CTL P17
#define LED P41

void playMusic(uint16_t speed) {
    for (uint16_t i = 0; i < MUSIC_LEN; i++) {
        uint8_t c = _asciimap[__conv(music[i].tone)];
        usbSetKeycode(0, 1);
        usbSetKeycode(1, (c & SHIFT) ? 0x02 : 0x00);
        usbSetKeycode(2, c & ~SHIFT);
        usbPushKeydata();
        delay(10);
        usbSetKeycode(1, 0);
        usbSetKeycode(2, 0);
        usbPushKeydata();
        delay(music[i].len * speed);

        if (CTL) break;
        LED = CTL;
    }
}

void main() {
    // P17
    P1_DIR &= ~(1 << 7);
    P1_PU |= (1 << 7);

    // P41
    P4_DIR |= (1 << 1);
    LED = 0;

    sysClockConfig();
    delay(5);

    usbDevInit();
    EA = 1;
    UEP1_T_LEN = 0;
    UEP2_T_LEN = 0;
    UEP3_T_LEN = 0;

    FLAG = 1;

    LED = 1;
    delay(500);
    LED = 0;
    usbReleaseAll();
    usbPushKeydata();
    requestHIDData();

    //print("echo \"Hello, Gensokyo!\"\n");

    while (1) {
        // if (!CTL) {
        //     usbClickMouse(1, 20);  delay(100);
        //     usbClickMouse(1, 20);  delay(100);
        //     usbClickMouse(1, 20);  delay(200);
        //     usbClickMouse(1, 200); delay(250);
        // }
        // if (!CTL) {
        //     usbScrollWheel(100);
        // }

        if (!CTL) {
            delay(1000);
            playMusic(80);
        }

        if (hasHIDData()) {
            for (uint8_t i = 0; i < HID_BUF_SIZE; i++)
                setHIDData(i, getHIDData(i));
            pushHIDData();
            requestHIDData();
        }

        LED = CTL;
    }
    
}
