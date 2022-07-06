#include "headers.h"
#include "ls.h"

// void ls_l_a(char **dir);

void ls(char *cmnd, char *prog_home)
{

    char *token = strtok(cmnd, " ");
    char *list_dir_flags[10000];
    int i = 0;
    int flag_l = 0;
    int flag_a = 0;

    while (token != NULL)
    {
        list_dir_flags[i] = token;
        i++;
        token = strtok(NULL, " ");
    }

    list_dir_flags[i] = NULL;

    // printf("%d\n",i);   // i = number of arguments
    // for (int j = 0; j < i; j++)
    // {

    // printf("dir/flags:%s\n",list_dir_flags[j]);  // print each argument
    // }

    char *dir_or_file[10000];

    int check_flag = 0;
    int t = 0;

    if (i == 1)
    {
        just_ls();
        // printf("just ls\n");
    }
    else
    {

        for (int j = 1; j < i; j++)
        {
            if (strcmp(list_dir_flags[j], "-l") == 0)
            {
                flag_l = 1;
                check_flag = 1;
            }
            if (strcmp(list_dir_flags[j], "-a") == 0)
            {
                flag_a = 1;
                check_flag = 1;
            }

            if (strcmp(list_dir_flags[j], "-la") == 0 || strcmp(list_dir_flags[j], "-al") == 0)
            {
                flag_l = 1;
                flag_a = 1;
                check_flag = 1;
            }

            if (check_flag == 0)
            {
                dir_or_file[t] = list_dir_flags[j];
                t++;
            }

            check_flag = 0;
        }
    }

    for (int j = 0; j < t; j++)
    {
        dir_or_file[strlen(dir_or_file[j])] = '\0';
    }

    dir_or_file[t] = NULL;
    char *dir_or_file_send[t];
    //     for (int j = 0; j < t; j++)
    //     {
    //         printf("dirorfile:%s\n", dir_or_file[j]);
    //     }
    //    printf("checkflag:%d\n", check_flag);

    //     printf("lflag:%d\n", flag_l);
    //     printf("aflag:%d\n", flag_a);

    int temp_temp_temp = 0;
    int j = 0;
    while (temp_temp_temp < t)
    {

        if (strcmp(dir_or_file[temp_temp_temp], "~") == 0)
        {
            dir_or_file_send[temp_temp_temp] = prog_home;
            dir_or_file_send[temp_temp_temp][strlen(dir_or_file_send[temp_temp_temp])] = '\0';
           //  printf("~case:%s\n", dir_or_file_send[temp_temp_temp]);

            strcpy(dir_or_file[temp_temp_temp], dir_or_file_send[temp_temp_temp]);
            dir_or_file[temp_temp_temp][strlen(dir_or_file[temp_temp_temp])] = '\0';
            temp_temp_temp++;
        }

        else if (dir_or_file[temp_temp_temp][0] == '~')
        {
            strcat(dir_or_file_send[temp_temp_temp], prog_home);
            // strcat(dir_or_file_send[temp_temp_temp], "/");
            char temporary_array_to_strcat[10000];
            for (int i = 1; i < strlen(dir_or_file[temp_temp_temp]); i++)
            {
                temporary_array_to_strcat[i - 1] = dir_or_file[temp_temp_temp][i];
            }

            temporary_array_to_strcat[strlen(dir_or_file[temp_temp_temp])] = '\0';
            strcat(dir_or_file_send[temp_temp_temp], temporary_array_to_strcat);
            dir_or_file_send[temp_temp_temp][strlen(dir_or_file_send[temp_temp_temp])] = '\0';

           //  printf("tildecase:%s\n", dir_or_file_send[temp_temp_temp]);

            strcpy(dir_or_file[temp_temp_temp], dir_or_file_send[temp_temp_temp]);
            dir_or_file[temp_temp_temp][strlen(dir_or_file[temp_temp_temp])] = '\0';
            temp_temp_temp++;
        }

        else
            temp_temp_temp++;
    }

    // printf("%d",temp_temp_temp);

    // for(int i = 0; i < t; i++)
    // {
    //     printf("dir_or_file[%d]:%s\n", i, dir_or_file[i]);
    // }

    if (flag_l == 1 && flag_a == 1)
    {
        if (t == 0)
        {
            // printf("reaching:t==0:  \n");
            char *cwd_temp = getcwd(NULL, 0);
            ls_l_a(cwd_temp, prog_home, t);
        }

        else
        {
            // printf("reaching:t>0:  \n");
            for (int i = 0; i < t; i++)
            {
                ls_l_a(dir_or_file[i], prog_home, t);
            }
        }
    }

    // ls_l
    if (flag_l == 1 && flag_a == 0)
    {
        if (t == 0)
        {
            // printf("reaching:t==0:  \n");
            char *cwd_temp = getcwd(NULL, 0);
            ls_l(cwd_temp, prog_home, t);
        }

        else
        {
            // printf("reaching:t>0:  \n");
            for (int i = 0; i < t; i++)
            {
                ls_l(dir_or_file[i], prog_home, t);
            }
        }
    }

    // ls _a
    if (flag_l == 0 && flag_a == 1)
    {
        if (t == 0)
        {
            char *cwd_temp = getcwd(NULL, 0);
            ls_a(cwd_temp, prog_home, t);
        }
        else
        {
            for (int i = 0; i < t; i++)
            {
                ls_a(dir_or_file[i], prog_home, t);
                printf("\n");
            }
        }
    }

    // ls_dir
    if (flag_l == 0 && flag_a == 0)
    {
        for (int i = 0; i < t; i++)
        {

            ls_dir(dir_or_file[i], prog_home, t);
            printf("\n");
        }
    }
}

// /// void just_ls ()                 //////////////////      ///////////////
void just_ls()
{
    DIR *dir;
    struct dirent **entry;

    char *curr_dir = getcwd(NULL, 0);

    long long int entries = scandir(curr_dir, &entry, 0, alphasort);

    if (entries < 0)
    {
        perror("scandir");
    }
    else
    {
        for (int i = 0; i < entries; i++)
        {
            if (entry[i]->d_name[0] != '.')
                printf("%s\n", entry[i]->d_name);
        }
    }
}

// // ls_dir /////////////////////////////////////// ///////////////////////////////////////

void ls_dir(char *given_dir_file, char *prog_home, int t)
{
    DIR *dir;
    struct dirent **entry;
   
    // printf("%s", given_dir_file);
    char *name_of_the_dir = strrchr(given_dir_file, '/');
    if (name_of_the_dir == NULL)
    {
        name_of_the_dir = given_dir_file;
    }
    printf("%s:\n", name_of_the_dir);

    long long int entries = scandir(given_dir_file, &entry, 0, alphasort);

    if (entries < 0)
    {
        perror("scandir");
    }
    else
    {
        for (int k = 0; k < entries; k++)
        {
            if (entry[k]->d_name[0] != '.')
                printf("%s\n", entry[k]->d_name);
        }
    }
}

// // /// ls -a // ///// /////////////// ///////////////// **************** ///

void ls_a(char *given_dir_file, char *prog_home, int t)
{

    DIR *dir;
    struct dirent **entry;
    // printf("%d",t);

    if (t > 0)
    {

        int temp_int = 0;
        char *name_of_the_dir = strrchr(given_dir_file, '/');
        if (name_of_the_dir == NULL)
        {
            name_of_the_dir = given_dir_file;
        }
        printf("%s:\n", name_of_the_dir); // print the name of the dir

        long long int entries = scandir(given_dir_file, &entry, 0, alphasort);
        if (entries < 0)
        {
            perror("scandir");
        }
        else
        {
            for (int k = 0; k < entries; k++)
            {
                printf("%s\n", entry[k]->d_name);
            }

            printf("\n");
        }
    }
    else
    {
        char *curr_dir = getcwd(NULL, 0);
        long long int entries = scandir(curr_dir, &entry, 0, alphasort);
        if (entries < 0)
        {
            perror("scandir");
        }
        else
        {
            for (int i = 0; i < entries; i++)
            {
                printf("%s\n", entry[i]->d_name);
            }
        }
    }
}

// /// ls -l /// ******************* ///////////////

void ls_l(char *given_dir, char *prog_home, int t)
{

    // (d)permission ogu - symbolic link - user - group - size - date - name

    DIR *dir;
    struct dirent **entry;

    // printf("%d", t);

    int temp_int = 0;
    if (t == 0) // if no directory is given, use current directory
    {
        char *cur_dir = getcwd(NULL, 0);                                   // get current directory
        long long int entries = scandir(cur_dir, &entry, NULL, alphasort); // scan directory
        if (entries < 0)
        {
            perror("scandir"); // error
        }
        else // if no error
        {
            // printf("reached here alpha:");
            for (int i = 0; i < entries; i++)
            {
                if (entry[i]->d_name[0] != '.')
                {

                    char ogu[15];
                    long long int symbolic_link;
                    char user[1000];
                    char group[1000];
                    long long int size;
                    char date[1000];
                    char name[1000];

                    struct stat fs;

                    // get permission
                    if (S_ISDIR(fs.st_mode))
                    {
                        strcpy(ogu, "d");
                    }
                    else
                    {
                        strcpy(ogu, "-");
                    }

                    if (fs.st_mode & S_IRUSR)
                    {
                        strcat(ogu, "r");
                    }
                    else
                    {
                        strcat(ogu, "-");
                    }

                    if (fs.st_mode & S_IWUSR)
                    {
                        strcat(ogu, "w");
                    }
                    else
                    {
                        strcat(ogu, "-");
                    }

                    if (fs.st_mode & S_IXUSR)
                    {
                        strcat(ogu, "x");
                    }
                    else
                    {
                        strcat(ogu, "-");
                    }

                    if (fs.st_mode & S_IRGRP)
                    {
                        strcat(ogu, "r");
                    }
                    else
                    {
                        strcat(ogu, "-");
                    }

                    if (fs.st_mode & S_IWGRP)
                    {
                        strcat(ogu, "w");
                    }
                    else
                    {
                        strcat(ogu, "-");
                    }

                    if (fs.st_mode & S_IXGRP)
                    {
                        strcat(ogu, "x");
                    }
                    else
                    {
                        strcat(ogu, "-");
                    }

                    if (fs.st_mode & S_IROTH)
                    {
                        strcat(ogu, "r");
                    }
                    else
                    {
                        strcat(ogu, "-");
                    }

                    if (fs.st_mode & S_IWOTH)
                    {
                        strcat(ogu, "w");
                    }
                    else
                    {
                        strcat(ogu, "-");
                    }

                    if (fs.st_mode & S_IXOTH)
                    {
                        strcat(ogu, "x");
                    }
                    else
                    {
                        strcat(ogu, "-");
                    }

                    // get symbolic link

                    symbolic_link = fs.st_nlink;

                    // get user
                     struct passwd *pd;
                pd = getpwuid(fs.st_uid);
                   

                    // get group
                     struct group *gr;
                gr = getgrgid(fs.st_gid);

                    // get size
                    size = fs.st_size;

                    // get date
                    strcpy(date, ctime(&fs.st_mtime));

                    // get name
                    strcpy(name, entry[i]->d_name);

                    // print
                    printf("%s %lld %s %s %lld %s %s\n", ogu, symbolic_link, pd->pw_name, gr->gr_name, size, date, name);
                }
            }
        }
    }
    else
    {
        long long int entries = 0;
        entries = scandir(given_dir, &entry, NULL, alphasort);
        if (entries < 0)
        {
            perror("scandir\n");
        }
        else
        {
            for (int i = 0; i < entries; i++)
            {
                if (entry[i]->d_name[0] != '.')
                {

                    char ogu[15];
                    long long int symbolic_link;
                    char user[100];
                    char group[100];
                    long long int size;
                    char date[100];
                    char name[100];

                    struct stat fs;

                    // get permission
                    if (S_ISDIR(fs.st_mode))
                    {
                        strcpy(ogu, "d");
                    }
                    else
                    {
                        strcpy(ogu, "-");
                    }

                    if (fs.st_mode & S_IRUSR)
                    {
                        strcat(ogu, "r");
                    }
                    else
                    {
                        strcat(ogu, "-");
                    }

                    if (fs.st_mode & S_IWUSR)
                    {
                        strcat(ogu, "w");
                    }
                    else
                    {
                        strcat(ogu, "-");
                    }

                    if (fs.st_mode & S_IXUSR)
                    {
                        strcat(ogu, "x");
                    }
                    else
                    {
                        strcat(ogu, "-");
                    }

                    if (fs.st_mode & S_IRGRP)
                    {
                        strcat(ogu, "r");
                    }
                    else
                    {
                        strcat(ogu, "-");
                    }

                    if (fs.st_mode & S_IWGRP)
                    {
                        strcat(ogu, "w");
                    }
                    else
                    {
                        strcat(ogu, "-");
                    }

                    if (fs.st_mode & S_IXGRP)
                    {
                        strcat(ogu, "x");
                    }
                    else
                    {
                        strcat(ogu, "-");
                    }

                    if (fs.st_mode & S_IROTH)
                    {
                        strcat(ogu, "r");
                    }
                    else
                    {
                        strcat(ogu, "-");
                    }

                    if (fs.st_mode & S_IWOTH)
                    {
                        strcat(ogu, "w");
                    }
                    else
                    {
                        strcat(ogu, "-");
                    }

                    if (fs.st_mode & S_IXOTH)
                    {
                        strcat(ogu, "x");
                    }
                    else
                    {
                        strcat(ogu, "-");
                    }

                    // get symbolic link

                    symbolic_link = fs.st_nlink;

                    // get user

                     struct passwd *pd;
                pd = getpwuid(fs.st_uid);

                    // get group

                    struct group *gr;
                gr = getgrgid(fs.st_gid);
                    // get size

                    size = fs.st_size;

                    // get date

                    strcpy(date, ctime(&fs.st_mtime));

                    // get name

                    strcpy(name, entry[i]->d_name);

                    // print

                    printf("%s %lld %s %s %lld %s %s\n", ogu, symbolic_link, pd->pw_name, gr->gr_name, size, date, name);
                }
            }
        }
    }
}

void ls_l_a(char *given_dir, char *prog_home, int t)
{

    // (d)permission ogu - symbolic link - user - group - size - date - name

    DIR *dir;
    struct dirent **entry;

    // printf("%d", t);

    int temp_int = 0;
    if (t == 0) // if no directory is given, use current directory
    {
        char *cur_dir = getcwd(NULL, 0);                                   // get current directory
        long long int entries = scandir(cur_dir, &entry, NULL, alphasort); // scan directory
        if (entries < 0)
        {
            perror("scandir"); // error
        }
        else // if no error
        {
            // printf("reached here alpha:");
            for (int i = 0; i < entries; i++)
            {
               
                char ogu[15];
                long long int symbolic_link;
                char user[1000];
                char group[1000];
                long long int size;
                char date[1000];
                char name[1000];

                struct stat fs;

                // get permission
                if (S_ISDIR(fs.st_mode))
                {
                    strcpy(ogu, "d");
                }
                else
                {
                    strcpy(ogu, "-");
                }

                if (fs.st_mode & S_IRUSR)
                {
                    strcat(ogu, "r");
                }
                else
                {
                    strcat(ogu, "-");
                }

                if (fs.st_mode & S_IWUSR)
                {
                    strcat(ogu, "w");
                }
                else
                {
                    strcat(ogu, "-");
                }

                if (fs.st_mode & S_IXUSR)
                {
                    strcat(ogu, "x");
                }
                else
                {
                    strcat(ogu, "-");
                }

                if (fs.st_mode & S_IRGRP)
                {
                    strcat(ogu, "r");
                }
                else
                {
                    strcat(ogu, "-");
                }

                if (fs.st_mode & S_IWGRP)
                {
                    strcat(ogu, "w");
                }
                else
                {
                    strcat(ogu, "-");
                }

                if (fs.st_mode & S_IXGRP)
                {
                    strcat(ogu, "x");
                }
                else
                {
                    strcat(ogu, "-");
                }

                if (fs.st_mode & S_IROTH)
                {
                    strcat(ogu, "r");
                }
                else
                {
                    strcat(ogu, "-");
                }

                if (fs.st_mode & S_IWOTH)
                {
                    strcat(ogu, "w");
                }
                else
                {
                    strcat(ogu, "-");
                }

                if (fs.st_mode & S_IXOTH)
                {
                    strcat(ogu, "x");
                }
                else
                {
                    strcat(ogu, "-");
                }

                // get symbolic link

                symbolic_link = fs.st_nlink;

                // get user
                struct passwd *pd;
                pd = getpwuid(fs.st_uid);
                
                // get group
                struct group *gr;
                gr = getgrgid(fs.st_gid);

                // get size
                size = fs.st_size;

                // get date
                strcpy(date, ctime(&fs.st_mtime));

                // get name
                strcpy(name, entry[i]->d_name);

                // print
                printf("%s %lld %s %s %lld %s %s\n", ogu, symbolic_link, pd->pw_name, gr->gr_name, size, date, name);
            }
        }
    }
    else
    {
        long long int entries = 0;
        entries = scandir(given_dir, &entry, NULL, alphasort);
        if (entries < 0)
        {
            perror("scandir\n");
        }
        else
        {
            for (int i = 0; i < entries; i++)
            {

                char ogu[15];
                long long int symbolic_link;
                char user[100];
                char group[100];
                long long int size;
                char date[100];
                char name[100];

                struct stat fs;

                // get permission
                if (S_ISDIR(fs.st_mode))
                {
                    strcpy(ogu, "d");
                }
                else
                {
                    strcpy(ogu, "-");
                }

                if (fs.st_mode & S_IRUSR)
                {
                    strcat(ogu, "r");
                }
                else
                {
                    strcat(ogu, "-");
                }

                if (fs.st_mode & S_IWUSR)
                {
                    strcat(ogu, "w");
                }
                else
                {
                    strcat(ogu, "-");
                }

                if (fs.st_mode & S_IXUSR)
                {
                    strcat(ogu, "x");
                }
                else
                {
                    strcat(ogu, "-");
                }

                if (fs.st_mode & S_IRGRP)
                {
                    strcat(ogu, "r");
                }
                else
                {
                    strcat(ogu, "-");
                }

                if (fs.st_mode & S_IWGRP)
                {
                    strcat(ogu, "w");
                }
                else
                {
                    strcat(ogu, "-");
                }

                if (fs.st_mode & S_IXGRP)
                {
                    strcat(ogu, "x");
                }
                else
                {
                    strcat(ogu, "-");
                }

                if (fs.st_mode & S_IROTH)
                {
                    strcat(ogu, "r");
                }
                else
                {
                    strcat(ogu, "-");
                }

                if (fs.st_mode & S_IWOTH)
                {
                    strcat(ogu, "w");
                }
                else
                {
                    strcat(ogu, "-");
                }

                if (fs.st_mode & S_IXOTH)
                {
                    strcat(ogu, "x");
                }
                else
                {
                    strcat(ogu, "-");
                }

                // get symbolic link

                symbolic_link = fs.st_nlink;

                // get user
                 struct passwd *pd;
                pd = getpwuid(fs.st_uid);
               

                // get group

                 struct group *gr;
                gr = getgrgid(fs.st_gid);


                // get size

                size = fs.st_size;

                // get date

                strcpy(date, ctime(&fs.st_mtime));

                // get name

                strcpy(name, entry[i]->d_name);

                // print

                printf("%s %lld %s %s %lld %s %s\n", ogu, symbolic_link, pd->pw_name, gr->gr_name, size, date, name);
            }
        }
    }
}