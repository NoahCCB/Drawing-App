#include "mainwindow.h"
// #include "./ui_mainwindow.h"
#include "drawarea.h"
#include <QtWidgets/qapplication.h>

// MainWindow::MainWindow(QWidget *parent)
//     : QMainWindow(parent)
//     , ui(new Ui::MainWindow)
// {
//     ui->setupUi(this);
// }

// MainWindow::~MainWindow()
// {
//     delete ui;
// }

MainWindow::MainWindow()
{
    drawArea = new DrawArea;
    setCentralWidget(drawArea);

    createActions();
    createMenus();

    setWindowTitle(tr("Draw App"));
    resize(500, 500);
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if(maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::open()
{
    if(maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
        if (!fileName.isEmpty()) {
            drawArea->openImage(fileName);
        }
    }
}

void MainWindow::save()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

void MainWindow::penColor()
{
    QColor newColor = QColorDialog::getColor(drawArea -> penColor());
    if(newColor.isValid()) {
        drawArea->setPenColor(newColor);
    }
}

void MainWindow::penWidth()
{
    bool ok;
    int newWidth = QInputDialog::getInt(this,
                                        tr("Draw App"),
                                        tr("Select pen width : "),
                                        drawArea->penWidth(), 1, 50, 1, &ok);

    if (ok) {
        drawArea->setPenWidth(newWidth);
    }
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About the Draw App"), tr("<p>Created by Noah Cunningham Baker</p>"));
}

void MainWindow::createActions()
{
    openAction = new QAction(tr("&Open"), this);
    if (!openAction) {
        qWarning() << "openAction is null!";
    }
    openAction->setShortcuts(QKeySequence::Open);
    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    // Create Save As actions for supported formats
    foreach(QByteArray format, QImageWriter::supportedImageFormats()) {
        QString text = tr("%1...").arg(QString(format).toUpper());
        QAction *action = new QAction(text, this);
        if (!action) {
            qWarning() << "Failed to create action for format" << format;
        }
        action->setData(format);
        connect(action, &QAction::triggered, this, &MainWindow::save);
        saveAsActions.append(action);
    }

    // Print action
    printAction = new QAction(tr("&Print..."), this);
    if (!printAction) {
        qWarning() << "printAction is null!";
    }
    connect(printAction, &QAction::triggered, drawArea, &DrawArea::print);

    // Exit action
    exitAction = new QAction(tr("&Exit"), this);
    if (!exitAction) {
        qWarning() << "exitAction is null!";
    }
    exitAction->setShortcuts(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);

    // Pen Color action
    penColorAction = new QAction(tr("&Pen Color..."), this);
    if (!penColorAction) {
        qWarning() << "penColorAction is null!";
    }
    connect(penColorAction, &QAction::triggered, this, &MainWindow::penColor);

    // Pen Width action
    penWidthAction = new QAction(tr("&Pen Width..."), this);
    if (!penWidthAction) {
        qWarning() << "penWidthAction is null!";
    }
    connect(penWidthAction, &QAction::triggered, this, &MainWindow::penWidth);

    // Clear Screen action
    clearScreenAction = new QAction(tr("&Clear Screen..."), this);
    if (!clearScreenAction) {
        qWarning() << "clearScreenAction is null!";
    }
    clearScreenAction->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAction, &QAction::triggered, drawArea, &DrawArea::clearImage);

    // About action
    aboutAction = new QAction(tr("&About..."), this);
    if (!aboutAction) {
        qWarning() << "aboutAction is null!";
    }
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);

    // About Qt action
    aboutQtAction = new QAction(tr("&About &QT..."), this);
    if (!aboutQtAction) {
        qWarning() << "aboutQtAction is null!";
    }
    connect(aboutQtAction, &QAction::triggered, qApp, &QApplication::aboutQt);
}


void MainWindow::createMenus()
{
    saveAsMenu = new QMenu(tr("&Save As"), this);
    foreach(QAction *action, saveAsActions){
        if (action) {
            saveAsMenu->addAction(action);
        }
    }
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAction);
    fileMenu->addMenu(saveAsMenu);
    fileMenu->addAction(printAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(penColorAction);
    optionMenu->addAction(penWidthAction);
    optionMenu->addSeparator();
    optionMenu->addAction(clearScreenAction);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionMenu);
    menuBar()->addMenu(helpMenu);
}

bool MainWindow::maybeSave()
{
    if (drawArea->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this,
                                    tr("Draw App"),
                                    tr("The image has been modified. \n"
                                    "Do you want to save your changes?"),
                                    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save) {
            return saveFile("png");
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return false;
}

bool MainWindow::saveFile(const QByteArray &fileFormat)
{
    QString initialPath = QDir::currentPath() + "/untitled" + fileFormat;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                    initialPath,
                                                    tr("%1 Files (*.%2;; All Files(*)")
                                                        .arg(QString::fromLatin1(fileFormat.toUpper()))
                                                        .arg(QString::fromLatin1(fileFormat)));
    if(fileName.isEmpty()) {
        return false;
    } else {
        return drawArea->saveImage(fileName, fileFormat.constData());
    }
}


