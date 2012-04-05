#ifndef __DRAWING_H__
#define __DRAWING_H__

#include <stdint.h>
#include <stdbool.h>

void DrawPixelWithClip(uint16_t *screenbase,int x,int y,int col,bool clip);
void DrawVerticalLineWithClip(uint16_t *screenbase,int x,int y,int h,int col,bool clip);
void DrawHorizontalLineWithClip(uint16_t *screenbase,int x,int y,int w,int col,bool clip);
void DrawLineWithClip(uint16_t *screenbase,int x1,int y1,int x2,int y2,int col,bool clip);
void DrawRectWithClip(uint16_t *screenbase,int x,int y,int w,int h,int col,bool clip);
void FillRectWithClip(uint16_t *screenbase,int x,int y,int w,int h,int col,bool clip);
void ClearScreen(uint16_t *screenbase,int col);

void DrawPixel(int x,int y,int col);
void DrawVerticalLine(int x,int y,int h,int col);
void DrawHorizontalLine(int x,int y,int w,int col);
void DrawLine(int x1,int y1,int x2,int y2,int col);
void DrawRect(int x,int y,int w,int h,int col);
void FillRect(int x,int y,int w,int h,int col);

bool ClipLine(int *x1,int *y1,int *x2,int *y2,int left,int top,int right,int bottom);

#endif
