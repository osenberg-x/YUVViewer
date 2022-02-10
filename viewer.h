#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>

namespace Ui {
class Viewer;
}

class Viewer : public QWidget {
  Q_OBJECT

 public:
  explicit Viewer(QWidget *parent = nullptr);
  ~Viewer();

  void showPicture(const QString &name, const int32_t &width,
                   const int32_t &height);

 private:
  Ui::Viewer *ui;
};

#endif  // VIEWER_H
