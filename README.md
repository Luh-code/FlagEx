# FlagEx
A simple header-only Library to aid with flags in your project.

**DISCLAIMER:** I abandoned this project, when I noticed it is more code-efficient, easy to use and easy to read to just define these macros:
```c++
#define IS_FLAG_SET(flag, val) ((val & flag) == val)
#define IF_FLAG_SET(flags, flag, func, ...) if (IS_FLAG_SET(flags, flag) && !static_cast<bool>(func(__VA_ARGS__)))
```
So make of that what you will moving forward.

## How To use
FlagEx is made with simplicity and ease of use in mind.
The way flags can be handled with FlagEx is by creating a FlagChain object and adding all of the Functions you may want to execute, aswell as the flag corresponding to that function.
This is done by calling .add<>().
The first argument for the template is the return type of your function. If you have a boolean as a return type, there is a slightly different way to handle that. Well get to that in a moment. 
The further arguments of the template are for the arguments your function takes in. So if you have a void with an integer as an argument, you'd use <void, int>.

The arguments for the add function Are as follows, first the flag, second the function you want to call if the flag is defined, and all of the rest are the arguments for said function.
So lets say our function is called testFunc. It's a void and takes an integer as its argument.
We want it to actuate when 'FLAGX' is set, with a 2 as an argument for testFunc. 
The notation for that would be: ```chain.add<void,int>(FLAGX, testFunc, 2);```

It's as easy as that.
This method works for any return type, though there is another way to do this with a function with a return type of boolean.
If you pass in a second function, that one is a sortoff catch for if the main method returns false. Another thing to mention is, that you can set this catch method to the pause method of the chain, stopping the rest of the steps from executing.
Lets say we have a func testFunc, with a return type of void and no arguments, and we want it to actuate when FLAGX is set. Also when it returns false we want to call the pause() function of the FlagChain.
That line would look like this: ```chain.add<>(FLAGX, testFunc, chain.pause);```
You might have noticed, that bool is missing in the templates. Thats because it wouldn't make sense to pass in anything other than a boolean because we destinctively *only* want the catch method to activate if the function returns FALSE.

The type of the flags are uint64_t, though there is a definition called FLAG for that in the FlagEx header.

When the whole FlagChain is set up you can call execute() to run all of the functions if their respective Flags are set.

## Simple Example

1. Create a flx::FlagChain
2. Set the flags of the FlagChain
3. Add functions in company with Flags
4. Call the execute() function in the FlagChain

```c++
#include <iostream>
#include "flagex_base.h"

FLAG FLAGA = 0b1 << 0;
FLAG FLAGB = 0b1 << 1;
FLAG FLAGC = 0b1 << 2;

void funcA(int a)
{
	std::cout << a*a << std::endl;
}

bool funcB()
{
	std::cout << "Done some stuff\n";
	return true;
}

bool funcB2()
{
	std::cout << "Done some unimportant stuff\n";
	return true;
}

void funcC()
{
	std::cout << "Finishing something up\n";
}

int main()
{
	flx::FlagChain chain;				// Create a flx::FlagChain object with the name chain
	chain.flags = FLAGX | FLAGY;			// Set the flags Memeber of the FlagChain object
	chain.add<void, int>(FLAGA, funcA, 2);		// funcA() is a void with an integer attribute, thus: <void, int>
	chain.add<>(FLAGB, funcB, chain.pause);		// funcB() is a boolean with no attributes. If funcB returns false, the chain.pause() is called
	chain.add<bool>(FLAGB, funcB2);			// Here bool needs to be defined in the template, because there isn't a catch function
	chain.add<void>(FLAGC, funcC);			// Doesn't get executed because FLAGC isn't defined
	chain.execute();				// Executes the FlagChain
}
```
