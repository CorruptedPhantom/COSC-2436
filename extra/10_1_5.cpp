#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stack>
#include <iomanip>
#include <algorithm>
using namespace std;

int priority(char a){
    if(a == '/' || a == '*'){
        return 2;
    }else if(a == '+' || a == '-'){
        return 1;
    }else{
        return 0;
    }
}

string getInfo(string str){
    stack<char> c;
    string result;

    for(int i=0; i<str.length(); i++) {
        if (str[i] >= '0' && str[i] <= '9'){
            result+=str[i];
        }
        else if (str[i] == '(') {    
            c.push(str[i]);
        }
        else if (str[i] == ')') {
            while(c.top() != '('){
                result += c.top();
                c.pop();
            }
            c.pop();
        }
        else{
            while(!c.empty() && priority(str[i]) <= priority(c.top())){
                result += c.top();
                c.pop();
            }
            c.push(str[i]);
        }
    }

    while(!c.empty()){
        result += c.top();
        c.pop();
    }
    return result;
}

int decodeInfo(string s){
    stack<int> st;
    int result;

    for (int i=0; i<s.length(); i++) {
        string temp;

        if (s[i] >= '0' && s[i] <= '9'){
            temp+=s[i];
            st.push(stoll(temp));
        }
        else {
            int num1 = st.top(); 
            st.pop();
            int num2 = st.top(); 
            st.pop();

            if (s[i]=='+'){
                st.push(num2 + num1);
            }
            else if (s[i]=='-'){ 
                st.push(num2 - num1);
            }
            else if (s[i]=='/'){
                st.push(num2 / num1);
            }
            else if (s[i]=='*'){
                st.push(num2 * num1);
            }
        }
        temp="";
    }

    result = st.top();
    return result;
}

int main(int argc, char *argv[]) {

    string general = "( 8 * 9 - ( 0 + ( 9 / 3 * 2 ) * 2 * 3 ) * 2 + 9 ) / x = 4", left, right;
    cout<<"Calculate equations using stack with postfix/infix"<<endl;
    cout<<"Equation is: "<<general<<endl;
    int locationOfEqual;
    
    //this loop obtains left side
    for(int i=0; i<general.size(); i++) {
        if(general[i] != '='){
            left += general[i];
        }else if(general[i] == '='){
            locationOfEqual = i;
            break;
        }
    }

    //this loop obtains right side
    for(int i=locationOfEqual+1; i<general.size(); i++) {
        right += general[i];
    }

    left.erase(remove(left.begin(), left.end(), '\n'), left.end());
    left.erase(remove(left.begin(), left.end(), '\r'), left.end());
    left.erase(remove(left.begin(), left.end(), ' '), left.end());

    right.erase(remove(right.begin(), right.end(), '\n'), right.end());
    right.erase(remove(right.begin(), right.end(), '\r'), right.end());
    right.erase(remove(right.begin(), right.end(), ' '), right.end());

    char oprt; //to find if opr is +,-,* or /
    bool test;//to find if x is left or right

    if(left[0]=='x'){// if x is left side
        test = true;
        oprt = left[1];
        left = left.substr(2, left.size()-1);
    }
    else if(left[left.size()-1]=='x'){// if x is right side
        test = false;
        oprt = left[left.size()-2];
        left = left.substr(0, left.size()-2);
    }

    double x, y, z;
    string info = getInfo(left);
    int result = decodeInfo(info);
    
    y= double(result);
    z= double(stoll(right));

    if(oprt== '+'){
        x = z - y;
    }
    else if(oprt== '-'){
        if (test==true){
            x = z+y;
        }else{
            x = z-y;
        }
    }
    else if(oprt== '*'){
        x = z/y;
    }else{
        if (test==true){
            x = z*y;
        }else{
            x = y/z;
        }
    }
    cout<<"Result: ";
    cout<<fixed<<setprecision(2)<<x<<endl;

    return 0;
}