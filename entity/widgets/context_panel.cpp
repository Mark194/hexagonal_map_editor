#include "context_panel.hpp"

#include <QPropertyAnimation>
#include <QPushButton>
#include <QVBoxLayout>

ContextPanel::ContextPanel(
    QWidget *parent)
    : QWidget{parent, Qt::Popup}
{
    setWindowFlags(Qt::Popup |
                   Qt::FramelessWindowHint);

    setAttribute(Qt::WA_ShowWithoutActivating);


    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(5);

    // Добавляем элементы управления как в Photoshop
    QStringList styles = {"Normal", "Multiply", "Screen", "Overlay", "Darken"};
    for (const QString& style : styles) {
        QPushButton* btn = new QPushButton(style, this);
        btn->setCheckable(true);
        layout->addWidget(btn);
    }

    setOpacity(0.0);
    resize(200, 180);
}

qreal ContextPanel::opacity() const
{
    return m_opacity;
}

void ContextPanel::setOpacity(qreal opacity)
{
    m_opacity = opacity;

    setWindowOpacity( opacity );
}

void ContextPanel::showNearWidget(QWidget * widget)
{
    if (!widget) return;

    // Позиционируем панель рядом с виджетом
    QPoint globalPos = widget->mapToGlobal(QPoint(0, 0));
    move(globalPos.x() + widget->width() + 5, globalPos.y());

    // Анимация появления
    QPropertyAnimation* anim = new QPropertyAnimation(this, "opacity");
    anim->setDuration(150);
    anim->setStartValue(0.0);
    anim->setEndValue(0.95);
    anim->start(QAbstractAnimation::DeleteWhenStopped);

    QWidget::show();
}
