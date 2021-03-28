#include "sys.h"

#include "ch559.h"

void sysClockConfig() {
    SAFE_MOD = 0x55;
    SAFE_MOD = 0xAA;
    CLOCK_CFG |= bOSC_EN_XT;
    delay(2);
    CLOCK_CFG &= ~bOSC_EN_INT;

    SAFE_MOD = 0x55;
    SAFE_MOD = 0xAA;
    CLOCK_CFG &= ~MASK_SYS_CK_DIV;
    CLOCK_CFG |= 5; // 56MHz

    SAFE_MOD = 0x00;
}

void delay_us(uint16_t n) {
	while (n) {  // total = 12~13 Fsys cycles, 1uS @Fsys=12MHz
		++ SAFE_MOD;  // 2 Fsys cycles, for higher Fsys, add operation here
        ++ SAFE_MOD;
        ++ SAFE_MOD;
        ++ SAFE_MOD;
        ++ SAFE_MOD;
        ++ SAFE_MOD;
        ++ SAFE_MOD;
        ++ SAFE_MOD;
        ++ SAFE_MOD;
        ++ SAFE_MOD;
        ++ SAFE_MOD;
        ++ SAFE_MOD;
        ++ SAFE_MOD;
        ++ SAFE_MOD;
        ++ SAFE_MOD;
        ++ SAFE_MOD;
        ++ SAFE_MOD;
        ++ SAFE_MOD;
        ++ SAFE_MOD;
        ++ SAFE_MOD;
        ++ SAFE_MOD;
        ++ SAFE_MOD;
        ++ SAFE_MOD;
		-- n;
	}
}

void delay(uint16_t n) {
	while (n) {
        delay_us(1000);
		-- n;
	}
}                  
