#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
/*
This program provides a possible solution for first readers writers problem using mutex and semaphore.
I have used 10 readers and 5 producers to demonstrate the solution. You can always play with these values.
*/

sem_t wrt;
pthread_mutex_t mutex;
int cnt = 1;
int numreader = 0;

void *writer(void *wno)
{ 

  int count = 0;
  while(count < 10) {
    sleep(1);
    sem_wait(&wrt);
    cnt = cnt*2;
    printf("Writer %d modified cnt to %d\n",(*((int *)wno)),cnt);
    sem_post(&wrt);
    count++;
    }
}
void *reader(void *rno)
{   
    // Reader acquire the lock before modifying numreader
    // printf("reader is trying to enter\n");
    int count = 0;
    while(count < 10) {
    sem_wait(&wrt);
    pthread_mutex_lock(&mutex);
    // printf("reader is entered\n");
    
    numreader++;
    if(numreader == 1) {
        sem_wait(&wrt); // If this id the first reader, then it will block the writer
    }
    pthread_mutex_unlock(&mutex);
    // Reading Section
    printf("Reader %d: read cnt as %d\n",*((int *)rno),numreader);

    // Reader acquire the lock before modifying numreader
    // printf("reader2 is trying to enter\n");
  
    pthread_mutex_lock(&mutex);
    numreader--;
    if(numreader == 0) {
        sem_post(&wrt); // If this is the last reader, it will wake up the writer.
    }
    pthread_mutex_unlock(&mutex);
    // printf("reader2 released\n");
      count++;
    sem_post(&wrt);
      
    }
}

int main()
{   

    pthread_t read,write;
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt,0,1);

    int a[10] = {1,2,3,4,5,6,7,8,9,10}; //Just used for numbering the producer and consumer
  pthread_create(&write, NULL, (void *)writer, (void *)&a[0]);
  
    // for(int i = 0; i < 10; i++) {
        pthread_create(&read, NULL, (void *)reader, (void *)&a[0]);
    // }
  
    // for(int i = 0; i < 5; i++) {
    //     pthread_create(&write[i], NULL, (void *)writer, (void *)&a[i]);
    // }


     pthread_join(read, NULL);

    // for(int i = 0; i < 5; i++) {
    //     pthread_join(write[i], NULL);
    // }
    pthread_join(write, NULL);
  
    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
    
}
