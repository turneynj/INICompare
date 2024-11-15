#include <QCoreApplication> // parse cmdline args
#include <QFileInfo>        // test existance of and open files
#include <QSettings>        // parse INI

/// @brief Compares two INI files and outputs differences
/// @arg two file paths
/// @return int 0 on success, qFatal on error
int main(int argc, char *argv[])
{
    // Two file paths as args
    QCoreApplication app(argc, argv);
    auto args = app.arguments();
    if( args.size() < 3 )
        qFatal() << "Not enough args, expect 2 args: <file1> <file2>\nProvided: " << args;
    auto file1 = args.at(1);
    auto file2 = args.at(2);

    // If either file does not exist return error
    if( !( QFileInfo::exists( file1 ) && QFileInfo::exists( file2 ) ) )
        qFatal() << "File not found: " << file1 << file2;

    // QSettings parses INIs for us
    QSettings s1( file1, QSettings::Format::IniFormat ), s2( file2, QSettings::Format::IniFormat );

    // Variables used to store results
    // for printing values in error as needed
    QString v1, v2;

    // Loop through all keys of file1
    for( const QString & key1 : s1.allKeys() )
        // If file2 does not contain file1:key or
        // file1:key does not equal file2:key then output error
        if( ( ! s2.contains( key1 ) ) ||
            ( v2 = s2.value( key1 ).toString() ).compare( v1 = s1.value( key1 ).toString() ) )
            qInfo() << key1 << "\t1: " << v1 << "\t2: " << ( s2.contains( key1 ) ? v2 : "[No value]" );

    // Loop through all keys in file2 to detect keys not present in file1
    for( const QString & key2 : s2.allKeys() )
        if( ! s1.contains( key2 ) )
            qInfo() << "Key only in File 2: " << key2 << s2.value( key2 ).toString();

    // Return success. qFatal() handles error returns
    return 0;
}
