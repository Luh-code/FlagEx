#pragma once

#include <vector>
#include <functional>
#include <cassert>

using FLAG = unsigned long;

namespace flx
{

	class FlaggedFunc
	{
	public:
		FLAG m_flag = 0b0;
		std::function<bool()> m_func;
		std::function<void()> m_catchFunc;
	};

	class FlagChain
	{
	public: 
		FLAG flags;
		std::vector<FlaggedFunc*> funcs;
		
		FlagChain() { flags = 0b0; };
		FlagChain(FLAG flags) : flags(flags) {}
		
		template<typename... Args>
		void add(FLAG flag, bool(__cdecl* func)(Args...), void(__cdecl* catchFunc)(void), Args... args)
		{
			std::function<bool()> temp;

			temp = [func, args...]() {
				return (*func)(args...);
			};

			std::function<void()> catchTemp;

			catchTemp = [catchFunc, args...]() {
				(*catchFunc)(args...);
			};

			FlaggedFunc* ff = new FlaggedFunc();
			ff->m_flag = flag;
			ff->m_func = temp;
			ff->m_catchFunc = catchTemp;
			funcs.push_back(ff);
		}

		template<typename FuncType, typename... Args>
		void add(FLAG flag, FuncType (__cdecl* func)(Args...), Args... args)
		{
			std::function<bool()> temp;

			temp = [func, args...]() {
				(*func)(args...);
				return true;
			};

			FlaggedFunc* ff = new FlaggedFunc();
			ff->m_flag = flag;
			ff->m_func = temp;
			funcs.push_back(ff);
		}

		void execute()
		{

			for (uint32_t i = 0; i < funcs.size(); i++)
			{
				if (isDefined(funcs[i]->m_flag)) 
					if(!funcs[i]->m_func() && funcs[i]->m_catchFunc) 
						funcs[i]->m_catchFunc();
			}
		}

		bool isDefined(FLAG flag)
		{
			return (flags & flag) == flag;
		}

		void deleteFlagChain()
		{
			delete[] funcs.data();
		}
	};
}