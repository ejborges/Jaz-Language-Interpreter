#include "subprogram_ctrl.h"

begin()
{
	//Any variable declared in here will need a scope level
	// 1 higher than the current scope level.
}

end()
{
	//This will signal the end of a subroutine call.
}

returnFromCall()
{
	//This will decrement the current scope level so the program
	// knows what variables it has access to.
}

call(std::string label)
{
	//We use the input label to jump to the subroutine specified
	// by the label parameter and increment the current scope level.
}