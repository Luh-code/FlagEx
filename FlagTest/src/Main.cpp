#include <iostream>
#include "flagex_base.h"


const FLAG FLAG1 = 0b1 << 0;
const FLAG FLAG2 = 0b1 << 1;

void f2()
{
	std::cout << "cought\n";
}

bool test()
{
	std::cout << "TestFunc\n";
	return true;
}

int main()
{
	std::cout << "Hello World!\n";

	auto f1 = []() -> bool { std::cout << "Test1\n"; return false; };
	auto ft1 = [](int a) -> bool { std::cout << a * a << std::endl; return false; };
	auto ft2 = [](int a) -> void { std::cout << a * a << std::endl; };

	flx::FlagChain chain;
	chain.flags = FLAG1 | FLAG2;
	chain.add<void, int>(FLAG1, (void(__cdecl*)(int))ft2, 2);
	chain.add<>(FLAG1, test, f2);
	chain.execute();

	return 0;
}