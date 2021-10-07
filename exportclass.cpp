#include "exportclass.h"
#include <QFileDialog>
#include <QFile>
ExportClass::ExportClass(QWidget *parent) : QWidget(parent)
{
    manage();
    setLayout(layout_principale);
    connect(button_finish,SIGNAL(clicked()),this,SLOT(finish()));
}
void ExportClass::manage()
{
    button_bmp->setCheckable(true);
    button_jepg->setCheckable(true);
    button_jpg->setCheckable(true);
    button_png->setCheckable(true);
    button_ppm->setCheckable(true);
    button_xbm->setCheckable(true);
    button_xpm->setCheckable(true);

    layout_format->addWidget(button_png,0,0,1,1);
    layout_format->addWidget(button_bmp,0,1,1,1);
    layout_format->addWidget(button_jpg,0,2,1,1);

    layout_format->addWidget(button_jepg,1,0,1,1);
    layout_format->addWidget(button_ppm,1,1,1,1);
    layout_format->addWidget(button_xbm,1,2,1,1);

    layout_format->addWidget(button_xpm,2,1,1,1);

    layout_size->addWidget(x_spin_box);
    layout_size->addWidget(y_spin_box);

    layout_principale->addLayout(layout_format);
    layout_principale->addLayout(layout_size);
    layout_principale->addWidget(button_finish);
}
void ExportClass::set_image(QImage img)
{
    m_image = img;
    x_spin_box->setValue(img.size().width());
    y_spin_box->setValue(img.size().height());
}
void ExportClass::finish()
{
    if(( x_spin_box->value() != m_image.size().width()) || (y_spin_box->value() != m_image.size().height()))
    {
        QImageWriter w;
        w.setFileName("f.png");
        QImage img = m_image;
        w.write(img);

        m_reader.setFileName("f.png");
        m_reader.setScaledSize(QSize(x_spin_box->value(),y_spin_box->value()));
        img = m_reader.read();

        QFile file("f.png");
        file.remove();
        QString *a = new QString("*.png");
        QFileDialog f;
        QString name = f.getSaveFileName(this,"Exporter l'image",QString(),"*.png *.bmp *.jpg *.jpeg *.ppm *.xpm *.xbm",a);
        m_writer.setFileName(name);
        m_writer.write(img);


        close();

    }
}
