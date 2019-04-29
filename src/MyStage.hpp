#pragma once

#include <halley.hpp>

class MyStage final : public Halley::EntityStage {
public:
  void init() override;

  void onVariableUpdate(Halley::Time) override;
  void onFixedUpdate(Halley::Time) override;
  void onRender(Halley::RenderContext&) const override;

  void createMap(Halley::Vector2f pos);
  void createPlayer(Halley::Vector2f pos);
  void createEnemy(Halley::Vector2f pos);

private:
  std::unique_ptr<Halley::World> world;

  Halley::EntityId playerId;
};

