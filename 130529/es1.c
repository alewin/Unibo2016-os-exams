// Scrivere un programma testeventfd che faccia uso della
// system call eventfd.In particolare il programma deve
// eseguire una fork, quando l'utente digita un numero
// letto dal processo padre, il processo figlio deve
// stampare un numero uguale di x.
//(negli esempi e' riportato in grassetto cio' che l'utente digita).
//$ testeventfd 3 xxx
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/eventfd.h>
#include <unistd.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/eventfd.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int efd, i;
  uint64_t u;
  long long unsigned int val;

  ssize_t s;
  efd = eventfd(0, 0);

  switch (fork()) {
  case 0: // child
    s = read(efd, &val, sizeof(long long unsigned int));
    for (i = (int)val; i > 0; i--)
      printf("x\n");
    exit(EXIT_SUCCESS);
  default: // parent
    while (1) {
      printf("Inserisci un intero diverso da 0: \n");
      scanf("%llu", &val);
      s = write(efd, &val, sizeof(long long unsigned int));
      exit(EXIT_SUCCESS);
    }
  }

  return 0;
}

/*

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/eventfd.h>
#include <unistd.h>

#define BUFFSIZE 10

int main(int argc, char *argv[]){
        int efd , n , i;
        uint64_t a , b;
        if ( ( efd = eventfd( 0 , EFD_SEMAPHORE ) ) < 0 )
                exit( 1 );
        if ( fork() > 0 ){
                while ( 1 ) {
                uint64_t a;
                scanf( "%lld" , &a );
                write( efd , &a , sizeof( a ) );
                                }
                }
        else {
                while ( 1 ) {
                uint64_t b;
                read( efd , &b , sizeof( b ) );
                printf( "x\n" );
                }
        }
}


int efd, i;
uint64_t u;
long long unsigned int val;

ssize_t s;
efd = eventfd(0, 0);

switch (fork()) {
case 0: // child
  s = read(efd, &val, sizeof(long long unsigned int));
  for (i = (int)val; i > 0; i--)
    printf("x\n");
  exit(EXIT_SUCCESS);
default: // parent
  printf("Inserisci un intero diverso da 0: \n");
  scanf("%llu", &val);
  s = write(efd, &val, sizeof(long long unsigned int));
  exit(EXIT_SUCCESS);
}

return 0;
}
*/
