#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKLogger/NkLog.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKEvent/NkMouseEvent.h"

using namespace nkentseu;

NKENTSEU_DEFINE_APP_DATA(([]()
                          {
    NkAppData data{};
    data.appName = "KDs Presse-Papper";
    data.appVersion = "1.0.0";
    return data; })());

int nkmain(const NkEntryState &)
{
    NkWindowConfig cfg;
    cfg.title = "KDs Presse-Papper";
    cfg.width = 800;
    cfg.height = 600;

    NkWindow window(cfg);
    if (!window.IsOpen())
    {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }

    // Lire et garder les deux contenus avant de modifier le presse-papiers.
    NkString texteAvant = window.GetClipboardText();

    NkClipboardImage image;
    const bool imageLue = window.GetClipboardImage(image);
    bool running = true;

    logger.Info("[texte avant]\n{0}", texteAvant.CStr());

    if (imageLue && image.IsValid())
    {
        logger.Info("[image avant] {0}x{1}",
                    image.width, image.height);
    }
    else
    {
        logger.Info("[image avant] aucune image lisible");
    }

    // Transformer le texte puis vérifier immédiatement ce que NkWindow relit.
    NkString texteMajuscule = texteAvant;
    texteMajuscule.ToUpper(); // Conversion ASCII.
    window.SetClipboardText(texteMajuscule);

    const NkString texteApres = window.GetClipboardText();
    logger.Info("[texte apres ecriture]\n{0}", texteApres.CStr());

    if (imageLue && image.IsValid())
    {
        // RGBA8 : inverser R, G et B, sans modifier A (l'alpha).
        for (usize i = 0; i < image.pixels.Size(); i += 4)
        {
            image.pixels[i] = static_cast<uint8>(255u - image.pixels[i]);
            image.pixels[i + 1] = static_cast<uint8>(255u - image.pixels[i + 1]);
            image.pixels[i + 2] = static_cast<uint8>(255u - image.pixels[i + 2]);
        }

        if (window.SetClipboardImage(image))
        {
            NkClipboardImage imageApres;

            if (window.GetClipboardImage(imageApres) && imageApres.IsValid())
            {
                logger.Info("[image apres ecriture] {0}x{1}",
                            imageApres.width, imageApres.height);
            }
            else
            {
                logger.Error("[image apres ecriture] impossible de relire l'image");
            }
        }
        else
        {
            logger.Error("[image] echec de l'ecriture dans le presse-papiers");
        }
    }

    // Vérifier si le texte est encore présent après l'écriture de l'image
    const NkString texteFinal = window.GetClipboardText();
    logger.Info("[texte final apres ecriture image]\n{0}", texteFinal.CStr());

    while (running)
    {
        NkEvent *event = nullptr;
        while ((event = NkEvents().PollEvent()) != nullptr)
        {
            if (event->Is<NkWindowCloseEvent>())
            {
                running = false;
            }
        }
    }

    return 0;
}