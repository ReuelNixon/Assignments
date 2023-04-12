#include<stdio.h>

struct process{
    int id;
    int arrival_time;
    int burst_time;
    int burst_time_temp;
    int completion_time;
    int turn_around_time;
    int waiting_time;
    int visited;
    int service_time;
};

int main(){
    int n;
    printf("Enter no of proccess you want:");
    scanf("%d",&n);
    struct process p[n];
    printf("Enter %d arrival time and burst time\n",n);
    int min=1000000000,ix=-1;

    for(int i=0; i<n; i++){
        p[i].id=i+1;
        printf("#P%d: ",i+1);
        scanf("%d %d",&p[i].arrival_time,&p[i].burst_time);
        p[i].burst_time_temp=p[i].burst_time;
        p[i].visited=0;
        if(min>p[i].arrival_time){
            min=p[i].arrival_time;
            ix=i;
        }
    }

    printf("Enter time quantam:");
    int m;
    scanf("%d",&m);
    int ans=0,ii=0,jj=0;
    int bf[10000];
    bf[jj++]=ix;
    p[ix].visited=1;
    for(int j=0; j<n; ){
        int o=p[bf[ii]].burst_time_temp,sub;
        if(o>m){
            ans+=m;
            p[bf[ii]].burst_time_temp-=m;
            for(int i=0; i<n; i++){
                if(p[i].visited==0 &&p[i].arrival_time<=ans){
                    bf[jj++]=i;
                    p[i].visited=1;
                }
            }
            bf[jj++]=bf[ii];
        }else{
            ans+=o;
            p[bf[ii]].burst_time_temp-=o;
            for(int i=0; i<n; i++){
                if(p[i].visited==0 &&p[i].arrival_time<=ans){
                    bf[jj++]=i;
                    p[i].visited=1;
                }
            }
            p[bf[ii]].completion_time=ans;
            p[bf[ii]].service_time=j;
            j++;
        }
        ii++;
    }

    float awt=0,atat=0;
    for (int i = 0; i < n; i++)
    {
        p[i].turn_around_time=p[i].completion_time-p[i].arrival_time;
        p[i].waiting_time=p[i].turn_around_time-p[i].burst_time;
        atat+=p[i].turn_around_time;
        awt+=p[i].waiting_time;
    }
    atat=atat/n;
    awt=awt/n;

    printf("\nID\t A.T\t B.T\t C.T\t TAT\t WT");
    for(int i=0; i<n; i++){
        printf("\n");
        printf("P%d\t", p[i].id);
        printf("%d\t", p[i].arrival_time);
        printf("%d\t", p[i].burst_time);
        printf("%d\t", p[i].completion_time);
        printf("%d\t", p[i].turn_around_time);
        printf("%d\t", p[i].waiting_time);
    }
    printf("\nAverage turn around time: %.1f",atat);
    printf("\nAverage waiting time: %.1f\n",awt);
    return 0;
}

/*
4 2
1 1
0 8
3 4
2 5
*/
