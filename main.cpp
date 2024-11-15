#include <QCoreApplication>
#include <QFileInfo>
#include <QSettings>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if(QCoreApplication::arguments().size() < 3)
        qFatal() << "Not enough args: " << QCoreApplication::arguments();
    auto f1 = QCoreApplication::arguments().at(1);
    auto f2 = QCoreApplication::arguments().at(2);
    if( !( QFileInfo::exists( f1 ) && QFileInfo::exists( f2 ) ) )
        qFatal() << "File not found: " << f1 << f2;
    QSettings s1(f1, QSettings::Format::IniFormat, &a), s2(f2, QSettings::Format::IniFormat, &a);
    QString v1, v2;
    for( const QString & key1 : s1.allKeys() )
        if( ( v2 = s2.value( key1, "" ).toString() ).compare( v1 = s1.value( key1 ).toString() ) )
            qInfo() << "Mismatched values for " << key1 << v1 << v2;

    for( const QString & key2 : s2.allKeys() )
        if( ! s1.contains( key2 ) )
            qInfo() << "Key only in second file: " << key2 << s2.value( key2 ).toString();
    return 0;
}
