#pragma once
#include <functional>

struct V2i {
	int x;
	int y;

	V2i() = default;

	V2i(int x, int y) {
		this->x = x;
		this->y = y;
	}

	V2i& add(V2i& v) {
		x += v.x;
		y += v.y;
		return *this;
	}

	V2i& sub(V2i& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}

	void loop(std::function<void(V2i)> callback) {
		for (int _x = 0; _x < x; _x++) {
			for (int _y = 0; _y < y; _y++) {
				callback(V2i(_x, _y));
			}
		}
	}

	V2i c() {
		return V2i(x, y);
	}
};

struct Rect {
	V2i pos;
	V2i size;

	Rect() = default;

	Rect(V2i pos, V2i size) {
		this->pos = pos;
		this->size = size;
	}

	int left() {
		return pos.x;
	}

	int top() {
		return pos.y;
	}

	int right() {
		return pos.x + size.x;
	}

	int bottom() {
		return pos.y + size.y;
	}

	void loop(std::function<void(V2i)> callback) {
		size.loop([&](V2i looppos) -> void {
			callback(looppos.add(pos));
		});
	}
};