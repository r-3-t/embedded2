#include <set>
#include "mcu_internal.h"

class used_pinout
{
public:

	static void register_port(port p)
	{
		if (instance()._used_port.find(p) != instance()._used_port.end())
		{
			while(true) {};
		}

		instance()._used_port.insert(p);
	}

	static void unregister_port(port p)
	{
		instance()._used_port.erase(p);
	}

private:
	used_pinout() {}

	static used_pinout& instance()
	{
		static used_pinout pinout;
		return pinout;
	}

	std::set<port> _used_port;
};
