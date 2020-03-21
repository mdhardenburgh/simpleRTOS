/**
 * @file qei.h
 * @project RTOS
 * @engineer Matthew Hardenburgh
 * @date 12/18/2019
 * 
 * @section LICENSE
 * 
 * RTOS
 * Copyright (C) 2019  Matthew Hardenburgh
 * mdhardenburgh@gmail.com
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
 * 
 * @section DESCRIPTION
 * 
 * Class header for the system control unit for the Texas Instruments Tiva C 
 * ARM4F microcontroller, TM4C123GH6PM. 
 * 
 * System Control Register Descriptions
 * 
 * All addresses given are relative to the System Control base address of 
 * 0x400F.E000. Registers provided for legacy software support only are listed 
 * in “System Control Legacy Register Descriptions” on page 424.
 * 
 * Quadrature Encoder Interface (QEI) Register Descriptions
 * 
 * The remainder of this section lists and describes the QEI registers, in 
 * numerical order by address offset.
 */

#ifndef QEI_H
#define QEI_H

#include "../systemControl/systemControl.h"

class Qei
{
    public:
        Qei();
        ~Qei();

    private:

        static const uint32_t qei0BaseAddress = 0x4002C000;
        static const uint32_t qei1BaseAddress = 0x4002D000;

        static const uint32_t PPQEI_OFFSET = 0x344; //0x344 PPQEI RO 0x0000.0003 Quadrature Encoder Interface Peripheral Present 306
        static const uint32_t SRQEI_OFFSET = 0x544; //0x544 SRQEI RW 0x0000.0000 Quadrature Encoder Interface Software Reset 332
        static const uint32_t RCGCQEI_OFFSET = 0x644; //0x644 RCGCQEI RW 0x0000.0000 Quadrature Encoder Interface Run Mode Clock Gating Control 355
        static const uint32_t SCGCQEI_OFFSET = 0x744; //0x744 SCGCQEI RW 0x0000.0000 Quadrature Encoder Interface Sleep Mode Clock Gating Control 377
        static const uint32_t DCGCQEI_OFFSET = 0x844; //0x844 DCGCQEI RW 0x0000.0000 Quadrature Encoder Interface Deep-Sleep Mode Clock Gating Control 399
        static const uint32_t PRQEI_OFFSET = 0xA44; //0xA44 PRQEI RO 0x0000.0000 Quadrature Encoder Interface Peripheral Ready 421

};

#endif //P_H