#ifndef __TM_TASK_QUEUE_H__
#define __TM_TASK_QUEUE_H__

#include <queue>
#include <mutex>
#include <memory>

namespace TM
{

struct ITask;

class TaskQueue
{
public:
	void push(std::shared_ptr<ITask> task);
	void pop(std::shared_ptr<ITask> &task);
private:
	std::queue<std::shared_ptr<ITask>> m_queue;

	std::mutex m_mutex;
	std::condition_variable m_newTaskAvailable;
};

}

#endif // !__TM_TASK_QUEUE_H__
