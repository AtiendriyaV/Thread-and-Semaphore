#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdlib.h>
#include<stdio.h>

union semun {
               int              val;    /* Value for SETVAL */
               struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
               unsigned short  *array;  /* Array for GETALL, SETALL */
               struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
           }a,b;

int main(int argc, char *argv[])
{
	int id,val,i;
	unsigned short arr[]={1,1,1,1,1};
	key_t k = 1012;	
	a.array=arr;	
	id= semget(k,  5, IPC_CREAT|0777);
	
	if (id == -1)
	{
		write(1, "Create Error", 12);
		exit(0);
	}
	
	val= semctl(id, 5, SETALL, a);

	if (val <0 )
	{
		write(1, "Set Error", 10);
		exit(0);
	}
	
	for(i=0; i< 5; i++)
	{
		val= semctl(id,i, GETVAL, b);

		if (val <0 )
		{
			write(1, "Get Error", 10);
			exit(0);
		}
	
		printf("\n Sem Val at %d position is %d", i,val);	
	}
}
        
// (0,4) (4,3) (3,2) (2, 1) (1,0) 
