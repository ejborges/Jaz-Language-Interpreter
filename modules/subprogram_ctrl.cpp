#include "subprogram_ctrl.h"

subprogram_ctrl::begin()
{
	//Any variable declared in here will need a scope level
	// 1 higher than the current scope level.
}

subprogram_ctrl::end()
{
	//This will signal the end of a subroutine call.
}

subprogram_ctrl::returnFromCall()
{
	//This will decrement the current scope level so the program
	// knows what variables it has access to.
}

subprogram_ctrl::call(string label)
{
	//We use the input label to jump to the subroutine specified
	// by the label parameter and increment the current scope level.
}