#include "utils.h"

#include <QDebug>

// 格式转换可以使用查表法优化

// static const double B_U_FACTOR = 1.732446;
// static const double G_U_FACTOR = 0.337633;
// static const double G_V_FACTOR = 0.698001;
// static const double R_U_FACTOR = 1.370705;

// BT601 NTSC
static const double R_V_FACTOR = 1.4075;
static const double G_U_FACTOR = 0.3455;
static const double G_V_FACTOR = 0.7169;
static const double B_U_FACTOR = 1.779;

// R = Y + 1.4075 * (V - 128)
// G = Y - 0.3455 * (U - 128) - 0.7169 * (V - 128)
// B = Y + 1.779 * (U - 128)

#define NUM(x) (x) < 0 ? 0 : ((x) > 255 ? 255 : (x))

void YUV420P2BGR24(uint8_t *src, const int32_t &width, const int32_t &height,
                   std::vector<uint8_t> *dst) {
  size_t ySize = width * height;
  uint8_t *yData = src;
  uint8_t *uData = src + ySize;
  uint8_t *vData = src + ySize + ySize / 4;

  int32_t value = 0;
  for (int32_t i = 0; i < height; ++i) {
    int32_t startY = i * width;
    int32_t startU = i / 2 * (width / 2);
    int32_t startV = startU;
    for (int32_t j = 0; j < width; ++j) {
      uint8_t y = yData[startY + j];
      uint8_t u = uData[startU + j / 2];
      uint8_t v = vData[startV + j / 2];

      value = y + R_V_FACTOR * (v - 128);
      uint8_t R = NUM(value);
      value = y - G_U_FACTOR * (u - 128) - G_V_FACTOR * (v - 128);
      uint8_t G = NUM(value);
      value = y + B_U_FACTOR * (u - 128);
      uint8_t B = NUM(value);

      dst->push_back(B);
      dst->push_back(G);
      dst->push_back(R);
    }
  }
}
