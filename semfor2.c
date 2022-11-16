#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#define a 4 

void printInt(int val)
{
	char buf[6];
	int len;
	len =sprintf(buf," %d",val);
	write(1,buf,len);
}
	time_t t;

int main(int argc, char *argv[])
{
	int len,val,i=0;
	int left,right,id;
	   //Variable Declaration
       int Numbers[a], p;
	char buf[30];
	//a=0;
	//b=4;
	key_t k = 100;	 //key_t k
 	struct  sembuf p1;//declaration of semaphore structure 
 	
 	id= semget(k, 1, IPC_CREAT|0777);
	if (id ==-1 )
	{
		write(1, "Refer Error", 11);
		exit(0);
	}	
	
	// id is variable declared to the int semget systemcall
	       //1 is number of semaphore to used //  
	       //checks the value of semaphore 0,1,-1//
	       // IPC_CREAT is the int flag value 
	
	
	while (1)
	{
		// Entry section 
		write(1,"\n",1);		
		write(1,"=====In Entry====", 18);
		write(1,"\n",1);
		p1.sem_num=0;  /* semaphore number */
		p1.sem_op=-1;   /* semaphore operation */
		p1.sem_flg=0;  /* operation flags */
		val=semop(id,&p1,1);
		
        
		if (val == -1 )
		{
			write(1, "Wait operation Failed", 22);
			exit(0);
		}
		
		write(1,"\n",1);
		val= semctl(id,0, GETVAL, NULL);
		write(1,"Semaphore value : ",19);
		printInt(val);
		
		write(1,"\n",1);
		write(1,"In Critical section : ", 19);
		write(1,"\n",1);
		write(1,ctime(&t),15);
		write(1,"\n",1);
		 
		
		
            {
           

	     // Read Numbers Using scanf and for Loop.
	     printf("Value at  : \n");
             for (p = 0; p <= a; p++)
            {
		printf("Enter the Number : %d  : ", (p+1));
                scanf("%d", &Numbers[p]);
            }

	    // Print Numbers Using for Loop.
            printf("\nPrinting Numbers Using for Loop: \n");
            for (p = 0; p <= a; ++p)
           {
              printf("hello in critical section number : %d\n", Numbers[p]);
           }
           }
           
           read(0,buf,1);
		
		
		// Exit section 
		p1.sem_num=0;  /* semaphore number */
		p1.sem_op=+1;   /* semaphore operation */
		p1.sem_flg=0;  /* operation flags */
		
		write(1,"\n",1);		
		write(1,"=====In Exit====", 17);
		write(1,"\n",1);
		
		val=semop(id,&p1,1);
		
		if (val ==-1 )
		{
			write(1, "Signal operation Failed", 24);
			exit(0);
		}
		
		write(1,"\n",1);
		val= semctl(id,0, GETVAL, NULL);
		write(1,"Semaphore value : ",19);
		printInt(val);	
			
	}
	
} 
		 
		 
		 
	
