clean:
	g++ -std=c++11 main.cpp jaz.cpp modules/control_flow.cpp modules/operators.cpp modules/stack_manip.cpp modules/subprogram_ctrl.cpp modules/working_data.cpp -o bin/jaz_interpreter
