#ifndef EXPORTCLASS_H
#define EXPORTCLASS_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QImage>
#include <QImageReader>
#include <QImageWriter>
#include <QDoubleSpinBox>
#include <QGroupBox>

class ExportClass : public QWidget
{
    Q_OBJECT
public:
    explicit ExportClass(QWidget *parent = nullptr);
    void set_image(QImage img);
    void manage();

public slots:
    void finish();

private:
    QImage m_image;
    QImageReader m_reader;
    QImageWriter m_writer;

    QPushButton *button_png = new QPushButton("PNG");
    QPushButton *button_jepg = new QPushButton("JPEG");
    QPushButton *button_jpg = new QPushButton("JPG");
    QPushButton *button_bmp = new QPushButton("BMP");
    QPushButton *button_ppm = new QPushButton("PPM");
    QPushButton *button_xbm = new QPushButton("XBM");
    QPushButton *button_xpm = new QPushButton("XPM");
    QGridLayout *layout_format = new QGridLayout();
    QGroupBox *box_format = new QGroupBox();

    QDoubleSpinBox *x_spin_box = new QDoubleSpinBox();
    QDoubleSpinBox *y_spin_box = new QDoubleSpinBox();
    QHBoxLayout *layout_size = new QHBoxLayout();

    QVBoxLayout *layout_principale = new QVBoxLayout();

    QPushButton *button_finish = new QPushButton(tr("Terminer"));


};

#endif // EXPORTCLASS_H
