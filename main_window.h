#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "datas.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_selectionButton_clicked();

  void on_comboBox_currentIndexChanged(int index);

 private:
  Ui::MainWindow *ui;

  PictureAttribute _attr;
};
#endif  // MAINWINDOW_H
