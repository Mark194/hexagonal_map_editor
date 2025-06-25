#pragma once


#include <QFrame>


class ColorSelector : public QFrame
{
    Q_OBJECT //

public:
    explicit ColorSelector(QWidget * parent = nullptr);

    void setTitle(const QString & title);

    void setSelectedColor(const QColor & color);

    QColor selectedColor();

public slots:
    void selectColor();

    void updateColor();

protected:
    bool eventFilter(QObject * obj, QEvent * event) override;

private:
    QColor m_selectedColor;

    QString m_title;
};
