#include <iostream>
#include <iterator>
#include <map>
using namespace std;

int main()
{
    cout<<"\tImplement map\n"<<endl;
    map<int, string, greater<int>> reptiles
  {
    {10, "Komodo Dragon"}, {15, "Saltwater Crocodile"}, {8, "Leatherback Sea Turtle"}
  };


    map<int, string> :: iterator iter;

    for (iter = reptiles.begin(); iter != reptiles.end(); ++iter){
        cout << '\t' << iter->first << '\t' << iter->second << '\n';
    }
}