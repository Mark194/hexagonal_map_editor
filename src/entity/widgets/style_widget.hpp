#pragma once


#include <QWidget>


class StyleWidget : public QWidget
{
    Q_OBJECT //

public:
    explicit StyleWidget
    (const QString & styleName, const QColor & color, const QString & imagePath = "", QWidget * parent = nullptr);

    [[nodiscard]] bool isSelected() const;

    void setSelected(bool selected);

signals:
    void clicked();

protected:
    void paintEvent(QPaintEvent * event) override;

    void mousePressEvent(QMouseEvent * event) override;

    bool event(QEvent * event) override;

private:
    bool m_isSelected;

    QString m_styleName;

    QColor m_color;

    QWidget * loadIcon(const QString & imagePath);
};
