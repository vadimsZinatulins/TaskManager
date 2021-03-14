#ifndef __TM_ACTION_HOLDER_H__
#define __TM_ACTION_HOLDER_H__

#include <mutex>
#include <vector>
#include <functional>

namespace TM
{

class ActionHolder
{
public:
	void scheduleAction(std::function<void()> action);
	void triggerActions();
	void delegateInvokations(ActionHolder *other);

private:
	std::vector<std::function<void()>> m_actions;
	ActionHolder *m_other{ nullptr };
	bool m_triggered{ false };

	std::mutex m_mutex;
};

}

#endif // !__TM_ACTION_HOLDER_H__
