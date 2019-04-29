#include "systems/shooter_system.h"

#include <components/ttl_component.h>
#include <components/bullet_component.h>
#include <components/sprite_component.h>
#include <components/position_component.h>
#include <components/velocity_component.h>

#include "types/GridAnimationPlayer.hpp"

using namespace Halley;


class ShooterSystem final : public ShooterSystemBase<ShooterSystem> {
public:

  void update(Halley::Time time, MainFamily& mainFamily) {
    auto& shooter = mainFamily.shooter;

    if (shooter.cooldown > 0) {
      shooter.cooldown -= time;
      return;
    }

    if (shooter.shooting) {
      shooter.cooldown = 0.5f;
      spawnBullet(mainFamily.position.position, shooter.shootDir);
    }
  }

private:
  void spawnBullet(Vector2f pos, Vector2f dir)
  {
    Vector2f origin = pos + dir * 50;
    float ttl = 0.5f;
    int damage = 1;

    getWorld().createEntity()
      .addComponent(PositionComponent(origin))
      .addComponent(VelocityComponent(dir*800, Vector2f()))
      .addComponent(SpriteComponent(
        GridAnimationPlayer::UpdateSprite(
          Sprite().setImage(getAPI().core->getResources(), "bubbles.png"), Vector2i(32,32), Vector2i(64,64), Vector2i(0,0)
        ), 188))
      .addComponent(BulletComponent(damage))
      .addComponent(TTLComponent(ttl));
      //.addComponent(ColliderComponent(Rect4f(-5, -5, 10, 10), 2, false, false));
      //.setRotation(dir.angle())

      //auto clip = getAPI().getResource<AudioClip>("sound/weak_shot.ogg");
      //getAPI().audio->play(clip, AudioSourcePosition::makePositional(origin));
	}


      
private:


};

REGISTER_SYSTEM(ShooterSystem)
