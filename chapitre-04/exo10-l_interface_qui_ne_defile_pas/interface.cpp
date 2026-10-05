#include "NKWindow/NKMain.h"
#include "NKCanvas/App/NkCanvasApp.h"
#include "NKCanvas/Renderer/Resources/NkFont.h"
#include "NKCanvas/Renderer/Resources/NkSprite.h"
#include "NKCanvas/Renderer/Shapes/NkRectangleShape.h"

#include <cmath>
#include <string>

using namespace nkentseu;
using namespace nkentseu::renderer;

class InterfaceQuiDefile : public NkCanvasApp {
public:
    InterfaceQuiDefile()
        : mBarre(NkVec2f{800.f, 76.f}),
          mCarre(NkVec2f{64.f, 64.f}) {
        Config().title = "Vue et interface fixe";
        Config().width = 800;
        Config().height = 600;
        Config().clearColor = NkColor2D{18, 18, 24, 255};
        Config().maxDeltaTime = 0.1f;

        mVue.size = {800.f, 600.f};
        mVue.center = {400.f, 300.f};

        mBarre.SetPosition({0.f, 0.f});
        mBarre.SetFillColor(NkColor2D{32, 42, 60, 255});

        mCarre.SetFillColor(NkColor2D{220, 70, 70, 255});
    }

    bool OnInit() override {
        if (!mPolice.LoadFromFile(*Target().GetRenderer(),
                                  "Resources/Fonts/OCRAEXT.TTF")) {
            return false;
        }

        mTexte.SetFont(mPolice);
        mTexte.SetString("Interface fixe - monde defilant");
        mTexte.SetCharacterSize(24);
        mTexte.SetFillColor(NkColor2D{255, 255, 255, 255});
        mTexte.SetPosition({24.f, 50.f});
        return true;
    }

    void OnUpdate(float32 dt) override {
        mTemps += dt;
        mVue.center.x = 400.f + 100.f * mTemps;
    }

    void OnRender(NkRenderWindow& target) override {
        target.SetView(mVue);

        for (int i = 0; i < 20; ++i) {
            mCarre.SetPosition({80.f + static_cast<float32>(i) * 130.f, 280.f});
            target.Draw(mCarre);
        }

        // Variante fautive pour sans.png : commenter l'appel ResetView().
        target.ResetView();

        target.Draw(mBarre);
        target.Draw(mTexte);
    }

private:
    NkFont mPolice;
    NkText mTexte;
    NkRectangleShape mBarre;
    NkRectangleShape mCarre;
    NkView2D mVue;
    float32 mTemps = 0.f;
};

int nkmain(const NkEntryState& state) {
    return NkCanvasApp::Run<InterfaceQuiDefile>(state);
}