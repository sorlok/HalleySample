#include "MyStage.hpp"
#include "registry.h"

#include <cstdlib>
#include <algorithm>

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

  Vector2f playerPos(100*32/2, 100*32/2);
  createMap(Vector2f(0,0));
  createPlayer(playerPos);

  // Make a bunch of random enemies
  ::srand (time(NULL));
  for (int y=0; y<10; y++) {
    for (int x=0; x<10; x++) {
      if (x!=5 && y!=5) {
        int xOff = ::rand()%10;
        int yOff = ::rand()%10;
        Vector2f pos((x*10+xOff)*32, (y*10+yOff)*32);
        createEnemy(pos);
      }
    }
  }
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

  // NOTE: Shortcut
  playerPos.x = std::max(std::min(playerPos.x, 2540.0f), 625.0f);
  playerPos.y = std::max(std::min(playerPos.y, 2824.0f), 350.0f);

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
  std::cout <<"Parsing map: " <<"sample_map.json" <<": " <<(parsingSuccessful ? "Ok" : "FAILED") <<std::endl;
  if ( !parsingSuccessful ){ throw std::runtime_error("Error reading json data for sample_map.json"); }
  if (root["renderorder"].asString() != "right-down") { throw std::runtime_error("Error; sample_map.json must have a render order of 'right-down'"); }

  // Process the data (create sprites)
  Vector2i mapSize(root["width"].asUInt(), root["height"].asUInt());
  Vector2i tileSize(root["tilewidth"].asUInt(), root["tileheight"].asUInt());
  Vector2i tilesetImageSize(1024,1024); // For the tileset
  Vector2i tilesetTilesSize(tilesetImageSize.x/tileSize.x,tilesetImageSize.y/tileSize.y); // For the tileset (in tiles)
  uint nextObjectId = root["nextobjectid"].asUInt(); // Anything below this is skipped.

  // Read all layers
  const Json::Value& layers = root["layers"];
  for (int id=0; id<layers.size(); id++) {
    const Json::Value& layer = layers[id];
    std::cout <<"Parsing layer: " <<layer["name"].asString() <<std::endl;

    // Sanity check
    if (layer["x"].asUInt()!=0 || layer["y"].asUInt()!=0 || layer["width"].asUInt()!=mapSize.x || layer["height"].asUInt()!=mapSize.y) { throw std::runtime_error("Offset or non-full-width layers not supported."); }

    // Read data
    const Json::Value& data = layers[id]["data"];
    for (size_t y=0; y<mapSize.y; y++) {
      for (size_t x=0; x<mapSize.y; x++) {
        uint tileId = data[int(y*mapSize.x+x)].asUInt();
        if (tileId < nextObjectId) { continue; }

        // Convert to 0-offset; index.
        tileId -= nextObjectId;

        // Make it.
        // TODO: Translate layer ID.
        auto nudge = 0; // TODO: why?
        world->createEntity()
          .addComponent(PositionComponent(pos + Vector2f(x*tileSize.x, y*tileSize.y)))
          .addComponent(SpriteComponent(
            GridAnimationPlayer::UpdateSprite(
              Sprite().setImage(getResources(), "grassland.png"), Vector2i(tileSize.x+nudge,tileSize.y+nudge), tilesetImageSize, Vector2i(tileId%tilesetTilesSize.x,tileId/tilesetTilesSize.x)
            ), id));
      }
    }

  }

  

  

/* // TODO:
  world->createEntity()
    .addComponent(PositionComponent(pos-Vector2f(100,100)))
    .addComponent(SpriteComponent(
      GridAnimationPlayer::UpdateSprite(
        Sprite().setImage(getResources(), "grassland.png"), Vector2i(256,256), Vector2i(1024,1024), Vector2i(1,1)
      ), 0));
*/

}


void MyStage::createPlayer(Vector2f pos) {
  auto keyboard = getAPI().input->getKeyboard(0);

  auto input = std::make_shared<InputVirtual>(0, 4);
  input->bindAxisButton(0, keyboard, Keys::A, Keys::D);
  input->bindAxisButton(1, keyboard, Keys::W, Keys::S);
  input->bindAxisButton(2, keyboard, Keys::Left, Keys::Right);
  input->bindAxisButton(3, keyboard, Keys::Up, Keys::Down);


  auto pl = world->createEntity()
    .addComponent(PositionComponent(pos))
    .addComponent(VelocityComponent(Vector2f(0, 0), Vector2f()))
    .addComponent(SpriteAnimationComponent(GridAnimationPlayer(Vector2i(122,114), Vector2i(366,456), Vector2i(3,4), {"down","left","right","up"}, true), 2.5, 5.0))
    .addComponent(SpriteComponent(Sprite()
      .setImage(getResources(), "phoenix.png")
      , 99))
    .addComponent(MobComponent(Vector2f(), Vector2f(), 50, 300))
    .addComponent(PlayerInputComponent(input))
    .addComponent(ShooterComponent(false, Vector2f(), 0))
    .addComponent(ColliderComponent(Rect4f(-13, -13, 26, 26), 0, false, false))
  ;

  playerId = pl.getEntityId();
}



void MyStage::createEnemy(Vector2f pos) {
  auto val = ::rand()%4;
  Vector2f dir(0,0);
  if (val==0) { dir.y = 1; }
  if (val==1) { dir.x = -1; }
  if (val==2) { dir.x = 1; }
  if (val==3) { dir.y = -1; }

  auto spr = ::rand()%100<25 ? "dknight.png" : "minotaur.png";

  auto en = world->createEntity()
    .addComponent(PositionComponent(pos))
    .addComponent(VelocityComponent(Vector2f(0, 0), Vector2f()))
    .addComponent(SpriteAnimationComponent(GridAnimationPlayer(Vector2i(282/3,400/4), Vector2i(282,400), Vector2i(3,4), {"down","left","right","up"}, true), 2.5, 5.0))
    .addComponent(SpriteComponent(Sprite()
      .setImage(getResources(), spr)
      , 99))
    .addComponent(MobComponent(Vector2f(), dir, 50, 300))
    .addComponent(ShooterComponent(false, Vector2f(), 0))
    .addComponent(ColliderComponent(Rect4f(-13, -13, 26, 26), 0, false, false))
  ;
}










