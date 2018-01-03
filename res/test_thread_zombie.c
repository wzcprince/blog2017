


#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>    // for socket
#include <stdio.h>        // for printf
#include <stdlib.h>        // for exit
#include <string.h>        // for bzero

#include <netinet/tcp.h>  // for SOL_TCP

#include <unistd.h> // for usleep
#include <time.h> // for nanosleep

#include <pthread.h>
#include <errno.h>


/* æ≤Ã¨TLB±‰¡ø */
__thread uintptr_t static_tls = 0x8888;

void* new_thread_routine(void* param)
{
	static_tls = 0x6666;
	printf ("new thread's are running static_tls %p\n", (void *)static_tls );
    return (void*)static_tls;
}

void sleep_second(unsigned sec)
{
	//usleep(1000); // obsolete  https://linux.die.net/man/3/usleep
    struct timespec interval;
    interval.tv_sec = sec; // √Î
    interval.tv_nsec = 0; // nano ƒ…√Î
    struct timespec remain = {0,0};
    
    while (-1 == nanosleep(&interval, &remain) && errno == EINTR)
    {
        printf ("nanosleep is interrupted by a signal handler\n");
        interval = remain;
    }
    
}

#define thread_count 10000
pthread_t arr_thread[thread_count];

int main(int argc, char **argv)
{
    void* result = NULL;
    
	printf ("stage 1 main thread create slave threads \n");
    for (int i = 0; i<thread_count; i++)
    {
        pthread_create(arr_thread + i, NULL, new_thread_routine, NULL);
    }
    
	printf ("stage 2 main thread sleeping\n");
    sleep_second(15);

	printf ("stage 3 main thread start pthread_join\n");
    
    for (int i = 0; i<thread_count; i++)
    {
        pthread_join(arr_thread[i], &result);
    }

	printf ("stage 4 main thread end pthread_join and sleep again\n");
    sleep_second(15);    
    
	printf ("stage 5 main thread exit\n");

	
}


