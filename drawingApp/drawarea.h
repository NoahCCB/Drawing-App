#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QtWidgets/qwidget.h>
#include <QMouseEvent>
#include <QPainter>

class DrawArea: public QWidget
{
    Q_OBJECT

public:
    DrawArea(QWidget *parent = 0);
    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);
    bool isModified() const {return modified;}
    QColor penColor() const {return myPenColor;}
    int penWidth() const {return myPenWidth;}

public slots:
    void clearImage();
    void print();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);
    bool modified;
    bool drawing;
    QColor myPenColor;
    QImage image;
    int myPenWidth;
    QPoint lastPoint;

};

#endif // DRAWAREA_H
