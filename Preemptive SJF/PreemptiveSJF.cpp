#include <iostream>
#include <algorithm> 
#include <iomanip>
#include <string.h> 
#include <bits/stdc++.h>
using namespace std;

int n;


struct process{
	
    int pNum;
    int burstTime;
    int arrivalTime;
}p[10];


bool burstTimeSort(process a,process b){
    return a.burstTime < b.burstTime; 
}

bool arrivalTimeSort(process a,process b){
    return a.arrivalTime < b.arrivalTime; 
}

void dispGanttChart(process p[],int n){
	
	int temp=0;
	for (int i=0 ; i<n ; i++){
		if (p[i].arrivalTime == 0 ){
			temp = i ;
			break;
		}
	}
			
    sort(p,p+n,arrivalTimeSort);
    sort(p,p+n,burstTimeSort);
	int Total_time=0;
    int i ;
    int j,Total_array[n];
    for(i=0;i<n;i++){
        j=i;
        while(p[j].arrivalTime<=Total_time&&j!=n){
            j++;
        }
        sort(p+i,p+j,burstTimeSort);
        Total_array[i]=Total_time;
        Total_time+=p[i].burstTime;
    }
    Total_array[i] = Total_time;

    cout <<endl;
    cout << "        Gantt Chart"<< endl;
    cout << "============================="<< endl << endl ;

	cout<<"   P"<< temp +0 <<"    |" ;
	for(int i=0;i<n;i++){
		cout<<"   P"<<p[i].pNum <<"    |"; 
	}
	cout<<endl;
	
	for (i=0; i<n+1; i++)
    {
        cout << Total_array[i] << "        ";
    }
}

void findTATime(process p[],int n, int waitingTime[], int turnaroundTime[]){
	for (int i=0; i<n ; i++){
		turnaroundTime[i]=p[i].burstTime+ waitingTime[i];
	}	
}

void findWTime(process p[],int n, int waitingTime[]){
	int responseTime[n];
	for (int i = 0; i < n; i++)
	responseTime[i] = p[i].burstTime;
   	int complete = 0;
	int t= 0;
	int min = 10000000;
 	int shortest = 0;
	int finishTime;
   	bool check = false;
   	
   	while (complete != n) {
      for (int j = 0; j < n; j++) {
         if ((p[j].arrivalTime <= t) && (responseTime[j] < min) && responseTime[j] > 0) {
            min = responseTime[j];
            shortest = j;
            check = true;
         }
      }
      if (check == false) {
        t++;
        continue;
      }
      
      responseTime[shortest]--;
      min = responseTime[shortest];
      if (min == 0)
        min = 10000000;
        if (responseTime[shortest] == 0) {
        	complete++;
            check = false;
            finishTime = t + 1;
            waitingTime[shortest] = finishTime-p[shortest].burstTime-p[shortest].arrivalTime;
            if (waitingTime[shortest] < 0)
               waitingTime[shortest] = 0;
        }
        t++;
   }
}



void find_AVGtime(process p[], int n){
	int waitingTime[n];
	int turnaroundTime[n];
	int total_waitingTime=0;
	int total_turnaroundTime=0;
	
	findWTime(p,n,waitingTime);
	findTATime(p, n, waitingTime, turnaroundTime);
	cout << "Process " << " Burst time " << "   Waiting time " << " Turn around time\n";
   	for (int i = 0; i < n; i++) {
      	total_waitingTime = total_waitingTime + waitingTime[i];
      	total_turnaroundTime = total_turnaroundTime + turnaroundTime[i];
      	cout << " " << p[i].pNum << "\t\t" 
		  << p[i].burstTime << "\t\t " << waitingTime[i] 
		  << "\t\t " << turnaroundTime[i] << endl;
  	}
   	cout << endl;
	cout << "Average waiting time = " << (float)total_waitingTime / (float)n << endl ; 
	cout << "Average turn around time = " << (float)total_turnaroundTime / (float)n << endl;
}



int main(){
	
	cout << "==========================================================" << endl;
    cout << "               PREEMPTIVE SJF SIMULATION                  " << endl;
    cout << "==========================================================" << endl;
	struct process p[10];
	

	cout<<"Number of Processes: ";
    cin>>n;
    cout << " " << endl;
	
	for(int i = 0; i < n; i++) {
        cout<<"Enter arrival time of P"<<i<<": ";
        cin>>p[i].arrivalTime;
        
        cout<<"Enter burst time of P"<<i<<": ";
        cin>>p[i].burstTime;
        p[i].pNum = i+1;
        cout<<endl;
    }
	
	find_AVGtime(p , n );
	
	dispGanttChart(p, n);

	
	return 0;
	

}
