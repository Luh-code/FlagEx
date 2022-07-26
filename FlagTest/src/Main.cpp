#include <iostream>
#include "flagex_base.h"

#include <windows.h>

const DWORD FLAG1 = 0b1 << 0;
const DWORD FLAG2 = 0b1 << 1;

void f2()
{
	std::cout << "Test2\n";
}

int main()
{
	std::cout << "Hello World!\n";

	auto f1 = []() -> void { std::cout << "Test1\n";  };

	flx::FlagChain chain;
	chain.flags = FLAG1 | FLAG2;
	chain.add(FLAG1, f1);
	chain.add(FLAG2, f2);
	chain.execute();

	return 0;
}