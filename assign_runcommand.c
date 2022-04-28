

#include "assign_shell.h"

void runcommand(char *single_instruc[300], int num_words)
{

    int word_num = 0;
    FILE *fp;
    int iofile;
    int temp, temp1;

    dup2(1, temp);
    dup2(0, temp1);

    while (word_num < num_words)
    {

        if (strcmp(single_instruc[word_num], ">") == 0)
        {
            fp = fopen(single_instruc[word_num + 1], "w");
            fclose(fp);
            iofile = open(single_instruc[word_num + 1], O_WRONLY | O_CREAT, 0644);

            dup2(iofile, 1);
            num_words -= 2;
        }
        else if (strcmp(single_instruc[word_num], ">>") == 0)
        {

            iofile = open(single_instruc[word_num + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);

            dup2(iofile, 1);
            num_words -= 2;
        }
        else if (strcmp(single_instruc[word_num], "<") == 0)
        {
            iofile = open(single_instruc[word_num + 1], O_RDONLY, 0644);
            if (iofile == -1)
                printf("The file does not exist\n");
            dup2(iofile, 0);
            num_words -= 2;
        }
        word_num++;
    }

    if (strcmp(single_instruc[0], "cd") == 0)
    {
        char dest_folder[300];
        //scanf("%s", dest_folder);
        strcpy(dest_folder, single_instruc[1]);
        /*if (strcmp(dest_folder, "sample_folder") == 0)*/

        chdir(dest_folder);
    }
    else if (strcmp(single_instruc[0], "echo") == 0)
    {
        char echo_word[300];

        //scanf("%s", echo_word);
        strcpy(echo_word, single_instruc[1]);

        printf("%s\n", echo_word);
    }
    else if (strcmp(single_instruc[0], "pwd") == 0)
    {
        char present_dir[300];

        getcwd(present_dir, sizeof(present_dir));

        printf("%s\n", present_dir);
    }

    else if (strcmp(single_instruc[0], "ls") == 0)
    {
        int i, dir_curr;
        int f_num;
        struct stat stats;

        int first_file = -1;
        dir_curr = 1;
        char *arr[300];
        DIR *dir = NULL;

        for (i = 1; i < num_words; i++)
        {

            if (single_instruc[i][0] != '-')
            {
                dir_curr = 0;
                //char * path;
                first_file = i;
                dir = opendir(single_instruc[i]);
                break;
            }
        }
        if (dir_curr == 1)
            dir = opendir(".");

        struct dirent *ds;
        int la;
        la = lacheck(single_instruc, num_words);
        f_num = 0;
        while (ds = readdir(dir))
        {
            arr[f_num] = ds->d_name;

            if (la == 1)
            {
                printf("%s ", arr[f_num]);
            }
            else if (la == -1 || la == 0)
            {
                //if (strcmp("..", ds->d_name) != 0 && strcmp(".", ds->d_name) != 0)
                if (ds->d_name[0] != '.')
                    printf("%s ", arr[f_num]);
            }
            else if (la == 2 || la == 3)
            {
                char address[300] = "";

                if (ds->d_name[0] == '.')

                {
                    if (la == 2)
                        continue;
                }

                if (first_file > 0)
                {
                    strcat(address, single_instruc[first_file]);
                    strcat(address, "/");

                    strcat(address, arr[f_num]);
                    stat(address, &stats);
                }
                else
                {
                    stat(arr[f_num], &stats);
                }

                printf((S_ISDIR(stats.st_mode)) ? "d" : "-");
                printf((stats.st_mode & S_IRUSR) ? "r" : "-");
                printf((stats.st_mode & S_IWUSR) ? "w" : "-");
                printf((stats.st_mode & S_IXUSR) ? "x" : "-");
                printf((stats.st_mode & S_IRGRP) ? "r" : "-");
                printf((stats.st_mode & S_IWGRP) ? "w" : "-");
                printf((stats.st_mode & S_IXGRP) ? "x" : "-");
                printf((stats.st_mode & S_IROTH) ? "r" : "-");
                printf((stats.st_mode & S_IWOTH) ? "w" : "-");
                printf((stats.st_mode & S_IXOTH) ? "x" : "-");
                printf(" %ld ", stats.st_nlink);
                printf(" %s", getpwuid(stats.st_uid)->pw_name);
                printf(" %s", getpwuid(stats.st_gid)->pw_name);
                printf(" %ld ", stats.st_size);
                char time[100];
                strftime(time, 100, "%Y-%m-%d %H:%M", localtime(&stats.st_mtime));
                printf("%s", time);
                printf("      %s", arr[f_num]);
                printf("\n");
            }

            f_num++;
        }
        printf("\n");
    }

    else if (strcmp(single_instruc[0], "repeat") == 0)
    {
        char times[300];
        strcpy(times, single_instruc[1]);
        int no_times = atoi(times);
        char *storestring[300];
        int i;
        for (i = 2; i < num_words; i++)
        {
            storestring[i - 2] = single_instruc[i];
        }
        for (i = 0; i < no_times; i++)
        {
            runcommand(storestring, num_words - 2);
        }
    }

    else if (strcmp(single_instruc[0], "pinfo") == 0)
    {
        pid_t p_id;
        int id_num;
        if (num_words == 1)
        {
            p_id = getpid();
        }
        else if (num_words == 2)
        {
            id_num = atoi(single_instruc[1]);
            p_id = id_num;
        }

        char filestring[300];
        char filestring_2[300];
        char filestring_3[300];
        char *split, *split_2, *split_3;
        int i = 0;
        char *kb, *kb_2;
        printf("pid -- %d\n", p_id);
        char pro_stat_path[300];
        sprintf(pro_stat_path, "/proc/%d/status", p_id);
        FILE *fp = fopen(pro_stat_path, "r");

        while (fgets(filestring_3, sizeof(filestring_3), (FILE *)fp) != NULL)
        {
            if (strncmp("Name:", filestring_3, strlen("Name")) == 0)
                break;
        }

        split_3 = strtok(filestring_3, ": ");
        split_3 = strtok(NULL, ": ");

        while (fgets(filestring, sizeof(filestring), (FILE *)fp) != NULL)
        {
            if (strncmp("State:", filestring, strlen("State")) == 0)
                break;
        }
        /*for (i = 0; i < strlen(filestring); i++)
        {
            printf("%d %c\n", i, filestring[i]);
        }*/
        split = strtok(filestring, ": \n");
        split = strtok(NULL, " \n");

        while (fgets(filestring_2, sizeof(filestring_2), (FILE *)fp) != NULL)
        {
            if (strncmp("VmRSS:", filestring_2, strlen("VmRSS")) == 0)
                break;
        }

        split_2 = strtok(filestring_2, " \n");
        split_2 = strtok(NULL, " \n");
        printf("Process Status -- %s\n", split);
        printf("memory -- %s kB\n", split_2);
        printf("Executable Path -- %s\n", split_3);
    }

    else if (strcmp(single_instruc[0], "jobs") == 0)
    {
        for (z = 0; z < proc_count; z++)
        {
            if (p_arr[z]->life == 'y')
                printf("[%d] %s [%d]\n", p_arr[z]->num, p_arr[z]->name, p_arr[z]->pid);
        }
    }

    else if (strcmp(single_instruc[0], "sig") == 0)
    {
        int val1, val2;
        val1 = atoi(single_instruc[1]);
        val2 = atoi(single_instruc[2]);
        if (val1 > proc_count)
        {
            printf("Process does not exist \n");
            //exit(0);
        }

        for (z = 0; z < proc_count; z++)
        {

            if (p_arr[z]->num == val1)
            {
                if (p_arr[z]->life == 'n')
                {
                    printf("Process does not exist anymore\n");
                    break;
                }

                kill(p_arr[z]->pid, val2);
            }
        }
    }

    else if (strcmp(single_instruc[0], "fg") == 0)
    {
        int val1;
        pid_t conc_id, conc_id_2;
        val1 = atoi(single_instruc[1]);
        for (z = 0; z < proc_count; z++)
        {

            if (p_arr[z]->num == val1)
            {
                conc_id = p_arr[z]->pid;
                conc_id_2 = p_arr[z]->pid;
                
                kill(conc_id, SIGCONT);
                int some;
                //printf("conc_id is %d\n", conc_id);
                while (kill(conc_id, 0) != -1)
                {
                }
                waitpid(conc_id, &some, WUNTRACED);
                
            }
        }
    }

    else if (strcmp(single_instruc[0], "bg") == 0)
    {
        int val1;
        pid_t conc_id, conc_id_2;
        val1 = atoi(single_instruc[1]);
        for (z = 0; z < proc_count; z++)
        {

            if (p_arr[z]->num == val1)
            {
                printf("%d\n", p_arr[z]->pid);
                kill(p_arr[z]->pid, SIGCONT);

                //if (kill(p_arr[z]->pid, 9) < 0)
                // printf("AYO\n");*/
            }
        }
    }

    else if (strcmp(single_instruc[0], "replay") == 0)
    {
        int r_time, r_avail;
        char command[300];
        int i;
        for (z = 0; z < num_words; z++)
        {
            if (strcmp(single_instruc[z], "-interval") == 0)
            {

                for (i = 2; i < z; i++)
                {
                    strcat(command, single_instruc[i]);
                    strcat(command, " ");
                }
                r_time = atoi(single_instruc[z + 1]);
            }
            if (strcmp(single_instruc[z], "-period") == 0)
            {
                r_avail = atoi(single_instruc[z + 1]);
            }
        }
        char ch;
        //printf("%d %d\n", r_time, r_avail);
        for (i = 1; i <= r_avail; i++)
        {
            sleep(1);
            for (int j = 0; j < strlen(command); j++)
            {
                ch = command[j];
            }
            //printf("\n");
            if (i % r_time == 0)
                separator(command);
        }
    }

    else if (strcmp("&", single_instruc[num_words - 1]) == 0)
    {
        //p_arr[p_count].name=single_instruc[0];
        strcpy(p_arr[proc_count]->name, single_instruc[0]);
        p_arr[proc_count]->num = assign_num;

        background(num_words, single_instruc);
    }
    else
    {
        foreground(num_words, single_instruc);
    }

    //dup2(temp, 1);
    freopen("/dev/tty", "w", stdout);

    //dup2(temp1, 0);
    freopen("/dev/tty", "r", stdin);
}

/*void checkIO(char *single_instruc[300], int num_words)
{
    int word_num=0;
    int iofile;
    while(word_num < num_words)
    {
        if(strcmp(single_instruc[word_num],">")==0)
        {
            iofile = open(single_instruc[n+1],O_WRONLY | O_RDONLY | O_CREAT , 0644 );
        }
        word_num++;
    }
}*/