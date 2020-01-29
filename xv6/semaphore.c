struct semaphore{
    int value,begin,end;
    struct spinlock lk;
    struct proc *wait_list[5];
};

void sem_init(struct semaphore *s,int value){
    s->value=value;
    s->begin=s->end=0;
}

void sem_wait(struct semaphore *s){
    struct proc *p=myproc();
    aquire(&s->lk);
    s->value--;
    if(s->value<0){
        s->wait_list[s->end]=p;
        s->end=(s->end+1)%5;
        sleep(p,&s->lk);
    }
    release(&s->lk);
}

void sem_signal(struct semaphore *s){
    aquire(&s->lk)
    s->value++;
    if(s->value<=0){
        wakeup(s->wait_list[s->begin]);
        s->begin=(s->begin+1)%5;
    }
    release(&s->lk);
}

semaphore chopsticks[5];

void philo_init(){
    for(int i=0;i<5;i++){
        sem_init(&chopsticks[i],1);
    }
}

void philo(int i){
    do{
        if(i%2){
            sem_wait(chopstick[i]);
            sem_wait(chopstick[(i+1)%5]);
        }
        else{
            sem_wait(chopstick[(i+1)%5]);
            sem_wait(chopstick[i]);
        }
        //eat
        sem_signal(chopstick[i]);
        sem_signal(chopstick[(i+1)%5]);
        //think
    }while(true);
}