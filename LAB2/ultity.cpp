#include "ultity.h"

using namespace std;

vector<struct CSVDATA> dataload() {
    std::ifstream inFile("E:/USTC/secrity/算法分析与设计/实验2/data_100000.csv", std::ios::in);
    std::string lineStr;
    std::vector<struct CSVDATA> csvData;
    std::getline(inFile, lineStr); // 跳过第一行(非数据区域)
    while (std::getline(inFile, lineStr)) {
        std::stringstream ss(lineStr); // string数据流化
        std::string str;
        struct CSVDATA csvdata;
        std::getline(ss, str, ','); // 获取 index
        csvdata.index = std::stoi(str);
        std::getline(ss, str, ','); // 获取 mac
        csvdata.mac = str;

        csvData.push_back(csvdata);
    }
    return csvData;
}