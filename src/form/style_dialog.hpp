#pragma once


#include <QDialog>

#include "map_size_editor.hpp"


class ImageSelector;
class ColorSelector;

class StyleDialog : public QDialog
{
public:
    explicit StyleDialog(QWidget * parent = nullptr);

    void loadStyle(const QString & name, const QString & color = QString(), const QString & image = QString());

    [[nodiscard]] QString styleName() const;

    [[nodiscard]] QString colorName() const;

    [[nodiscard]] QString image() const;

private:
    QLineEdit * m_styleNameEditor;

    ColorSelector * m_colorSelector;

    ImageSelector * m_imageSelector;

    void setupUI();
};
