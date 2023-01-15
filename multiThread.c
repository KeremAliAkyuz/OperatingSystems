#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <math.h>

float total=0;
int threadNo=0;
int travelledLines=-1;
double inputs[1000];
sem_t s;
void *func(void* var)
{
int *id = (int *)var;
float value;
sem_wait(&s);
threadNo=threadNo+1;
for(int i=0;i<*id;i++){
travelledLines=travelledLines+1;
printf("Thread %d reads %d. line. The value is %.2f ",threadNo,travelledLines+1,inputs[travelledLines]);
printf("\n");
total=total+inputs[travelledLines];
}
printf("Shared Resource: %.2f",total);
printf("\n");
sem_post(&s);
}

int main()
{
sem_init(&s,0,1);
int lines=0;
double input;
while(scanf("%lf", &input) != EOF)
{
inputs[lines]=input;
lines=lines+1;
}

pthread_t tid;
double restf=(double)lines/5;
int restHigher=ceil(restf);
int restLower=floor(restf);

double tot;
for(int i=1;i<6;i++){
tot=(double)lines/(6-i);
if(tot>restLower){
    lines=lines-restHigher;
    pthread_create(&tid,NULL,func,(void*)&restHigher);
    pthread_join(tid,NULL);
} 
else{
    lines=lines-restLower;
    pthread_create(&tid,NULL,func,(void*)&restLower);
    pthread_join(tid,NULL);
}    

}
pthread_exit(NULL);
return 0;
}
