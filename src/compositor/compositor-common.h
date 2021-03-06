/*
 * This file is part of budgie-rd
 *
 * Copyright © 2017-2018 Budgie Desktop Developers
 *
 * budgie-rd is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */

#pragma once

#include <QObject>

namespace Budgie::Compositor
{
    Q_NAMESPACE

    /**
     * Each surface is allocated a basic rendering layer, which simply determines
     * the baseline z-index for rendering. This is further refined within each
     * layer by list ordering.
     */
    enum RenderLayer {
        BACKGROUND = 0, /* Wallpaper */
        DESKTOP,        /* Desktop icons */
        APPLICATION,    /* Application windows */
        PANEL,          /* Budgie Panel */
        SIDEBAR,        /* Raven */
        FULLSCREEN,     /* Fullscreen window */
        NOTIFICATION,   /* OSD/Notification */
        DND,            /* Drag & Drop */
    };

    Q_ENUM_NS(RenderLayer)

    /**
     * Helper to define the base rendering layer
     */
    static const RenderLayer MinLayer = RenderLayer::BACKGROUND;

    /**
     * Helper to define the top rendering layer
     */
    static const RenderLayer MaxLayer = RenderLayer::DND;
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
