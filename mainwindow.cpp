#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::bulidUI()
{//创建状态栏上的组件
    labFile = new QLabel(this);
    labFile->setMidLineWidth(150);
    labFile->setText("文件名:");
    ui->statusBar->addWidget(labFile);

    progressBar1 = new QProgressBar(this);
    progressBar1->setMinimumWidth(200);
    progressBar1->setMinimum(5);
    progressBar1->setMaximum(50);
    progressBar1->setValue(ui->textEdit->font().pointSize());
    ui->statusBar->addWidget(progressBar1);

    labInfo = new QLabel(this);
    labInfo->setText("字体名称:");
    ui->statusBar->addPermanentWidget(labInfo);

    //为汉语和英语创建互斥选项
    actionGroup = new QActionGroup(this);
    actionGroup->addAction(ui->actLang_CN);
    actionGroup->addAction(ui->actLang_EN);
    actionGroup->setExclusive(true);
    ui->actLang_CN->setChecked(true);

    //创建工具栏上一些无法可视化的一些组件
    spinFontSize = new QSpinBox(this);
    spinFontSize->setRange(5,50);
    spinFontSize->setValue(ui->textEdit->font().pointSize());
    spinFontSize->setMinimumWidth(50);
    ui->mainToolBar->addWidget(spinFontSize);
    ui->mainToolBar->addSeparator();

    comboFontName = new QFontComboBox(this);
    comboFontName->setMinimumWidth(150);

    ui->mainToolBar->addWidget(comboFontName);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actClose);
}

void MainWindow::bulidSignalSlots()
{
    connect(spinFontSize,&QSpinBox::valueChanged,this,&MainWindow::do_fontSize_changed);

    connect(comboFontName,&QFontComboBox::currentFontChanged,this,&MainWindow::do_fontSelected);

    connect(ui->textEdit,&QPlainTextEdit::selectionChanged,this,[this](){
        QTextCursor cursor = ui->textEdit->textCursor();
        labInfo->setText(cursor.selectedText());
        QTextCharFormat fmt = ui->textEdit->currentCharFormat();
        ui->actFont_Bold->setChecked(fmt.font().bold());
        ui->actFont_Italic->setChecked(fmt.font().italic());
        ui->actFont_UnderLine->setChecked(fmt.font().underline());

    });

    //粗体bold
    connect(ui->actFont_Bold,&QAction::triggered,this,[this](bool checked){
        QTextCharFormat fmt = ui->textEdit->currentCharFormat();
        if(checked){
            fmt.setFontWeight(QFont::Bold);
        }else{
            fmt.setFontWeight(QFont::Normal);
        }
        ui->textEdit->setCurrentCharFormat(fmt);

    });
    //斜体
    connect(ui->actFont_Italic,&QAction::triggered,this,[this](bool checked){
        QTextCharFormat fmt = ui->textEdit->currentCharFormat();
        fmt.setFontItalic(checked);
        ui->textEdit->mergeCurrentCharFormat(fmt);
    });
    //下划线
    connect(ui->actFont_UnderLine,&QAction::triggered,this,[this](bool checked){
        QTextCharFormat fmt = ui->textEdit->currentCharFormat();
        fmt.setFontUnderline(checked);
        ui->textEdit->mergeCurrentCharFormat(fmt);
    });
    connect(ui->actFile_Save,&QAction::triggered,this,[this](){
        ui->textEdit->document()->setModified(false);
        labFile->setText("文件已保存");
    });
    connect(ui->actSys_ToggleText,&QAction::triggered,this,[this](bool checked){
        //是否显示工具按钮文字
        if(checked){
            ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        }else{
            ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
        }
    });
    connect(ui->textEdit,&QPlainTextEdit::copyAvailable,this,[this](bool checked){
        ui->actEdit_Copy->setEnabled(checked);
        ui->actEdit_Cut->setEnabled(checked);
        ui->actEdit_Paste->setEnabled(ui->textEdit->canPaste());
    });
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bulidUI();
    bulidSignalSlots();
    ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::do_fontSize_changed(int fontSize)
{
    //    QFont font = ui->textEdit->font();
    //    font.setPointSize(fontSize);
    //    ui->textEdit->setFont(font);
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();
    fmt.setFontPointSize(fontSize);
    ui->textEdit->mergeCurrentCharFormat(fmt);
    progressBar1->setValue(fontSize);
}

void MainWindow::do_fontSelected(const QFont &font)
{//选中的字体 FontComboBox
    labInfo->setText("字体名称:"+font.family()); //状态栏上显示
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();
    fmt.setFont(font);
    ui->textEdit->setCurrentCharFormat(fmt);
}

