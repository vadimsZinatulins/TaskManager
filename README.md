# Task Manager 
Simple task manager library that manages asynchronous task wth some amount of flexibility.

# Build
Open the project in Visual Studio 2019, choose the Platform and Configuration and hit Build.

The output goes to `bin/{Platform}/{Configuration}/` and it will contain two directories:
- include\: Contains all __header__ files
- lib\: Contains the __.lib__ file
You can then include these in your project and make use of this library.

## Caution
You should use ISO C++ 17 (or higher if available) to build this project. This can be done by going to `Configuration Properties`->`General`->`C++ Language Standard` and set it to (at least) `ISO C++ 17 Standard (/std:c++17)`.

# Usage
The only 2 header files that should have most interest to you are `TaskManager.h` and `Scheduler.h`.
```c++
#include <TaskManager/TaskManager.h>
#include <TaskManager/Scheduler.h>
```

The first thing you must do when using this library is to initialize the scheduler and at the end shut it down.
```c++
int main(int argc, char *argv[])
{
  TM::Scheduler::getInstance().initialize();
  // Do some work
  TM::Scheduler::getInstance().shutdown();
  return 0;
}
```

Yo create an ascynchronous task use `make_task` function and pass in a lambda. This function returns a `std::shared_ptr` that points to the task. If the task returns any value you can retriev it by calling `result()` on the task.
```c++
auto get4 = TM::make_task([] { return 4;  });
std::cout << get4->result() << std::endl;   // This will print 4
```

You can get a little bit fancier with task dependencies. This is usefull if a certain task depends on values returned from another task.

# Credits
Credits goes to [Vladimir Mokhovikov](https://github.com/nongeneric)

This project is based on Vladimir Mokhovikov's tutorial "[a tiny C++ task library](https://www.rcebits.com/code/2019/05/02/tinytasks.html)" which you should definitely checkout if you are interested in implementation details.
