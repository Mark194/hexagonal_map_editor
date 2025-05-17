#include "menu_sub_form.hpp"

MenuSubForm::MenuSubForm()
{
    createFileMenu();

    createStyleMenu();
}

void MenuSubForm::createFileMenu()
{
    QMenu * fileMenu = addMenu( "Файл" );

    m_createMap = fileMenu->addAction( "Создать" );

    fileMenu->addSeparator();

    fileMenu->addAction( "Открыть" );

    fileMenu->addSeparator();

    fileMenu->addAction( "Сохранить" );

    m_saveMap = fileMenu->addAction( "Сохранить как..." );

    fileMenu->addSeparator();

    fileMenu->addAction( "Выход" );
}

void MenuSubForm::createStyleMenu()
{
    QMenu * styleMenu = addMenu( "Стили" );

    styleMenu->addAction( "Создать" );

    styleMenu->addAction( "Добавить" );

    styleMenu->addAction( "Изменить" );

    styleMenu->addAction( "Сохранить" );
}
