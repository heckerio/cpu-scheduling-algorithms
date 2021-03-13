#include<iostream>
#include<algorithm>
using namespace std;
struct Process
{
    char process[100];
    int Burst_time;
    int Arrival_time;
}
A[100];
void insert(int n)
{
    for(int i=0;i<n;i++)
    {
        cout << "Enter process : ";
        cin>>A[i].process;
        cout << "Enter arrival time : ";
        cin>>A[i].Arrival_time;
        cout << "Enter burst time : ";
        cin>>A[i].Burst_time;

        cout << endl << endl;
    }
}
bool Burst_timeSort(Process x,Process y)
{
    return x.Burst_time < y.Burst_time;
}
bool Arrival_timeSort(Process x,Process y)
{
    return x.Arrival_time < y.Arrival_time;
}
void display(int n)
{
    sort(A,A+n,Burst_timeSort);
    sort(A,A+n,Arrival_timeSort);
    int Total_time=0;
    int i ;
    int j,Total_array[n];
    for(i=0;i<n;i++)
        {
        j=i;
        while(A[j].Arrival_time<=Total_time&&j!=n){
            j++;
        }
        sort(A+i,A +j,Burst_timeSort);
        Total_array[i]=Total_time;
        Total_time+=A[i].Burst_time;
    }
    Total_array[i] = Total_time;
    float AVG_WaitingTime=0;
    float AVG_ResponseTime=0;
    float AVG_turnaround=0;
    cout<<"\n";
    cout<<"Process  Arrival-Time\t  Burst-Time\t Finishing time\tTurnaround-Time\t  Waiting-Time\n";
    for (i=0; i<n; i++)
    {
        cout <<"P"<<A[i].process << "\t\t";
        cout << A[i].Arrival_time << "\t\t";
        cout << A[i].Burst_time << "\t\t";
        cout << Total_array[i+1] << "\t\t"; //Finish
        cout << Total_array[i]-A[i].Arrival_time+A[i].Burst_time << "\t\t";//turnaround
        AVG_turnaround+=Total_array[i]-A[i].Arrival_time+A[i].Burst_time;
        cout << Total_array[i]-A[i].Arrival_time << "\t";
        AVG_WaitingTime+=Total_array[i]-A[i].Arrival_time;
        cout << "\n";
    }
    cout<<"\n\n";
    cout<<"\n----------------Gantt Chart---------------------------\n";
    for (i=0; i<n; i++)
    {
        cout <<"|  "<< "P"<< A[i].process << "   ";

    }

    cout<<"\n";
    for (i=0; i<n+1; i++)
    {
        cout << Total_array[i] << "\t";
    }

    cout<<"\n\n";
    cout<<"The average waiting time is : "<<(float)AVG_WaitingTime/(float)n<<endl;
    cout<<"The average turnaround time is: "<<(float)AVG_turnaround/(float)n<<endl;
}
int main()
{
    int P,choice,i;
    cout << "Non-Preemptive SJF Method"<< endl;
    cout << "-------------------------"<< endl << endl;
    cout<<"Enter the total number of processes: ";
    cin>>P;
    if(P < 3)
    {
        cout << endl;
        cout << "Not enough processes !" << endl;
        return 0;
    }

    else if(P > 10)
    {
        cout << endl;
        cout << "Too much processes !" << endl;
        return 0;
    }

    else
    {
        cout << endl;
        cout <<"You have entered " << P << " Processes." << endl;
    }
    cout << endl << endl;
    insert(P);
    display(P);
    return 0;
}
