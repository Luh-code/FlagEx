#pragma once

#include <wincon.h>
#include <vector>

namespace flx
{
	struct Func
	{
		DWORD flag;
		void* func;
	};

	struct Func
	{
		DWORD flag;
		bool* func;
		void* catchFunc;
	};

	class FlagChain
	{
	public: 
		DWORD flags;
		std::vector<Func> funcs;
		
		FlagChain();
		FlagChain(DWORD flags);

		void add(DWORD flag, void* func);
		void add(DWORD flag, bool* func, void* catchFunc);

		void execute(bool deleteAfterExecution = false);

		void deleteFlagChain();
	};
}