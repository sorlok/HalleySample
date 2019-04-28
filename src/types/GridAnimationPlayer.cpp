#include "GridAnimationPlayer.hpp"

#include <halley.hpp>

using namespace Halley;

GridAnimationPlayer::GridAnimationPlayer(Vector2i frameSize, Vector2i imageSize, Vector2i gridCount, std::vector<std::string> rowNames, bool fwdBack)
  : frameSize(frameSize), imageSize(imageSize), gridCount(gridCount), speed(1), remainder(0), fwdBack(fwdBack?1:0)
{
  // Build the lookup
  for (size_t i=0; i<rowNames.size(); i++) {
    std::string name = rowNames[i];
    if (!rowNameLookup.insert(std::make_pair(name,i)).second) {
      throw std::runtime_error(std::string("GridAnimation; key already exists: " + name).c_str());
    }
  }
}


void GridAnimationPlayer::setSpeed(double speed)
{
  this->speed = speed;
}

void GridAnimationPlayer::setDirection(const std::string& keyname)
{
  auto it = rowNameLookup.find(keyname);
  if (it == rowNameLookup.end()) {
    throw std::runtime_error(std::string("GridAnimation; key does not exist: " + keyname).c_str());
  }
  setDirection(it->second);
}

void GridAnimationPlayer::setDirection(int dir)
{
  if (dir>=0 && dir<gridCount.y) {
    currFrame.y = dir;
  }
}

bool GridAnimationPlayer::isPaused() const
{
  return speed == 0;
}

void GridAnimationPlayer::update(Halley::Time time)
{
  if (!isPaused()) {
    remainder += time * speed;
    if (remainder >= 1.0) {
      if (fwdBack > 0) {
        currFrame.x += 1;
        if (currFrame.x+1 >= gridCount.x) { fwdBack *= -1; }
      } else if (fwdBack < 0) {
        currFrame.x -= 1;
        if (currFrame.x <= 0) { fwdBack *= -1; }
      } else {
        currFrame.x = (currFrame.x + 1) % gridCount.x;
      }
      remainder -= 1.0;
    }
  }
}

void GridAnimationPlayer::updateSprite(Halley::Sprite& sprite) const
{
  GridAnimationPlayer::UpdateSprite(sprite, frameSize, imageSize, currFrame);
}


Halley::Sprite& GridAnimationPlayer::UpdateSprite(Halley::Sprite& sprite, Halley::Vector2i frameSize, Halley::Vector2i imageSize, Halley::Vector2i currFrame)
{
  int w = frameSize.x;
  int h = frameSize.y;

//if (imageSize.x==1024) { std::cout <<"TEST: " <<frameSize <<" => " <<imageSize <<" => " <<currFrame <<std::endl; }

  auto clip = Halley::Rect4f(-w/2, -h/2, w, h);
  auto pivot = Halley::Vector2f((currFrame.x*w+w/2.0)/imageSize.x, (currFrame.y*h+h/2.0)/imageSize.y);

  sprite.setPivot(pivot);
  sprite.setClip(clip);

  return sprite;
}



