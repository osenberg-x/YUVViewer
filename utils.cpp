#include "utils.h"

static const double B_U_FACTOR = 2.03211;
static const double G_U_FACTOR = 0.39465;
static const double G_V_FACTOR = 0.58060;
static const double R_V_FACTOR = 1.13983;

void YUV420P2BGR24(uint8_t *src, const int32_t &width, const int32_t &height,
                   std::vector<uint8_t> *dst) {
  size_t ySize = width * height;
  size_t u = 0;
  size_t v = 0;
  uint8_t *uData = src + ySize;
  uint8_t *vData = src + ySize + ySize / 4;
  for (size_t y = 0; y < ySize; ++y) {
    uint8_t B = src[y] + B_U_FACTOR * (uData[u] - 128);
    uint8_t G =
        src[y] - G_U_FACTOR * (uData[u] - 128) - G_V_FACTOR * (vData[v] - 128);
    uint8_t R = src[y] + R_V_FACTOR * (vData[v] - 128);

    dst->push_back(B);
    dst->push_back(G);
    dst->push_back(R);

    if (y != 0 && y % 4 == 0) {
      ++u;
      ++v;
    }
  }
}
