#pragma once

#include <windows.h>
#include <wincon.h>
#include <vector>

namespace flx
{
	/*interface Func
	{
	public:
		DWORD flag;
		void exec();
	};

	struct VFunc : public Func
	{
	public:
		VFunc(DWORD flag, void (*func)()) : func(func) { this->flag = flag; }

		void (*func)();
		void exec();
	};*/

	struct Func
	{
	public:
		Func(DWORD flag, void (*func)(), bool (*bfunc)(),
			void (*catchFunc)(), bool boolean)
			: func(func), bfunc(bfunc), catchFunc(catchFunc), boolean(boolean) {
			this->flag = flag;
		}

		DWORD flag;

		bool boolean;
		void (*func)();
		bool (*bfunc)();
		void (*catchFunc)();
		void exec();
	};

	class FlagChain
	{
	public: 
		DWORD flags;
		std::vector<Func> funcs;
		
		FlagChain() { flags = 0b0; };
		FlagChain(DWORD flags);

		void add(DWORD flag, void (*func)());
		void add(DWORD flag, bool (*func)(), void (*catchFunc)() = 0);

		void execute(/*bool deleteAfterExecution = false*/);

		bool isDefined(DWORD flag);

		//void deleteFlagChain();
	};
}