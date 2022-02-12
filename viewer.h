#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>

#include "datas.h"

namespace Ui {
class Viewer;
}

class Viewer : public QWidget {
  Q_OBJECT

 public:
  explicit Viewer(QWidget *parent = nullptr);
  ~Viewer();

  void showPicture(const PictureAttribute &attribute);

 private:
  QPixmap singleYUV2Pixmap(const uint8_t *data, const int32_t &width,
                           const int32_t &height);
  Ui::Viewer *ui;
};

#endif  // VIEWER_H
