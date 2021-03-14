#ifndef __TM_TASK_TRAITS__
#define __TM_TASK_TRAITS__

namespace TM
{

template <typename T, typename ...Deps>
class Task;

template <typename T>
using TaskPtr = std::shared_ptr<Task<T>>;

template <typename T>
struct TaskTraits
{
	static constexpr bool isTask{ false };
	static constexpr bool isReturningTask{ false };
};

template <typename T>
struct TaskTraits<TaskPtr<TaskPtr<T>>>
{
	static constexpr bool isTask{ true };
	static constexpr bool isReturningTask{ true };
};

}

#endif // !__TM_TASK_TRAITS__
