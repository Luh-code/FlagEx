#include "flagex_base.h"

namespace flx
{
	void FlaggedFunc::exec() {
		if (!this->boolean)
		{
			func();
			return;
		}
		if (!bfunc()) catchFunc();
	}

	/*void VFunc::exec() {
		func();
	}

	void BFunc::exec(){
		if (!func() && catchFunc) catchFunc();
	}*/
}