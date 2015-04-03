/* Arduino RDA5807M Library
 * See the README file for author and licensing information. In case it's
 * missing from your distribution, use the one here as the authoritative
 * version: https://github.com/csdexter/RDA5807M/blob/master/README
 *
 * This library is for interfacing with a RDA Microelectronics RDA5807M
 * single-chip FM broadcast radio receiver.
 * See the example sketches to learn how to use the library in your code.
 *
 * This is the main include file for the library.
 */

#ifndef _RDA5807M_H_INCLUDED
#define _RDA5807M_H_INCLUDED

#if defined(ARDUINO) && ARDUINO >= 100
# include <Arduino.h>
#else
# include <WProgram.h>
#endif

//Register file origins for sequential mode
#define RDA5807M_FIRST_REGISTER_WRITE 0x02
#define RDA5807M_FIRST_REGISTER_READ 0x0A
#define RDA5807M_LAST_REGISTER 0x3A

//Register addresses
#define RDA5807M_REG_CHIPID 0x00
#define RDA5807M_REG_CONFIG 0x02
#define RDA5807M_REG_TUNING 0x03
#define RDA5807M_REG_PARAMS1 0x04
#define RDA5807M_REG_PARAMS2 0x05
#define RDA5807M_REG_OPEN 0x06
#define RDA5807M_REG_PARAMS3 0x07
#define RDA5807M_REG_FREQ 0x08
#define RDA5807M_REG_STATUS 0x0A
#define RDA5807M_REG_RSSI 0x0B
#define RDA5807M_REG_RDSA 0x0C
#define RDA5807M_REG_RDSB 0x0D
#define RDA5807M_REG_RDSC 0x0E
#define RDA5807M_REG_RDSD 0x0F
#define RDA5807M_REG_SEEK 0x20

//Status bits (from the chip)
#define RDA5807M_STATUS_RDSR 0x8000
#define RDA5807M_STATUS_STC 0x4000
#define RDA5807M_STATUS_SF 0x2000
#define RDA5807M_STATUS_RDSS 0x1000
#define RDA5807M_STATUS_BLKE 0x0800
#define RDA5807M_STATUS_ST 0x0400

//Flag bits (to the chip)
#define RDA5807M_FLG_DHIZ 0x8000
#define RDA5807M_FLG_DMUTE 0x4000
#define RDA5807M_FLG_MONO 0x2000
#define RDA5807M_FLG_BASS 0x1000
#define RDA5807M_FLG_RCLKNOCAL 0x0800
#define RDA5807M_FLG_RCLKDIRECT 0x0400
#define RDA5807M_FLG_SEEKUP 0x0200
#define RDA5807M_FLG_SEEK 0x0100
#define RDA5807M_FLG_SKMODE word(0x0080)
#define RDA5807M_FLG_RDS word(0x0008)
#define RDA5807M_FLG_NEW word(0x0004)
#define RDA5807M_FLG_RESET word(0x0002)
#define RDA5807M_FLG_ENABLE word(0x0001)
#define RDA5807M_FLG_DIRECT word(0x0020)
#define RDA5807M_FLG_TUNE word(0x0010)
#define RDA5807M_FLG_DE 0x0800
#define RDA5807M_FLG_SOFTMUTE 0x0200
#define RDA5807M_FLG_AFCD 0x0100
#define RDA5807M_FLG_INTMODE 0x8000
#define RDA5807M_FLG_EASTBAND65M 0x0200
#define RDA5807M_FLG_SOFTBLEND word(0x0002)
#define RDA5807M_FLG_FREQMODE word(0x0001)
#define RDA5807M_FLG_FMTRUE 0x0100
#define RDA5807M_FLG_FMREADY word(0x0080)
#define RDA5807M_FLG_BLOCKE word(0x0010)

//Masks and constants for configuration parameters
#define RDA5807M_CHIPID 0x58
#define RDA5807M_CLKMODE_MASK word(0x0070)
#define RDA5807M_CLKMODE_32K (0x0 << 4)
#define RDA5807M_CLKMODE_12M (0x1 << 4)
#define RDA5807M_CLKMODE_13M (0x2 << 4)
#define RDA5807M_CLKMODE_19M (0x3 << 4)
#define RDA5807M_CLKMODE_24M (0x5 << 4)
#define RDA5807M_CLKMODE_26M (0x6 << 4)
#define RDA5807M_CLKMODE_38M (0x7 << 4)
#define RDA5807M_CHAN_MASK 0xFFC0
#define RDA5807M_CHAN_SHIFT 6
#define RDA5807M_BAND_MASK word(0x000C)
#define RDA5807M_BAND_WEST 0x0
#define RDA5807M_BAND_JAPAN 0x1
#define RDA5807M_BAND_WORLD 0x2
#define RDA5807M_BAND_EAST 0x3
#define RDA5807M_SPACE_MASK word(0x0003)
#define RDA5807M_SPACE_100K 0x0
#define RDA5807M_SPACE_200K 0x1
#define RDA5807M_SPACE_50K 0x2
#define RDA5807M_SPACE_25K 0x3
#define RDA5807M_SEEKTH_MASK 0x0F00
#define RDA5807M_SEEKTH_SHIFT 8
#define RDA5807M_VOLUME_MASK word(0x000F)
#define RDA5807M_VOLUME_SHIFT 0
#define RDA5807M_OPENMODE_MASK word(0x6000)
#define RDA5807M_OPENMODE_WRITE (0x3 << 13)
#define RDA5807M_SOFTBLENDTH_MASK 0x7C00
#define RDA5807M_SOFTBLENDTH_SHIFT 10
#define RDA5807M_SEEKTHOLD_MASK word(0x00FC)
#define RDA5807M_SEEKTHOLD_SHIFT 2
#define RDA5807M_SEEKMODE_MASK 0x7000
#define RDA5807M_SEEKMODE_OLD (0x1 << 12)
#define RDA5807M_READCHAN_MASK 0x03FF
#define RDA5807M_READCHAN_SHIFT 0
#define RDA5807M_RSSI_MASK 0xFE00
#define RDA5807M_RSSI_SHIFT 9
#define RDA5807M_BLERA_MASK word(0x000C)
#define RDA5807M_BLERA_0 word(0x0000)
#define RDA5807M_BLERA_12 word(0x0004)
#define RDA5807M_BLERA_35 word(0x0008)
#define RDA5807M_BLERA_U (RDA5807M_BLERA_12 | RDA5807M_BLERA_35)
#define RDA5807M_BLERB_MASK word(0x0003)
#define RDA5807M_BLERB_0 word(0x0000)
#define RDA5807M_BLERB_12 word(0x0001)
#define RDA5807M_BLERB_35 word(0x0002)
#define RDA5807M_BLERB_U (RDA5807M_BLERB_12 | RDA5807M_BLERB_35)

typedef struct __attribute__ ((__packed__)) {
    uint8_t disableHiZ:1;
    uint8_t disableMute:1;
    uint8_t mono:1;
    uint8_t bass:1;
    uint8_t rClkNotAlways:1;
    uint8_t rClkInput:1;
    uint8_t seekUp:1;
    uint8_t seek:1;
    uint8_t seekMode:1;
    uint8_t clkMode:3;
    uint8_t rds:1;
    uint8_t newDemodulation:1;
    uint8_t softReset:1;
    uint8_t enable:1;
    uint16_t channel:10;
    uint8_t direct:1;
    uint8_t tune:1;
    uint8_t band:2;
    uint8_t space:2;
    uint8_t reserved1:4;
    uint8_t deEmphasis:1;
    uint8_t reserved2:1;
    uint8_t softMute:1;
    uint8_t afcDisable:1;
    uint8_t reserved3;
    uint8_t interruptMode:1;
    uint8_t reserved4:3;
    uint8_t seekThreshold:4;
    uint8_t reserved5:4;
    uint8_t volume:4;
    uint8_t reserved6:1;
    uint8_t openMode:2;
    uint16_t reserved7:13;
    uint8_t reserved8:1;
    uint8_t softBlendThreshold:5;
    uint8_t bandLimit65M:1;
    uint8_t reserved9:1;
    uint8_t seekThresholdOld:6;
    uint8_t softBlend:1;
    uint8_t frequencyMode:1;
    uint16_t frequencyDirect;
} TRDA5807MRegisterFileWrite;

#define RDA5807M_SIZE_BULK_WRITE (sizeof(TRDA5807MRegisterFileWrite) / sizeof(word))

typedef struct __attribute__ ((__packed__)) {
    uint8_t rdsReady:1;
    uint8_t seekTuneComplete:1;
    uint8_t seekFail:1;
    uint8_t rdsSynchronized:1;
    uint8_t blockEFound:1;
    uint8_t stereo:1;
    uint16_t readChannel:10;
    uint8_t rssi:7;
    uint8_t isStation:1;
    uint8_t ready:1;
    uint8_t reserved1:2;
    uint8_t blockE:1;
    uint8_t blerA:2;
    uint8_t blerB:2;
    uint16_t rdsA;
    uint16_t rdsB;
    uint16_t rdsC;
    uint16_t rdsD;
} TRDA5807MRegisterFileRead;

#define RDA5807M_SIZE_BULK_READ (sizeof(TRDA5807MRegisterFileRead) / sizeof(word))

class RDA5807M
{
    public:
        /*
        * Description:
        *   This is the constructor, it initializes internal data structures.
        */
        RDA5807M(void) {};

        /*
        * Description:
        *   This is the destructor, it delegates to end().
        */
        ~RDA5807M() { end(); };

        /*
        * Description:
        *   Mutes and disables the chip.
        */
        void end(void);

        /*
        * Description:
        *   Initializes the RDA5807M, starts the radio and configures band
        *   limits.
        * Parameters:
        *   band - The desired band limits, one of the RDA5807M_BAND_* 
        *          constants.
        */
        void begin(byte band);

        /*
        * Description:
        *   Getter and setter for single random access to registers.
        * Parameters:
        *   reg - byte, register to get or set, one of the RDA5807M_REG_* 
        *         constants.
        *   value - word, value to set the given register to.
        * Returns:
        *   word, current value of given register.
        */
        void setRegister(byte reg, word value);
        word getRegister(byte reg);

        /*
        * Description:
        *   Getter and setter for bulk sequential access to registers. Gets
        *   always start at RDA5807M_FIRST_REGISTER_READ while sets always
        *   start at RDA5807M_FIRST_REGISTER_WRITE. The RDA5807M register file
        *   has exactly RDA5807M_LAST_REGISTER word-sized entries.
        * Parameters:
        *   count - byte, how many sequential registers to get/set.
        *   regs - word[], will be filled with the values of the got registers
        *          or will be the source of the values for the set registers.
        */
        void setRegisterBulk(byte count, const word regs[]);
        void getRegisterBulk(byte count, word regs[]);
};

#endif