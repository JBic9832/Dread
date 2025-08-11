#pragma once

#include <string>

namespace Dread {

	class Event {
	public:
		virtual ~Event() = default;
		virtual std::string GetName() const = 0;
	};

}
