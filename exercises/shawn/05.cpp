#include <iostream>
using namespace std;
int main()
{
    int a,b,c,t;
    a=10;
    b=20;
    c=30;
    cout<<a<<" "<<b<<" "<<c<<endl;
    t=c;
    c=b;
    b=a;
    a=t;
    cout<<a<<" "<<b<<" "<<c<<endl;
}
