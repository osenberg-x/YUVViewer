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
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_selectionButton_clicked() {
  _fileName = QFileDialog::getOpenFileName(this, "选择要显示的文件", "./");
  qDebug() << "file name: " << _fileName;
  auto widthStr = ui->widthEdit->text();
  auto heightStr = ui->heightEdit->text();
  if (widthStr.isEmpty() || heightStr.isEmpty()) {
    QMessageBox::warning(this, "警告", "请输入图片的宽高!");
    return;
  }
  _width = ui->widthEdit->text().toInt();
  _height = ui->heightEdit->text().toInt();
  qDebug() << "width: " << _width;
  qDebug() << "height: " << _height;

  Viewer *viewer = new Viewer(this);
  viewer->showPicture(_fileName, _width, _height);
  viewer->show();
}
