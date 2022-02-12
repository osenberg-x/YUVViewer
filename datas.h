#ifndef DATAS_H
#define DATAS_H

#include <QMetaType>
#include <iostream>

enum class YUVType : uint32_t {
  YUV420P = 1,
  SINGLE_Y = 2,
  SINGLE_U = 3,
  SINGLE_V = 4,
};
Q_DECLARE_METATYPE(YUVType);

typedef struct PictureAttribute {
  std::string _name;
  int32_t _width;
  int32_t _height;
  YUVType _type;
} PictureAttribute;

#endif  // DATAS_H
