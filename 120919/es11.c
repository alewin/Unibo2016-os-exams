#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
 
#define BUFSIZE 1024
 
long int n = 0;
 
void handler(int sig_num){
 
	signal(SIGUSR1, handler);
	fprintf(stderr, "\n%ld Bytes copied until now\n", n);
 
}
 
int main(){
 
	int nread, nwritten,
	    i = 0;
	char buffer[BUFSIZE],
	     cool_gui[] = "-\\|/";
 
	signal(SIGUSR1, handler);
	fprintf(stderr, "Copying   ");
 
	while( (nread = read(STDIN_FILENO, buffer, BUFSIZE)) != 0 ){
		if(nread < 0){
			perror("Read error: ");
			exit(EXIT_FAILURE);
		}
 
		nwritten = write(STDOUT_FILENO, buffer, nread);
                if(nwritten < 0){
                        perror("Write error: ");
                        exit(EXIT_FAILURE);
                }
 
		n += nwritten;
		fprintf(stderr, "\b\b%c ",cool_gui[i%4]);
		(i == INT_MAX) ? (i=0) : (i++); 	
	}
 
	fprintf(stderr, "\nDone\n");
 
	return EXIT_SUCCESS;
 
}