/*
 * Copyright (c) 2019-2020, Jesse Buhagiar <jooster669@gmail.com>
 * Copyright (c) 2021, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2021, Sam Atkins <atkinssj@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "BackgroundSettingsWidget.h"
#include "DesktopSettingsWidget.h"
#include "FontSettingsWidget.h"
#include "MonitorSettingsWidget.h"
#include <LibConfig/Client.h>
#include <LibGUI/Application.h>
#include <LibGUI/Icon.h>
#include <LibGUI/SettingsWindow.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    if (pledge("stdio thread recvfd sendfd rpath cpath wpath unix", nullptr) < 0) {
        perror("pledge");
        return 1;
    }

    auto app = GUI::Application::construct(argc, argv);
    Config::pledge_domains("WindowManager");

    auto app_icon = GUI::Icon::default_icon("app-display-settings");

    auto window = GUI::SettingsWindow::construct("Display Settings");
    window->add_tab<DisplaySettings::BackgroundSettingsWidget>("Background");
    window->add_tab<DisplaySettings::FontSettingsWidget>("Fonts");
    window->add_tab<DisplaySettings::MonitorSettingsWidget>("Monitor");
    window->add_tab<DisplaySettings::DesktopSettingsWidget>("Workspaces");

    window->set_icon(app_icon.bitmap_for_size(16));

    window->show();
    return app->exec();
}
