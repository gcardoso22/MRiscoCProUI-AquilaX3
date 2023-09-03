/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2021 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

/********************************************************************************
 * @file     lcd/e3v2/jyersui/dwin_lcd.h
 * @brief    DWIN screen control functions
 ********************************************************************************/

#include "../common/dwin_api.h"

// Draw the degree (°) symbol
// color: color
//  x/y: Upper-left coordinate of the first pixel
void dwinDrawDegreeSymbol(uint16_t color, uint16_t x, uint16_t y);

// Write buffer data to the SRAM or Flash
//  mem: 0x5A=32KB SRAM, 0xA5=16KB Flash
//  addr: start address
//  length: Bytes to write
//  data: address of the buffer with data
void dwinWriteToMem(uint8_t mem, uint16_t addr, uint16_t length, uint8_t *data);

// Draw an Icon from SRAM without background transparency for DACAI Screen support
//  x/y: Upper-left point
//  addr: SRAM address
void dwinIconShow(uint16_t x, uint16_t y, uint16_t addr);

// Write the contents of the 32KB SRAM data memory into the designated image memory space.
//  picID: Picture memory space location, 0x00-0x0F, each space is 32Kbytes
void dwinSRAMToPic(uint8_t picID);

// Write buffer data to the SRAM
//  addr: SRAM start address 0x0000-0x7FFF
//  length: Bytes to write
//  data: address of the buffer with data
inline void writeToSRAM(uint16_t addr, uint16_t length, uint8_t *data) {
  dwinWriteToMem(0x5A, addr, length, data);
}

// Write buffer data to the Flash
//  addr: Flash start address 0x0000-0x3FFF
//  length: Bytes to write
//  data: address of the buffer with data
inline void writeToFlash(uint16_t addr, uint16_t length, uint8_t *data) {
  dwinWriteToMem(0xA5, addr, length, data);
}