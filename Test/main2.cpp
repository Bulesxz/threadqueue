#include <iostream>

#include "../base/cir_buff.h"
#include "../base/timer.h"
using namespace std;

void print(int i){
    cout<<endl<<"i: "<<i<<endl;
}
int main()
{
    cout << "Hello world!" << endl;
    cir_buffer<int> buff(3);
    buff.insert(1);
    cout <<buff.back();
    cout<<buff.begin();
    cout<<buff.end();
    buff.insert(2);
    cout<<buff.back();
     cout<<buff.begin();
    cout<<buff.end();
    buff.insert(3);
    cout<<buff.back();
     cout<<buff.begin();
    cout<<buff.end();
    buff.insert(4);
    cout<<buff.back();
     cout<<buff.begin();
    cout<<buff.end();
    buff.insert(5);
    cout<<buff.back();


    cout<<buff.begin();
    cout<<buff.end();

    Timestamp when = 0 ;
    TimerCallback callback= std::bind(&print,2);
    Timer timer(callback,when,0);
    timer.run();

    Timestamp now=10;
    timer.restart(now);
    timer.run();
    return 0;
}
