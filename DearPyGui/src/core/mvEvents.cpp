#include "mvEvents.h"

namespace Marvel {

	mvID SID(const std::string& value)
	{
		return std::hash<std::string>{}(value);
	}

	void mvEventBus::Publish(mvEvent event)
	{
		if (event.type == 0)
			return;

		if (GetEventHandlers().find(event.type) != GetEventHandlers().end())
		{
			for (mvEventHandler* handler : GetEventHandlers()[event.type])
			{
				if (handler->onEvent(event))
					break;
			}
		}

		if (event.category == 0)
			return;

		if (GetEventCategoryHandlers().find(event.category) != GetEventCategoryHandlers().end())
		{
			for (mvEventHandler* handler : GetEventCategoryHandlers()[event.category])
			{
				if (handler->onEvent(event))
					break;
			}
		}

	}

	void mvEventBus::Subscribe(mvEventHandler* handler, mvID type, mvID category)
	{
		if (type != 0)
		{
			if (GetEventHandlers().find(type) == GetEventHandlers().end())
				GetEventHandlers()[type] = { handler };
			else
				GetEventHandlers()[type].push_back(handler);
		}

		if (category == 0)
			return;

		if (GetEventCategoryHandlers().find(category) == GetEventCategoryHandlers().end())
			GetEventCategoryHandlers()[category] = { handler };
		else
			GetEventCategoryHandlers()[category].push_back(handler);
	}

	std::unordered_map<mvID, std::vector<mvEventHandler*>>& mvEventBus::GetEventHandlers()
	{
		static std::unordered_map<mvID, std::vector<mvEventHandler*>> eventHandlers;
		return eventHandlers;
	}

	std::unordered_map<mvID, std::vector<mvEventHandler*>>& mvEventBus::GetEventCategoryHandlers()
	{
		static std::unordered_map<mvID, std::vector<mvEventHandler*>> eventCategoryHandlers;
		return eventCategoryHandlers;
	}

}