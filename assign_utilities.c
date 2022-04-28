
#include "assign_shell.h"

static struct sigaction dead_struct;
void remove_dead_process(int sig, siginfo_t *siginfo, void *context)
{

    int x;
    pid_t pid = waitpid(-1, &x, 1);
    for (int i = 0; i < proc_count; i++)
    {
        if (p_arr[i]->pid == siginfo->si_pid)
        {
            p_arr[i]->life = 'n';
        }
    }
}

void z_handle(int signum)
{
    //printf("HAREEEEEEEE\n");
    int new_id = getpid();
    //printf("new is %d\n", new_id);
    strcpy(p_arr[proc_count]->name, "ex-foreground");
    p_arr[proc_count]->num = assign_num;
    p_arr[proc_count]->pid = new_id;

    p_arr[proc_count]->life = 'y';
    proc_count++;
    assign_num++;
}
void c_func()
{
    //printf("%d %d\n", getpid(), s_id);
    c_status=1;
    //kill(s_id, 9);
}
void start_signals()
{
    dead_struct.sa_sigaction = *remove_dead_process;
    dead_struct.sa_flags |= SA_SIGINFO;
    sigaction(SIGCHLD, &dead_struct, NULL);
    //signal(SIGTSTP, z_handle);

    signal(SIGTSTP, z_handle);
    signal(SIGINT, c_func);

    //signal(SIGCHLD, remove_dead_process);
}

char *remove_substring(char str[], char word[])
{
    int i, j = 0, k = 0, n = 0;
    int flag = 0;

    char *neww;
    neww = (char *)malloc(100 * sizeof(char));

    for (i = 0; str[i] != '\0'; i++)
    {
        k = i;

        while (str[i] == word[j])
        {
            i++, j++;
            if (j == strlen(word))
            {
                flag = 1;
                break;
            }
        }
        j = 0;

        if (flag == 0)
            i = k;
        else
            flag = 0;

        neww[n++] = str[i];
    }

    neww[n] = '\0';

    return neww;
}

int lacheck(char *single_instruc[300], int num_words)
{
    if (num_words == 1)
        return -1;
    int i, sum;
    sum = 0;
    for (i = 1; i < num_words; i++)
    {
        if (strcmp(single_instruc[i], "-a") == 0)
            sum += 1;
        else if (strcmp(single_instruc[i], "-l") == 0)
            sum += 2;
        else if ((strcmp(single_instruc[i], "-la") == 0) || (strcmp(single_instruc[i], "-al") == 0))
        {
            sum = 3;
            break;
        }
    }
    return sum;
}

void separator(char instruc[300])
{
    int num_words;
    char *splitcommands, *splitwords, *tokstore1, *tokstore2;
    char *single_instruc[300];
    num_words = 0;
    splitcommands = strtok_r(instruc, ";", &tokstore1);
    while (splitcommands != NULL)
    {

        num_words = 0;
        splitwords = strtok_r(splitcommands, " \n", &tokstore2);
        while (splitwords != NULL)
        {
            single_instruc[num_words] = splitwords;
            num_words++;
            splitwords = strtok_r(NULL, " \n", &tokstore2);
        }
        runcommand(single_instruc, num_words);

        splitcommands = strtok_r(NULL, ";", &tokstore1);
    }
}

void pipe_separator(char instruc[300])
{
    int num_words = 0, num_sect = 0;
    char *splitcommands, *splitwords, *tokstore1, *tokstore2, *tokstore3, *splitsects;
    int i = 0;
    char *single_word[20][300];
    char *single_sect[300];
    int num_for_sect[20];
    FILE *fp, *fp1, *fp2, *fp3, *fp4;
    fp = fopen("temp.txt", "w+");
    fp1 = fopen("temp1.txt", "w+");

    num_words = 0;
    splitcommands = strtok_r(instruc, ";", &tokstore1);
    while (splitcommands != NULL)
    {

        num_words = 0;
        splitsects = strtok_r(splitcommands, "|", &tokstore2);
        while (splitsects != NULL)
        {
            single_sect[num_sect] = splitsects;

            num_sect = num_sect + 1;
            splitsects = strtok_r(NULL, "|", &tokstore2);
        }

        if (1 < num_sect)
        {
            i = 0;
            while (i < num_sect)
            {
                splitwords = strtok_r(single_sect[i], " \n", &tokstore3);
                while (splitwords != NULL)
                {
                    single_word[i][num_words] = splitwords;

                    num_words++;
                    splitwords = strtok_r(NULL, " \n", &tokstore3);
                }
                num_for_sect[i] = num_words;
                num_words = 0;

                i++;
            }
        }

        for (i = 0; i < num_sect; i++)
        {
            int out_file, in_file, out_file2;
            char *str;

            out_file = open("temp1.txt", O_WRONLY | O_RDONLY | O_CREAT, 0644);

            dup2(out_file, 1);
            if (i == num_sect - 1)
            {
                freopen("/dev/tty", "w", stdout);
            }

            if (i > 0)
            {

                single_word[i][num_for_sect[i]] = "temp.txt";

                int x = num_for_sect[i] + 1;
                //printf("i is %d String is %s\n", i,single_word[i][0]);
                runcommand(single_word[i], x);
            }
            else
            {
                runcommand(single_word[i], num_for_sect[i]);
            }
            fp = fopen("temp.txt", "w+");
            char c;

            while ((c = fgetc(fp1)) != EOF)
            {
                fseek(fp, 0, SEEK_CUR);
                //printf("%c",c);
                fputc(c, fp);
            }
            fp1 = fopen("temp1.txt", "w+");
            fseek(fp1, 0, SEEK_CUR);
        }

        splitcommands = strtok_r(NULL, ";", &tokstore1);
        num_sect = 0;
    }
}

//void remove_dead_process(int sig, siginfo_t *info, void *vp)
