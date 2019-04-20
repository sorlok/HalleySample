#include "systems/sprite_animation_system.h"

class SpriteAnimationSystem final : public SpriteAnimationSystemBase<SpriteAnimationSystem> {
public:
	void update(Halley::Time time, MainFamily& mainFamily)
	{
		auto& sprite = mainFamily.sprite.sprite;

		auto vel = mainFamily.mob.faceDir;
		int dir = std::abs(vel.y) > std::abs(vel.x) ? (vel.y < 0 ? 0 : 1) : (vel.x < 0 ? 2 : 3);

		auto& player = mainFamily.spriteAnimation.player;


//std::cout <<"TESTING: " <<texSz.x <<std::endl;



// TEMP: 0,0
//sprite.setPivot(Halley::Vector2f(32/2/256.0f, 48/2/256.0f));
//sprite.setClip(Halley::Rect4f(-16, -24, 32, 48));
//sprite.setRotation(Halley::Angle1f::fromDegrees(45.0f));
// TEMP: 0,1
//sprite.setPivot(Halley::Vector2f(0/256.0f, 48/256.0f));
//sprite.setPivot(Halley::Vector2f(0/256.0f, 2*48/192.0f));
//sprite.setClip(Halley::Rect4f(0, 0, 32, 48));
//sprite.setRotation(Halley::Angle1f::fromDegrees(45.0f));
// NOTE: It's easy to set using the same Clip and just moving the pivot.

//For currFrame: (0,0) setting clip: (-16, -24, 32, 48) and pivot: (0.0625,0.09375)
//For currFrame: (1,0) setting clip: (-16, -24, 32, 48) and pivot: (0.1875,0.09375)

// END TEMP


		// Are we moving?
		// TODO: Invert
		player.setPause(mainFamily.mob.moveDir.squaredLength() < 0.5f);
		player.setDirection(dir);
        player.update(time);
		player.updateSprite(sprite);

	}
};

REGISTER_SYSTEM(SpriteAnimationSystem)
