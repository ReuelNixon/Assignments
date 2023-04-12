//less value higher priority

#include<stdio.h>

struct process{
    int id;
    int arrival_time;
    int burst_time;
    int burst_time_temp;
    int priority;
    int completion_time;
    int turn_around_time;
    int waiting_time;
    int visited;
};

int main(){
    int n;
    printf("Enter no of proccess you want:");
    scanf("%d",&n);
    struct process p[n];
    printf("Enter %d arrival time, burst time and priority\n",n);
    for(int i=0; i<n; i++){
        p[i].id=i+1;
        printf("#P%d: ",i+1);
        scanf("%d %d %d",&p[i].arrival_time,&p[i].burst_time,&p[i].priority);
        p[i].visited=0;
        p[i].burst_time_temp=p[i].burst_time;
    }
    int ans=0;
    for(int j=0; j<n;){
        int mn,idx;
        mn=idx=1000000000;
        for(int i=0; i<n; i++){
            if(p[i].visited==0){
                if(ans>=p[i].arrival_time && mn>p[i].priority){
                    mn=p[i].priority;
                    idx=i;
                }
                else if(ans>=p[i].arrival_time && mn==p[i].priority){
                    if(p[idx].arrival_time>p[i].arrival_time){
                        mn=p[i].priority;
                        idx=i;
                    }
                }
            }
        }
        if(idx==1000000000){
            ans++;
        }else{
            ans++;
            p[idx].burst_time--;
            if(p[idx].burst_time==0){
                j++;
                p[idx].visited=1;
                p[idx].completion_time=ans;
            }
        }
    }
    float awt=0,atat=0;
    printf("\nID\tA.T\tB.T\tC.T\tTAT\tWT");
    for(int i=0; i<n; i++){
        p[i].turn_around_time=p[i].completion_time-p[i].arrival_time;
        p[i].waiting_time=p[i].turn_around_time-p[i].burst_time_temp;
        atat+=p[i].turn_around_time;
        awt+=p[i].waiting_time;
    }
    atat=atat/n;
    awt=awt/n;
    for(int i=0; i<n; i++){
        printf("\n");
        printf("P%d\t",p[i].id);
        printf("%d\t",p[i].arrival_time);
        printf("%d\t",p[i].burst_time_temp);
        printf("%d\t",p[i].completion_time);
        printf("%d\t",p[i].turn_around_time);
        printf("%d\t",p[i].waiting_time);
    }

    printf("\nAverage turnaround time is %.1f",atat);
    printf("\nAverage waiting time is %.1f\n",awt);
    return 0;
}

/*
4 2 2 
1 1 4
0 8 4
3 4 1
2 5 2
*/