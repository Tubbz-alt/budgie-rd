/*
 * This file is part of budgie-rd
 *
 * Copyright © 2017 Budgie Desktop Developers
 *
 * budgie-rd is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */

#pragma once

// Fuckin seriously? Sort out cflags and expose xdg as a .so
#include "../../../xdg/desktop-file.h"

#include <QHash>
#include <QSharedPointer>
#include <QWidget>

namespace Panel
{
    class MenuWindow : public QWidget
    {
        Q_OBJECT

    public:
        explicit MenuWindow();
        void toggleVisibility();

    private:
        // TODO: Create MenuButton -> desktopFile association
        QHash<QString, QSharedPointer<Desktop::DesktopFile>> menuEntries;

        // TODO: Do this based on a list of XDG dirs
        void scanDirectory(const QString &location);
    };
}

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 4
 * tab-width: 4
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=4 tabstop=4 expandtab:
 * :indentSize=4:tabSize=4:noTabs=true:
 */