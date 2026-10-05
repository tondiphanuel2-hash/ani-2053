#include <iostream>
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKLogger/NkLog.h"
#include "NKTime/NkTime.h"
#include "NKTime/NkChrono.h"

#include "NKEvent/NkWindowEvent.h"

using namespace nkentseu;

NKENTSEU_DEFINE_APP_DATA(([]()
                          {
    NkAppData d{};
    d.appName = "MaFenetre";
    return d; })());

int nkmain(const NkEntryState &)
{
    NkWindowConfig cfg;
    cfg.title = "Ma première fenêtre";
    cfg.width = 800;
    cfg.height = 600;

    // les droits de Nkentseu
    cfg.resizable = true;
    cfg.movable = true;
    cfg.closable = true;
    cfg.minimizable = true;
    cfg.maximizable = true;
    cfg.canFullscreen = true;
    cfg.modal = true;

    NkWindow window(cfg);
    if (!window.IsOpen())
    {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }

    bool running = true;

    float tailleX = 0;
    float tailleY = 0;

    while (running)
    {
        NkEvent *event = nullptr;
        while ((event = NkEvents().PollEvent()) != nullptr)
        {
            // process events
            if (event->Is<NkWindowCloseEvent>())
            {
                running = false;
            }
        }

        if (window.GetSize().x != tailleX || window.GetSize().y != tailleY)
        {
            logger.Info("[mesures] Taille rendue par la fenêtre {0} | DPI {1}", window.GetSize(), window.GetDpiScale());
            logger.Info("[mesures] Taille rendue par la fenêtre {0}x{1} | DPI {2}", window.GetSize().x, window.GetSize().y, window.GetDpiScale());

            tailleX = window.GetSize().x;
            tailleY = window.GetSize().y;
        }
    }

    return 0;
}