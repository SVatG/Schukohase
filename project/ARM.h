#ifndef __ARM_H__
#define __ARM_H__

#include "Utils.h"
#include <stdint.h>

void ClaimWRAM();

void ATTR_ITCM Decay(uint16_t *screenbase,int lines);

void ATTR_ITCM RenderBackgroundARM(int t,uint8_t *screen);

void ATTR_ITCM RenderRadialARM(int t,int cx,int cy,uint8_t *screen,uint16_t *vram,
uint32_t *lookup1,uint32_t *lookup2,uint32_t *lookup3,uint32_t *lookup4);

#endif
