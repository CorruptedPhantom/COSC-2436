#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

int main(){
    cout<<endl;
    cout<<"Implement priority queue"<<endl;
    cout<<"Adding 89 6 54 18 34 into queue"<<endl;

    priority_queue<int> pq;
    pq.push(89);
    pq.push(6);
    pq.push(54);
    pq.push(18);
    pq.push(34);
    cout<<endl;

    cout<<"The priority queue will always put the highest number at the front of the queue"<<endl;
    cout<<"Therefore we can sort the array descendingly by printing the queue"<<endl;
    cout<<endl;
    cout<<"The numbers after being sorted:"<<endl;
    for(int i=0; i<5; i++){
        cout<<pq.top()<<" ";
        pq.pop();
    }

    return 0;
}