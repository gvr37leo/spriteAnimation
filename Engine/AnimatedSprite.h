#pragma once
#include "Surface.h"
#include "Rect.h"
#include "Graphics.h"
#include <vector>

struct AnimatedSprite {

	Surface* img;
	V2i frameSize;
	std::vector<V2i> frames;

	AnimatedSprite() = default;

	AnimatedSprite(Surface* img, V2i& frameSize, std::vector<V2i>& frames) {
		this->img = img;
		this->frameSize = frameSize;
		this->frames = frames;
	}

	void Draw(int x, int y, int frame, Rect clip, Graphics& gfx) {
		gfx.DrawSprite(x,y,
			Rect(
				V2i(frameSize.x * frames[frame].x, frameSize.y * frames[frame].y),
				frameSize
			),
			clip,*img);
	}
};