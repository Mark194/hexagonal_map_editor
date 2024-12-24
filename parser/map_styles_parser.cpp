#include "map_styles_parser.hpp"


#include <QApplication>
#include <QFile>
#include <QJsonObject>
#include <QJsonParseError>


MapStylesParser::MapStylesParser() {}

StylesDict MapStylesParser::load(QString fileName)
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

    StylesDict dict;

    for ( auto it = obj.begin(); it != obj.end(); it++ )
    {
        auto jsonStyle = it.value().toObject();

        MapStyle styleMap{ jsonStyle.value( "color" ).toString(),
                           jsonStyle.value( "image" ).toString()  };

        if ( styleMap.image[0] == '.' ) styleMap.image.replace( 0, 1, qApp->applicationDirPath() );

        dict.insert( it.key(), styleMap );
    }


    return dict;
}
