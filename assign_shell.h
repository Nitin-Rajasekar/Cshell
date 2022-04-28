#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/mman.h>

typedef struct
{
    char name[100];
    pid_t pid;
    int num;
    char life;
} process;

//process p_arr[100];
process *p_arr[100];
//extern int procu_count=0;

int proc_count, assign_num, z;
int *check;
int s_id;
int c_status;
int c_id_2;

char *remove_substring(char str[], char word[]);
void foreground(int num_words, char *single_instruc[300]);
void start_signals();
void remove_dead_process();
void background(int num_words, char *single_instruc[300]);
int lacheck(char *single_instruc[300], int num_words);
void runcommand(char *single_instruc[300], int num_words);
void separator(char instruc[300]);
void pipe_separator(char instruc[300]);
void remove_dead_process(int sig, siginfo_t *siginfo, void *context);
void c_func();

