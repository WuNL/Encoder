#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <string>

using namespace std;
using namespace boost::property_tree;

int main(int argc, const char *argv[])
{
//    std::string str_json0 = "{\"array\":[1,2,3],\"boolean\":true,\"null\":null,\"number\":123,\"object\":{\"a\":\"b\",\"c\":\"d\",\"e\":\"f\"},\"string\":\"Hello World\"}";
    std::string str_json = R"({"array":[1,2,3],"boolean":true,"null":null,"number":123,"object":{"a":"b","c":"d","e":"f"},"string":"Hello World"})";

    ptree root, arr, object;
    arr.push_back(std::make_pair("", ptree("1")));
    arr.push_back(std::make_pair("", ptree("2")));
    arr.push_back(std::make_pair("", ptree("3")));

    object.put("a", "b");
    object.put("c", "d");
    object.put("e", "f");

    root.add_child("array", arr);
    auto boolvalue = true;
    root.put("boolean", boolvalue);
    root.put("null", "null");
    int num = 123;
    root.put("number", num);
    root.add_child("object", object);
    root.put("string", "Hello World");

    //write_json("out.json", root);
    stringstream s;
    write_json(s, root, false);
    string out = s.str();
    cout << out;
    return 0;
}