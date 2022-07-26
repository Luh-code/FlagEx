#pragma once

#include <windows.h>
#include <wincon.h>
#include <vector>

namespace flx
{
	struct Func
	{
	public:
		DWORD flag;
		virtual void exec();
	};

	struct VFunc : public Func
	{
	public:
		void (*func)();
		void exec();
	};

	struct BFunc : public Func
	{
	public:
		bool (*func)();
		void (*catchFunc)();
		void exec();
	};

	class FlagChain
	{
	public: 
		DWORD flags;
		std::vector<Func> funcs;
		
		FlagChain();
		FlagChain(DWORD flags);

		void add(DWORD flag, void (*func)());
		void add(DWORD flag, bool (*func)(), void (*catchFunc)() = 0);

		void execute(/*bool deleteAfterExecution = false*/);

		//void deleteFlagChain();
	};
}