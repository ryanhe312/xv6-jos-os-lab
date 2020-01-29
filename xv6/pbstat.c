#include "types.h"
#include "user.h"

// Round Robin Statistics
int main(int argc, char *argv[])
{
    if(argc!=2){
        printf(1, "error: expect 1 arg, but have %d arg(s)\n",argc-1);
	//exit();
    }
    int num=atoi(argv[1])*4;
    if (num>20)
    {
        printf(1, "error: process number is too large, expect at most 20 processes but have %d processes\n",argc);
	//exit();
    }
    
    int pid=0, retime_avg[4]={0}, rutime_avg[4]={0}, sltime_avg[4]={0};
    int creation_index = 0,round = 30;

    // create num childs
    while (creation_index < num)
    {

        if ((pid = fork()) == 0){
            break;
        }
        setPriority(pid,pid%4+1);
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
            
            retime_avg[pid%4] = retime_avg[pid%4] + retime;
            rutime_avg[pid%4] = rutime_avg[pid%4] + rutime;
            sltime_avg[pid%4] = sltime_avg[pid%4] + sltime;
            creation_index++;
        }

        // print the summary
        for (int i = 0; i < 4; i++)
        {
            printf(1,"\npriority[%d]: \nwait: %d , running: %d and sleep: %d\n",i+1, retime_avg[i]*4/num, rutime_avg[i]*4/num, sltime_avg[i]*4/num);
        }
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
