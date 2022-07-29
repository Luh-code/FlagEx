#include "flagex_base.h"

namespace flx
{
	//FlagChain::FlagChain() { flags = 0; }
	FlagChain::FlagChain(FLAG flags) : flags(flags) {}

	template <typename FuncType, typename... Args>
	void FlagChain::add(FLAG flag, FuncType(*func)(Args...),
		Args... args) {
		NestedFunc<FuncType, Args...> f(func, args...);
		FlaggedFunc<FuncType, Args...> ff(flag, f, nullptr);
		funcs.push_back(f);
	}

	/*void FlagChain::add(FLAG flag, bool (*func)(), void (*catchFunc)()) {
		//FlaggedFunc f(flag, nullptr, func, catchFunc, true);
		
		//funcs.push_back(f);
	}*/

	void FlagChain::execute(/*bool deleteAfterExecution = false*/)
	{
		//funcs.shrink_to_fit();S

		for (uint32_t i = 0; i < funcs.size(); i++)
		{
			//FlaggedFunc f = (FlaggedFunc)funcs[i];

			if (isDefined(funcs[i].flag)) funcs[i].exec();
		}

		//if (deleteAfterExecution) deleteFlagChain();
	}

	bool FlagChain::isDefined(FLAG flag)
	{
		return (flags & flag) == flag;
	}
}