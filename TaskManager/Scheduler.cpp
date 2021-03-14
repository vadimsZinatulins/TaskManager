#include "Scheduler.h"
#include "Task.h"

namespace TM
{

Scheduler Scheduler::m_instance;

Scheduler &Scheduler::getInstance()
{
	return m_instance;
}

void Scheduler::initialize()
{
	auto body = [this] {
		while (true)
		{
			std::shared_ptr<ITask> task;

			m_queue.pop(task);

			if (!task)
			{
				return;
			}

			(*task)();
		}
	};

	m_threads.resize(std::thread::hardware_concurrency());
	for (auto &thread : m_threads)
	{
		thread = std::thread(body);
	}
}

void Scheduler::shutdown()
{
	for (std::size_t i = 0; i < m_threads.size(); i++)
	{
		m_queue.push({});
	}

	for (auto &thread : m_threads)
	{
		thread.join();
	}
}

void Scheduler::schedule(std::shared_ptr<ITask> task)
{
	m_queue.push(task);
}

Scheduler::Scheduler()
{
}

Scheduler::~Scheduler()
{
}

}