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

/********************************************************************************
 * @file     lcd/e3v2/jyersui/dwin_lcd.cpp
 * @brief    DWIN screen control functions
 ********************************************************************************/

#include "../../../inc/MarlinConfigPre.h"

#if ENABLED(DWIN_CREALITY_LCD_JYERSUI)

#include "dwin_lcd.h"

/*-------------------------------------- System variable function --------------------------------------*/

void dwinStartup() {}

/*---------------------------------------- Drawing functions ----------------------------------------*/

// Draw the degree (°) symbol
// color: color
//  x/y: Upper-left coordinate of the first pixel
void dwinDrawDegreeSymbol(uint16_t color, uint16_t x, uint16_t y) {
  dwinDrawPoint(color, 1, 1, x + 1, y);
  dwinDrawPoint(color, 1, 1, x + 2, y);
  dwinDrawPoint(color, 1, 1, x, y + 1);
  dwinDrawPoint(color, 1, 1, x + 3, y + 1);
  dwinDrawPoint(color, 1, 1, x, y + 2);
  dwinDrawPoint(color, 1, 1, x + 3, y + 2);
  dwinDrawPoint(color, 1, 1, x + 1, y + 3);
  dwinDrawPoint(color, 1, 1, x + 2, y + 3);
}

/*---------------------------------------- Picture related functions ----------------------------------------*/

// Draw an Icon
//  libID: Icon library ID
//  picID: Icon ID
//  x/y: Upper-left point
void dwinIconShow(uint8_t libID, uint8_t picID, uint16_t x, uint16_t y) {
  dwinIconShow(true, false, false, libID, picID, x, y);
}

// Write buffer data to the SRAM or Flash
//  mem: 0x5A=32KB SRAM, 0xA5=16KB Flash
//  addr: start address
//  length: Bytes to write
//  data: address of the buffer with data
void dwinWriteToMem(uint8_t mem, uint16_t addr, uint16_t length, uint8_t *data) {
  const uint8_t max_size = 128;
  uint16_t pending = length;
  uint16_t to_send;
  uint16_t indx;
  uint8_t block = 0;

  while (pending > 0) {
    indx = block * max_size;
    to_send = _MIN(pending, max_size);
    size_t i = 0;
    dwinByte(i, 0x31);
    dwinByte(i, mem);
    dwinWord(i, addr + indx); // start address of the data block
    ++i;
    for (uint8_t j = 0; j < i; ++j) { LCD_SERIAL.write(dwinSendBuf[j]); delayMicroseconds(1); }  // Buf header
    for (uint16_t j = indx; j <= indx + to_send - 1; j++) LCD_SERIAL.write(*(data + j)); delayMicroseconds(1);  // write block of data
    for (uint8_t j = 0; j < 4; ++j) { LCD_SERIAL.write(dwinBufTail[j]); delayMicroseconds(1); }
    block++;
    pending -= to_send;
  }
}

void dwinIconShow(uint16_t x, uint16_t y, uint16_t addr) {
  dwinIconShow(0, 0, 1, x, y, addr);
}

// Write the contents of the 32KB SRAM data memory into the designated image memory space.
//  picID: Picture memory space location, 0x00-0x0F, each space is 32Kbytes
void dwinSRAMToPic(uint8_t picID) {
  size_t i = 0;
  dwinByte(i, 0x33);
  dwinByte(i, 0x5A);
  dwinByte(i, 0xA5);
  dwinByte(i, picID);
  dwinSend(i);
}

#endif // DWIN_CREALITY_LCD_JYERSUI
