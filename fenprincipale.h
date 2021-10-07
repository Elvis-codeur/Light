#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QMainWindow>
#include <QAction>
#include <QPushButton>
#include <QTextDocument>
#include <QTextEdit>
#include "exportclass.h"
#include "fen.h"
#include "filemanager.h"

class Fenprincipale : public QMainWindow
{
    Q_OBJECT
public:
    explicit Fenprincipale(QWidget *parent = nullptr);
    void manage_bar();
    void keyPressEvent(QKeyEvent *event);
    int get_element_pos(QString element,QStringList list);

public slots:
    void open_file();
    void open_file(QString name);
    void open_folder();
    void show_file();
    void next();
    void previous();
    void s_export();
    void help();
    void about_me();


signals:

private:

    QAction *A_open = new QAction("Ouvrir un fichier ");
    QAction *A_open_folder = new QAction("Ouvrir un dossier");
    QAction *A_print = new QAction("Imprimer");
    QAction *A_save_as = new QAction("Enrégistrer comme ");
    QAction *A_exit = new QAction("Quitter  ");
    QAction *A_export = new QAction("Exporter ");

    QAction *A_copy = new QAction("Copier");
    QAction *A_paste = new QAction("Coller");
    QAction *A_next = new QAction("Suivant");
    QAction *A_previous = new QAction("Précédent");

    QAction *A_zoom_in = new QAction("Zoomer");
    QAction *A_zoom_out = new QAction("Dézoomer");
    QAction *A_fit_to_window = new QAction("Ajuster à la taille de l'écran");
    QAction *A_normal_size = new QAction("Taille normale");

    QAction *A_help = new QAction("Aide");
    QAction *A_about_me = new QAction("Au sujet du développeur");

    Fen *fen_principale = new Fen();
    //ExportClass *export_fen = new ExportClass();
    QString m_filename;
    QStringList m_filenames;
    FileManager file_manager;
    int compteur = 0;

    QPushButton *button_next = new QPushButton();
    QPushButton *button_previous = new QPushButton();

    // Help
    QLabel help_label;


    // About me
    QLabel w;


};

#endif // FENPRINCIPALE_H
