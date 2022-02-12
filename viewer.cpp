#include "viewer.h"

#include <QDebug>
#include <QMessageBox>

#include "ui_viewer.h"
#include "utils.h"

Viewer::Viewer(QWidget *parent) : QWidget(parent), ui(new Ui::Viewer) {
  ui->setupUi(this);
}

Viewer::~Viewer() { delete ui; }

void Viewer::showPicture(const PictureAttribute &attribute) {
  auto &&name = attribute._name;
  auto &&width = attribute._width;
  auto &&height = attribute._height;
  auto &&type = attribute._type;
  FILE *fp = fopen(name.c_str(), "rb+");
  if (fp == nullptr) {
    QMessageBox::warning(this, "警告", "打开文件失败!");
    return;
  }
  QString qName = QString{name.c_str()};
  setWindowTitle(qName);

  size_t size = 0;
  std::vector<uint8_t> data;

  bool isSingleUVFile = false;
  if (qName.contains(".yuv")) {
    size = width * height * 3 / 2;
  } else if (qName.contains(".y")) {
    if (type == YUVType::SINGLE_Y) {
      size = width * height;
    } else if (type == YUVType::SINGLE_U || type == YUVType::SINGLE_V) {
      size = width * height / 4;
      isSingleUVFile = true;
    }
  }
  data.reserve(size);
  fread(data.data(), 1, size, fp);

  //  FILE *yfp = fopen("./output_y.y", "wb+");
  //  FILE *ufp = fopen("./output_u.y", "wb+");
  //  FILE *vfp = fopen("./output_v.y", "wb+");
  //  fwrite(data.data(), 1, width * height, yfp);
  //  fwrite(data.data() + width * height, 1, width * height / 4, ufp);
  //  fwrite(data.data() + width * height * 5 / 4, 1, width * height / 4, vfp);
  //  fclose(ufp);
  //  fclose(vfp);
  //  fclose(yfp);

  fclose(fp);

  QPixmap showPixmap;
  switch (type) {
    case YUVType::YUV420P: {
      std::vector<uint8_t> bgr24Data;
      bgr24Data.reserve(width * height * 3);
      YUV420P2BGR24(data.data(), width, height, &bgr24Data);
      QImage image(bgr24Data.data(), width, height, width * 3,
                   QImage::Format_BGR888);
      showPixmap.convertFromImage(image);
      break;
    }
    case YUVType::SINGLE_Y: {
      showPixmap = singleYUV2Pixmap(data.data(), width, height);
      break;
    }
    case YUVType::SINGLE_U: {
      if (!isSingleUVFile) {
        size_t ySize = width * height;
        size_t uSize = ySize / 4;
        std::vector<uint8_t> uData(uSize);
        memcpy(uData.data(), data.data() + ySize, uSize);

        showPixmap = singleYUV2Pixmap(uData.data(), width / 2, height / 2);
      } else {
        showPixmap = singleYUV2Pixmap(data.data(), width / 2, height / 2);
      }
      break;
    }
    case YUVType::SINGLE_V: {
      if (!isSingleUVFile) {
        size_t ySize = width * height;
        size_t vSize = ySize / 4;
        std::vector<uint8_t> vData(vSize);
        memcpy(vData.data(), data.data() + ySize + vSize, vSize);

        showPixmap = singleYUV2Pixmap(vData.data(), width / 2, height / 2);
      } else {
        showPixmap = singleYUV2Pixmap(data.data(), width / 2, height / 2);
      }
      break;
    }
    default:
      break;
  }

  ui->label->setAutoFillBackground(true);
  ui->label->setPixmap(showPixmap);
  resize(showPixmap.size());
}

QPixmap Viewer::singleYUV2Pixmap(const uint8_t *data, const int32_t &width,
                                 const int32_t &height) {
  QImage image(width, height, QImage::Format_Indexed8);
  QVector<QRgb> table(256);
  for (int32_t i = 0; i < 256; ++i) {
    table[i] = qRgb(i, i, i);
  }
  image.setColorTable(table);
  int32_t index = 0;
  for (int32_t i = 0; i < height; ++i) {
    for (int32_t j = 0; j < width; ++j) {
      uint8_t value = data[index];
      image.setPixel(j, i, value);
      ++index;
    }
  }
  return QPixmap::fromImage(image);
}
