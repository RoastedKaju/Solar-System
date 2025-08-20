#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

#include "PCH.h"
#include "Event.h"

namespace SOLAR
{
	// Forward declare 'SubscriptionHandle' class
	class SubscriptionHandle; 

	class EventDispatcher
	{
	public:
		EventDispatcher(const EventDispatcher&) = delete;
		EventDispatcher(EventDispatcher&&) = delete;
		EventDispatcher& operator=(const EventDispatcher&) = delete;
		EventDispatcher& operator=(EventDispatcher&&) = delete;

		using FunctionType = std::function<void(Event&)>;

		static EventDispatcher& Get()
		{
			static EventDispatcher instance;
			return instance;
		}

		/**
		* @brief Subscribes the event and it's callback
		*
		* @return Returns the unique ID for the subscription later used to unsubscribe
		*/
		size_t Subscribe(const EventType& type, FunctionType&& function);

		bool Unsubscribe(const EventType& type, size_t id);

		// Using this any client can send events to all observers that are intrested in them.
		void Broadcast(Event& event) const;

	protected:
		std::unordered_map<EventType, std::vector<std::pair<size_t, FunctionType>>> observersMap;

		/// Store unique ID for each subscription so we can remove it later.
		size_t nextId = 1;

	private:
		// This forces users to call the EventDispatcher::Get()
		EventDispatcher() = default;
	};
}

#endif // !EVENT_DISPATCHER_H
