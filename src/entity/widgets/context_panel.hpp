#pragma once


#include <QWidget>


class ContextPanel : public QWidget
{
    Q_OBJECT                                                  //
    Q_PROPERTY( qreal opacity READ opacity WRITE setOpacity ) //
public:
    explicit ContextPanel(QWidget * parent = nullptr);

    [[nodiscard]] qreal opacity() const;

    void setOpacity(qreal newOpacity);

    void showNearWidget(QWidget * widget);

    void addWidget(QWidget * widget) const;

    void clearContent();

public slots:
    void changeOpacity(bool isChecked);

private:
    qreal m_opacity = 1.0;
};
