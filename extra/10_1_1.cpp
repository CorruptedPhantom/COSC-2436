#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main(){
    cout<<"Reverse string using stack"<<endl;

    string str = "If only I can buy a 911 Speedster", empty_str;

    stack<char> st;
    for(int i = 0; i < str.length(); i++){
        st.push(str[i]);
    }

    for(int i = 0; i < str.length(); i++){
        empty_str+=st.top();
        st.pop();
    }

    cout<<"Reverse string :"<<empty_str;

    return 0;
}