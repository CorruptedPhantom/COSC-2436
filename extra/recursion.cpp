#include <iostream>
using namespace std;

int add( int x, int y ) {
    cout<<x<<" ";
    if( x != y ){
        return add(x + 1, y);
    }
}

int main(){
    cout<<"Recursively add number"<<endl;

    int n = 10;

    add(0, n);

    return 0;
}