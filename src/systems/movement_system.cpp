#include "systems/movement_system.h"

using namespace Halley;


class MovementSystem final : public MovementSystemBase<MovementSystem> {
public:

  void update(Halley::Time time, MainFamily& mainFamily) {
    mainFamily.position.position = mainFamily.position.position + mainFamily.velocity.velocity * time;
    //mainFamily.velocity.targetPosition;
  }

private:


      
private:


};

REGISTER_SYSTEM(MovementSystem)
