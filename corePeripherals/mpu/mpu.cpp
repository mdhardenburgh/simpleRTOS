/**
 * @file mpu.c
 * @project RTOS
 * @engineer Matthew Hardenburgh
 * @date 12/03/2019
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
 * Driver impelemtation for the memory protection unit for the Texas Instruments 
 * Tiva C ARM4F microcontroller, TM4C123GH6PM. 
 * 
 * This section lists and describes the Memory Protection Unit (MPU) registers, 
 * in numerical order by address offset.
 * 
 * The MPU registers can only be accessed from privileged mode.
 */

#include "mpu.h"

Mpu::Mpu()
{

}

Mpu::~Mpu()
{
    
}