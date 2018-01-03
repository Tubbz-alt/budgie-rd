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

#include "server.h"

using namespace Budgie::Compositor;

void Server::surfaceCreated(QWaylandSurface *surface)
{
    if (m_surfaces.contains(surface)) {
        qWarning() << "Accounting error: Already know about " << surface;
        return;
    }

    auto item = new Compositor::SurfaceItem(surface);
    qDebug() << "Added surface:" << item;

    // TODO: Decide which output we wanna put this guy on and map it there.
    m_surfaces.insert(surface, QSharedPointer<Compositor::SurfaceItem>(item));

    // TODO: Only allocate when we really need this..
    item->setLayer(RenderLayer::APPLICATION);

    // Le Hacky Demos
    auto view = m_displays[0]->mapSurfaceItem(item);
    if (!view) {
        return;
    }
    view->setOutput(m_displays[0]->output());
    view->setPrimary();
}

/**
 * The WaylandSurface is about to be destroyed, so we must remove knowledge
 * of this from ourselves and all displays
 */
void Server::surfaceDestroying(QWaylandSurface *surface)
{
    auto item = m_surfaces.value(surface, nullptr);
    if (!item) {
        qWarning() << "Accounting error: Don't know about " << surface;
        return;
    }

    // Remove item from all displays
    for (auto &display : m_displays) {
        // TODO: If the display contains then unmap
        display->unmapSurfaceItem(item.data());
    }

    qDebug() << "Removed surface:" << item.data();

    // TODO: Cycle focus to the next available candidate instead.
    if (item.data() == m_keyFocus) {
        setKeyFocus(nullptr, nullptr);
    }
    if (item.data() == m_mouseFocus) {
        setMouseFocus(nullptr, nullptr);
    }

    m_surfaces.remove(surface);
}

/**
 * A new wl_shell window has been constructed.
 * At this point we will associate it with a WaylandWindow and make it
 * a candidate for rendering.
 */
void Server::wlShellCreated(QWaylandWlShellSurface *shell)
{
    auto surface = m_surfaces.value(shell->surface(), nullptr);
    if (!surface) {
        qWarning() << "Shell surface for unknown client. Recommend you kill!";
        return;
    }
    promoteWindow(WaylandWindow::create(surface.data(), shell));
}

/**
 * New xdg surface has been constructed, do the same thing as we'd do
 * for a normal wl_shell window.
 */
void Server::xdgShellv5Created(QWaylandXdgSurfaceV5 *shell)
{
    auto surface = m_surfaces.value(shell->surface(), nullptr);
    if (!surface) {
        qWarning() << "XDG surface for unknown client. Recommend you kill!";
        return;
    }
    promoteWindow(WaylandWindow::create(surface.data(), shell));
}

/**
 * We've been created so we need to get ready to show stuff on screen.
 */
void Server::wlCreated()
{
    if (!isCreated()) {
        return;
    }
    // Enforce some kind of seat knowledge.
    wlSeatChanged(defaultSeat(), nullptr);
}

/**
 * Handle seat changes. In future we'll need to rebind active focus and such
 * and remove knowledge of the old seat from existing clients. For now, just
 * stash the pointer.
 */
void Server::wlSeatChanged(QWaylandSeat *newSeat, QWaylandSeat *oldSeat)
{
    Q_UNUSED(oldSeat);
    qDebug() << "Seat set to: " << newSeat;
    m_seat = newSeat;
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
