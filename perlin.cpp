#include "perlin.h"
#include <math.h>

float noise3d(float x, float y, float z) {
  int X = static_cast<int>(floor(x)) & 255;  // static_cast<int> added
  int Y = static_cast<int>(floor(y)) & 255;  // static_cast<int> added
  int Z = static_cast<int>(floor(z)) & 255;  // static_cast<int> added
  x -= floor(x); y -= floor(y); z -= floor(z);
  float u = fade(x), v = fade(y), w = fade(z);

  int A = p[p[p[X] + Y] + Z];
  int AA = p[p[p[X + 1] + Y] + Z];
  int AB = p[p[p[X] + (Y + 1)] + Z];
  int BA = p[p[p[X] + Y] + (Z + 1)];
  int BB = p[p[p[X + 1] + (Y + 1)] + Z];
  int AC = p[p[p[X] + Y] + (Z + 1)];
  int BC = p[p[p[X + 1] + Y] + (Z + 1)];
  int CA = p[p[p[X] + (Y + 1)] + (Z + 1)];
  int CB = p[p[p[X + 1] + (Y + 1)] + (Z + 1)];

  int hash_A = p[static_cast<int>(A) & 15];      // static_cast<int> added
  int hash_AA = p[static_cast<int>(AA) & 15];    // static_cast<int> added
  int hash_AB = p[static_cast<int>(AB) & 15];    // static_cast<int> added
  int hash_BA = p[static_cast<int>(BA) & 15];    // static_cast<int> added
  int hash_BB = p[static_cast<int>(BB) & 15];    // static_cast<int> added
  int hash_AC = p[static_cast<int>(AC) & 15];    // static_cast<int> added
  int hash_BC = p[static_cast<int>(BC) & 15];    // static_cast<int> added
  int hash_CA = p[static_cast<int>(CA) & 15];    // static_cast<int> added
  int hash_CB = p[static_cast<int>(CB) & 15];    // static_cast<int> added


  float grad_A = grad(hash_A, x, y, z);
  float grad_AA = grad(hash_AA, x - 1, y, z);
  float grad_AB = grad(hash_AB, x, y - 1, z);
  float grad_BA = grad(hash_BA, x, y, z - 1);
  float grad_BB = grad(hash_BB, x - 1, y - 1, z);
  float grad_AC = grad(hash_AC, x, y, z - 1);
  float grad_BC = grad(hash_BC, x - 1, y, z - 1);
  float grad_CA = grad(hash_CA, x, y - 1, z - 1);
  float grad_CB = grad(hash_CB, x - 1, y - 1, z - 1);

  float result = lerp(w, lerp(v, lerp(u, grad_A, grad_AA),
                               lerp(u, grad_AB, grad_BB)),
                     lerp(v, lerp(u, grad_AC, grad_BC),
                               lerp(u, grad_CA, grad_CB)));
  return result;
}

float fade(float t) { return t * t * t * (t * (t * 6 - 15) + 10); }

float lerp(float a, float b, float x) { return a + x * (b - a); }

float grad(int hash, float x, float y, float z) {
  int case_num = hash & 15; // Fixed the issue here
  switch (case_num) {
    case 0: return x + y;
    case 1: return -x + y;
    case 2: return x - y;
    case 3: return -x - y;
    case 4: return x + z;
    case 5: return -x + z;
    case 6: return x - z;
    case 7: return -x - z;
    case 8: return y + z;
    case 9: return -y + z;
    case 10: return y - z;
    case 11: return -y - z;
    case 12: return x + y;
    case 13: return -x + y;
    case 14: return x - y;
    case 15: return -x - y;
    default: return 0;
  }
}

const int p[512] = {
  // ... (The Perlin permutation table - same as before)
};
