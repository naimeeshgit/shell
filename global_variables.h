int exit_num;
int jobs_in_bg;

struct jobs
{
    int pid;
    char command[10000];
    int job_id;
    char job_run_status;
};

struct jobs job_list[10000];

int jobs_in_fg;
struct jobs_in_fg 
{
    int pid;
    char command[10000];
    int job_id;
    char job_run_status;
};

struct jobs_in_fg job_list_fg[10000];

pid_t shell_pid ;


