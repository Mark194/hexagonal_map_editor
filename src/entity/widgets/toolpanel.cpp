#include "toolpanel.hpp"
#include <QStyle>
#include <QFontMetrics>

ToolPanel::ToolPanel(QWidget * parent, bool initiallyCollapsed)
    : QWidget( parent )
  , m_isCollapsed( initiallyCollapsed )
  , m_iconSize( 30, 30 )
  , m_spacing( 4 )
  , m_expandedWidth( 100 )
{
    setObjectName( "toolPanel" );

    setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Preferred );

    // Main vertical layout
    m_mainLayout = new QVBoxLayout( this );
    m_mainLayout->setContentsMargins( 2, 2, 2, 2 );
    m_mainLayout->setSpacing( m_spacing );

    // Collapse button (topmost)
    m_collapseButton = new QToolButton( this );
    m_collapseButton->setObjectName( "collapseButton" );
    m_collapseButton->setAutoRaise( true );
    m_collapseButton->setIconSize( QSize( 16, 16 ) );
    m_collapseButton->setToolButtonStyle( Qt::ToolButtonIconOnly );
    m_collapseButton->setStyleSheet( "QToolButton { border: none; }" );
    connect( m_collapseButton, &QToolButton::clicked, this, &ToolPanel::toggleCollapsed );
    m_mainLayout->addWidget( m_collapseButton, 0, Qt::AlignHCenter );

    // Add stretch to push tools up when panel is small
    m_mainLayout->addStretch( 1 );

    setLayout( m_mainLayout );
    updateCollapseButton();
    updateGeometry();
}

QToolButton * ToolPanel::addButton(const QIcon & icon, const QString & text)
{
    QToolButton * button = new QToolButton( this );
    button->setIcon( icon );
    button->setToolTip( text );
    button->setIconSize( m_iconSize );
    button->setAutoRaise( true );
    button->setStyleSheet( "QToolButton { border: none; text-align: left; }" );

    if ( not m_isCollapsed and not text.isEmpty() )
    {
        button->setText( text );
        button->setToolButtonStyle( Qt::ToolButtonTextBesideIcon );
    }
    else
    {
        button->setToolButtonStyle( Qt::ToolButtonIconOnly );
    }

    m_mainLayout->insertWidget( m_mainLayout->count() - 1, button );
    m_toolWidgets.append( button );

    // Update expanded width if needed
    if ( not m_isCollapsed )
    {
        QFontMetrics fm( button->font() );
        int textWidth = fm.horizontalAdvance( text );
        int buttonWidth = m_iconSize.width() + textWidth + 5;
        m_expandedWidth = qMax( m_expandedWidth, buttonWidth );
        updateGeometry();
    }

    return button;
}

QToolButton * ToolPanel::addButtonWithText(const QIcon & icon, const QString & text)
{
    QToolButton * button = addButton( icon, text );

    if ( not m_isCollapsed )

        button->setToolButtonStyle( Qt::ToolButtonTextBesideIcon );

    return button;
}

void ToolPanel::addSeparator()
{
    QFrame * separator = new QFrame( this );
    separator->setFrameShape( QFrame::HLine );
    separator->setFrameShadow( QFrame::Sunken );
    separator->setFixedHeight( 12 );
    separator->setStyleSheet( "color: palette(mid);" );

    m_mainLayout->insertWidget( m_mainLayout->count() - 1, separator );
    m_toolWidgets.append( separator );
}

void ToolPanel::addWidget(QWidget * widget)
{
    m_mainLayout->insertWidget( m_mainLayout->count() - 1, widget );
}

void ToolPanel::toggleCollapsed()
{
    setCollapsed( not m_isCollapsed );
}

bool ToolPanel::isCollapsed() const
{
    return m_isCollapsed;
}

QSize ToolPanel::sizeHint() const
{
    int width = m_isCollapsed ? m_iconSize.width() + 5 : m_expandedWidth;
    int height = QWidget::sizeHint().height();
    return QSize( width, height );
}

void ToolPanel::setSpacing(int spacing)
{
    m_spacing = spacing;
    m_mainLayout->setSpacing( spacing );
}

void ToolPanel::setIconSize(const QSize & size)
{
    m_iconSize = size;
    for ( QWidget * widget : m_toolWidgets )

        if ( QToolButton * button = qobject_cast<QToolButton *>( widget ) )

            button->setIconSize( m_iconSize );


    if ( not m_isCollapsed )
    {
        m_expandedWidth = calculateExpandedWidth();
        updateGeometry();
    }
}

void ToolPanel::collapse()
{
    setCollapsed( true );
}

void ToolPanel::extend()
{
    setCollapsed( false );
}

void ToolPanel::updateButtonsVisibility()
{
    for ( QWidget * widget : m_toolWidgets )
    {
        if ( QToolButton * button = qobject_cast<QToolButton *>( widget ) )
        {
            if ( m_isCollapsed )
            {
                button->setToolButtonStyle( Qt::ToolButtonIconOnly );

                continue;
            }

            if ( button->text().isEmpty() )
                button->setToolButtonStyle( Qt::ToolButtonIconOnly );
            else
                button->setToolButtonStyle( Qt::ToolButtonTextBesideIcon );
        }
    }
}

void ToolPanel::updateCollapseButton()
{
    if ( m_isCollapsed )
    {
        m_collapseButton->setIcon( style()->standardIcon( QStyle::SP_ArrowRight ) );

        m_collapseButton->setToolTip( "Развернуть панель" );
    }
    else
    {
        m_collapseButton->setIcon( style()->standardIcon( QStyle::SP_ArrowLeft ) );

        m_collapseButton->setToolTip( "Свернуть панель" );
    }
}

void ToolPanel::setCollapsed(bool isCollapsed)
{
    if ( m_isCollapsed == isCollapsed )
        return;

    m_isCollapsed = isCollapsed;

    if ( m_isCollapsed )
        // Calculate required width when expanding
        m_expandedWidth = calculateExpandedWidth();


    updateButtonsVisibility();
    updateCollapseButton();
    updateGeometry();
    emit collapsedStateChanged( m_isCollapsed );
}

int ToolPanel::calculateExpandedWidth() const
{
    int maxWidth = 0;

    QFontMetrics fm( font() );

    for ( QWidget * widget : m_toolWidgets )
    {
        if ( QToolButton * button = qobject_cast<QToolButton *>( widget ) )
        {
            if ( !button->text().isEmpty() )
                continue;

            int textWidth = fm.horizontalAdvance( button->text() );

            int buttonWidth = m_iconSize.width() + textWidth + 5;

            maxWidth = qMax( maxWidth, buttonWidth );
        }
    }

    return qMax( maxWidth, 100 ); // Minimum width 100px
}
