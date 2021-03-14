#ifndef __TM_TASK_H__
#define __TM_TASK_H__

#include <memory>
#include <future>
#include <tuple>
#include <atomic>
#include <type_traits>

#include "ActionHolder.h"
#include "TaskTraits.h"
#include "Scheduler.h"

namespace TM
{

struct ITask
{
	virtual ~ITask() = default;
	virtual void operator()() = 0;
};

template <typename T, typename ...Deps>
class Task final : public ITask, public std::enable_shared_from_this<Task<T, Deps...>>
{
public:
	using R = std::invoke_result_t<T, typename Deps::element_type::R...>;

	Task(int dependenciesCount, T t, Deps ...deps) :
		m_body(t),
		m_future(m_promise.get_future()),
		m_deps(deps...),
		m_dependeciesCount(dependenciesCount)
	{
	}

	void operator()()
	{
		auto run = [this](Deps ... deps) {
			m_promise.set_value(m_body(deps->result()...));
		};

		std::apply(run, m_deps);

		if constexpr (TaskTraits<R>::isTask)
		{
			auto &task = m_future.get();
			m_actionHolder.delegateInvokation(&task->getActionHolder());
		}
		else
		{
			m_actionHolder.triggerActions();
		}
	}

	void addFinishAction(std::function<void()> action)
	{
		m_actionHolder.scheduleAction(action);
	}

	R result()
	{
		return m_future.get();
	}

	ActionHolder &getActionHolder()
	{
		return m_actionHolder;
	}

	void signalDependency()
	{
		if (!--m_dependeciesCount)
		{
			Scheduler::getInstance().schedule(this->shared_from_this());
		}
	}
private:
	T m_body;

	std::promise<R> m_promise;
	std::shared_future<R> m_future;
	std::tuple<Deps...> m_deps;

	std::atomic<int> m_dependeciesCount;
	ActionHolder m_actionHolder;
};

}

#endif // !__TM_TASK_H__
