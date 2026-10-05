#include <iostream>
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKLogger/NkLog.h"
#include "NKTime/NkTime.h"
#include "NKTime/NkChrono.h"

#include "NKEvent/NkWindowEvent.h"

using namespace nkentseu;

static void ActualiserTitre(NkWindow &window, const NkString &nomDocument, bool documentModifie)
{
    const auto taille = window.GetSize();

    const NkString titre = NkString::Format(
        "%s%s - (%u , %u)",
        nomDocument.CStr(),
        documentModifie ? "*" : "",
        taille.x,
        taille.y);

    window.SetTitle(titre);
}

NKENTSEU_DEFINE_APP_DATA(([]()
                          {
    NkAppData d{};
    d.appName = "MaFenetre";
    d.appVersion = "1.0.0";
    return d; })());

int nkmain(const NkEntryState &)
{
    NkWindowConfig cfg;
    cfg.title = "KDs Editor 📝";
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

    bool documentModifier = false;
    bool running = true;

    ActualiserTitre(window, cfg.title, documentModifier);

    // Valeur initialisé des dimensions avant changement
    float tailleX = 0, tailleY = 0;

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
            else if (event->Is<NkWindowResizeEvent>())
            {
                documentModifier = true;
            }

            ActualiserTitre(window, cfg.title, documentModifier);
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