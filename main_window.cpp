#include "main_window.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

#include "./ui_main_window.h"
#include "viewer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle("YUVViewer");

  QVariant v;
  v.setValue(YUVType::YUV420P);
  ui->comboBox->addItem("YUV420P", v);
  v.setValue(YUVType::YUV420P2GRAY);
  ui->comboBox->addItem("YUV420P2GRAY", v);
  v.setValue(YUVType::YUV420PBrightnessHalf);
  ui->comboBox->addItem("YUV420PBrightnessHalf", v);
  v.setValue(YUVType::SINGLE_Y);
  ui->comboBox->addItem("Single Y", v);
  v.setValue(YUVType::SINGLE_U);
  ui->comboBox->addItem("Single U", v);
  v.setValue(YUVType::SINGLE_V);
  ui->comboBox->addItem("Single V", v);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_selectionButton_clicked() {
  _attr._name = QFileDialog::getOpenFileName(this, "选择要显示的文件", "./")
                    .toStdString();
  qDebug() << "file name: " << QString{_attr._name.c_str()};
  auto widthStr = ui->widthEdit->text();
  auto heightStr = ui->heightEdit->text();
  if (widthStr.isEmpty() || heightStr.isEmpty()) {
    QMessageBox::warning(this, "警告", "请输入图片的宽高!");
    return;
  }
  _attr._width = widthStr.toInt();
  _attr._height = heightStr.toInt();
  qDebug() << "width: " << _attr._width;
  qDebug() << "height: " << _attr._height;

  Viewer *viewer = new Viewer();
  viewer->showPicture(_attr);
  viewer->show();
}

void MainWindow::on_comboBox_currentIndexChanged(int index) {
  qDebug() << "current index: " << ui->comboBox->currentIndex();
  qDebug() << "current text: " << ui->comboBox->currentText();
  _attr._type = ui->comboBox->currentData().value<YUVType>();
}
