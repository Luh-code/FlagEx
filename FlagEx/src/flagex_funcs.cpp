#include "flagex_base.h"

namespace flx
{
	void Func::exec() {}

	void VFunc::exec()
	{
		func();
	}

	void BFunc::exec()
	{
		if (!func() && catchFunc) catchFunc();
	}
}