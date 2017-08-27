#pragma once
#include <vector>
#include <functional>
#include "AnimatedSprite.h"
#include "Event.h"

struct Transition {
	AnimState next;
	Event triggered;
};

struct AnimState {
	float waited = 0;
	float duration = 1;
	std::vector<Transition> transitions;
	AnimatedSprite animation;

	AnimState() {

	}
	
	void progress(float dt) {
		waited += dt;
		if (waited > duration) {
			waited = 0;
		}
	}

	float getCompletion() {
		return waited / duration;
	}
};

struct Animator {
	AnimState currentState;

	Animator() {

	}

	void progress(float dt) {
		currentState.progress(dt);
		

	}
};