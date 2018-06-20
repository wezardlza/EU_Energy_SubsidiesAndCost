/***********************************************************************************************************************
Author: Ziang Li
Institution: Control Group, UOM

	This file defines the saving and reading methods of .csv document.
***********************************************************************************************************************/

#include <iostream>  
#include <fstream>  
#include <sstream>  
#include <string>  
#include <vector>  

//删除字符串中空格，制表符tab等无效字符  
std::string Trim(std::string& str)
{
	//str.find_first_not_of(" \t\r\n"),在字符串str中从索引0开始，返回首次不匹配"\t\r\n"的位置  
	str.erase(0, str.find_first_not_of(" \t\r\n"));
	str.erase(str.find_last_not_of(" \t\r\n") + 1);
	return str;
}

int main()
{
	std::ifstream fin("../Data_Files/TEST_1_LCOE.csv"); //打开文件流操作  
	std::string line;
	while (std::getline(fin, line))   //整行读取，换行符“\n”区分，遇到文件尾标志eof终止读取  
	{
		std::cout << "原始字符串：" << line << std::endl; //整行输出  
		std::istringstream sin(line); //将整行字符串line读入到字符串流istringstream中  
		std::vector<std::string> fields; //声明一个字符串向量  
		std::string field;
		while (std::getline(sin, field, ',')) //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符  
		{
			fields.push_back(field); //将刚刚读取的字符串添加到向量fields中  
		}
		std::string name = Trim(fields[0]); //清除掉向量fields中第一个元素的无效字符，并赋值给变量name  
		std::string age = Trim(fields[1]); //清除掉向量fields中第二个元素的无效字符，并赋值给变量age  
		std::string birthday = Trim(fields[2]); //清除掉向量fields中第三个元素的无效字符，并赋值给变量birthday  
		std::cout << "处理之后的字符串：" << name << "\t" << age << "\t" << birthday << std::endl;
	}
	return EXIT_SUCCESS;
}