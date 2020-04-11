/**
 * @file adc.h
 * @brief TM4C123GH6PM ADC Driver Declaration
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
 * @class Adc
 * @brief TM4C123GH6PM ADC Driver
 * 
 * @section adcDescription ADC Description
 * 
 * The TM4C123GH6PM microcontroller ADC has 12-bit resolution at 1Msps. There
 * are two ADC blocks and they share the 12 input channels. Other features include:
 *      - Single-ended and differential-input configurations
 *      - On-chip internal temperature sensor
 *      - Optional phase shift in sample time programmable from 22.5º to 337.5º
 *      - Four programmable sample conversion sequencers from one to eight 
 *        entries long, with corresponding conversion result FIFOs
 *      - Flexible trigger control
 *          - Controller (software)
 *          - Timers
 *          - Analog Comparators
 *          - PWM
 *          - GPIO
 *      - Hardware averaging of up to 64 samples
 *      -  Eight digital comparators
 *      - Power and ground for the analog circuitry is separate from the digital 
 *        power and ground
 *      - Efficient transfers using Micro Direct Memory Access Controller (µDMA)
 *          - Dedicated channel for each sample sequencer
 *          - ADC module uses burst requests for DMA
 * 
 * For more detailed information on the ADC please see page 799 of the 
 * TM4C123GH6PM datasheet @ https://www.ti.com/lit/ds/symlink/tm4c123gh6pm.pdf
 * 
 * @subsection adcSignalDescription ADC Signal Description
 * 
 * The following table lists the GPIO pin mux and physical pin number of the
 * pins that can be muxed for use by the ADC. To configure a pin for analog use
 * clear the coresponding GPIO's \c DEN bit in the GPIO Digital Enable (GPIODEN)
 * register and set the coresponding \c AMSEL bit in the GPIO Analog Mode Select 
 * (GPIOAMSEL) register. 
 * 
 * @image html adcSignalPins.PNG
 * @image latex adcSignalPins.PNG
 * 
 * @subsection adcSystemControlRegisterDescription ADC System Control Register Descriptions
 * 
 * All addresses given are relative to the System Control base address of 
 * 0x400F.E000. Legacy registers not supported.
 * 
 * @subsection adcRegisterDescription ADC Register Description
 * 
 * The Adc class contains a list of ADC registers listed as an offset relative 
 * to the hexadecimal base address of the ADC module block, ADC0 or ADC1. 
 * Note that the ADC module clock must be enabled before the registers can be 
 * programmed (see page 352). There must be a delay of 3 system clocks after the 
 * ADC module clock is enabled before any ADC module registers are accessed.
 * 
 */

#ifndef ADC_H
#define ADC_H

#include "../systemControl/systemControl.h"

class Adc
{
    public:
        Adc();
        ~Adc();

    private:

        static const uint32_t adc0BaseAddress = 0x40038000; // ADC block 0 base address
        static const uint32_t adc1BaseAddress = 0x40039000; // ADC block 1 base address

        static const uint32_t PPADC_OFFSET = 0x338; // 0x338 PPADC RO 0x0000.0003 Analog-to-Digital Converter Peripheral Present 303
        static const uint32_t SRADC_OFFSET = 0x538; // 0x538 SRADC RW 0x0000.0000 Analog-to-Digital Converter Software Reset 327 
        static const uint32_t RCGCADC_OFFSET = 0x638; // 0x638 RCGCADC RW 0x0000.0000 Analog-to-Digital Converter Run Mode Clock Gating Control 352
        static const uint32_t SCGCADC_OFFSET = 0x738; // 0x738 SCGCADC RW 0x0000.0000 Analog-to-Digital Converter Sleep Mode Clock Gating Control 374
        static const uint32_t DCGCADC_OFFSET = 0x838; // 0x838 DCGCADC RW 0x0000.0000 Analog-to-Digital Converter Deep-Sleep Mode Clock Gating Control 396
        static const uint32_t PRADC_OFFSET = 0xA38; // 0xA38 PRADC RO 0x0000.0000 Analog-to-Digital Converter Peripheral Ready 418

        static const uint32_t ADCACTSS_OFFSET = 0x000; // 0x000 ADCACTSS RW 0x0000.0000 ADC Active Sample Sequencer 821
        static const uint32_t ADCRIS_OFFSET = 0x004; // 0x004 ADCRIS RO 0x0000.0000 ADC Raw Interrupt Status 823
        static const uint32_t ADCIM_OFFSET = 0x008; // 0x008 ADCIM RW 0x0000.0000 ADC Interrupt Mask 825
        static const uint32_t ADCISC_OFFSET = 0x00C; // 0x00C ADCISC RW1C 0x0000.0000 ADC Interrupt Status and Clear 828
        static const uint32_t ADCOSTAT_OFFSET = 0x010; // 0x010 ADCOSTAT RW1C 0x0000.0000 ADC Overflow Status 831
        static const uint32_t ADCEMUX_OFFSET = 0x014; // 0x014 ADCEMUX RW 0x0000.0000 ADC Event Multiplexer Select 833
        static const uint32_t ADCUSTAT_OFFSET = 0x018; // 0x018 ADCUSTAT RW1C 0x0000.0000 ADC Underflow Status 838
        static const uint32_t ADCTSSEL_OFFSET = 0x01C; // 0x01C ADCTSSEL RW 0x0000.0000 ADC Trigger Source Select 839
        static const uint32_t ADCSSPRI_OFFSET = 0x020; // 0x020 ADCSSPRI RW 0x0000.3210 ADC Sample Sequencer Priority 841
        static const uint32_t ADCSPC_OFFSET = 0x024; // 0x024 ADCSPC RW 0x0000.0000 ADC Sample Phase Control 843
        static const uint32_t ADCPSSI_OFFSET = 0x028; // 0x028 ADCPSSI RW - ADC Processor Sample Sequence Initiate 845
        static const uint32_t ADCSAC_OFFSET = 0x030; // 0x030 ADCSAC RW 0x0000.0000 ADC Sample Averaging Control 847
        static const uint32_t ADCDCISC_OFFSET = 0x034; // 0x034 ADCDCISC RW1C 0x0000.0000 ADC Digital Comparator Interrupt Status and Clear 848
        static const uint32_t ADCCTL_OFFSET = 0x038; // 0x038 ADCCTL RW 0x0000.0000 ADC Control 850
        static const uint32_t ADCSSMUX0_OFFSET = 0x040; // 0x040 ADCSSMUX0 RW 0x0000.0000 ADC Sample Sequence Input Multiplexer Select 0 851
        static const uint32_t ADCSSCTL0_OFFSET = 0x044; // 0x044 ADCSSCTL0 RW 0x0000.0000 ADC Sample Sequence Control 0 853
        static const uint32_t ADCSSFIFO0_OFFSET = 0x048; // 0x048 ADCSSFIFO0 RO - ADC Sample Sequence Result FIFO 0 860
        static const uint32_t ADCSSFSTAT0_OFFSET = 0x04C; // 0x04C ADCSSFSTAT0 RO 0x0000.0100 ADC Sample Sequence FIFO 0 Status 861
        static const uint32_t ADCSSOP0_OFFSET = 0x050; // 0x050 ADCSSOP0 RW 0x0000.0000 ADC Sample Sequence 0 Operation 863
        static const uint32_t ADCSSDC0_OFFSET = 0x054; // 0x054 ADCSSDC0 RW 0x0000.0000 ADC Sample Sequence 0 Digital Comparator Select 865
        static const uint32_t ADCSSMUX1_OFFFSET = 0x060; // 0x060 ADCSSMUX1 RW 0x0000.0000 ADC Sample Sequence Input Multiplexer Select 1 867
        static const uint32_t ADCSSCTL1_OFFSET = 0x064; // 0x064 ADCSSCTL1 RW 0x0000.0000 ADC Sample Sequence Control 1 868
        static const uint32_t ADCSSFIFO1_OFFSET = 0x068; // 0x068 ADCSSFIFO1 RO - ADC Sample Sequence Result FIFO 1 860
        static const uint32_t ADCSSFSTAT1_OFFSET = 0x06C; // 0x06C ADCSSFSTAT1 RO 0x0000.0100 ADC Sample Sequence FIFO 1 Status 861
        static const uint32_t ADCSSOP1_OFFSET = 0x070; // 0x070 ADCSSOP1 RW 0x0000.0000 ADC Sample Sequence 1 Operation 872
        static const uint32_t ADCSSDC1_OFFSET = 0x074; // 0x074 ADCSSDC1 RW 0x0000.0000 ADC Sample Sequence 1 Digital Comparator Select 873
        static const uint32_t ADCSSMUX2_OFFSET = 0x080; // 0x080 ADCSSMUX2 RW 0x0000.0000 ADC Sample Sequence Input Multiplexer Select 2 867
        static const uint32_t ADCSSCTL2_OFFSET = 0x084; // 0x084 ADCSSCTL2 RW 0x0000.0000 ADC Sample Sequence Control 2 868
        static const uint32_t ADCSSFIFO2_OFFSET = 0x088; // 0x088 ADCSSFIFO2 RO - ADC Sample Sequence Result FIFO 2 860
        static const uint32_t ADCSSFSTAT2_OFFSET = 0x08C; // 0x08C ADCSSFSTAT2 RO 0x0000.0100 ADC Sample Sequence FIFO 2 Status 861
        static const uint32_t ADCSSOP2_OFFSET = 0x090; // 0x090 ADCSSOP2 RW 0x0000.0000 ADC Sample Sequence 2 Operation 872
        static const uint32_t ADCSSDC2_OFFSET = 0x094; // 0x094 ADCSSDC2 RW 0x0000.0000 ADC Sample Sequence 2 Digital Comparator Select 873
        static const uint32_t ADCSSMUX3_OFFSET = 0x0A0; // 0x0A0 ADCSSMUX3 RW 0x0000.0000 ADC Sample Sequence Input Multiplexer Select 3 875
        static const uint32_t ADCSSCTL3_OFFSET = 0x0A4; // 0x0A4 ADCSSCTL3 RW 0x0000.0000 ADC Sample Sequence Control 3 876
        static const uint32_t ADCSSFIFO3_OFFSET = 0x0A8; // 0x0A8 ADCSSFIFO3 RO - ADC Sample Sequence Result FIFO 3 860
        static const uint32_t ADCSSFSTAT3_OFFSET = 0x0AC; // 0x0AC ADCSSFSTAT3 RO 0x0000.0100 ADC Sample Sequence FIFO 3 Status 861
        static const uint32_t ADCSSOP3_OFFSET = 0x0B0; // 0x0B0 ADCSSOP3 RW 0x0000.0000 ADC Sample Sequence 3 Operation 878
        static const uint32_t ADCSSDC3_OFFSET = 0x0B4; // 0x0B4 ADCSSDC3 RW 0x0000.0000 ADC Sample Sequence 3 Digital Comparator Select 879
        static const uint32_t ADCDCRIC_OFFSET = 0xD00; // 0xD00 ADCDCRIC WO 0x0000.0000 ADC Digital Comparator Reset Initial Conditions 880
        static const uint32_t ADCDCCTL0_OFFSET = 0xE00; // 0xE00 ADCDCCTL0 RW 0x0000.0000 ADC Digital Comparator Control 0 885
        static const uint32_t ADCDCCTL1_OFFSET = 0xE04; // 0xE04 ADCDCCTL1 RW 0x0000.0000 ADC Digital Comparator Control 1 885
        static const uint32_t ADCDCCTL2_OFFSET = 0xE08; // 0xE08 ADCDCCTL2 RW 0x0000.0000 ADC Digital Comparator Control 2 885
        static const uint32_t ADCDCCTL3_OFFSET = 0xE0C; // 0xE0C ADCDCCTL3 RW 0x0000.0000 ADC Digital Comparator Control 3 885
        static const uint32_t ADCDCCTL4_OFFSET = 0xE10; // 0xE10 ADCDCCTL4 RW 0x0000.0000 ADC Digital Comparator Control 4 885
        static const uint32_t ADCDCCTL5_OFFSET = 0xE14; // 0xE14 ADCDCCTL5 RW 0x0000.0000 ADC Digital Comparator Control 5 885
        static const uint32_t ADCDCCTL6_OFFSET = 0xE18; // 0xE18 ADCDCCTL6 RW 0x0000.0000 ADC Digital Comparator Control 6 885
        static const uint32_t ADCDCCTL7_OFFSET = 0xE1C; // 0xE1C ADCDCCTL7 RW 0x0000.0000 ADC Digital Comparator Control 7 885
        static const uint32_t ADCDCCMP0_OFFSET = 0xE40; // 0xE40 ADCDCCMP0 RW 0x0000.0000 ADC Digital Comparator Range 0 888
        static const uint32_t ADCDCCMP1_OFFSET = 0xE44; // 0xE44 ADCDCCMP1 RW 0x0000.0000 ADC Digital Comparator Range 1 888
        static const uint32_t ADCDCCMP2_OFFSET = 0xE48; // 0xE48 ADCDCCMP2 RW 0x0000.0000 ADC Digital Comparator Range 2 888
        static const uint32_t ADCDCCMP3_OFFSET = 0xE4C; // 0xE4C ADCDCCMP3 RW 0x0000.0000 ADC Digital Comparator Range 3 888
        static const uint32_t ADCDCCMP4_OFFSET = 0xE50; // 0xE50 ADCDCCMP4 RW 0x0000.0000 ADC Digital Comparator Range 4 888
        static const uint32_t ADCDCCMP5_OFFSET = 0xE54; // 0xE54 ADCDCCMP5 RW 0x0000.0000 ADC Digital Comparator Range 5 888
        static const uint32_t ADCDCCMP6_OFFSET = 0xE58; // 0xE58 ADCDCCMP6 RW 0x0000.0000 ADC Digital Comparator Range 6 888
        static const uint32_t ADCDCCMP7_OFFSET = 0xE5C; // 0xE5C ADCDCCMP7 RW 0x0000.0000 ADC Digital Comparator Range 7 888
        static const uint32_t ADCPP_OFFSET = 0xFC0; // 0xFC0 ADCPP RO 0x00B0.20C7 ADC Peripheral Properties 889
        static const uint32_t ADCPC_OFFSET = 0xFC4; // 0xFC4 ADCPC RW 0x0000.0007 ADC Peripheral Configuration 891
        static const uint32_t ADCCC_OFFSET = 0xFC8; // 0xFC8 ADCCC RW 0x0000.0000 ADC Clock Configuration 892

};

#endif //ADC_H