#include "map_buildings_parser.hpp"

#include <QApplication>
#include <QColor>
#include <QDir>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>

BuildingsDict MapBuildingsParser::load(const QString & fileName)
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

    BuildingsDict dict;

    const QFileInfo fileInfo( fileName );

    const auto fileDir = fileInfo.absoluteDir().absolutePath();

    for ( const auto & value : array )
    {
        auto jsonStyle = value.toObject();

        BuildingStyle building{
            jsonStyle.value( "color" ).toString(),
            fileDir + "/" + jsonStyle.value( "image" ).toString()
        };

        dict.insert( jsonStyle.value( "name" ).toString(),
                     building );
    }

    return dict;
}

void MapBuildingsParser::save(const QString & fileName, const BuildingsDict & buildings)
{
    QJsonObject rootObject;

    QString appDir = QApplication::applicationDirPath();

    for ( auto it = buildings.constKeyValueBegin(); it != buildings.constKeyValueEnd(); ++it )
    {
        const auto [ name, style ] = *it;

        QJsonObject styleObject;
        if ( not style.color.isEmpty() )

            styleObject[ "color" ] = style.color;
        else
            styleObject[ "color" ] = Qt::transparent;

        if ( not style.imagePath.isEmpty() )

            styleObject[ "image" ] = QDir( appDir ).relativeFilePath( style.imagePath );


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
