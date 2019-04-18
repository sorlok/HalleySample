#include "MyStage.hpp"
#include "registry.h"

#include <components/position_component.h>
#include <components/sprite_component.h>
#include <components/sprite_animation_component.h>
#include <components/collider_component.h>
#include <components/mob_component.h>
#include <components/shooter_component.h>
#include <components/player_input_component.h>


using namespace Halley;

void MyStage::init()
{
  world = createWorld("game_world", createSystem);

  createPlayer(Vector2f(350, 350));
  //createEnemy(Vector2f(400, 400))
}

void MyStage::onVariableUpdate(Time t)
{
  world->step(TimeLine::VariableUpdate, t);
}

void MyStage::onFixedUpdate(Time t)
{
  world->step(TimeLine::FixedUpdate, t);
}

void MyStage::onRender(RenderContext& context) const
{
  // Follow the player.
  Vector2f playerPos = world->getEntity(playerId).getComponent<PositionComponent>().position;
  Camera cam(playerPos);
  RenderContext rc = context.with(cam);

  // Draw the BG color
  rc.bind([&] (Painter& painter) {
    painter.clear(Colour(0.5f, 0.5f, 1.0f));
  });

  // Dispatch the rest to world
  world->render(rc);
}


void MyStage::createPlayer(Vector2f pos) {
  auto keyboard = getAPI().input->getKeyboard(0);

  auto input = std::make_shared<InputVirtual>(0, 4);
  input->bindAxisButton(0, keyboard, Keys::A, Keys::D);
  input->bindAxisButton(1, keyboard, Keys::W, Keys::S);
  input->bindAxisButton(2, keyboard, Keys::Left, Keys::Right);
  input->bindAxisButton(3, keyboard, Keys::Up, Keys::Down);

// TODO: This is what crashes.
//auto blah = getResource<Animation>("Hero");
//std::cout <<"BLAH: " <<blah->getName() <<std::endl;

  auto pl = world->createEntity()
    .addComponent(PositionComponent(pos))
//    .addComponent(VelocityComponent(Vector2f(0, 0), Vector2f()))
    .addComponent(SpriteAnimationComponent(AnimationPlayer(getResource<Animation>("Hero"))))
    .addComponent(SpriteComponent(Sprite()
      //.setSprite(getResources(), "some_sprite.json", "U_0.png")
      , 0))
    .addComponent(MobComponent(Vector2f(), Vector2f(), 50, 300))
    .addComponent(PlayerInputComponent(input))
//    .addComponent(PlayerComponent())
    .addComponent(ShooterComponent(false, Vector2f(), 0))
//    .addComponent(GunComponent(0.1f, "machinegun"))
    .addComponent(ColliderComponent(Rect4f(-13, -13, 26, 26), 0, false, false))
//    .addComponent(RepulseFieldComponent(10)
  ;

  playerId = pl.getEntityId();

}


