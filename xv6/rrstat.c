#include "types.h"
#include "user.h"

// Round Robin Statistics
int main(int argc, char *argv[])
{
    if(argc!=2){
        printf(1, "error: expect 1 arg, but have %d arg(s)\n",argc-1);
	//exit();
    }
    int num=atoi(argv[1]);
    if (num>20)
    {
        printf(1, "error: process number is too large, expect at most 20 processes but have %d processes\n",argc);
        //exit();
    }
    
    int pid=0, retime_avg=0, rutime_avg=0, sltime_avg=0;
    int creation_index = 0,round = 30;

    // create num childs
    while (creation_index < num)
    {

        if ((pid = fork()) == 0){
            break;
        }
        creation_index++;
    }

    // in the parent process we calculate the avg time
    if ( pid > 0 )
    {
        creation_index = 0;
        int retime , rutime, sltime;

        // wait for num childs to exit 
        while ( creation_index < num){
            pid = waitSch(&rutime,&retime,&sltime);
            printf(1, "pid index : %d \n", pid);
            printf(1, "child's waiting time : %d , running time: %d and sleep time: %d \n", retime, rutime,
                       sltime);
            retime_avg = retime_avg + retime;
            rutime_avg = rutime_avg + rutime;
            sltime_avg = sltime_avg + sltime;
            creation_index++;
        }

        // print the summary
        printf(1," \nstatistics: \nwait: %d , running: %d and sleep: %d \n", retime_avg/num, rutime_avg/num, sltime_avg/num);
        exit();
    }

    // in the child process we simply increase value
    else {
        creation_index = 0;
        while(creation_index <= 10000000 && 0 < round)
        {
            if(creation_index == 10000000){
	        round--;
                creation_index = 0;
            }
            creation_index++;	    
        }
	exit();
    }
}
