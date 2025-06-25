#include "style_dialog.hpp"

#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>


#include "../entity/widgets/color_selector.hpp"
#include "../entity/widgets/image_selector.hpp"


StyleDialog::StyleDialog(QWidget * parent)
    : QDialog( parent )
{
    setupUI();
}

void StyleDialog::loadStyle(const QString & name, const QString & color, const QString & image)
{
    m_styleNameEditor->setText( name );

    m_colorSelector->setSelectedColor( color );

    m_imageSelector->setImage( image );
}

QString StyleDialog::styleName() const { return m_styleNameEditor->text(); }

QString StyleDialog::colorName() const { return m_colorSelector->selectedColor().name(); }

QString StyleDialog::image() const { return m_imageSelector->image(); }

void StyleDialog::setupUI()
{
    auto * layout = new QFormLayout( this );

    layout->setLabelAlignment( Qt::AlignRight | Qt::AlignVCenter );

    setLayout( layout );


    m_styleNameEditor = new QLineEdit( this );

    layout->addRow( "Название:",
                    m_styleNameEditor );


    m_colorSelector = new ColorSelector( this );

    layout->addRow( "Цвет:",
                    m_colorSelector );


    m_imageSelector = new ImageSelector( this );

    layout->addRow( "Иконка:",
                    m_imageSelector );

    auto buttonBox = new QDialogButtonBox( QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                           this );

    buttonBox->setCenterButtons( true );

    connect( buttonBox,
             &QDialogButtonBox::accepted,
             this,
             &QDialog::accept );

    connect( buttonBox,
             &QDialogButtonBox::rejected,
             this,
             &QDialog::reject );

    layout->addRow( buttonBox );

    buttonBox->button( QDialogButtonBox::Ok )->setText( "Подтвердить" );
    buttonBox->button( QDialogButtonBox::Cancel )->setText( "Отменить" );
}
