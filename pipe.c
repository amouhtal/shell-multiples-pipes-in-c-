#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include<sys/wait.h>
#define nbrofpipes 3
/*
 * loop over commands by sharing
 * pipes.
 */
 
 int ft_p(char ***cmd, int fd[2], pid_t pid,int in, int out )
 {
   				/* Backup */
	
	pipe(fd);
	if ((pid = fork()) == -1) {
		perror("fork");
		exit(1);
	}
	else if (pid == 0) {
	dup2(in, 0);
	    close(fd[0]);
		if (*(cmd + 1) != NULL) {
			dup2(fd[1], 1);
			out = fd[1];
		}
		return 2;
	//	exit(1);
	}
	else
	{
		wait(NULL); 		/* Collect childs */
		close(fd[1]);
		in = fd[0];
		//dup2(in, 0);
		return 1;
		//cmd++;
	}
}

static void pipeline(char ***cmd)
{
   
    int commandc = 0;
    int pipefds[nbrofpipes];
    pid_t pid;
    
    for( i = 0; i < nbrofpipes; i++ ){
        if( pipe(pipefds + i*2) < 0 )
        {
            exit(0);
        }
    }
    
    while (*cmd != NULL)
    {
        pid = fork();
        if( pid == 0 ){
            /* child gets input from the previous command,
                if it's not the first command */
        if(*(cmd - 1) != NULL)
        {
            if(dup2(pipefds[(commandc-1)*2], 0) < 0)
            {
                exit(0);
            }
        }
            /* child outputs to next command, if it's not
                the last command */
        if(*(cmd + 1) != NULL)
        {
            if( dup2(pipefds[commandc*2+1], 1) < 0 )
            {
                    exit(0);
            }
        }
        //close all pipe-fds
        execvp((*cmd)[0], *cmd);
       // perror and exit
        }
        else if( pid < 0 )
        {
            exit(0);
        }
        cmd++;
        commandc++;
       
    }
    for( i = 0; i < 2 * num-pipes; i++ )
    {
        close( pipefds[i] );
    }
}

/*
 * Compute multi-pipeline based
 * on a command list.
 */
int main(int argc, char *argv[])
{
	char *ls[] = {"ls", "-al", NULL};
	char *rev[] = {"ls", NULL};
	char *nl[] = {"nl", NULL};
	char *cat[] = {"cat", "-e", NULL};
	char **cmd[] = {ls, rev, nl, cat, NULL};

	pipeline(cmd);

	return (0);
}