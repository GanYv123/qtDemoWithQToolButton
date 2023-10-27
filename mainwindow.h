#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QProgressBar>
#include <QSpinBox>
#include <QFontComboBox>
#include <QActionGroup>
#include <QFont>
#include <QTextCharFormat>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QLabel *labFile; //添加到状态栏里
    QLabel *labInfo;
    QProgressBar *progressBar1; //进度条添加到状态栏中
    QSpinBox *spinFontSize; //字体大小添加到工具栏上
    QFontComboBox *comboFontName;//字体名称
    QActionGroup *actionGroup;  //action分组 ，用于汉语和英语的互斥选项


    void bulidUI(); //手写代码方式创建ui
    void bulidSignalSlots();    //手动关联信号和槽

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void do_fontSize_changed(int fontSize);
    void do_fontSelected(const QFont &font);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
