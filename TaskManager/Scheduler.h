#ifndef __TM_SCHEDULER_H__
#define __TM_SCHEDULER_H__

#include "TaskQueue.h"

#include <vector>
#include <thread>

namespace TM
{

class Scheduler
{
public:
	static Scheduler &getInstance();

	void initialize();
	void shutdown();

	void schedule(std::shared_ptr<ITask> task);
private:
	Scheduler();
	~Scheduler();

	static Scheduler m_instance;
	
	TaskQueue m_queue;
	std::vector<std::thread> m_threads;
};

}

#endif // !__TM_SCHEDULER_H__
