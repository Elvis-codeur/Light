#include <QtWidgets>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif
#endif


#include "fen.h"
#include <iostream>
#include <cmath>
#include <QFileDialog>
Fen::Fen(QWidget *parent) : QWidget(parent)
{
    m_label = new QLabel();
    m_reader = new QImageReader();
    m_writer = new QImageWriter();

    //m_label->setBackgroundRole(QPalette::Base);
    //m_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    //m_label->setScaledContents(true);
    //m_area->setBackgroundRole(QPalette::Dark);

    m_label->setAlignment(Qt::AlignCenter);
    m_label->setScaledContents(true);
    m_area->setWidget(m_label);
    m_area->setAlignment(Qt::AlignCenter);
    //m_area->setWidgetResizable(true);
    m_area->setVisible(false);




    layout_principale->addWidget(m_area);
    setLayout(layout_principale);

}
QImage Fen::get_image()
{
    return m_main_image;
}
void Fen::afficher_image(QImage img)
{
    m_main_image = img;
    m_label->setPixmap(QPixmap::fromImage(img));
    m_label->resize(img.size());
    m_area->setVisible(true);

}
void Fen::adjustScrollBar(QScrollBar *scrollBar, double factor)
//! [25] //! [26]
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}
void Fen::zoom_in()
{
    Q_ASSERT(m_label->pixmap());
    scaleFactor *= 1.1;
    m_label->resize(m_label->pixmap()->size()*scaleFactor);
    adjustScrollBar(m_area->horizontalScrollBar(), 1.1);
    adjustScrollBar(m_area->verticalScrollBar(), 1.1);

}
void Fen::zoom_out()
{
    Q_ASSERT(m_label->pixmap());
    scaleFactor *=0.9;
    m_label->resize(m_label->pixmap()->size()*scaleFactor);
    adjustScrollBar(m_area->horizontalScrollBar(), 0.9);
    adjustScrollBar(m_area->verticalScrollBar(),0.9) ;
}
void Fen::fit_to_window()
{
    m_label->resize(m_area->size());
}
void Fen::afficher_image(QString name)
{
    m_reader->setFileName(name);

    if((m_reader->size().height() > this->height()) && (m_reader->size().width() > this->width()) )
    {
        float f1 = m_reader->size().height()/this->height();

        float f2 = m_reader->size().width()/this->width();

        if(f1 > f2)
        {
            std::cout <<f1 << "\n\n\n\n"<< m_reader->size().width() << "\n\n" << this->height() << "\n\n" << m_reader->size().height();

            m_reader->setScaledSize(QSize(m_reader->size().width()/f1,this->height()-50));//*factor,
        }

        else
        {
            std::cout << "El";
            std::cout << f2 << "\n\n\n\n"<< m_reader->size().width() << "\n\n" << this->height() << "\n\n" << m_reader->size().height();

            m_reader->setScaledSize(QSize(this->width()-50,m_reader->size().height()/f2));//*factor
        }

    }


    m_main_image = m_reader->read();
    m_label->setPixmap(QPixmap::fromImage(m_main_image));
    m_label->resize(m_main_image.size());
    m_area->setVisible(true);
}
void Fen::save_as()
{
    QFileDialog f;
    QString *_s = new QString();
    QString name = f.getSaveFileName(this,"Enrégistrer l'image",QString(),"*.png *.jpeg *.jpg *.bmp *.ppm *.xbm *.xpm",_s);
    if (name.size() > 0)
    {
        m_writer->setFileName(name);
        m_writer->write(m_main_image);
    }
}
void Fen::print()
{
    Q_ASSERT(m_label->pixmap());
#if QT_CONFIG(printdialog)
//! [6] //! [7]
    QPrintDialog dialog(&printer, this);
//! [7] //! [8]
    if (dialog.exec()) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = m_label->pixmap()->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(m_label->pixmap()->rect());
        painter.drawPixmap(0, 0, *m_label->pixmap());
    }
#endif
}

#ifndef QT_NO_CLIPBOARD
static QImage clipboardImage()
{
    if (const QMimeData *mimeData = QGuiApplication::clipboard()->mimeData()) {
        if (mimeData->hasImage()) {
            const QImage image = qvariant_cast<QImage>(mimeData->imageData());
            if (!image.isNull())
                return image;
        }
    }
    return QImage();
}
#endif // !QT_NO_CLIPBOARD

void Fen::copy()
{
#ifndef QT_NO_CLIPBOARD
    QGuiApplication::clipboard()->setImage(m_main_image);
#endif // !QT_NO_CLIPBOARD
}

void Fen::paste()
{
#ifndef QT_NO_CLIPBOARD
    const QImage newImage = clipboardImage();
    if (newImage.isNull()) {
        //statusBar()->showMessage(tr("No image in clipboard"));
    } else {
        afficher_image(newImage);
        setWindowFilePath(QString());

    }
#endif // !QT_NO_CLIPBOARD
}
