#include <iostream>
#include "flagex_base.h"

#include <windows.h>

const flx::FLAG FLAG1 = 0b1 << 0;
const flx::FLAG FLAG2 = 0b1 << 1;

void f2()
{
	std::cout << "Test2\n";
}

void test()
{

}

int main()
{
	std::cout << "Hello World!\n";

	auto f1 = []() -> bool { std::cout << "Test1\n"; return false; };

	

	flx::FlagChain chain;
	chain.flags = FLAG1 | FLAG2;
	//chain.add(FLAG1, f1, []() -> void {std::cout << "fuck\n"; });
	//chain.add(FLAG2, f2);
	chain.add<bool, void (*)()>(FLAG1, test, 1);
	chain.execute();


	auto ft1 = [](int a) -> void { std::cout << a * a << std::endl; };

	std::function<bool()> func;
	func = f1;

	chain.add<void, int>(FLAG2, flx::NestedFunc<void, int>(ft1, 2))


	flx::NestedFunc<void, int> f(ft1, 2);
	f();

	return 0;
}