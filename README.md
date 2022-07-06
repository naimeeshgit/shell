# HOW TO RUN?
-> type make and then hit enter
-> now execute ./a.out to run the shell



# Implementations:
1. cd 
2. pwd
3. echo
4. ls
5. foreground/background process
6. pinfo
7. exit
8. repeat
9. redirection
10. piping
11. piping + redirection
12. jobs
13. sig
14. ctrl + z
15. ctrl + c
16. history


# The code is well commented , comments are themselves very much explanatory

- The directory from which the shell is invoked is the home directory of the shell.



# Corresponding files:

The zip contains:
1. makefile
2. README.md
3. files with the implementations


- Files:
0. basic header file -> header.h
1. file from which the shell is run -> shell.c 
2. for displaying/giving prompts -> prompt.h, prompt.c
3. cd -> cd.c, cd.h
4. pwd -> pwd.c, pwd.h
5. echo -> echo.c, echo.h
6. ls -> ls.c , ls.h
7. foreground process -> foreground.c, foreground.h
8. background process -> background.c, background.h
9. repeat -> repeat.c, repeat.h
10. pinfo -> pinfo.c, pinfo.h
11. helpful in command execution -> strcompare.c, strcompare.h
12. redirection related -> io.c, io.h
13. piping related -> piping.c, piping,h
14. jobs related -> jobs.c, jobs.h
15. sig related -> signal.c, signal.h, shell.c 
16. global variables -> global_variables.h

- Other implementations are : history, exit

# Description
- shell.c calls strcompare fn for each command typed in the terminal
- strcompare fn calls various other fns
- almost each fn has its own header and .c file
- the code has been well commented for explanatory purposes
- prompt fn provides prompts and displays <username@system_name:curr_dir>


# redirection : possible operations:
1. >
2. >>
3. <
4. < >
5. < >>
