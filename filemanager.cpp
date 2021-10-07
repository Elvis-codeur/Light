#include "filemanager.h"

FileManager::FileManager()
{

}
QStringList FileManager::folder_file(QString name, bool sub,QStringList filters)
{
    QStringList result;
    if(sub == false)
    {
        QDirIterator iter(name,filters,QDir::Files,QDirIterator::NoIteratorFlags);
        while(iter.hasNext())
        {
            result.append(iter.next());
        }
    }
    else
    {
        QDirIterator iter(name,filters,QDir::Files,QDirIterator::Subdirectories);
        while(iter.hasNext())
        {
            result.append(iter.next());
        }
    }

    return result;

}
