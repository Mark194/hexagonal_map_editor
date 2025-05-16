#pragma once


#include <QWidget>


class ContextPanel : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:
    explicit ContextPanel(QWidget *parent = nullptr);

    qreal opacity() const;
    void setOpacity(qreal newOpacity);

    void showNearWidget(QWidget * widget);

signals:

private:
    qreal m_opacity = 1.0;
};

