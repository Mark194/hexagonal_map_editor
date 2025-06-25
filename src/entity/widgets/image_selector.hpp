//
// Created by Женя on 25.06.2025.
//

#pragma once


#include <QFrame>
#include <QSvgWidget>


class ImageSelector : public QFrame
{
    Q_OBJECT //

public:
    explicit ImageSelector(QWidget * parent = nullptr);

    void setImage(const QString & image);

    QString image() const;

protected:
    void mousePressEvent(QMouseEvent * event) override;

private:
    QString m_image;

    QSvgWidget * m_svgWidget;
};
