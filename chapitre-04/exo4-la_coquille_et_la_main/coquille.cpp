#include "NKWindow/NKMain.h"
#include "NKCanvas/App/NkCanvasApp.h"
using namespace nkentseu;
using namespace nkentseu::renderer;
class CarreApp : public NkCanvasApp {
public:
CarreApp() {
Config().title = "Carre rouge";
Config().width = 640;
Config().height = 480;
Config().clearColor = NkColor2D{18, 18, 24, 255};
Config().maxDeltaTime = 0.1f;
mCarre.SetFillColor(NkColor2D{255, 0, 0, 255});
mCarre.SetPosition({50.f, 100.f});
}
void OnUpdate(float32 dt) override {
x += 100.f * dt;
mCarre.SetPosition({x, 100.f});
}
void OnRender(NkRenderWindow& target) override {
target.Draw(mCarre);
}
private:
float32 x = 50.f;
NkRectangleShape mCarre{50.f, 50.f};
};
int nkmain(const NkEntryState& state) {
return NkCanvasApp::Run<CarreApp>(state);
}