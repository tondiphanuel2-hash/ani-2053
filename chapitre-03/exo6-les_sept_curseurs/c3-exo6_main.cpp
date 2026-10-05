#include <iostream>
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKLogger/NkLog.h"
#include "NKTime/NkTime.h"
#include "NKTime/NkChrono.h"
#include "NKEvent/NkMouseEvent.h"

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

    // Les septs bandes de gauche à droite
    const NkWindow::NkCursorType curseurs[7] = {
        NkWindow::NkCursorType::Arrow,
        NkWindow::NkCursorType::TextInput,
        NkWindow::NkCursorType::Hand,
        NkWindow::NkCursorType::ResizeNS,
        NkWindow::NkCursorType::ResizeWE,
        NkWindow::NkCursorType::ResizeNWSE,
        NkWindow::NkCursorType::ResizeNESW};

    const char *nomsCurseurs[7] = {
        "Arrow", "TextInput", "Hand", "ResizeNS", "ResizeWE", "ResizeNWSE", "ResizeNESW"};

    // Déclare la dernière zone pour affihcer le message dès le départ
    int32 dernierZone = -1;

    window.SetCursor(curseurs[0]); // J'initialise le curseur en flèche au départ

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

            if (event->Is<NkWindowResizeEvent>())
            {
                documentModifier = true;
            }

            if (auto *mouvement = event->As<NkMouseMoveEvent>())
            {
                const auto taille = window.GetSize();
                const int32 x = mouvement->GetX(), y = mouvement->GetY();

                if (taille.x == 0 || taille.y == 0 || x < 0 || y < 0 ||
                    static_cast<uint32>(x) >= taille.x || static_cast<uint32>(y) >= taille.y)
                {
                    continue;
                }

                uint32 zone = static_cast<uint32>(
                    (static_cast<float32>(x) * 7.0f) / static_cast<float32>(taille.x));

                // Si jamais ma souris dépasse la zone limite
                if (zone > 6)
                    zone = 6;

                if (static_cast<int32>(zone) != dernierZone)
                {
                    logger.Info(
                        "[souris] Zone {0}/7, curseur associé {1}",
                        zone + 1, nomsCurseurs[zone]);

                    dernierZone = static_cast<int32>(zone);
                }

                // Le changement réelle du curseur
                window.SetCursor(curseurs[zone]);
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