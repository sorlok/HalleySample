#include "systems/sprite_animation_system.h"

class SpriteAnimationSystem final : public SpriteAnimationSystemBase<SpriteAnimationSystem> {
public:
	void update(Halley::Time time, MainFamily& mainFamily)
	{
		auto& sprite = mainFamily.sprite.sprite;

		auto vel = mainFamily.mob.faceDir;
		int dir = std::abs(vel.y) > std::abs(vel.x) ? (vel.y < 0 ? 0 : 2) : (vel.x < 0 ? 3 : 1);

		auto& player = mainFamily.spriteAnimation.player;


// TEMP: 0,0
//sprite.setPivot(Halley::Vector2f(32/2/256.0f, 48/2/256.0f));
//sprite.setClip(Halley::Rect4f(-16, -24, 32, 48));
//sprite.setRotation(Halley::Angle1f::fromDegrees(45.0f));
// TEMP: 0,1
//sprite.setPivot(Halley::Vector2f(32/2/256.0f, (48+48/2)/256.0f));
//sprite.setClip(Halley::Rect4f(-16, -24, 32, 48));
//sprite.setRotation(Halley::Angle1f::fromDegrees(45.0f));
// NOTE: It's easy to set using the same Clip and just moving the pivot.
// END TEMP


// TODO: Use the GridAnimationPlayer to update

		// Are we moving?
		if (mainFamily.mob.moveDir.squaredLength() > 0.5f) {
//			player.setSequence("walking");
		} else {
//			player.setSequence("idle");
		}

//		player.setDirection(dir);
//		player.update(time);
//		player.updateSprite(sprite);
	}
};

REGISTER_SYSTEM(SpriteAnimationSystem)
