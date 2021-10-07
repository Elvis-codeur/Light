#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QDirIterator>
#include <QStringList>

class FileManager : public QObject
{
public:
    FileManager();
    QStringList folder_file(QString name,bool sub_directories,QStringList filters);

private:

};

#endif // FILEMANAGER_H
