#include "systems/expirettl_system.h"

#include <cmath>

using namespace Halley;

class ExpireTTLSystem final : public ExpireTTLSystemBase<ExpireTTLSystem> {
public:
  void update(Halley::Time time)
  {
    // Sort of an exploit to get the player's position (maybe ok?)
    Vector2f playerPos;
    for (auto& e : playerFamily) {
      playerPos = e.position.position;
      break;
    }

    // Account for some large sprites (no need to measure)
    Vector2f tooFar(1280/2+200, 720/2+200);

    for (auto& e : mainFamily) {
      auto& item = e.tTL;
      item.timeLeft -= time;

      if (item.timeLeft <= 0) {
        if (item.onScreenOk) {
          getWorld().destroyEntity(e.entityId);
        } else {
          // Are we onscreen?
          Vector2f disp = playerPos - e.position.position;
          if (abs(disp.x) > tooFar.x || abs(disp.y) > tooFar.y) {
            getWorld().destroyEntity(e.entityId);
          }
        }
      }
    }

  }
};

REGISTER_SYSTEM(ExpireTTLSystem)
