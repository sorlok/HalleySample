#pragma once 

#include <string>
#include <vector>
#include <map>

#include "halley/maths/vector2.h"
#include "halley/time/halleytime.h"
#include "halley/core/graphics/sprite/sprite.h"

// Used for abstracting a sprite sheet using basic assumptions.

class GridAnimationPlayer {
public:

  // frameSize = size of a single frame in the sequence (e.g., 32x48)
  // imageSize = the original image size
  // gridCount = number of frames in each row/column (e.g., 3 horiz, 2 vert)
  // speed = how much of 1.0f to update per second
  // rowNames = optional, list of names to use for each row (e.g., "up,down,left,right")
  GridAnimationPlayer() {}
  GridAnimationPlayer(Halley::Vector2i frameSize, Halley::Vector2i imageSize, Halley::Vector2i gridCount, double speed, std::vector<std::string> rowNames = {});

  void setPause(bool paused);
  void setDirection(int dir);
  void update(Halley::Time time);
  void updateSprite(Halley::Sprite& sprite) const;


private:
  Halley::Vector2i frameSize;
  Halley::Vector2i imageSize;
  Halley::Vector2i gridCount;
  double speed;
  std::map<std::string, size_t> rowNameLookup; // "up" => 0

  Halley::Vector2i currFrame; // repeat within each row
  double remainder; // at 1.0, we increment frames.
  bool paused; // are we animating?

  //Halley::Vector2i lastFrame; // Avoid spurious updates (TODO)
};

