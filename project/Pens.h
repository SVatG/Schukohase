#ifndef __PENS_H__
#define __PENS_H__

#include <stdint.h>
#include <stdbool.h>

#define MaxPens 5

typedef struct PenFrame
{
	struct { uint8_t x,y; } pens[MaxPens];
} PenFrame;

void InitPensOnSecondaryScreen(bool recordmode);

void RunPens(PenFrame *frames,int numframes,int frame);

void ClearPenData(PenFrame *frames,int numframes);
bool LoadPenData(PenFrame *frames,int numframes,const char *filename);
bool SavePenData(PenFrame *frames,int numframes,const char *filename);

#endif
