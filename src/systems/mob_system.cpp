#include "systems/mob_system.h"

using namespace Halley;

class MobSystem final : public MobSystemBase<MobSystem> {
public:
  void update(Time p, MainFamily& entity)
  {
    float maxSpeed = entity.mob.maxSpeed;
    float acceleration = entity.mob.accel;
    Vector2f inVec = entity.mob.moveDir;
    if (inVec.squaredLength() > 1) {
      inVec = inVec.unit();
    }
    Vector2f& vel = entity.velocity.velocity;

    Vector2f brake = vel.unit() * acceleration * 0.5f;
    vel += inVec * acceleration;
    if (brake.squaredLength() > vel.squaredLength()) {
      vel = Vector2f();
    } else {
      vel -= brake;
    }
    vel *= inVec.length() > 0.1f ? 0.99f : 0.80f;
    float len2 = vel.squaredLength();
    if (len2 < 10.0f) {
      vel = Vector2f();
    } else if (len2 > maxSpeed * maxSpeed) {
      vel = vel * (maxSpeed / sqrt(len2));
    }
  }
};

REGISTER_SYSTEM(MobSystem)
