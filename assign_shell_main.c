

#include "assign_shell.h"

int main()
{
    char device[300], start_dir[300], username[300];
    char curr_dir[300];
    char *cut_dir;
    proc_count = 0;
    assign_num = 1;
    int ab;
    s_id = getpid();
    check = mmap(NULL, sizeof *check, PROT_READ | PROT_WRITE,
                 MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    for (int i = 0; i < 100; i++)
    {
        p_arr[i] = mmap(NULL, sizeof *p_arr[i], PROT_READ | PROT_WRITE,
                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    }
    char *instruc = NULL;
    ssize_t instruc_size = 0;
    start_signals();
    getcwd(start_dir, sizeof(start_dir));

    gethostname(device, sizeof(device));
    getlogin_r(username, sizeof(username));
    while (1)
    {
        //printf("%d\n", s_id);

        c_status = 0;

        getcwd(curr_dir, sizeof(curr_dir));
        cut_dir = remove_substring(curr_dir, start_dir);
        printf("<%s@%s:~%s>\n", username, device, cut_dir);
        //scanf("%s", instruc);
        ssize_t instruc_size = 0;
        ab = getline(&instruc, &instruc_size, stdin);
        if (ab == -1)
        {
            //printf("%d\n", s_id);
            kill(s_id, 9);
            kill(c_id_2, 9);

        }
        //printf("IT IS %s\n", instruc);

        //execute_instruc(instruc);
        if (strchr(instruc, '|'))
            pipe_separator(instruc);
        else
            separator(instruc);
    }
}