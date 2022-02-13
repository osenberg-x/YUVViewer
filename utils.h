#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>

void YUV420P2BGR24(uint8_t *src, const int32_t &width, const int32_t &height,
                   std::vector<uint8_t> *dst);

// YUV420P 亮度减半
// 将图像的亮度减半，只要将图像的每个像素的Y值取出来分别进行除以2的工作就可以了。
void YUV420PBrightnessInHalf(uint8_t *src, const int32_t &width,
                             const int32_t &height, std::vector<uint8_t> *dst);

// YUV420P convert GRAY
// 从代码可以看出，如果想把YUV格式像素数据变成灰度图像，只需要将U、V分量设置成128即可。
// 这是因为U、V是图像中的经过偏置处理的色度分量。色度分量在偏置处理前的取值范围是-128至127，
// 这时候的无色对应的是“0”值。经过偏置后色度分量取值变成了0至255，因而此时的无色对应的就是128了。
void YUV420P2GRAY(uint8_t *src, const int32_t &width, const int32_t &height,
                  std::vector<uint8_t> *dst);
void SingleY2BGR24(uint8_t *src, const int32_t &width, const int32_t &height,
                   std::vector<uint8_t> *dst);

#endif  // UTILS_H
