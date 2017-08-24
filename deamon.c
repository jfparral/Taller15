
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
void deamon()
{
    if (( pid = fork()) < 0) {
       perror("fork error");
    } else if (pid == 0) { // child 
        umask(0);
    } else {
        //Atrapamos la señal en el padre
        signal(SIGTSTP,catch);
} 
int main()
{
    return 0;    
}
