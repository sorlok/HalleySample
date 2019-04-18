#include "systems/sprite_render_system.h"

using namespace Halley;


class SpriteRenderSystem final : public SpriteRenderSystemBase<SpriteRenderSystem> {
public:

  void render(RenderContext& rc) const {
    // NOTE: Render Context (in this case) already has the camera applied.
    // TODO: The "mask" is a bitflag used to hide sprites in large batches... why?
    rc.bind([&] (Painter& painter) {
      Rect4f worldView = getWorldView(painter);

      spritePainter.start(mythingFamily.count());
      for (auto& e : mythingFamily) {
        auto& sprite = e.sprite.sprite;
        sprite.setPos(e.position.position);
        spritePainter.add(sprite, 1, e.sprite.layer, sprite.getPosition().y - worldView.getY());
      }

      spritePainter.draw(1, painter);
    });
  }

private:
  Rect4f getWorldView(Painter& painter) const {
    Camera& cam = painter.getCurrentCamera();
    Rect4i viewPort = painter.getViewPort();

    Vector2f size = Vector2f(viewPort.getSize()) / cam.getZoom();
    assert(cam.getAngle().getRadians() == 0); // Camera rotation not accounted by following line
    return Rect4f(cam.getPosition() - size * 0.5f, size.x, size.y);
}


      
private:
  mutable SpritePainter spritePainter;

};

REGISTER_SYSTEM(SpriteRenderSystem)
