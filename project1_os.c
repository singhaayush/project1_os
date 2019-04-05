#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<pthread.h>
pthread_mutex_t l;
int pen=0;
int paper=1;
int quespaper=1;

void *teacher()
{  int count=0;
   while(1)
    
   {
      pthread_mutex_lock(&l);
	   count++;
       if(count%3==0)
	    {
	     pen=paper=1;
         quespaper=0;	
        }
      if(count%3==1)
        {
          paper=quespaper=1;
           pen=0;
	    }
       if(count%3==2)
        {
	    pen=quespaper=1;
          paper=0;
	    }
        pthread_mutex_unlock(&l);
    
   }
}
void *student1(void *res)
{     
        while(paper==0||quespaper==0);
        pthread_mutex_lock(&l);
      
      
	   printf("student 1 is working.... \n");
	    sleep(2);
	   printf("student 1 finished \n"); 
       pthread_mutex_unlock(&l);
  
}
void *student2(void *res)
{  
      
     while(pen==0||quespaper==0);
       pthread_mutex_lock(&l);
       printf("student 2 is working.... \n");
	    sleep(1);
	   printf("student 2 finished \n");
    	   pthread_mutex_unlock(&l); 

    

}
void *student3(void *res)
{     
       while(pen==0||paper==0);
       pthread_mutex_lock(&l);
       printf("student 3 is working.... \n");
	    sleep(3);
	   printf("student 3 finished \n"); 
      pthread_mutex_unlock(&l);

}
int main()
{
int p=10;
pthread_t t1;
pthread_mutex_init(&l,NULL);
pthread_create(&t1,NULL,teacher,NULL);
pthread_t s1,s2,s3;
pthread_create(&s1,NULL,student1,NULL);
pthread_create(&s2,NULL,student2,NULL);
pthread_create(&s3,NULL,student3,NULL);
pthread_join(t1,NULL);
pthread_join(s1,NULL);
pthread_join(s2,NULL);
pthread_join(s3,NULL);
}
