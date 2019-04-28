#include "MyStage.hpp"
#include "registry.h"

#include <components/position_component.h>
#include <components/velocity_component.h>
#include <components/sprite_component.h>
#include <components/sprite_animation_component.h>
#include <components/collider_component.h>
#include <components/mob_component.h>
#include <components/shooter_component.h>
#include <components/player_input_component.h>

#include <halley/halley_json.h>

#include "types/GridAnimationPlayer.hpp"


using namespace Halley;

void MyStage::init()
{
  world = createWorld("game_world", createSystem);

  createMap(Vector2f(0,0));
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



void MyStage::createMap(Vector2f pos) {
  // Load the json file
  auto srcBytes = getResources().get<BinaryFile>("sample_map.json")->getBytes();
  Json::Value root;
  Json::Reader reader;
  bool parsingSuccessful = reader.parse((const char*)srcBytes.data(), (const char*)srcBytes.data() + srcBytes.size(), root );
  if ( !parsingSuccessful ){
    throw std::runtime_error("Error reading json data for sample_map.json");
  }

  // Process the data (create sprites)


std::cout <<"TEST: " <<root["width"].asUInt() <<" x " <<root["height"].asUInt() <<std::endl;
  


}


void MyStage::createPlayer(Vector2f pos) {
  auto keyboard = getAPI().input->getKeyboard(0);

  auto input = std::make_shared<InputVirtual>(0, 4);
  input->bindAxisButton(0, keyboard, Keys::A, Keys::D);
  input->bindAxisButton(1, keyboard, Keys::W, Keys::S);
  input->bindAxisButton(2, keyboard, Keys::Left, Keys::Right);
  input->bindAxisButton(3, keyboard, Keys::Up, Keys::Down);



  // TODO: How best to do tilesets



  // NOTE: Add a non-player.
  world->createEntity()
    .addComponent(PositionComponent(pos-Vector2f(100,100)))
    .addComponent(SpriteComponent(
      GridAnimationPlayer::UpdateSprite(
        Sprite().setImage(getResources(), "grassland.png"), Vector2i(256,256), Vector2i(1024,1024), Vector2i(1,1)
      ), 0))
  ;


  auto pl = world->createEntity()
    .addComponent(PositionComponent(pos))
    .addComponent(VelocityComponent(Vector2f(0, 0), Vector2f()))
    .addComponent(SpriteAnimationComponent(GridAnimationPlayer(Vector2i(122,114), Vector2i(366,456), Vector2i(3,4), {"down","left","right","up"}, true), 2.5, 5.0))
    .addComponent(SpriteComponent(Sprite()
      .setImage(getResources(), "phoenix.png")
      , 0))
    .addComponent(MobComponent(Vector2f(), Vector2f(), 50, 300))
    .addComponent(PlayerInputComponent(input))
    .addComponent(ShooterComponent(false, Vector2f(), 0))
    .addComponent(ColliderComponent(Rect4f(-13, -13, 26, 26), 0, false, false))
  ;

  playerId = pl.getEntityId();




}


