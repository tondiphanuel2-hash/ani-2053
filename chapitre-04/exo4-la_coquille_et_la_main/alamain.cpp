#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKCanvas/Core/NkContextDesc.h"
#include "NKCanvas/Core/NkGraphicsApi.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include "NKCanvas/Renderer/Shapes/NkRectangleShape.h"
#include "NKEvent/NkEventSystem.h"
#include <chrono>
using namespace nkentseu;
using namespace nkentseu::renderer;
int nkmain(const NkEntryState& state) {
(void)state;
NkWindowConfig cfg;
cfg.title = "Carre rouge";
cfg.width = 640;
cfg.height = 480;
NkWindow window;
if (!window.Create(cfg)) return -1;
NkContextDesc desc;
desc.api = NkGraphicsApi::NK_GFX_API_OPENGL;
NkRenderWindow target(window, desc);
if (!target.IsValid()) return -2;
NkRectangleShape carre{50.f, 50.f};
carre.SetFillColor(NkColor2D{255, 0, 0, 255});
float32 x = 50.f;
carre.SetPosition({x, 100.f});
auto& events = NkEvents();
auto previous = std::chrono::steady_clock::now();
while (window.IsOpen()) {
auto now = std::chrono::steady_clock::now();
float32 dt = std::chrono::duration<float>(now - previous).count();
if (dt > 0.1f) dt = 0.1f;
previous = now;
events.PollEvents();
x += 100.f * dt;
carre.SetPosition({x, 100.f});
target.Clear(NkColor2D{18, 18, 24, 255});
target.Draw(carre);
target.Display();
}
return 0;
}