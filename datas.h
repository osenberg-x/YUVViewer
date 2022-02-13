#ifndef DATAS_H
#define DATAS_H

#include <QMetaType>
#include <iostream>

enum class YUVType : uint32_t {
  YUV420P = 1,
  YUV420P2GRAY,
  YUV420PBrightnessHalf,
  SINGLE_Y,
  SINGLE_U,
  SINGLE_V,
};
Q_DECLARE_METATYPE(YUVType);

typedef struct PictureAttribute {
  std::string _name;
  int32_t _width;
  int32_t _height;
  YUVType _type;
} PictureAttribute;

#endif  // DATAS_H
