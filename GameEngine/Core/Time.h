#pragma once

namespace Dread {
class Time {
public:
	static void Tick();
	static float deltaTime;
	static float currentTime; 

private:
	static float lastTime;
	Time();
	~Time();
};
}
