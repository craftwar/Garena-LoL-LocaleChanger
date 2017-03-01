#include <QtCore/QCoreApplication>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QProcess>

#ifdef WIN32
#define _UNICODE
#include <qt_windows.h>
#endif

bool PatchLocale(QString BasePath);
bool PatchFont(QString BasePath);
bool PatchChat(QString BasePath);



int main(int argc, char *argv[])
{
    QString BasePath;

    QCoreApplication a(argc, argv);



    // patch Local file
    if ( argc >=2)
        BasePath = argv[1];
    else
        BasePath = QCoreApplication::applicationDirPath();


    if ( argc >=3 && QString::compare(argv[2], "/no-locale")!=0 )
        PatchLocale(BasePath);
    PatchFont(BasePath);
    PatchChat(BasePath);

//    return a.exec();
    return 0;
}
bool PatchLocale(QString BasePath) {
    QString LocalePath = "/GameData/Apps/LoLTW/Game/DATA/CFG/Locale.cfg";
    QFile FileEnUS;
    DWORD dwAttrs;

    FileEnUS.setFileName(BasePath + LocalePath);
    FileEnUS.open(QIODevice::WriteOnly);
    FileEnUS.write("[General]\n");
    FileEnUS.write("LanguageLocaleRegion=en_US\n");
    FileEnUS.close();
//        setPermissions can't set read-only in M$
//        QFileDevice::Permissions perm = FileEnUS.permissions();
//        perm &= ~QFileDevice::WriteUser;
//        bool result = FileEnUS.setPermissions(perm);

    //set read-only
    //convert '/' to '\\' and add trailing '\0'
    QString msPath = FileEnUS.fileName().replace('/', '\\');
    wchar_t * wpath = new wchar_t[msPath.length()+1];
    msPath.toWCharArray(wpath);
    wpath[msPath.length()] ='\0';

    dwAttrs = GetFileAttributes(wpath);
    SetFileAttributes(wpath, dwAttrs | FILE_ATTRIBUTE_READONLY);
    delete[] wpath;

    return true;
}
bool PatchFont(QString BasePath) {
    QString FontconfigPath = "/GameData/Apps/LoLTW/Game/DATA/Menu/fontconfig_en_US.txt";
    QString FontconfigZhTWPath = "/GameData/Apps/LoLTW/Game/DATA/Menu/fontconfig_zh_TW.txt";
    QString GamePermanentPath = "/GameData/Apps/LoLTW/Game/DATA/CFG/defaults/GamePermanent.cfg";
    QString GamePermanentZhTWPath = "/GameData/Apps/LoLTW/Game/DATA/CFG/defaults/GamePermanent_zh_TW.cfg";
    QFile FileEnUS, FileZhTW, FileBackup;
    QFileInfo FileInfo;
    QTextStream TextStreamReaderZhTW, TextStreamWriterEnUS, TextStreamReaderBackup;
    QString ModifiedTime;


    // patch Fontconfig file
    FileEnUS.setFileName(BasePath + FontconfigPath);
    FileEnUS.open(QIODevice::ReadWrite | QIODevice::Text);
    // make backup
    FileInfo.setFile(FileEnUS);
    ModifiedTime = FileInfo.lastModified().toString("yyyy M d hh_mm");
    QString backupFile = FileInfo.absolutePath() + "/" + FileInfo.baseName() + " " + ModifiedTime + "." + FileInfo.suffix();
    FileEnUS.copy(backupFile);

    FileBackup.setFileName(backupFile);
    FileBackup.open(QIODevice::ReadOnly);
    TextStreamReaderBackup.setDevice(&FileBackup);

    TextStreamWriterEnUS.setDevice(&FileEnUS);
    FileZhTW.setFileName(BasePath + FontconfigZhTWPath);
    FileZhTW.open(QIODevice::ReadOnly);
    TextStreamReaderZhTW.setDevice(&FileZhTW);
    TextStreamReaderZhTW.setCodec("UTF-8");

    //get tw first 6 lines and backup(en) remaining lines
    for(int i=1; i<=6; ++i) {
        TextStreamWriterEnUS << TextStreamReaderZhTW.readLine() <<"\n";
        TextStreamReaderBackup.readLine();
    }
    while (!TextStreamReaderBackup.atEnd())
        TextStreamWriterEnUS << TextStreamReaderBackup.readLine() <<"\n";
    FileEnUS.close();

    // overwrite GamePermanent.cfg with GamePermanent_zh_TW.cfg
    FileEnUS.setFileName(BasePath + GamePermanentPath);
    FileEnUS.open(QIODevice::ReadWrite | QIODevice::Text);
    // make backup
    FileInfo.setFile(FileEnUS);
//    ModifiedTime = FileInfo.lastModified().toString("yyyy M d");
    ModifiedTime = FileInfo.lastModified().toString("yyyy M d hh_mm");
    backupFile = FileInfo.absolutePath() + "/" + FileInfo.baseName() + " " + ModifiedTime + "." + FileInfo.suffix();
    FileEnUS.copy(backupFile);
    FileEnUS.remove();
    QFile::copy(BasePath + GamePermanentZhTWPath, BasePath + GamePermanentPath);

    return true;
}

bool PatchChat(QString BasePath) {
    QString ClientZipsPath = "/GameData/Apps/LoLTW/Game/ClientZips.txt";
    const QString patchFileName = "Chat.zip";
    QFile FileClientZips;
    QTextStream TextStreamReader;
    bool patched = false;

    FileClientZips.setFileName(BasePath + ClientZipsPath);
    FileClientZips.open(QIODevice::ReadWrite | QIODevice::Text);
    TextStreamReader.setDevice(&FileClientZips);
    TextStreamReader.setCodec("UTF-8");

    while (!TextStreamReader.atEnd()) {
        QString lineData = TextStreamReader.readLine();
        if (lineData.compare("Chat.zip")==0)
            patched = true;
    }
    if (!patched)
        TextStreamReader <<'\n' << patchFileName <<'\n';
    FileClientZips.close();

    //    7za a -spf -tzip Chat.zip DATA\Menu\fontconfig_en_US.txt
    QProcess createZip;
    // create zip
    createZip.startDetached("7za.exe", {"a", "-spf", "-tzip", "Chat.zip", "DATA\\Menu\\fontconfig_en_US.txt"}, BasePath + "/GameData/Apps/LoLTW/Game");
    //    createZip.setProcessChannelMode(QProcess::ForwardedChannels);
    //    createZip.setWorkingDirectory(BasePath + "/GameData/Apps/LoLTW/Game");
    //    createZip.setProgram("7za.exe");
    //    QStringList args = {"a", "-spf", "-tzip", "Chat.zip", "DATA\\Menu\\fontconfig_en_US.txt"};
    //    createZip.setArguments( args );
    //    createZip.setArguments( {"a", "-spf", "-tzip", "Chat.zip", "DATA\\Menu\\fontconfig_en_US.txt"} );
    //    createZip.start();
    return true;
}
