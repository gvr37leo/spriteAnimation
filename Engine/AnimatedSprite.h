#pragma once
#include "Surface.h"
#include "Rect.h"
#include "Graphics.h"
#include <vector>

struct AnimatedSprite {

	Surface* img;
	V2i frameSize;
	std::vector<V2i> frames;
	float animDuration;


	AnimatedSprite(Surface* img, V2i& frameSize, std::vector<V2i>& frames, float animDuration) {
		this->img = img;
		this->frameSize = frameSize;
		this->frames = frames;
		this->animDuration = animDuration;
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