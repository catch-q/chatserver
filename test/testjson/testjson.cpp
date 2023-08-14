#include <iostream>
#include <vector>
#include <map>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

// json序列化实例1
string func1(){
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg"] = "hello ,what are you doing now?";

    string sendbuf = js.dump(); //将json格式转化为字符串
    // cout<<sendbuf.c_str()<<endl; //将字符串转化为c风格字符串，以便做数据序列化
    return sendbuf;
}

// json序列化实例2
string func2(){
    json js;
    
    //添加数组
    js["id"] = {1,2,3,4,5};
    
    //添加key-value
    js["name"] = "zhang san";
    
    //添加对象
    js["msg"]["zhang san"] = "hello world";
    js["msg"]["liu shuo"] = "hello china";

    //上面等同于下面这就要一次性添加数组对象
    js["msg"] = {{"zhang san","hello world"},{"liu shuo","hello china"}};

    // cout<<js<<endl;
    return js.dump();

}

// json序列化实例代码3
string func3(){
    json js;

    //直接序列化一个vector容器
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(5);

    js["list"] = vec;

    //直接序列化一个map容器
    map<int, string> m;
    m.insert({1,"黄山"});
    m.insert({2,"华山"});
    m.insert({3,"泰山"});

    js["path"] = m;

    // string sendbuf = js.dump(); //将json对象序列化为json字符串
    // cout<<sendbuf<<endl;
    return js.dump();

}

// 数据的反序列化 json字符串 --> 反序列化 数据对象（看作容器，方便访问）
void func4(){
    string recvbuf = func1();
    json jsbuf = json::parse(recvbuf); //解析成json对象
    cout<<jsbuf["msg_type"]<<endl;
    cout<<jsbuf["from"]<<endl;
    cout<<jsbuf["to"]<<endl;
    cout<<jsbuf["msg"]<<endl;

    cout<<"-------------------------------"<<endl;

    recvbuf = func2();
    jsbuf = json::parse(recvbuf);
    cout<<jsbuf["id"]<<endl;
    auto arr = jsbuf["id"];
    cout<<arr[2]<<endl;
    
    auto msg = jsbuf["msg"];
    cout<<msg["zhang san"]<<endl;
    cout<<msg["liu shuo"]<<endl;

    cout<<"-------------------------------"<<endl;
    recvbuf = func3();
    jsbuf = json::parse(recvbuf);

    vector<int> vec = jsbuf["list"];
    for(int &i : vec){
        cout<<i<<endl;
    }

    cout<<endl;

    map<int,string> m = jsbuf["path"];
    for(auto &p : m){
        cout<<p.first<<" "<<p.second<<endl;
    }

}

int main(){
    func4();
    return 0;
}