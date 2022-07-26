#pragma once

//#include <windows.h>
//#include <wincon.h>
#include <vector>
//#include <tuple>
#include <functional>

namespace flx
{
	/*interface FlaggedFunc
	{
	public:
		FLAG flag;
		void exec();
	};

	struct VFunc : public FlaggedFunc
	{
	public:
		VFunc(FLAG flag, void (*func)()) : func(func) { this->flag = flag; }

		void (*func)();
		void exec();
	};*/

	typedef unsigned long FLAG;

	/*template<typename... Args>
	struct Func
	{
	public:
		Func(void (*func)(Args...), Args... args)
		{
			func = func;
			arguments = ::std::make_tuple(::std::apply(args));
		}

		::std::tuple<Args...> arguments;

		void(*func)(Args...);
	};*/

	template<typename FuncType, typename... Args>
	struct NestedFunc
	{
	public:
		std::function<FuncType()> m_func;

		NestedFunc(FuncType (*f)(Args...), Args... args) {
			m_func = [f, args...]()
			{
				(f)(args...);
			};
		}

		void operator () () {
			m_func();
		}
	};

	struct FlaggedFunc
	{
	public:
		FlaggedFunc(FLAG flag, void (*func)(), bool (*bfunc)(),
			void (*catchFunc)(), bool boolean)
			: func(func), bfunc(bfunc), catchFunc(catchFunc), boolean(boolean) {
			this->flag = flag;
		}

		FLAG flag;

		bool boolean;
		void (*func)();
		bool (*bfunc)();
		void (*catchFunc)();
		void exec();
	};

	class FlagChain
	{
	public: 
		FLAG flags;
		std::vector<FlaggedFunc> funcs;
		
		FlagChain() { flags = 0b0; };
		FlagChain(FLAG flags);

		void add(FLAG flag, void (*func)());
		void add(FLAG flag, bool (*func)(), void (*catchFunc)() = 0);

		void execute(/*bool deleteAfterExecution = false*/);

		bool isDefined(FLAG flag);

		//void deleteFlagChain();
	};
}