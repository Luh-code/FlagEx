#include "flagex_base.h"

namespace flx
{
	FlagChain::FlagChain() {}
	FlagChain::FlagChain(DWORD flags) : flags(flags) {}

	void FlagChain::add(DWORD flag, void (*func)())
	{
		VFunc f;
		f.flag = flag;
		f.func = func;

		funcs.push_back(f);
	}

	void FlagChain::add(DWORD flag, bool (*func)(), void (*catchFunc)() = 0)
	{
		BFunc f;
		f.flag = flag;
		f.func = func;
		f.catchFunc = catchFunc;

		funcs.push_back(f);
	}

	void FlagChain::execute(/*bool deleteAfterExecution = false*/)
	{
		//funcs.shrink_to_fit();

		for (auto f : funcs)
		{
			f.exec();
		}

		//if (deleteAfterExecution) deleteFlagChain();
	}
}