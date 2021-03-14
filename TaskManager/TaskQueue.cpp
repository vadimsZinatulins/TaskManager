#include "TaskQueue.h"

namespace TM
{

void TaskQueue::push(std::shared_ptr<ITask> task)
{
	std::unique_lock<std::mutex> lock(m_mutex);

	m_queue.push(task);


	m_newTaskAvailable.notify_one();
}

void TaskQueue::pop(std::shared_ptr<ITask> &task)
{
	std::unique_lock<std::mutex> lock(m_mutex);

	m_newTaskAvailable.wait(lock, [this] {return !m_queue.empty(); });

	task = m_queue.front();

	m_queue.pop();
}

}