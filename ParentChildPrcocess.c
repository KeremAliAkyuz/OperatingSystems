#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/ipc.h>
#include  <sys/types.h>
#include  <sys/shm.h>

void  ClientProcess(int []);


void  main(int  argc, char *argv[])
{
     int    ShmID;
     int    *ShmPTR;
     pid_t  pid;
     int    status;
     int sumNumber;
     int array[5];

     
     for(int i=0;i<4;i++)
     {
     scanf("%d",&array[i]);
     }
     
     

     ShmID = shmget(IPC_PRIVATE, 4*sizeof(int), IPC_CREAT | 0666);
    
     printf("Server has received a shared memory of four integers...\n");

     ShmPTR = (int *) shmat(ShmID, NULL, 0);
   
     printf("Server has attached the shared memory...\n");

     ShmPTR[0] = array[0];
     ShmPTR[1] = array[1];
     ShmPTR[2] = array[2];
     ShmPTR[3] = array[3];
     printf("Server has filled %d %d %d %d in shared memory...\n",
            ShmPTR[0], ShmPTR[1], ShmPTR[2], ShmPTR[3]);
     
     sumNumber=ShmPTR[0]+ShmPTR[1]+ShmPTR[2]+ShmPTR[3];
     ShmPTR[4]=sumNumber;
     
     printf("Server is about to fork a child process...\n");
     fflush(stdout);
     pid = fork();
  
     if (pid == 0) {
          ClientProcess(ShmPTR);
          exit(0);
     }

     wait(&status);
     printf("Server has detected the completion of its child...\n");
     
     printf("Parent sum of shared memory %d \n",ShmPTR[4]);
     shmdt((void *) ShmPTR);
     printf("Server has detached its shared memory...\n");
     shmctl(ShmID, IPC_RMID, NULL);
     printf("Server has removed its shared memory...\n");
     printf("Server exits...\n");
     exit(0);
}

void  ClientProcess(int  SharedMemory[])
{
     printf("   Client process started\n");
     printf("   Client found %d %d %d %d in shared memory\n",
                SharedMemory[0], SharedMemory[1], SharedMemory[2], SharedMemory[3]);
     printf("   Client sum of shared integer values %d \n",SharedMemory[4]);           
     printf("   Client is about to exit\n");
}


