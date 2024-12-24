#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>
#include <QColorDialog>
#include <QInputDialog>
#include <QImageWriter>
#include <QAction>

class DrawArea;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //MainWindow(QWidget *parent = nullptr);
    MainWindow();

private:
    void createActions();
    void createMenus();
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);
    DrawArea *drawArea;
    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;
    QAction *openAction;
    QList<QAction *> saveAsActions;
    QAction *penColorAction;
    QAction *penWidthAction;
    QAction *printAction;
    QAction *exitAction;
    QAction *clearScreenAction;
    QAction *aboutAction;
    QAction *aboutQtAction;


protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void open();
    void save();
    void penColor();
    void penWidth();
    void about();




};
#endif // MAINWINDOW_H
