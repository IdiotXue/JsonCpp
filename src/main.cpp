#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
// #include <jsoncpp/json/json.h> // or json/json.h
#include "json/json.h"
using namespace std;

int main(int argc, char *argv[])
{
    /**
     * 解析：主要是Value的访问和类型转换，及Reader的操作（反序列化）
     */
    //example 1: 从文件中解析json
    cout << "--- Example 1 ---" << endl;
    //Json::ValueType 枚举值，可以查看支持的类型
    ifstream ifIn("alice.json");
    Json::Reader reader;
    Json::Value obj;
    if (!reader.parse(ifIn, obj)) //从ifstream文件流中解析，解析正确返回true，错误返回false
    {
        cout << "parse error" << endl;
        exit(EXIT_FAILURE);
    }
    if (!obj["year"].isInt()) //类型转换前最好判断是否属于该类型
    {
        cout << "year is not int" << endl;
        exit(EXIT_FAILURE);
    }
    cout << "Book: " << obj["book"].asString() << endl; //类型转换
    cout << "Year: " << obj["year"].asUInt() << endl;
    const Json::Value &characters = obj["characters"]; //array of characters
    cout << "characters size:" << characters.size() << endl;
    for (const auto &x : characters)
    {
        cout << "     name: " << x["name"].asString();
        cout << ", chapter: " << x["chapter"].asUInt() << endl;
    }

    //example 2: 从string中解析
    cout << "--- Example 2 ---" << endl;
    string str("{\"book\":\"UNIX Program\",\"isbn\":100}");
    reader.parse(str, obj); //从string中解析，反序列化
    string stBook = obj["book"].asString();
    int nIsbn = obj["isbn"].asInt();
    int nYear = obj.get("year", 2018).asInt(); //如果不存在，就返回默认值2018
    cout << obj << endl;                       //Value对象重载了<<
    cout << "Book: " << stBook << ", Isbn: " << nIsbn << ", Year: " << nYear << endl;

    /**
     * 生成：主要是Value的插入 和 Writer的操作（序列化）
     */
    //example 3：Value底层用map实现，因此其操作类比map就懂了
    cout << "--- Example 3 ---" << endl;
    Json::Value json_temp; // 临时对象，供如下代码使用
    json_temp["name"] = Json::Value("搞笑");
    json_temp["age"] = Json::Value(66);
    cout << "json_temp: " << json_temp << endl;

    Json::Value root;                                 // 表示整个 json 对象
    root["key_string"] = Json::Value("value_string"); // 新建一个 Key（名为：key_string），赋予字符串值："value_string"。
    root["key_number"] = Json::Value(12345);          // 新建一个 Key（名为：key_number），赋予数值：12345。
    root["key_boolean"] = Json::Value(false);         // 新建一个 Key（名为：key_boolean），赋予bool值：false。
    root["key_double"] = Json::Value(12.345);         // 新建一个 Key（名为：key_double），赋予double 值：12.345。
    root["key_object"] = json_temp;                   // 新建一个 Key（名为：key_object），赋予json::Value 对象值。
    //javascript数组的元素类型可以不必是相同的，json同理
    root["key_array"].append("array_string"); // 新建一个 Key（名为：key_array），类型为数组，对第一个元素赋值为字符串："array_string"。
    root["key_array"].append(1234);           // 为数组 key_array 赋值，对第二个元素赋值为：1234
    cout << "root: " << root << endl;
    Json::ValueType type = root.type(); // 获得root的类型，此处为 objectValue 类型，在enum中编号7
    cout << "type root: " << type << endl;

    //Writer是抽象基类（有virtual write函数），派生出了FastWriter（无格式）和StyledWriter（有格式）
    //example 4：
    cout << "--- Example 4 ---" << endl;
    string stJson = json_temp.toStyledString();              //把Json::Value转成带格式的string
    cout << "json_temp to format string:" << stJson << endl; //注意与直接输出json_temp是不同的
    Json::FastWriter fastW;
    string stFast = fastW.write(json_temp);
    cout << "fast writer json_temp: " << stFast << endl; //无格式，即无换行，一行输出整个json，序列化
    Json::StyledWriter styleW;
    string stStyle = styleW.write(json_temp);
    cout << "styled writer json_temp: " << stStyle << endl; //与toStyledString一样

    //还需要一些操作Value的方法，如isMember，removeMember，get等可以在ReadMe的参考连接wiki_cpp查看，都很简单
}