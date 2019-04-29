#include "systems/player_input_system.h"

#include <algorithm>

using namespace Halley;

class PlayerInputSystem final : public PlayerInputSystemBase<PlayerInputSystem> {
public:

  void update(Halley::Time time, MainFamily& mainFamily) {
    auto& input = mainFamily.playerInput.input;
    auto moveDir = Halley::Vector2f(input->getAxis(0), input->getAxis(1));
    auto shootDir = Halley::Vector2f(input->getAxis(2), input->getAxis(3));

    // Ignore if too far (note: this should be a different system)
    auto pos = mainFamily.position.position;
    if (pos.x<=0) { moveDir.x = std::max(0.0f, moveDir.x); }
    if (pos.y<=0) { moveDir.y = std::max(0.0f, moveDir.y); }
    if (pos.x>=3166) { moveDir.x = std::min(0.0f, moveDir.x); }
    if (pos.y>=3128) { moveDir.y = std::min(0.0f, moveDir.y); }

    mainFamily.mob.moveDir = moveDir;
    Halley::Vector2f faceDir = moveDir;
		
    if (faceDir.squaredLength() > 0.1f) {
      mainFamily.mob.faceDir = faceDir.unit();
    }

    mainFamily.shooter.shooting = shootDir.length() > 0.1f;
    mainFamily.shooter.shootDir = shootDir.unit();
  }

};

REGISTER_SYSTEM(PlayerInputSystem)
