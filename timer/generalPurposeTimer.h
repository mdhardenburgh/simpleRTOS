/**
 * @file generalPurposeTimer.h
 * @brief TM4C123GH6PM General Purpose Timer Driver Declaration
 * @author Matthew Hardenburgh
 * @version 0.1
 * @date 3/21/2020
 * @copyright Matthew Hardenburgh 2020
 * 
 * @section license LICENSE
 * 
 * TM4C123GH6PM Drivers
 * Copyright (C) 2020  Matthew Hardenburgh
 * mdhardenburgh@protonmail.com
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see https://www.gnu.org/licenses/.
 */

/**
 * @class GeneralPurposeTimer
 * @brief TM4C123GH6PM General Purpose Timer Driver
 * 
 * @section generalPurposeTimerDescription General Purpose Timer Description
 * 
 * The TM4C123GH6PM microcontroller has 6 16/32-bit "short" general purpose 
 * timer blocks and 6 32/64-bit wide timer blocks. Each short timer block is 
 * split up into 2 16-bit timers (Timer A and Timer B). The A and B timer can be
 * concatenated to make the short timer a single 32-bit timer. The same 
 * functionality goes for 32/64-bit wide timers as well. ADC can be triggered
 * using a general purose timer. The General Purpose Timer module has the 
 * following capabilities:
 *      - Twelve 16/32-bit Capture Compare PWM pins (CCP)
 *      - Twelve 32/64-bit Capture Compare PWM pins (CCP)
 *      - Daisy chaining of timer modules to allow a single timer to initiate multiple timing events
 *      - Timer synchronization allows selected timers to start counting on the same clock cycle
 *      - ADC event trigger
 *      - User-enabled stalling when the microcontroller asserts CPU Halt flag 
 *        during debug (excluding RTC mode)
 *      - Ability to determine the elapsed time between the assertion of the 
 *        timer interrupt and entry into the interrupt service routine
 *     - Efficient transfers using Micro Direct Memory Access Controller (µDMA)
 *          - Dedicated channel for each timer
 *          - Burst request generated on timer interrupt
 * 
 * Additionally, the short and wide timers have the following capabilities 
 * listed in the following table.
 * 
 * @image html timerCapabilities.png
 * @image latex timerCapabilities.png
 * 
 * The prescaler is only available when the timers are used individually
 * 
 * A prescaler is an electronic counting circuit used to reduce a high frequency 
 * electrical signal to a lower frequency by integer division. The prescaler 
 * takes the basic timer clock frequency (which may be the CPU clock frequency 
 * or may be some higher or lower frequency) and divides it by some value before 
 * feeding it to the timer, according to how the prescaler register(s) are 
 * configured. The prescaler values that may be configured might be limited to a 
 * few fixed values (powers of 2), or they may be any integer value from 1 to 
 * 2^P, where P is the number of prescaler bits.
 * 
 * For more detailed information on the General Purpose Timer please see page 704 of the 
 * TM4C123GH6PM datasheet @ https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf
 * 
 * @subsection generalPurposeTimerSignalDescription General Purpose Timer Signal Description
 * 
 * The following table lists the external signals and thier associtated pins 
 * for the Timer module. The GPIO needs to be configured for the Timer alternate
 * function using the \c AFSEL bit in the GPIO Alternate Function Register 
 * (GPIOAFSEL). The number in parenthesis in the Pin Mux / Pin Assignment 
 * column of the table below is what is programmed into the \c PMCn field in
 * the GPIO Port Control (GPIOPCTL) register to assign a Timer signal to a GPIO. 
 * 
 * @image html timerSignalPins.png
 * @image html timerSignalPins2.png
 * @image latex timerSignalPins.png
 * @image latex timerSignalPins2.png
 * 
 */


#ifndef GENERAL_PURPOSE_TIMER_H
#define GENERAL_PURPOSE_TIMER_H

#include "../systemControl/systemControl.h"

/**
 * Mode of the timer.
 */
enum timerMode
{
    oneShot, periodic, realTimeClock, edgeCount, edgeTime, PWM
};

/**
 * Which timer block to use.
 */
enum timerBlock
{
    shortTimer0, shortTimer1, shortTimer2, shortTimer3, shortTimer4, shortTimer5,
    wideTimer0, wideTimer1, wideTimer2, wideTimer3, wideTimer4, wideTimer5
};

/**
 * Count direction of the timer.
 */
enum countDirection
{
    up, down
};

/**
 * Which subtimer to use or both in concatenated mode.
 */
enum timerUse
{
    timerA, timerB, concatenated
};


class GeneralPurposeTimer
{
    public:
        GeneralPurposeTimer();
        ~GeneralPurposeTimer();

        void initializeForPolling(timerMode mode, timerBlock block, uint32_t clockCycles, countDirection dir, timerUse use, void (*action)(void));
        void initializeForInterupt(timerMode mode, timerBlock block, uint32_t clockCycles, countDirection dir, timerUse use, uint32_t interuptPriority);

        void pollStatus(void);
        void clearInterrupt(void);
        void enableTimer(void);

    private:

        void initialize(timerMode mode, timerBlock block, uint32_t clockCycles, countDirection dir, timerUse use);

        void (*action)(void);
        timerUse use;
        uint32_t rawInterruptStatusBit;
        uint32_t baseAddress;

        static const uint32_t _16_32_bit_Timer_0_base = 0x40030000;
        static const uint32_t _16_32_bit_Timer_1_base = 0x40031000;
        static const uint32_t _16_32_bit_Timer_2_base = 0x40032000;
        static const uint32_t _16_32_bit_Timer_3_base = 0x40033000;
        static const uint32_t _16_32_bit_Timer_4_base = 0x40034000;
        static const uint32_t _16_32_bit_Timer_5_base = 0x40035000;

        static const uint32_t _32_64_bit_Wide_Timer_0_base = 0x40036000;
        static const uint32_t _32_64_bit_Wide_Timer_1_base = 0x40037000;
        static const uint32_t _32_64_bit_Wide_Timer_2_base = 0x4004C000;
        static const uint32_t _32_64_bit_Wide_Timer_3_base = 0x4004D000;
        static const uint32_t _32_64_bit_Wide_Timer_4_base = 0x4004E000;
        static const uint32_t _32_64_bit_Wide_Timer_5_base = 0x4004F000;

        static const uint32_t timerBaseAddresses[12];

        static const uint32_t PPTIMER_OFFSET = 0x304; //0x304 PPTIMER RO 0x0000.003F 16/32-Bit General-Purpose Timer Peripheral Present 288
        static const uint32_t SRTIMER_OFFSET = 0x504; //0x504 SRTIMER RW 0x0000.0000 16/32-Bit General-Purpose Timer Software Reset 312
        static const uint32_t RCGCTIMER_OFFSET = 0x604; //0x604 RCGCTIMER RW 0x0000.0000 16/32-Bit General-Purpose Timer Run Mode Clock Gating Control 338
        static const uint32_t SCGCTIMER_OFFSET = 0x704; //0x704 SCGCTIMER RW 0x0000.0000 16/32-Bit General-Purpose Timer Sleep Mode Clock Gating Control 360
        static const uint32_t DCGCTIMER_OFFSET = 0x804; //0x804 DCGCTIMER RW 0x0000.0000 16/32-Bit General-Purpose Timer Deep-Sleep Mode Clock Gating Control 382
        static const uint32_t PRTIMER_OFFSET = 0xA04; //0xA04 PRTIMER RO 0x0000.0000 16/32-Bit General-Purpose Timer Peripheral Ready 404

        static const uint32_t PPWTIMER_OFFSET = 0x35C; //0x35C PPWTIMER RO 0x0000.003F 32/64-Bit Wide General-Purpose Timer Peripheral Present 308
        static const uint32_t SRWTIMER_OFFSET = 0x55C; //0x55C SRWTIMER RW 0x0000.0000 32/64-Bit Wide General-Purpose Timer Software Reset 335
        static const uint32_t RCGCWTIMER_OFFSET = 0x65C; //0x65C RCGCWTIMER RW 0x0000.0000 32/64-Bit Wide General-Purpose Timer Run Mode Clock Gating Control 357
        static const uint32_t SCGCWTIMER_OFFSET = 0x75C; //0x75C SCGCWTIMER RW 0x0000.0000 32/64-Bit Wide General-Purpose Timer Sleep Mode Clock Gating Control 379
        static const uint32_t DCGCWTIMER_OFFSET = 0x85C; //0x85C DCGCWTIMER RW 0x0000.0000 32/64-Bit Wide General-Purpose Timer Deep-Sleep Mode Clock Gating Control 401
        static const uint32_t PRWTIMER_OFFSET = 0xA5C; //0xA5C PRWTIMER RO 0x0000.0000 32/64-Bit Wide General-Purpose Timer Peripheral Ready 423

        static const uint32_t PPnTIMER_OFFSET[2];
        static const uint32_t SRnTIMER_OFFSET[2];
        static const uint32_t RCGCnTIMER_OFFSET[2];
        static const uint32_t SCGCnTIMER_OFFSET[2];
        static const uint32_t DCGCnTIMER_OFFSET[2];
        static const uint32_t PRnTIMER_OFFSET[2];

        static const uint32_t GPTMCFG_OFFSET = 0x000; // 0x000 GPTMCFG RW 0x0000.0000 GPTM Configuration 727
        static const uint32_t GPTMTAMR_OFFSET = 0x004; // 0x004 GPTMTAMR RW 0x0000.0000 GPTM Timer A Mode 729
        static const uint32_t GPTMTBMR_OFFSET = 0x008; // 0x008 GPTMTBMR RW 0x0000.0000 GPTM Timer B Mode 733
        static const uint32_t GPTMCTL_OFFSET = 0x00C; // 0x00C GPTMCTL RW 0x0000.0000 GPTM Control 737
        static const uint32_t GPTMSYNC_OFFSET = 0x010; // 0x010 GPTMSYNC RW 0x0000.0000 GPTM Synchronize 741
        static const uint32_t GPTMIMR_OFFSET = 0x018; // 0x018 GPTMIMR RW 0x0000.0000 GPTM Interrupt Mask 745
        static const uint32_t GPTMRIS_OFFSET = 0x01C; // 0x01C GPTMRIS RO 0x0000.0000 GPTM Raw Interrupt Status 748
        static const uint32_t GPTMMIS_OFFSET = 0x020; // 0x020 GPTMMIS RO 0x0000.0000 GPTM Masked Interrupt Status 751
        static const uint32_t GPTMICR_OFFSET = 0x024; // 0x024 GPTMICR W1C 0x0000.0000 GPTM Interrupt Clear 754
        static const uint32_t GPTMTAILR_OFFSET = 0x028; // 0x028 GPTMTAILR RW 0xFFFF.FFFF GPTM Timer A Interval Load 756
        static const uint32_t GPTMTBILR_OFFSET = 0x02C; // 0x02C GPTMTBILR RW - GPTM Timer B Interval Load 757
        static const uint32_t GPTMTAMATCHR_OFFSET = 0x030; // 0x030 GPTMTAMATCHR RW 0xFFFF.FFFF GPTM Timer A Match 758
        static const uint32_t GPTMTBMATCHR_OFFSET = 0x034; // 0x034 GPTMTBMATCHR RW - GPTM Timer B Match 759
        static const uint32_t GPTMTAPR_OFFSET = 0x038; // 0x038 GPTMTAPR RW 0x0000.0000 GPTM Timer A Prescale 760
        static const uint32_t GPTMTBPR_OFFSET = 0x03C; // 0x03C GPTMTBPR RW 0x0000.0000 GPTM Timer B Prescale 761
        static const uint32_t GPTMTAPMR_OFFSET = 0x040; // 0x040 GPTMTAPMR RW 0x0000.0000 GPTM Timer A Prescale Match 762
        static const uint32_t GPTMTBPMR_OFFSET = 0x044; // 0x044 GPTMTBPMR RW 0x0000.0000 GPTM Timer B Prescale Match 763
        static const uint32_t GPTMTAR_OFFSET = 0x048; // 0x048 GPTMTAR RO 0xFFFF.FFFF GPTM Timer A 764
        static const uint32_t GPTMTBR_OFFSET = 0x04C; // 0x04C GPTMTBR RO - GPTM Timer B 765
        static const uint32_t GPTMTAV_OFFSET = 0x050; // 0x050 GPTMTAV RW 0xFFFF.FFFF GPTM Timer A Value 766
        static const uint32_t GPTMTBV_OFFSET = 0x054; // 0x054 GPTMTBV RW - GPTM Timer B Value 767
        static const uint32_t GPTMRTCPD_OFFSET = 0x058; // 0x058 GPTMRTCPD RO 0x0000.7FFF GPTM RTC Predivide 768
        static const uint32_t GPTMTAPS_OFFSET = 0x05C; // 0x05C GPTMTAPS RO 0x0000.0000 GPTM Timer A Prescale Snapshot 769
        static const uint32_t GPTMTBPS_OFFSET = 0x060; // 0x060 GPTMTBPS RO 0x0000.0000 GPTM Timer B Prescale Snapshot 770
        static const uint32_t GPTMTAPV_OFFSET = 0x064; // 0x064 GPTMTAPV RO 0x0000.0000 GPTM Timer A Prescale Value 771
        static const uint32_t GPTMTBPV_OFFSET = 0x068; // 0x068 GPTMTBPV RO 0x0000.0000 GPTM Timer B Prescale Value 772
        static const uint32_t GPTMPP_OFFSET = 0xFC0; // 0xFC0 GPTMPP RO 0x0000.0000 GPTM Peripheral Properties 773

        static const uint32_t GPTMTnMR_OFFSET[2];
        static const uint32_t GPTMTnILR_OFFSET[2];
        static const uint32_t GPTMTnMATCHR_OFFSET[2];
        static const uint32_t GPTMTnPR_OFFSET[2];
        static const uint32_t GPTMTnPMR_OFFSET[2];
        static const uint32_t GPTMTnR_OFFSET[2];
        static const uint32_t GPTMTnV_OFFSET[2];
        static const uint32_t GPTMTnPS_OFFSET[2];
        static const uint32_t GPTMTnPV_OFFSET[2];

};

#endif //GENERAL_PURPOSE_TIMER_H
