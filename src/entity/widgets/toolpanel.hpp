#pragma once


#include <QToolButton>
#include <QVBoxLayout>


class ToolPanel final : public QWidget
{
    Q_OBJECT //
public:
    explicit ToolPanel(QWidget * parent = nullptr, bool initiallyCollapsed = false);

    QToolButton * addButton(const QIcon & icon, const QString & text = "");

    QToolButton * addButtonWithText(const QIcon & icon, const QString & text);

    void addSeparator();

    void addWidget(QWidget * widget) const;

    [[nodiscard]] bool isCollapsed() const;

    [[nodiscard]] QSize sizeHint() const override;

    void setSpacing(int spacing);

    void setIconSize(const QSize & size);

    void collapse();

    void extend();

signals:
    void collapsedStateChanged(bool isCollapsed);

private slots:
    void toggleCollapsed();

private:
    void updateButtonsVisibility();

    void updateCollapseButton();

    void setCollapsed(bool isCollapsed);

    QVBoxLayout * m_mainLayout;
    QToolButton * m_collapseButton;
    QList<QWidget *> m_toolWidgets;
    bool m_isCollapsed;
    QSize m_iconSize;
    int m_spacing;
    int m_expandedWidth;

    int calculateExpandedWidth() const;
};
