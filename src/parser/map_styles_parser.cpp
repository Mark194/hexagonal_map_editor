#include "map_styles_parser.hpp"


#include <QApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
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

    const auto doc = QJsonDocument::fromJson( content,
                                              &parser );

    if ( parser.error != QJsonParseError::NoError )

        throw std::logic_error( parser.errorString().toStdString() );


    QJsonArray array = doc.array();

    StylesDict dict;

    const QFileInfo fileInfo( fileName );

    const auto fileDir = fileInfo.absoluteDir().absolutePath();

    for ( const auto & value : array )
    {
        auto jsonStyle = value.toObject();

        MapStyle styleMap{
            jsonStyle.value( "color" ).toString(),
            fileDir + "/" + jsonStyle.value( "image" ).toString()
        };

        dict.insert( jsonStyle.value( "name" ).toString(),
                     styleMap );
    }

    return dict;
}

void MapStylesParser::save(const QString & fileName, const StylesDict & stylesDict)
{
    QJsonObject rootObject;

    QString appDir = QApplication::applicationDirPath();

    for ( auto it = stylesDict.constKeyValueBegin(); it != stylesDict.constKeyValueEnd(); ++it )
    {
        const auto [ name, style ] = *it;

        QJsonObject styleObject;
        if ( not style.color.isEmpty() )

            styleObject[ "color" ] = style.color;

        if ( not style.image.isEmpty() )

            styleObject[ "image" ] = QDir( appDir ).relativeFilePath( style.image );


        rootObject[ name ] = styleObject;
    }

    QJsonDocument doc( rootObject );
    QFile file( fileName );
    if ( not file.open( QIODevice::WriteOnly ) )
    {
        qWarning( "Couldn't open file for writing" );
        return;
    }

    file.write( doc.toJson() );
    file.close();
}
