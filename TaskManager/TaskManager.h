#ifndef __TM_TASK_MANAGER_H__
#define __TM_TASK_MANAGER_H__

#include "Task.h"
#include "TaskTraits.h"
#include "Scheduler.h"
#include "TaskTraits.h"

namespace TM
{


template <typename T, typename ...Deps>
auto make_task(T t, Deps ...deps)
{
	auto const dependeciesCount = sizeof...(deps);

	auto task = std::make_shared<Task<T, Deps...>>(dependeciesCount, t, deps...);

	if constexpr (dependeciesCount == 0)
	{
		Scheduler::getInstance().schedule(task);
	}
	else
	{
		(..., deps->addFinishAction([=] { task->signalDependency(); }));
	}

	if constexpr (TaskTraits<TaskPtr<Task<T, Deps...>::R>>::isReturningTask)
	{
		return make_task([](auto x) { return x->result(); }, task);
	}
	else
	{
		return task;
	}
}

}

#endif // !__TM_TASK_MANAGER_H__
