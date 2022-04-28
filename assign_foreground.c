
#include "assign_shell.h"

void foreground(int num_words, char *single_instruc[300])
{

    pid_t p_id;
    int status;
    single_instruc[num_words] = NULL;
    p_id = fork();
    if (p_id == 0)
    {

        void thisfunction()
        {
            //printf("check1\n");
        }
        signal(SIGTSTP, SIG_DFL);
        /*if(signal(SIGINT, thisfunction))
        {
            printf("check2\n");
            
        }*/

        if (execvp(single_instruc[0], single_instruc) == -1)

            printf("Command not found\n");
        exit(0);
    }
    else if (p_id > 0)
    {
        signal(SIGINT, c_func);

        do
        {
            waitpid(p_id, &status, 0);
            //printf("WAITING\n");

        } while (WIFEXITED(status) == 0 && c_status != 1);
    }
}