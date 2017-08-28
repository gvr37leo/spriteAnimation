#pragma once
#include <vector>
#include <functional>
#include "AnimatedSprite.h"
#include "Event.h"

struct Transition {
	AnimState next;
	Event triggered;

	Transition(AnimState& next, Event& triggered) {
		this->next = next;
		this->triggered = triggered;
	}
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

	void set(AnimState animState) {
		for each (Transition transition in animState.transitions) {
			transition.triggered.listen([=](int val) -> void {



				/*transition.triggered.callbacks.empty();
				currentState = transition.next;*/
			});
		}
	}

	void progress(float dt) {
		currentState.progress(dt);
		

	}
};