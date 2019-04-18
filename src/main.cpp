#include <halley.hpp>

#include "MyStage.hpp"

using namespace Halley;

// Forward declare various plugin registrations
void initOpenGLPlugin(IPluginRegistry& registry);
void initSDLSystemPlugin(IPluginRegistry& registry, Maybe<String> cryptKey);
void initSDLAudioPlugin(IPluginRegistry& registry);
void initSDLInputPlugin(IPluginRegistry& registry);
void initDX11Plugin(IPluginRegistry& registry);
void initWinRTPlugin(IPluginRegistry& registry);
void initMFPlugin(IPluginRegistry& registry);


class MyGame final : public Halley::Game
{
public:

  virtual String getName() const override {
    return "Sample Game";
  }

  virtual String getDataPath() const override {
    return "Halley/SampleGame";
  }

  virtual bool isDevMode() const override {
    return true;
  }


  virtual int initPlugins(IPluginRegistry &registry) {
#ifdef WITH_SDL2
    initSDLSystemPlugin(registry, Maybe<String>());
    initSDLInputPlugin(registry);
    initSDLAudioPlugin(registry);
#endif

#ifdef WITH_WINRT
    initWinRTPlugin(registry);
#endif

#ifdef WITH_MEDIA_FOUNDATION
    initMFPlugin(registry);
#endif

#ifdef WITH_OPENGL
    initOpenGLPlugin(registry);
#endif

#ifdef WITH_DX11
    initDX11Plugin(registry);
#endif

    return HalleyAPIFlags::Video | HalleyAPIFlags::Audio | HalleyAPIFlags::Input | HalleyAPIFlags::Movie;
  }

  virtual void initResourceLocator(const Path& gamePath, const Path& assetsPath, const Path& unpackedAssetsPath, ResourceLocator& locator) override {
    locator.addFileSystem(unpackedAssetsPath);
  }

  virtual std::unique_ptr<Stage> startGame(const HalleyAPI* api) override {
    api->video->setWindow(WindowDefinition(WindowType::BorderlessWindow, Vector2i(1280, 720), getName()));
//    api->audio->startPlayback(audioDeviceN);

    return std::make_unique<MyStage>();
  }









};

HalleyGame(MyGame);



