#ifndef FEN_H
#define FEN_H

#include <QWidget>
#include <QLabel>
#include <QImageReader>
#include <QImageWriter>
#include <QImage>
#include <QVBoxLayout>
#include <QScrollArea>

#include <QMainWindow>
#include <QImage>
#ifndef QT_NO_PRINTER
#include <QPrinter>
#endif

class Fen : public QWidget
{
    Q_OBJECT
public:
    explicit Fen(QWidget *parent = nullptr);
    void afficher_image(QImage img);
    void afficher_image(QString name);

public slots:
    void zoom_in();
    void zoom_out();
    void fit_to_window();
    void save_as();
    void print();
    void copy();
    void paste();
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    QImage get_image();

signals:

private:

    QPrinter printer;

    QImage m_main_image;
    QImageReader *m_reader;
    QImageWriter *m_writer;
    QLabel *m_label;
    QVBoxLayout *layout_principale = new QVBoxLayout;
    QScrollArea *m_area = new QScrollArea();
    int zoom_factor = 12;
    double scaleFactor = 1;
    QString m_file_name;
};

#endif // FEN_H
