#include "map_parser.hpp"


#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>


MapParser::MapParser() {}

void MapParser::load(QString fileName)
{
    QFile file( fileName );

    if ( not file.open( QFile::ReadOnly | QFile::Text ) )

        throw std::logic_error( file.errorString().toStdString() );

    QByteArray content = file.readAll();

    file.close();


    QJsonParseError parser;

    auto doc = QJsonDocument::fromJson( content, &parser );

    if ( parser.error != QJsonParseError::NoError )

        throw std::logic_error( parser.errorString().toStdString() );


    QJsonObject obj = doc.object();

    for ( auto it = obj.begin(); it != obj.end(); it++ )
    {
        qDebug() << *it;
    }
}
