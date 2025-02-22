#ifndef PERLIN_H
#define PERLIN_H

float noise3d(float x, float y, float z);
float fade(float t);
float lerp(float a, float b, float x);
float grad(int hash, float x, float y, float z);

extern const int p[512];

#endif
