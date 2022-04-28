assign_runcommand.c contains the runcommand() function which is the primary function to resolve commands after they are parsed, includes echo, cd, pwd, ls and directs to the procedures for foreground and background processes.
assign_foreground.c, assign_background.c are responsible for foreground and background processes respectively, and commands not found in runcommand.
assign_utilities.c contains some utility functions related to parsing commands and ls.
assign_shell_main.c contains the main() function and assign_shell.h contains the headers and function prototypes.
