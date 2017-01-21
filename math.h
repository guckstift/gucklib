#ifndef math_h
#define math_h

#include "basetypes.h"

ulong nextPowerOf2(ulong val);
ulong normalize(ulong x);
ulong clz(ulong x);

#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))
#define clamp(x, l, u) min(max(x, l), u)

#endif
