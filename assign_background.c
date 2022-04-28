
#include "assign_shell.h"

void background(int num_words, char *single_instruc[300])
{

    pid_t p_id;
    pid_t p_id_2;
    pid_t p_id_store;
    char proc_store[300];
    strcpy(proc_store, single_instruc[0]);
    int status;
    num_words--;
    single_instruc[num_words] = NULL;
    p_id = fork();

    if (p_id == 0)
    {

        execvp(single_instruc[0], single_instruc);

        exit(0);
    }
    else if (p_id > 0)
    {

        //printf("%d\n", getpid());
        p_arr[proc_count]->pid = p_id;
        p_arr[proc_count]->life = 'y';

        /*for (z = 0; z <= proc_count; z++)
        {
            printf("%d and %d and %s and %d\n", z, p_arr[z].num, p_arr[z].name, p_arr[z].pid);
        }*/

        printf("%d\n", p_id);
        assign_num++;

        proc_count++;

        p_id_2 = fork();
        c_id_2=p_id_2;
        if (p_id_2 == 0)
        {
            /*printf("PID INSIDE IS %d\n",p_id);

            do
            {
                waitpid(p_id, &status, 0);
                //printf("WAITING\n");

            } while (WIFEXITED(status) == 0);
            printf("THHHHAAAAATTT PROCESSSSSSS EXITED\n");*/
            //exit(0);
        }
        else if (p_id_2 > 0)
        {

            do
            {
                waitpid(p_id, &status, 0);
                //printf("WAITING\n");

            } while (WIFEXITED(status) == 0);
            printf("%s with pid %d exited\n", proc_store, p_id);
            
            do
            {
                waitpid(p_id_2, &status, 0);
                //printf("WAITING\n");

            } while (WIFEXITED(status) == 0);
        }
    }
}