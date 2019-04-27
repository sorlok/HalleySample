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
  GridAnimationPlayer() : speed(0), remainder(0), fwdBack(0) {}
  GridAnimationPlayer(Halley::Vector2i frameSize, Halley::Vector2i imageSize, Halley::Vector2i gridCount, std::vector<std::string> rowNames = {}, bool fwdBack = false);

  void setSpeed(double speed); // 0 == paused
  void setDirection(const std::string& keyname);
  void setDirection(int dir);
  void update(Halley::Time time);
  void updateSprite(Halley::Sprite& sprite) const;
  bool isPaused() const;


private:
  Halley::Vector2i frameSize;
  Halley::Vector2i imageSize;
  Halley::Vector2i gridCount;
  double speed;
  std::map<std::string, size_t> rowNameLookup; // "up" => 0

  Halley::Vector2i currFrame; // repeat within each row
  double remainder; // at 1.0, we increment frames.

  int fwdBack; // If 1, move the animation fwd; if -1 move it back (and reverse on end). If 0, just cycle it.

  //Halley::Vector2i lastFrame; // Avoid spurious updates (TODO)
};

