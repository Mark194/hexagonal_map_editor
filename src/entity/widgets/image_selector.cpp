//
// Created by Женя on 25.06.2025.
//

#include "image_selector.hpp"

#include <QFileDialog>
#include <QVBoxLayout>
#include <QMouseEvent>


ImageSelector::ImageSelector(QWidget * parent)
    : QFrame( parent )
{
    setFixedSize( 35,
                  35 );

    m_svgWidget = new QSvgWidget( this );

    auto layout = new QVBoxLayout();
    layout->addWidget( m_svgWidget );
    layout->setContentsMargins( 0,
                                0,
                                0,
                                0 );

    setLayout( layout );
}

void ImageSelector::setImage(const QString & image)
{
    m_image = image;

    m_svgWidget->load( image );
}

QString ImageSelector::image() const
{
    return m_image;
}

void ImageSelector::mousePressEvent(QMouseEvent * event)
{
    if ( event->button() == Qt::LeftButton )
    {
        const QString path = QFileDialog::getOpenFileName( this,
                                                           tr( "Select SVG File" ),
                                                           QDir::homePath(),
                                                           tr( "SVG Files (*.svg)" ) );
        if ( not path.isEmpty() )
        {
            setImage( path );
        }
    }
    QFrame::mousePressEvent( event );
}
