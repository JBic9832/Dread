#pragma once

namespace Dread {
class Time {
public:
	static void Tick();
	static float deltaTime;


private:
	static float lastTime;
	Time();
	~Time();
};
}
