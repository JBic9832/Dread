#include "EventListener.h"

namespace Dread {

EventListener::EventListener(const Callback& callback)
	: m_Callback{ callback }
{}

void EventListener::OnEvent(const Event& event) {
	m_Callback(event);
}

}
