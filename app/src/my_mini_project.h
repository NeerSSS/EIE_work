/**
* @file my_mini_project.h
 */

 #ifndef MY_STATE_MACHINE_H
 #define MY_STATE_MACHINE_H

 //initializes statemachine before it is executed
 //handles setting the initial state, intializes variables within the state machine,
 //and executing any entry actions
 void state_machine_init(); 

 //executes the logic associated with the current state,
 //checks inputs and transition conditions
 //transitions states and executes entry and exit during state transitions
 int state_machine_run(); 

 #endif // MY_STATE_MACHINE_H