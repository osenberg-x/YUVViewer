#include "viewer.h"

#include <QDebug>
#include <QMessageBox>

#include "ui_viewer.h"
#include "utils.h"

Viewer::Viewer(QWidget *parent) : QWidget(parent), ui(new Ui::Viewer) {
  ui->setupUi(this);
}

Viewer::~Viewer() { delete ui; }

void Viewer::showPicture(const QString &name, const int32_t &width,
                         const int32_t &height) {
  FILE *fp = fopen(name.toStdString().c_str(), "rb+");
  if (fp == nullptr) {
    QMessageBox::warning(this, "警告", "打开文件失败!");
    return;
  }

  size_t size = width * height * 3 / 2;
  std::vector<uint8_t> data(size);
  fread(data.data(), 1, size, fp);

  std::vector<uint8_t> bgr24Data;
  YUV420P2BGR24(data.data(), width, height, &bgr24Data);

  QImage image(bgr24Data.data(), width, height, width * 3,
               QImage::Format_BGR888);
  QPixmap pixmap = QPixmap::fromImage(image);
  // ui->label->setAutoFillBackground(true);
  ui->label->setPixmap(pixmap);
  qDebug() << "pixmap size: " << pixmap.size();
  qDebug() << "label size: " << ui->label->size();
  qDebug() << "widget size: " << this->size();
}
