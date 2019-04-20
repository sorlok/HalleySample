#include "GridAnimationPlayer.hpp"

#include <halley.hpp>

using namespace Halley;

GridAnimationPlayer::GridAnimationPlayer(Vector2i frameSize, Vector2i gridCount, double speed, std::vector<std::string> rowNames)
  : frameSize(frameSize), gridCount(gridCount), speed(speed), remainder(0), paused(false)
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
  // We need the full texture size to scale our pivot point correctly.
  auto tex = sprite.getMaterial().getTexture(0);
  Expects(tex);
  auto texSz = tex->getSize();

  int w = frameSize.x;
  int h = frameSize.y;

  auto clip = Halley::Rect4f(-w/2, -h/2, w, h);
  auto pivot = Halley::Vector2f((currFrame.x*w+w/2.0)/texSz.x, (currFrame.y*h+h/2.0)/texSz.y);


// TEMP: Figuring out
//clip = Halley::Rect4f(0, 0, w, h);
//pivot = Halley::Vector2f((currFrame.x*w/1.0)/texSz.x, (currFrame.y*h/1.0)/texSz.y);

//std::cout <<"For currFrame: " <<currFrame <<" setting clip: " <<clip <<" and pivot: " <<pivot <<std::endl;

  sprite.setPivot(pivot);
  sprite.setClip(clip);
}



