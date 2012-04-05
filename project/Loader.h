/**
 * Functions that load things from the file system.
 */

#ifndef __LOADER_H__
#define __LOADER_H__

// General-purpose includes
//#include <nds.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// Register definitions
#include "Hardware.h"

// Buffer for VRAM image load functions. It would be a good idea not to try to
// load images bigger than 256x256.
uint16_t* tempImage;

// Keep in mind that loadVRAMIndirect and loadImage make sure the alpha bit
// is set.
void loadVRAMIndirect(char* path, uint16_t* vramPos, uint32_t size);
void loadImage(char* path, uint16_t* buffer, uint32_t size);
void load8bVRAMIndirect(char* path, uint16_t* vramPos, uint32_t size);
void loadData(char* path, uint8_t* target, uint32_t size);
uint16_t* loadSpriteA( char* path );
uint16_t* loadSpriteB( char* path );
uint16_t* loadSprite32A( char* path );
uint16_t* loadSprite32B( char* path );

#endif
