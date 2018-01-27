#include <iostream>
#include <string>
#include <fstream>
#include <jsoncpp/json/json.h> // or json/json.h
// #include "json/json.h"
using namespace std;

int main(int argc, char *argv[])
{
    /**
     * 解析：主要是Reader的操作
     */
    //example 1: 从文件中解析json
    //Json::ValueType 枚举值，可以查看支持的类型
    ifstream ifIn("alice.json");
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifIn, obj); //从ifstream文件流中解析
    cout << "--- Example 1 ---" << endl;
    cout << "Book: " << obj["book"].asString() << endl;
    cout << "Year: " << obj["year"].asUInt() << endl;
    const Json::Value &characters = obj["characters"]; //array of characters
    cout << "characters size:" << characters.size() << endl;
    for (const auto &x : characters)
    {
        cout << "     name: " << x["name"].asString();
        cout << ", chapter: " << x["chapter"].asUInt() << endl;
    }
    string stAlice = obj.toStyledString(); //把Json::Value转成带格式的string
    // cout << "Alice json to string:" << stAlice << endl;

    //example 2: 从string中解析
    string str("{\"book\":\"UNIX Program\",\"isbn\":100}");
    reader.parse(str, obj); //从string中解析
    string stBook = obj["book"].asString();
    int nIsbn = obj["isbn"].asInt();
    int nYear = obj.get("year", 2018).asInt(); //如果不存在，就返回默认值2018
    cout << "--- Example 2 ---" << endl;
    cout << obj << endl; //Value对象重载了<<
    cout << "Book: " << stBook << ", Isbn: " << nIsbn << ", Year: " << nYear << endl;

    //example 3：
}