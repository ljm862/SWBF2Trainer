#include "includes.h"
void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color);

void DrawLine(int x1, int y1, int x2, int y2, int thickness, D3DCOLOR color);
void DrawLine(Vector2 src, Vector2 dst, int thickness, D3DCOLOR color);

void DrawText(const char* text, float x, float y, D3DCOLOR color);