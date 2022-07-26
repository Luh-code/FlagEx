#include "flagex_base.h"

namespace flx
{
	//FlagChain::FlagChain() { flags = 0; }
	FlagChain::FlagChain(FLAG flags) : flags(flags) {}

	void FlagChain::add(FLAG flag, void (*func)()){
		FlaggedFunc f(flag, func, nullptr, nullptr, false);

		funcs.push_back(f);
	}

	void FlagChain::add(FLAG flag, bool (*func)(), void (*catchFunc)()){
		FlaggedFunc f(flag, nullptr, func, catchFunc, true);
		
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

	bool FlagChain::isDefined(FLAG flag)
	{
		return (flags & flag) == flag;
	}
}