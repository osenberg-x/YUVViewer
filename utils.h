#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>

void YUV420P2BGR24(uint8_t *src, const int32_t &width, const int32_t &height,
                   std::vector<uint8_t> *dst);

void SingleY2BGR24(uint8_t *src, const int32_t &width, const int32_t &height,
                   std::vector<uint8_t> *dst);

#endif  // UTILS_H
