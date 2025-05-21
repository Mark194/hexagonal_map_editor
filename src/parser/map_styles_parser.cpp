#include "map_styles_parser.hpp"


#include <QApplication>
#include <qdir.h>
#include <QFile>
#include <qfileinfo.h>
#include <qjsonarray.h>
#include <QJsonObject>
#include <QJsonParseError>


MapStylesParser::MapStylesParser() = default;

StylesDict MapStylesParser::load(const QString & fileName)
{
    QFile file( fileName );

    if ( not file.open( QFile::ReadOnly | QFile::Text ) )

        throw std::logic_error( file.errorString().toStdString() );

    const QByteArray content = file.readAll();

    file.close();


    QJsonParseError parser{};

    const auto doc = QJsonDocument::fromJson( content, &parser );

    if ( parser.error != QJsonParseError::NoError )

        throw std::logic_error( parser.errorString().toStdString() );


    QJsonArray array = doc.array();

    StylesDict dict;

    QFileInfo fileInfo( fileName );

    auto fileDir = fileInfo.absoluteDir().absolutePath();

    for ( const auto & value : array )
    {
        auto jsonStyle = value.toObject();

        MapStyle styleMap{
            jsonStyle.value( "color" ).toString(),
            fileDir + "/" + jsonStyle.value( "image" ).toString()
        };

        dict.insert( jsonStyle.value( "name" ).toString(), styleMap );
    }


    // for ( auto it = obj.begin(); it != obj.end(); ++it )
    // {
    //     auto jsonStyle = it.value().toObject();
    //
    //     MapStyle styleMap{ jsonStyle.value( "color" ).toString(),
    //                        jsonStyle.value( "image" ).toString()  };
    //
    //     if ( styleMap.image[0] == '.' ) styleMap.image.replace( 0, 1, qApp->applicationDirPath() );
    //
    //     dict.insert( it.key(), styleMap );
    // }


    return dict;
}
