#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define tam 100
int main(int argc, char* argv[])
{
    FILE *fp= NULL;
    FILE *cpu= NULL;
    char *buf= (char*) malloc(sizeof(char)*tam);
    memset(buf,0,sizeof(char)*tam);
    pid_t process_id = 0;
    pid_t sid = 0;
    // Create child process
    process_id = fork();
    // Indication of fork() failure
    if (process_id < 0)
    {
        printf("fork failed!\n");
        // Return failure in exit status
        exit(1);
    }
    // PARENT PROCESS. Need to kill it.
    if (process_id > 0)
    {
        printf("process_id of child process %d \n", process_id);
        // return success in exit status
        exit(0);
    }
    //unmask the file mode
    umask(0);
    //set new session
    sid = setsid();
    if(sid < 0)
    {
        // Return failure
        exit(1);
    }
    // Change the current working directory to root.
    chdir(".");
    // Close stdin. stdout and stderr
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    // Open a log file in write mode.
    fp = fopen ("log_cpu.log", "w+");
    
    while (1)
    {
        //Dont block context switches, let the process sleep for some time
        sleep(5);
        cpu = popen("top -bn2 | grep '%Cpu' | tail -1", "r");
        fread(buf,tam,1, cpu);
        //printf("buffer: %s", buf);
        //fprintf(fp, buf);
        fwrite(buf, strlen(buf),1,fp );
        fflush(fp);
        // Implement and call some function that does core work for this daemon.
        memset(buf,0,sizeof(char)*tam);
    }
    fclose(fp);
    return (0);
}
