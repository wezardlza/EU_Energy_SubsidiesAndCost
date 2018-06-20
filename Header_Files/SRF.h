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

//ɾ���ַ����пո��Ʊ��tab����Ч�ַ�  
std::string Trim(std::string& str)
{
	//str.find_first_not_of(" \t\r\n"),���ַ���str�д�����0��ʼ�������״β�ƥ��"\t\r\n"��λ��  
	str.erase(0, str.find_first_not_of(" \t\r\n"));
	str.erase(str.find_last_not_of(" \t\r\n") + 1);
	return str;
}

int main()
{
	std::ifstream fin("../Data_Files/TEST_1_LCOE.csv"); //���ļ�������  
	std::string line;
	while (std::getline(fin, line))   //���ж�ȡ�����з���\n�����֣������ļ�β��־eof��ֹ��ȡ  
	{
		std::cout << "ԭʼ�ַ�����" << line << std::endl; //�������  
		std::istringstream sin(line); //�������ַ���line���뵽�ַ�����istringstream��  
		std::vector<std::string> fields; //����һ���ַ�������  
		std::string field;
		while (std::getline(sin, field, ',')) //���ַ�����sin�е��ַ����뵽field�ַ����У��Զ���Ϊ�ָ���  
		{
			fields.push_back(field); //���ոն�ȡ���ַ�����ӵ�����fields��  
		}
		std::string name = Trim(fields[0]); //���������fields�е�һ��Ԫ�ص���Ч�ַ�������ֵ������name  
		std::string age = Trim(fields[1]); //���������fields�еڶ���Ԫ�ص���Ч�ַ�������ֵ������age  
		std::string birthday = Trim(fields[2]); //���������fields�е�����Ԫ�ص���Ч�ַ�������ֵ������birthday  
		std::cout << "����֮����ַ�����" << name << "\t" << age << "\t" << birthday << std::endl;
	}
	return EXIT_SUCCESS;
}