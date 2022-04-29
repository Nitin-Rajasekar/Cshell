### Compilation

Run `make` to build and generate the a.out executable

---

### File breakdown

<p>assign_runcommand.c contains the runcommand() function which is the primary function to resolve commands after they are parsed, includes echo, cd, pwd, ls and directs to the procedures for foreground and background processes.</p>
<p>assign_foreground.c, assign_background.c are responsible for foreground and background processes respectively, and commands not found in runcommand.</p>
<p>assign_utilities.c contains some utility functions related to parsing commands and ls.</p>
<p>assign_shell_main.c contains the main() function and assign_shell.h contains the headers and function prototypes.</p>
