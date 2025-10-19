#include <iostream>
using namespace std;
int main()
{
    int a,b;
    cout<<"你能给我买一个烤冷面吗？（1-能，0-不能）"<<endl;
    cin>>a;
    if(a>1||a<0){
        cout<<"输入错误，请输入1或0"<<endl;
    }else if(a==1){
        cout<<"太好了！谢谢你！"<<endl;
        cout<<"咱们几点去【（16-20）只写数字】？"<<endl;
        cin>>b;
        if(b>20||b<16)
            cout<<"输入错误，请输入16-22之间的数字"<<endl;
        else
         cout<<"好的，咱们"<<b<<"点见！"<<endl;
    }
    else{
         cout<<"你怎么能这样，你明明答应我了，你真是太可恶了。！"<<endl;
    }
}

















