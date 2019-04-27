#include "GridAnimationPlayer.hpp"

#include <halley.hpp>

using namespace Halley;

GridAnimationPlayer::GridAnimationPlayer(Vector2i frameSize, Vector2i imageSize, Vector2i gridCount, double speed, std::vector<std::string> rowNames)
  : frameSize(frameSize), imageSize(imageSize), gridCount(gridCount), speed(speed), remainder(0), paused(false)
{
  // Build the lookup
  for (size_t i=0; i<rowNames.size(); i++) {
    std::string name = rowNames[i];
    if (!rowNameLookup.insert(std::make_pair(name,i)).second) {
      throw std::runtime_error(std::string("GridAnimation; key already exists: " + name).c_str());
    }
  }

}


void GridAnimationPlayer::setPause(bool paused)
{
  this->paused = paused;
}

void GridAnimationPlayer::setDirection(int dir)
{
  if (dir>=0 && dir<gridCount.y) {
    currFrame.y = dir;
  }
}

void GridAnimationPlayer::update(Halley::Time time)
{
  if (!paused) {
    remainder += time * speed;
    if (remainder >= 1.0) {
      currFrame.x = (currFrame.x + 1) % gridCount.x;
      remainder -= 1.0;
    }
  }
}

void GridAnimationPlayer::updateSprite(Halley::Sprite& sprite) const
{
  int w = frameSize.x;
  int h = frameSize.y;

  auto clip = Halley::Rect4f(-w/2, -h/2, w, h);
  auto pivot = Halley::Vector2f((currFrame.x*w+w/2.0)/imageSize.x, (currFrame.y*h+h/2.0)/imageSize.y);

  sprite.setPivot(pivot);
  sprite.setClip(clip);
}



