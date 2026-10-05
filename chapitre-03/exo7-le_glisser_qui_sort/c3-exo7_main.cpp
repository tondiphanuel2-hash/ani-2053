#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKLogger/NkLog.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKEvent/NkMouseEvent.h"

using namespace nkentseu;

static void ActualiserTitre(
    NkWindow &window,
    const NkString &nomDocument,
    bool documentModifie)
{
    const auto taille = window.GetSize();

    window.SetTitle(NkString::Format(
        "%s%s - (%u, %u)",
        nomDocument.CStr(),
        documentModifie ? "*" : "",
        taille.x,
        taille.y));
}

NKENTSEU_DEFINE_APP_DATA(([]()
                          {
    NkAppData data{};
    data.appName = "MaFenetre";
    data.appVersion = "1.0.0";
    return data; })());

int nkmain(const NkEntryState &)
{
    NkWindowConfig cfg;
    cfg.title = "KDs Editor";
    cfg.width = 800;
    cfg.height = 600;
    cfg.resizable = true;
    cfg.movable = true;
    cfg.closable = true;
    cfg.minimizable = true;
    cfg.maximizable = true;
    cfg.canFullscreen = true;

    NkWindow window(cfg);
    if (!window.IsOpen())
    {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }

    bool running = true;

    ActualiserTitre(window, nomDocument, documentModifie);

    while (running && window.IsOpen())
    {
        NkEvent *event = nullptr;

        while ((event = NkEvents().PollEvent()) != nullptr)
        {
            if (event->Is<NkWindowCloseEvent>())
            {
                running = false;
            }

            ///////////////////////////
            bool capturerPendantGlisser = false; // premier essai : sans capture
            bool enGlisser = false;

            if (auto *press = event->As<NkMouseButtonPressEvent>())
            {
                if (press->IsLeft())
                {
                    enGlisser = true;

                    if (capturerPendantGlisser)
                    {
                        window.CaptureMouse(true);
                    }

                    logger.Info("[drag] debut");
                }
            }
            else if (auto *release = event->As<NkMouseButtonReleaseEvent>())
            {
                if (release->IsLeft())
                {
                    if (capturerPendantGlisser)
                    {
                        window.CaptureMouse(false);
                    }

                    enGlisser = false;
                    logger.Info("[drag] fin");
                }
            }
        }
    }

    return 0;
}