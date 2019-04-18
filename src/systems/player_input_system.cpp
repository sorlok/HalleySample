#include "systems/player_input_system.h"

class PlayerInputSystem final : public PlayerInputSystemBase<PlayerInputSystem> {
public:

  //void update(Halley::Time, MainFamily& entity) {
  void update(Halley::Time time, MainFamily& mainFamily) {



    auto& input = mainFamily.playerInput.input;
    auto moveDir = Halley::Vector2f(input->getAxis(0), input->getAxis(1));
    //auto shootDir = Halley::Vector2f(input->getAxis(2), input->getAxis(3));

    //bool shooting = shootDir.length() > 0.1f;
    //Halley::Vector2f faceDir = shooting ? shootDir : moveDir;

    mainFamily.mob.moveDir = moveDir;
    Halley::Vector2f faceDir = moveDir;
		
    if (faceDir.squaredLength() > 0.1f) {
      mainFamily.mob.faceDir = faceDir.unit();
    }

    //entity.shooter.shooting = shooting;
    //entity.shooter.shootDir = faceDir.unit();
  }

};

REGISTER_SYSTEM(PlayerInputSystem)
