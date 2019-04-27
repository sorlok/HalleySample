#include "systems/sprite_animation_system.h"

class SpriteAnimationSystem final : public SpriteAnimationSystemBase<SpriteAnimationSystem> {
public:
	void update(Halley::Time time, MainFamily& mainFamily)
	{
		auto& sprite = mainFamily.sprite.sprite;

		auto vel = mainFamily.mob.faceDir;
		std::string dir = std::abs(vel.y) > std::abs(vel.x) ? (vel.y < 0 ? "up" : "down") : (vel.x < 0 ? "left" : "right");

		auto& player = mainFamily.spriteAnimation.player;

		// Are we moving?
		player.setSpeed(mainFamily.mob.moveDir.squaredLength() < 0.5f ? mainFamily.spriteAnimation.idleSpeed : mainFamily.spriteAnimation.moveSpeed);
		player.setDirection(dir);
        player.update(time);
		player.updateSprite(sprite);

	}
};

REGISTER_SYSTEM(SpriteAnimationSystem)
