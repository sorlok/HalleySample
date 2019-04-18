#include "systems/sprite_animation_system.h"

class SpriteAnimationSystem final : public SpriteAnimationSystemBase<SpriteAnimationSystem> {
public:
	void update(Halley::Time time, MainFamily& mainFamily)
	{
		auto& sprite = mainFamily.sprite.sprite;

		auto vel = mainFamily.mob.faceDir;
		int dir = std::abs(vel.y) > std::abs(vel.x) ? (vel.y < 0 ? 0 : 2) : (vel.x < 0 ? 3 : 1);

		auto& player = mainFamily.spriteAnimation.player;
		player.setDirection(dir);
		player.update(time);
		player.updateSprite(sprite);
	}
};

REGISTER_SYSTEM(SpriteAnimationSystem)
