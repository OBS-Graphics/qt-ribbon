/*
 * Copyright (C) 2020 Adrian Carpenter
 *
 * This file is part of the Nedrysoft Ribbon Bar. (https://github.com/nedrysoft/qt-ribbon)
 *
 * A cross-platform ribbon bar for Qt applications.
 *
 * Created by Adrian Carpenter on 02/12/2020.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <QGuiApplication>
#include <QPalette>

#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
#include <QStyleHints>
#endif

namespace Nedrysoft::Ribbon {

    inline bool isDarkMode() {
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
        return QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark;
#else
        const auto bg = QGuiApplication::palette().color(QPalette::Window);
        const auto fg = QGuiApplication::palette().color(QPalette::WindowText);
        return fg.lightness() > bg.lightness();
#endif
    }

    template<typename Receiver, typename Slot>
    inline void connectThemeChange(Receiver *receiver, Slot &&slot) {
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
        QObject::connect(
            QGuiApplication::styleHints(), &QStyleHints::colorSchemeChanged,
            receiver, [slot](Qt::ColorScheme scheme) {
                slot(scheme == Qt::ColorScheme::Dark);
            }
        );
#else
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
        QObject::connect(
            qGuiApp, &QGuiApplication::paletteChanged,
            receiver, [slot](const QPalette &) {
                slot(isDarkMode());
            }
        );
QT_WARNING_POP
#endif
    }

} // namespace Nedrysoft::Ribbon
