# Logger

example:

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "../include/Logger.h"

using namespace std;


int main(){
	Logger::init("log\\");

	

	for (int i = 0; i < 1000; i++)
	{
		string text = to_string(i);
		Logger::addLog(text, INFO);
		Logger::addLog(text, WARN);
		Logger::addLog(text, ERROR);
	}

	Logger::write();

	while (!Logger::logReady())
	{

	}

	Logger::deinit();

	return 0;
}
```
