#include "fenprincipale.h"
#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>
#include <QKeyEvent>
#include <QFileInfo>
#include <iostream>
#include <QTextStream>
#include <QTextDocument>
#include <QPlainTextEdit>
#include <QPainter>

Fenprincipale::Fenprincipale(QWidget *parent) : QMainWindow(parent)
{
    setWindowIcon(QIcon(":/new/prefix1/light.png"));

    /* QWidget *w = new QWidget();
    QHBoxLayout l;
    l.addWidget(button_previous);
    l.addWidget(fen_principale);
    l.addWidget(button_next);
    w->setLayout(&l);
    */

    setFocus(Qt::ActiveWindowFocusReason);
    setCentralWidget(fen_principale);
    manage_bar();


     connect(A_open,SIGNAL(triggered()),this,SLOT(open_file()));
     connect(A_open_folder,SIGNAL(triggered()),this,SLOT(open_folder()));
     connect(A_zoom_in,SIGNAL(triggered()),fen_principale,SLOT(zoom_in()));
     connect(A_zoom_out,SIGNAL(triggered()),fen_principale,SLOT(zoom_out()));
     connect(A_fit_to_window,SIGNAL(triggered()),fen_principale,SLOT(fit_to_window()));
     connect(A_save_as,SIGNAL(triggered()),fen_principale,SLOT(save_as()));
     connect(A_copy,SIGNAL(triggered()),fen_principale,SLOT(copy()));
     connect(A_paste,SIGNAL(triggered()),fen_principale,SLOT(paste()));
     connect(A_print,SIGNAL(triggered()),fen_principale,SLOT(print()));
     connect(A_exit,SIGNAL(triggered()),qApp,SLOT(quit()));
     connect(A_help,SIGNAL(triggered()),this,SLOT(help()));
     connect(A_about_me,SIGNAL(triggered()),this,SLOT(about_me()));
     //connect(A_export,SIGNAL(triggered()),this,SLOT(s_export()));
}
void Fenprincipale::keyPressEvent(QKeyEvent *event)
{
    event->accept();
    switch (event->key()) {
         case Qt::Key_Right:
            next();
            break;
         case Qt::Key_Left:
            previous();
            break;
         case Qt::Key_Space:
            fen_principale->fit_to_window();
            break;

    }

}
void Fenprincipale::manage_bar()
{
    A_open->setShortcut(QKeySequence("Ctrl+O"));
    A_open_folder->setShortcut(QKeySequence("Ctrl+F"));
    A_save_as->setShortcut(QKeySequence("Ctrl+Shift+S"));
    A_print->setShortcut(QKeySequence::Print);
    A_exit->setShortcut(QKeySequence("Ctrl+Q"));
    A_copy->setShortcut(QKeySequence("Ctrl+C"));
    A_paste->setShortcut(QKeySequence("Ctrl+V"));

    A_open_folder->setIcon(QIcon(":/new/prefix1/open_folder.png"));
    A_open->setIcon(QIcon(":/new/prefix1/open_folder.png"));
    A_save_as->setIcon(QIcon(":/new/prefix1/save.png"));
    A_copy->setIcon(QIcon(":/new/prefix1/copy.png"));
    A_paste->setIcon(QIcon(":/new/prefix1/paste.png"));
    A_print->setIcon(QIcon(":/new/prefix1/print.png"));
    A_zoom_in->setIcon(QIcon(":/new/prefix1/zoom_in.png"));
    A_zoom_out->setIcon(QIcon(":/new/prefix1/zoom_out.png"));
    A_help->setIcon(QIcon(":/new/prefix1/help.png"));
    A_about_me->setIcon(QIcon(":/new/prefix1/me.png"));


    A_zoom_in->setShortcut(QKeySequence::ZoomIn);
    A_zoom_out->setShortcut(QKeySequence::ZoomOut);

    QMenu *f_menu = menuBar()->addMenu(tr("Fichier"));
    f_menu->addAction(A_open);
    f_menu->addAction(A_open_folder);
    f_menu->addAction(A_save_as);

    f_menu->addSeparator();
    f_menu->addAction(A_print);
    //f_menu->addAction(A_export);

    f_menu->addSeparator();
    f_menu->addAction(A_exit);


    QMenu *e_menu = menuBar()->addMenu(tr("Editer"));
    e_menu->addAction(A_copy);
    e_menu->addAction(A_paste);


    QMenu *a_menu = menuBar()->addMenu(tr("Affichage"));
    a_menu->addAction(A_zoom_in);
    a_menu->addAction(A_zoom_out);
    a_menu->addAction(A_fit_to_window);

    QMenu *about_menu = menuBar()->addMenu(tr("A propos"));
    about_menu->addAction(A_help);
    //about_menu->addAction(A_about_me);


}
void Fenprincipale::open_file()
{
    QFileDialog f;
    m_filename = f.getOpenFileName(this,tr("Choisisez un fichier"),QString(),
                                   "*.png *.ico *.gif *.jpg *.jpeg *.bmp *.pgm *.pbm *.ppm *.xbm *.xpm");

    if(m_filename.size() >0)
    {
        QString a = m_filename;

        QFileInfo info(a);
        QString sub = info.absolutePath();
        QStringList filters;
        filters.append("*.png");
        filters.append("*.bmp");
        filters.append("*.gif");
        filters.append("*.jpg");
        filters.append("*.jpeg");
        filters.append("*.pgm");
        filters.append("*.pbm");
        filters.append("*.ppm");
        filters.append("*.xbm");
        filters.append("*.xpm");

        if(sub.size() > 0)
        {
            m_filenames = file_manager.folder_file(sub,false,filters);
            compteur = get_element_pos(m_filename,m_filenames);
        }

        show_file();

    }

}
void Fenprincipale::open_file(QString name)
{
    m_filename = name;
    if(m_filename.size() >0)
    {
        QString a = m_filename;

        QFileInfo info(a);
        QString sub = info.absolutePath();
        QStringList filters;
        filters.append("*.png");
        filters.append("*.bmp");
        filters.append("*.gif");
        filters.append("*.jpg");
        filters.append("*.jpeg");
        filters.append("*.pgm");
        filters.append("*.pbm");
        filters.append("*.ppm");
        filters.append("*.xbm");
        filters.append("*.xpm");

        if(sub.size() > 0)
        {
            m_filenames = file_manager.folder_file(sub,false,filters);
            compteur = get_element_pos(m_filename,m_filenames);
        }

        show_file();

    }
}
void Fenprincipale::show_file()
{
    fen_principale->afficher_image(m_filename);
}
void Fenprincipale::open_folder()
{
    QFileDialog f;
    QString sub = f.getExistingDirectory(this,tr("Choisir un dossier"),QString());
    QStringList filters;
    filters.append("*.png");
    filters.append("*.bmp");
    filters.append("*.gif");
    filters.append("*.jpg");
    filters.append("*.jpeg");
    filters.append("*.pgm");
    filters.append("*.pbm");
    filters.append("*.ppm");
    filters.append("*.xbm");
    filters.append("*.xpm");

    if(sub.size() > 0)
    {
        m_filenames = file_manager.folder_file(sub,false,filters);
    }
    if(m_filenames.size() > 0)
    {
        fen_principale->afficher_image(m_filenames.at(0));
    }
}
void Fenprincipale::next()
{
    //std::cout << "Hello -";
    if (m_filenames.size() > 0)
    {
        if(compteur < m_filenames.size()-1)
        {
            compteur += 1;
            fen_principale->afficher_image(m_filenames.at(compteur));
        }
    }

}
void Fenprincipale::previous()
{
    //std::cout << "Hello +";
    if (m_filenames.size() > 0)
    {
        if(compteur > 0)
        {
            compteur -= 1;
            fen_principale->afficher_image(m_filenames.at(compteur));
        }
    }
}
int Fenprincipale::get_element_pos(QString element,QStringList list)
{
    for(int i = 0; i < list.size(); i++)
    {
        if(element == list.at(i))
        {
            return i;
            break;
        }
    }

}
void Fenprincipale::s_export()
{
    //export_fen->set_image(fen_principale->get_image());
    //export_fen->show();
}
void Fenprincipale::help()
{
    QFont font;
    font.setFamily("Constantia");
    font.setPointSize(15);
    help_label.setFont(font);
    QString addresse = "http//Glodi-Technologies.com/Logiciels/Light";

    help_label.setOpenExternalLinks(true);


    help_label.setText(
                       "<a href =" +addresse+ "> Pour apprendre à utiliser le logiciel"+ "</a>");
    help_label.show();


}
void Fenprincipale::about_me()
{

    QPixmap pixmap(600,600);
    pixmap.fill(Qt::white);
    QPainter painter;
    painter.begin(&pixmap);
    QFont font("Consolas");
    QPen pen(QColor(0,0,0));
    font.setPixelSize(15);
    painter.setFont(font);
    painter.drawText(QRect(0,0,300,300),1,"Je m'appele AGBALENYO Komi Barthélémy Elvis. Je suis étudiant."
                                            " J'aime la programmation et les mathématiques. "
                                            "J'ai donc décidé de faire bénéficier mon expérience aux autres en"
                                            " créant le logiciel Light. "
                                            "Pour me contacter ecrivez à l'addresse gmail suivant . Vous pouvez y envoyer vos suggestions,"
                                            " me montrer de potentiels bugs ou pour tout autre chose que vous voulez me dire.");

    painter.end();
    w.setPixmap(pixmap);
    w.show();


}
