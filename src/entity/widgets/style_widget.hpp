#pragma once


#include <QWidget>


class StyleWidget : public QWidget
{
public:
    explicit StyleWidget
    (const QString & styleName, const QColor & color, const QString & imagePath = "", QWidget * parent = nullptr);

protected:
    void paintEvent(QPaintEvent * event) override;


    bool event(QEvent * event) override;

private:
    QString m_styleName;

    QColor m_color;

    QWidget * loadIcon(const QString & imagePath);
};
