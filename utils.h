#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>

void YUV420P2BGR24(uint8_t *src, const int32_t &width, const int32_t &height,
                   std::vector<uint8_t> *dst);

bool yuv420pToRgb24(uint8_t *ch_YuvData, uint i_width, uint i_height,
                    uint8_t *ch_RgbData);
#endif  // UTILS_H
