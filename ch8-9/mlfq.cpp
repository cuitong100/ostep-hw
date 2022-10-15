#include <stdio.h>

struct process
{
    char name;
    int AT; // Arrive time
    int WL; // Work length
    int TAT; //Turnaround time
    int responseTime; 
    int remainingTime;
} Q1[5], Q2[10], Q3[20]; //Three queues

int n;

void sortByArrival()
{
    struct process temp;
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (Q1[i].AT > Q1[j].AT)
            {
                temp = Q1[i];
                Q1[i] = Q1[j];
                Q1[j] = temp;
            }
        }
    }
}

void RR(process queue[], int r, int quantum1, int quantum2, int quantum3, int time) {
    process queue1[20];
    int m = 0;
    if(r <= 0) return;
    for (int i = 0; i < r; i++){
        if (queue[i].remainingTime <= quantum3) {
            time += queue[i].remainingTime;
            queue[i].remainingTime = 0;
            queue[i].TAT = time - queue[i].AT;
            printf("\n%c\t\t\t%d\t\t\t%d", queue[i].name, queue[i].responseTime, queue[i].TAT);
        } else {
            time += quantum3;
            queue[i].remainingTime -= quantum3;
            queue1[m].WL = queue[i].remainingTime;
            queue1[m].remainingTime = queue1[m].WL;
            queue1[m].name = queue[i].name;
            queue1[m].AT = queue[i].AT;
            queue1[m].responseTime = queue[i].responseTime;
            m++;
        }
    }
    return RR(queue1, m, quantum1, quantum2, quantum3, time);
}

int main()
{
    int i, j, k = 0, r = 0, time = 0, quantum1 = 5, quantum2 = 10, quantum3 = 20, flag = 0;
    char c;
    printf("Enter no of processes:");
    scanf("%d", &n);
    for (i = 0, c = 'A'; i < n; i++, c++)
    {
        Q1[i].name = c;
        printf("Enter the arrival time process %c: ", Q1[i].name);
        scanf("%d", &Q1[i].AT);
        printf("Enter work length of process %c: ", Q1[i].name);
        scanf("%d", &Q1[i].WL);
        Q1[i].remainingTime = Q1[i].WL;
    }

    sortByArrival();
    time = Q1[0].AT;


    printf("Process end in first queue following RR with qt = 5");
    printf("\nProcess\t\t\tReponse Time\t\tTurnarround Time\t\t");
    for (int i = 0; i < n; i++){
        if (Q1[i].remainingTime <= quantum1) {
            time += Q1[i].remainingTime;
            Q1[i].remainingTime = 0;
            Q1[i].responseTime = time - Q1[i].AT - Q1[i].WL;
            Q1[i].TAT = time - Q1[i].AT; 
            printf("\n%c\t\t\t%d\t\t\t%d", Q1[i].name, Q1[i].responseTime, Q1[i].TAT);

        } else {
            if (Q1[i].AT < time) Q2[k].responseTime = time - Q1[i].AT;
            else {
                if(i > 0 && Q1[i - 1].remainingTime == 0) time = Q1[i].AT;
                Q2[k].responseTime = 0;
                }
            time += quantum1;
            Q1[i].remainingTime -= quantum1;
            Q2[k].WL = Q1[i].remainingTime;
            Q2[k].remainingTime = Q2[k].WL;
            Q2[k].name = Q1[i].name;
            Q2[k].AT = Q1[i].AT;
            k ++;
            flag = 1;
        }
    }

    if (flag == 1){
        printf("\nProcess end in second queue following RR with qt = 10");
        printf("\nProcess\t\t\tReponse Time\t\tTurnarround Time\t\t");
    }

    for (int i = 0; i < k; i++){
        if (Q2[i].remainingTime <= quantum2){
            time += Q2[i].remainingTime;
            Q2[i].remainingTime = 0;
            Q2[i].TAT = time - Q2[i].AT;
            printf("\n%c\t\t\t%d\t\t\t%d", Q2[i].name, Q2[i].responseTime, Q2[i].TAT);

        } else {
            time += quantum2;
            Q2[i].remainingTime -= quantum2;
            Q3[r].WL = Q2[i].remainingTime;
            Q3[r].remainingTime = Q3[r].WL;
            Q3[r].name = Q2[i].name;
            Q3[r].AT = Q2[i].AT;
            Q3[r].responseTime = Q2[i].responseTime;
            r++;
            flag = 2;
        }
    }

    if (flag == 2){
        printf("\nProcess end in third queue following RR with qt = 20");
        printf("\nProcess\t\t\tReponse Time\t\tTurnarround Time\t\t");
    }
    if (r > 0) RR(Q3, r, quantum1, quantum2, quantum3, time);
}
