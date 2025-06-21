//
// Created by Женя on 13.06.2025.
//

#pragma once


enum class ActionType
{
    NoAction,
    ChangeColor,
    ChangeStyle,
    ClearStyle,
    GrabColor,
    FillColor,
};

Q_DECLARE_METATYPE( ActionType )
