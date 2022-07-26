#include "flagex_base.h"

namespace flx
{
	//FlagChain::FlagChain() { flags = 0; }
	FlagChain::FlagChain(DWORD flags) : flags(flags) {}

	void FlagChain::add(DWORD flag, void (*func)()){
		Func f(flag, func, nullptr, nullptr, false);

		funcs.push_back(f);
	}

	void FlagChain::add(DWORD flag, bool (*func)(), void (*catchFunc)()){
		Func f(flag, nullptr, func, catchFunc, true);
		
		funcs.push_back(f);
	}

	void FlagChain::execute(/*bool deleteAfterExecution = false*/)
	{
		//funcs.shrink_to_fit();

		for (uint32_t i = 0; i < funcs.size(); i++)
		{
			if (isDefined(funcs[i].flag)) funcs[i].exec();
		}

		//if (deleteAfterExecution) deleteFlagChain();
	}

	bool FlagChain::isDefined(DWORD flag)
	{
		return (flags & flag) == flag;
	}
}