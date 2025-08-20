#include "EventDispatcher.h"

namespace SOLAR
{
	size_t EventDispatcher::Subscribe(const EventType& type, FunctionType&& function)
	{
		const size_t id = nextId++;
		observersMap[type].emplace_back(id, std::move(function));
		return id;
	}

	bool EventDispatcher::Unsubscribe(const EventType& type, size_t id)
	{
		auto itr = observersMap.find(type);
		// If no even of this type exists return false
		if (itr == observersMap.end()) return false;

		// Get the vector from observers map which contain ID and Function signature
		auto& id_func_map = itr->second;
		auto pervSize = id_func_map.size(); // Store old size before removal of element

		id_func_map.erase(std::remove_if(
			id_func_map.begin(),									// Start
			id_func_map.end(),										// End
			[id](const auto& pair) {return pair.first == id; }),	// Predicate
			id_func_map.end());

		fmt::print(fmt::fg(fmt::color::yellow), "Unsubscribed Event ID: {}\n", id);

		return id_func_map.size() != pervSize;
	}

	void EventDispatcher::Broadcast(Event& event) const
	{
		auto type = event.GetType();

		if (observersMap.find(type) == observersMap.end())
		{
			// No registered functions for this event type found.
			return;
		}

		auto&& observers = observersMap.at(type);

		for (auto&& [id, observer] : observers)
		{
			if (event.IsHandled())
			{
				break;
			}
			// Call the function using the event you got in parameter
			observer(event);
		}
	}
}