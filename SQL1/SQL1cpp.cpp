#include<iostream>
#include<string>
#include<conio.h>
#include<fstream>
#include<sstream>

using namespace std;

int flag = 0;//结尾的回车已经被取过了置为1

struct attr
{
	char name[30];
	char type[30];
	char is_null[5];
	char is_key[5];
	int attr_length;
};

struct database
{
	char name[30];
	int attr_num;
	struct attr attrs[20];
	int database_length;
};

void removeThirtyNine(string &s)
{
	int i = 0;
	string str = "";
	while (s[i] != '\0')
	{
		if (s[i] == 39);
		else str = str + s[i];
		i++;
	}
	s = str;
}

database getDatabaseFromFile(string name, int &e)
{
	database d;
	fstream attrData;
	char compare[30];
	strcpy_s(compare, name.c_str());
	attrData.open("attrData.txt", ios_base::in);
	while (!attrData.eof())
	{
		attrData.read((char *)&d, sizeof(d));
		if (!strcmp(compare, d.name))
		{
			cout << d.name << endl;
			for (int i = 0; d.attrs[i].name[0] != -52; i++)
			{
				cout << d.attrs[i].name << "  " << d.attrs[i].type << endl;
			}
			return d;
		}
		else;
	}
	cout << "没有找到指定的database(getDatabaseFromFile函数)" << endl;
	e = -1;
	attrData.close();
}

void deleteDatabaseFromFile(string name)
{
	database d;
	char name_1[30];
	char compare[30];
	strcpy_s(name_1, name.c_str());
	fstream guodu, attrData;
	guodu.open("guodu.txt", ios::out);
	attrData.open("attrData.txt", ios::in);
	string s;
	attrData >> s;
	guodu << s;
	guodu.close();
	attrData.close();
	int flag = 0;
	guodu.open("guodu.txt", ios_base::in);
	attrData.open("attrData.txt", ios_base::out);
	while (!guodu.eof())
	{
		guodu.read((char *)&d, sizeof(d));
		if (strcmp(d.name,name_1) && strcmp(compare,d.name))
		{
			attrData.write((char *)&d, sizeof(d));
			strcpy_s(compare, d.name);
			flag = 1;
		}
		else;
	}
	if (!strcmp(d.name, name_1)) flag = 1;
	if (flag == 0)
	{
		cout << "没有找到对应database" << endl;
	}
	guodu.close();
	attrData.close();
}

char getWordWithoutSymbol(string &s)
{
	char a[100], ch;
	s = "";
	ch = getchar();
	while (ch == ' ') ch = getchar();
	while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == '-' || ch == '_')
	{
		s = s + ch;
		ch = getchar();
	}
	return ch;
}

void where(string tableName, database &d, int *jilu_shuzu, int &e)
{
	fstream table, attrData, panduanTable;
	string s = "and";
	char ch, end;
	string shuxing_name;
	string panduan_name;
	int compare[50];
	for (int i = 0; i < 50; i++)
	{
		compare[i] = -1;
		jilu_shuzu[i] = -1;
	}
	int time = 0;
	while (s == "and")
	{	
		int symbolFlag = -1;
		attrData.open("attrData.txt", ios_base::in);
		ch = getWordWithoutSymbol(s);
		if (ch == '=')
		{
			symbolFlag = 0;
			ch = getchar();
		}
		else if (ch == '>')
		{
			ch = getchar();
			if (ch == '=') 
			{
				symbolFlag = 1;
				ch = getchar();
			}
			else symbolFlag = 2;
		}
		else if (ch == '<')
		{
			if (ch == '=')
			{
				symbolFlag = 3;
				ch = getchar();
			}
			else symbolFlag = 4;
		}
		else
		{
			cout << "where表达式中符号有问题(where函数)" << endl;
			flag = 1;
			e = -1;
			return;
		}
		shuxing_name = s;
		cin >> s;
		s = ch + s;
		removeThirtyNine(s);
		panduan_name = s;
		/*判断等号右边的是否是另一个属性名*/
		int panduanShuxingNum = 0;
		int panduanNameFlag = 0;
		int i1 = 0;
		while (d.attrs[panduanShuxingNum].name[0] != -52)
		{
			if (!strcmp(d.attrs[panduanShuxingNum].name, panduan_name.c_str())) break;
			panduanShuxingNum++;
		}
		if (!strcmp(d.attrs[panduanShuxingNum].name, panduan_name.c_str()))
		{
			panduanNameFlag = 1;
			while (strcmp(d.attrs[i1].name, panduan_name.c_str()) && d.attrs[i1].name[0] != -52)
			{
				i1++;
			}
		}

		int i = 0;
		if (!strcmp(d.name, "guodu"));
		else
		{
			while (!attrData.eof())
			{
				attrData.read((char *)&d, sizeof(d));
				if (attrData.eof() || !strcmp(d.name, tableName.c_str())) break;
				else;
			}
			if (attrData.eof())
			{
				cout << "在系统表中没有找到相应的database(where函数)" << endl;
				e = -1;
				return;
			}
		}
		while (strcmp(d.attrs[i].name, shuxing_name.c_str()) && d.attrs[i].name[0] != -52)
		{
			i++;
		}
		if (d.attrs[i].name[0] == -52)
		{
			cout << "在database中没有找到相应的属性名(where函数)" << endl;
			e = -1;
			return;
		}
		char zifu[30];
		char panduanZifu[30];
		int shuxing_num;
		int shuxing_num1;
		int jilu_num = 0;
		int jishuqi = 0;
		table.close();
		table.open(tableName + ".txt", ios_base::in);
		panduanTable.close();
		panduanTable.open(tableName + ".txt", ios_base::in);
		while (!table.eof())
		{
			shuxing_num = 0;
			shuxing_num1 = 0;
			while (shuxing_num <= i)
			{
				table.read(zifu, sizeof(zifu));
				if (table.eof()) break;
				shuxing_num++;
			}
			if (panduanNameFlag != 0)
			{
				while (shuxing_num1 <= i1)
				{
					panduanTable.read(panduanZifu, sizeof(panduanZifu));
					if (panduanTable.eof()) break;
					shuxing_num1++;
				}
			}
			if(symbolFlag==0)
			{
				if (panduanNameFlag == 0)
				{
					if (!strcmp(zifu, panduan_name.c_str()))
					{
						if (time == 0)
						{
							jilu_shuzu[jishuqi] = jilu_num;
							jishuqi++;
						}
						else
						{
							int compare_num = 0;
							for (compare_num = 0; jilu_shuzu[compare_num] >= 0; compare_num++)
							{
								if (jilu_shuzu[compare_num] == jilu_num) break;
							}
							if (jilu_shuzu[compare_num] >= 0)
							{
								compare[jishuqi] = jilu_num;
								jishuqi++;
							}
						}
					}
				}
				else
				{
					if (!strcmp(zifu, panduanZifu))
					{
						if (time == 0)
						{
							jilu_shuzu[jishuqi] = jilu_num;
							jishuqi++;
						}
						else
						{
							int compare_num = 0;
							for (compare_num = 0; jilu_shuzu[compare_num] >= 0; compare_num++)
							{
								if (jilu_shuzu[compare_num] == jilu_num) break;
							}
							if (jilu_shuzu[compare_num] >= 0)
							{
								compare[jishuqi] = jilu_num;
								jishuqi++;
							}
						}
					}
				}
			}
			else if (symbolFlag == 1)
			{
				if ((!strcmp(zifu, panduan_name.c_str())) || strcmp(zifu, panduan_name.c_str()) > 0)
				{
					if (time == 0)
					{
						jilu_shuzu[jishuqi] = jilu_num;
						jishuqi++;
					}
					else
					{
						int compare_num = 0;
						for (compare_num = 0; jilu_shuzu[compare_num] >= 0; compare_num++)
						{
							if (jilu_shuzu[compare_num] == jilu_num) break;
						}
						if (jilu_shuzu[compare_num] >= 0)
						{
							compare[jishuqi] = jilu_num;
							jishuqi++;
						}
					}
				}
			}
			else if (symbolFlag == 2)
			{
				if (strcmp(zifu, panduan_name.c_str()) > 0)
				{
					if (time == 0)
					{
						jilu_shuzu[jishuqi] = jilu_num;
						jishuqi++;
					}
					else
					{
						int compare_num = 0;
						for (compare_num = 0; jilu_shuzu[compare_num] >= 0; compare_num++)
						{
							if (jilu_shuzu[compare_num] == jilu_num) break;
						}
						if (jilu_shuzu[compare_num] >= 0)
						{
							compare[jishuqi] = jilu_num;
							jishuqi++;
						}
					}
				}
			}
			else if (symbolFlag == 3) 
			{
				if ((!strcmp(zifu, panduan_name.c_str())) || strcmp(zifu,panduan_name.c_str()) < 0)
				{
					if (time == 0)
					{
						jilu_shuzu[jishuqi] = jilu_num;
						jishuqi++;
					}
					else
					{
						int compare_num = 0;
						for (compare_num = 0; jilu_shuzu[compare_num] >= 0; compare_num++)
						{
							if (jilu_shuzu[compare_num] == jilu_num) break;
						}
						if (jilu_shuzu[compare_num] >= 0)
						{
							compare[jishuqi] = jilu_num;
							jishuqi++;
						}
					}
				}
			}
			else if (symbolFlag == 4)
			{
				if (strcmp(zifu, panduan_name.c_str()) < 0)
				{
					if (time == 0)
					{
						jilu_shuzu[jishuqi] = jilu_num;
						jishuqi++;
					}
					else
					{
						int compare_num = 0;
						for (compare_num = 0; jilu_shuzu[compare_num] >= 0; compare_num++)
						{
							if (jilu_shuzu[compare_num] == jilu_num) break;
						}
						if (jilu_shuzu[compare_num] >= 0)
						{
							compare[jishuqi] = jilu_num;
							jishuqi++;
						}
					}
				}
			}
			while (shuxing_num != d.attr_num)
			{
				table.read(zifu, sizeof(zifu));
				if (table.eof()) break;
				shuxing_num++;
			}
			while (shuxing_num1 != d.attr_num)
			{
				panduanTable.read(panduanZifu, sizeof(panduanZifu));
				if (panduanTable.eof()) break;
				shuxing_num1++;
			}
			jilu_num++;
		}
		if (time != 0)
		{
			for (int i = 0; i < 50; i++)
			{
				jilu_shuzu[i] = compare[i];
			}
		}
		time++;
		for (int i = 0; i < 50; i++)
		{
			compare[i] = -1;
		}
		jishuqi = 0;
		attrData.close();
		end = getchar();
		if (end == ' ') end = getchar();
		if (end == '\n') break;
		else
		{
			cin >> s;
			s = end + s;
		}
	}
	if (end != '\n')
	{
		cout << "多个条件用and连接" << endl;
		e = -1; 
		return;
	}
	if (jilu_shuzu[0] == -1)
	{
		cout << "没有符合条件的记录" << endl;
		flag = 1;
		e = -1;
		return;
	}
}

void cifa(int &e, string &s)
{
	cout << "---------------------------------------" << endl;
	cout << "请输入SQL语句(输入exit退出)：" << endl;
	e = 0;
	cin >> s;
	if (s == "create")
	{
		e = 1;
	}
	else if (s == "drop")
	{
		e = 2;
	}
	else if (s == "alter")
	{
		e = 3;
	}
	else if (s == "insert")
	{
		e = 4;
	}
	else if (s == "delete")
	{
		e = 5;
	}
	else if (s == "update")
	{
		e = 6;
	}
	else if (s == "select")
	{
		e = 7;
	}
	else if (s == "grant")
	{
		e = 8;
	}
	else if (s == "revoke")
	{
		e = 9;
	}
	else if (s == "exit")
	{
		e = 0;
	}
	else if (s == "print")
	{
		e = 30;
	}
	else
	{
		e = -1;
		return;
	}
}

void createTable(database &d1, string s, int &e)
{
	database d;
	d.database_length = 0;
	char ch;
	int attrNo = 0;
	string file = "";
	cout << "正在创建表" << s << "……" << endl;
	fstream table;
	if (s == "" || s == "\n")
	{
		cout << "格式错误(createTable函数)" << endl;
		flag = 1;
		e = -1;
		return;
	}
	table.open(s + ".txt", ios::in);
	table >> file;
	if (file != "")
	{
		cout << "表" << s << "已经存在" << endl;
		e = -1;
		return;
	}
	file = s;
	strcpy_s(d.name, s.c_str());
	table.close();
	ch = getchar();
	while (ch == ' ' || ch == '(') ch = getchar();
	while (ch != ')' && ch != '\n' && ch != ' ')
	{
		s = "";
		while (ch != ' ' && ch != '\n' && ch != ')')
		{
			s = s + ch;
			ch = getchar();
		}
		
		if (s == "primary")//如果声明主键
		{
			getWordWithoutSymbol(s);
			if (s == "key")
			{
				ch = ',';
				while (ch == ',')
				{
					ch = getWordWithoutSymbol(s);
					int i = 0;
					while (i < 20 && d.attrs[i].name != s)
					{
						i++;
					}
					if (i >= 20)
					{
						cout << "找不到主键" << endl;
						e = -1;
						return;
					}
					else
					{
						strcpy_s(d.attrs[i].is_key, "1");
					}
				}
			}
		}
		else//如果声明的不是主键
		{
			strcpy_s(d.attrs[attrNo].is_key, "0");
			strcpy_s(d.attrs[attrNo].name, s.c_str());
			cin >> s;
			strcpy_s(d.attrs[attrNo].type, s.c_str());
			cin >> s;
			if (s == "not")
			{
				cin >> s;
				strcpy_s(d.attrs[attrNo].is_null, "0");
			}
			else if (s == "NULL" || s == "null")
			{
				strcpy_s(d.attrs[attrNo].is_null, "1");
			}
			else;
		}
		while (ch == ' ') ch = getchar();
		attrNo++;
	}
	while (ch != 10) ch = getchar();
	attrNo--;
	table.open(file + ".txt", ios_base::out);
	table << "-1";
	cout << "创建表" << file << "成功" << endl;
	table.close();
	fstream attrData;
	attrData.open("attrData.txt", ios_base::app);
	d.attr_num = attrNo++;
	attrData.write((char *)&d, sizeof(d));
	d.database_length = sizeof(attr) * (d.attr_num);
}

void dropTable(string s)
{
	cout << "正在删除表" << s << "……" << endl;
	fstream table;
	string file = "";
	table.open(s + ".txt", ios::in);
	table >> file;
	if (file == "")
	{
		cout << "要删除的表不存在" << endl;
	}
	else
	{
		table.close();
		table.open(s + ".txt", ios::out);
		table << "";
		deleteDatabaseFromFile(s);
		cout << "删除表成功" << endl;
	}
}

void insertInto(string s, int &e)
{
	string file = "";
	char ch;
	database d;
	int shuxing_num;
	char insert[30];
	cout << "正在向表" << s << "中插入……" << endl;
	fstream table, attrData, guodu;
	table.open(s + ".txt", ios::in);
	table >> file;
	if (file == "")
	{
		cout << "要插入的表不存在" << endl;
		e = -1;
		return;
	}
	else if (file == "-1")
	{
		table.close();
		table.open(s + ".txt", ios_base::out);
		attrData.open("attrData.txt", ios_base::in);
		while (!attrData.eof())
		{
			attrData.read((char *)&d, sizeof(d));
			if (attrData.eof()) break;
			if (!strcmp(d.name, s.c_str()) || d.name[0] == -52)
			{
				break;
			}
		}
		if (d.name[0] == -52 || (attrData.eof()))
		{
			cout << "在系统表中没有找到database(insert函数)" << endl;
			e = -1;
			return;
		}
	}
	else
	{
		table.close();
		table.open(s + ".txt", ios_base::app);
		attrData.open("attrData.txt", ios_base::in);
		while (!attrData.eof())
		{
			attrData.read((char *)&d, sizeof(d));
			if (attrData.eof()) break;
			if (!strcmp(d.name, s.c_str())|| d.name[0] == -52)
			{
				break;
			}
		}
		if (d.name[0] == -52 || (attrData.eof()))
		{
			cout << "在系统表中没有找到database(insert函数)" << endl;
			e = -1;
			return;
		}
	}
	getWordWithoutSymbol(s);
	if (s != "values")
	{
		e = -1;
		cout << "表名后接values" << endl;
		return; 
	}
	ch = ',';
	shuxing_num = 0;
	while (ch == ',')
	{
		guodu.open("guodu.txt", ios_base::out);
		guodu.close();
		guodu.open("guodu.txt", ios_base::app);
		s = "";
		while (1)
		{
			ch = getchar();
			if (ch == ',' || ch == ')') break;
			else if (ch == ' ' || ch == '(');
			else s = s + ch;
		}
		removeThirtyNine(s);
		//table.write((char *)&s, sizeof(s));
		strcpy_s(insert, s.c_str());
		shuxing_num++;
		guodu.write(insert, sizeof(insert));
	}
	guodu.close();
	if (shuxing_num == d.attr_num)
	{
		guodu.open("guodu.txt", ios_base::in);
		while (!guodu.eof())
		{
			guodu.read(insert, sizeof(insert));
			if (guodu.eof()) break;
			table.write(insert, sizeof(insert));
		}
		cout << "向表" << "中插入成功" << endl;
	}
	else
	{
		cout << "属性数量不一致，插入失败" << endl;
		if (file == "-1")
		{
			table << "-1";
		}
		e = -1;
		return;
	}
}

void printTable(string tableName, int &e)
{
	database d;
	d = getDatabaseFromFile(tableName,e);
	if (e == -1)
	{
		cout << "打印失败" << endl;
		return;
	}
	int num = 0;
	fstream table;
	char zifu[30];
	char compare[30];
	strcpy_s(zifu, "-1");
	table.open(tableName + ".txt", ios_base::in);
	while (!table.eof())
	{
		num = 0;
		
		while (num < d.attr_num )
		{
			strcpy_s(compare, zifu);
			table.read(zifu, sizeof(zifu));
			if (table.eof()) break;
			cout << zifu << "  ";
			num++;
		}
		if (table.eof()) { break; }
		cout << endl;
	}
	
}

void alterTable(string s, int &e)  
{
	cout << "正在执行alter函数" << endl;
	database d;
	string name;
	char ch = '\0';
	name = s;
	char compare[30];
	string shuxing_name;
	strcpy_s(compare, s.c_str());
	fstream table, attrData, guodu;
	table.open(s + ".txt", ios::in);
	string panduan;
	table >> panduan;
	if (panduan == "")
	{
		cout << "要修改的表不存在" << endl;
		table.close();
		e = -1;
		return;
	}
	else if (panduan == "-1")
	{
		cout << "要修改的表中没有数据" << endl;
		table.close();
		/*e = -1;
		return;*/
	}
	table.close();
	cin >> s;
	int i = 0;

/*          add      */

	if (s == "add")
	{
		attrData.open("attrData.txt", ios_base::in);
		while (!attrData.eof())
		{
			attrData.read((char *)&d, sizeof(d));
			if (!strcmp(compare, d.name))
			{
				break;
			}
			else;
		}
		if (attrData.eof())
		{
			cout << "系统表中没有找到相应的database(alter函数中的add)" << endl;
			e = -1;
			attrData.close();
			return;
		}


		while (ch != '\n')
		{
			table.open(name + ".txt", ios_base::in);
			guodu.open("guodu.txt", ios_base::out);
			i = 0;
			cin >> s;
			shuxing_name = s;
			while (d.attrs[i].name[0] != -52)
			{
				i++;
			}
			strcpy_s(d.attrs[i].name, s.c_str());
			ch = getWordWithoutSymbol(s);
			
			if (ch == '[')
			{
				while (ch != ',' && ch != ' ' && ch != '\n')
				{
					s = s + ch;
					ch = getchar();
				}
			}



			if (ch == ' ')
			{
				ch = getchar();
			}
			strcpy_s(d.attrs[i].type, s.c_str());
			strcpy_s(d.attrs[i].is_key, "0");
			strcpy_s(d.attrs[i].is_null, "0");

			/*           更新文件                  */
			int num = 0;
			char zifu[30];
			char compare[30];
			strcpy_s(zifu, "-1");
			while (!table.eof())
			{
				num = 0;
				while (num < d.attr_num)
				{
					table.read(zifu, sizeof(zifu));
					if (table.eof()) break;
					guodu.write(zifu, sizeof(zifu));
					num++;
				}
				strcpy_s(zifu, "0");
				if (!table.eof() || num == d.attr_num)
				{
					guodu.write(zifu, sizeof(zifu));
				}
			}
			d.attr_num++;
			cout << "alter函数插入属性" << shuxing_name << "成功" << endl;
			table.close();
			guodu.close();
			table.open(name + ".txt", ios::out);
			guodu.open("guodu.txt", ios::in);
			string chongxie;
			guodu >> chongxie;
			table << chongxie;
			table.close();
			guodu.close();
		}
	}

/*            delete              */
	else if (s == "delete")
	{

		attrData.open("attrData.txt", ios_base::in);
		while (!attrData.eof())
		{
			attrData.read((char *)&d, sizeof(d));
			if (!strcmp(compare, d.name))
			{
				break;
			}
			else;
		}
		if (attrData.eof())
		{
			cout << "系统表中没有找到相应的database(alter函数中的delete)" << endl;
			e = -1;
			attrData.close();
			return;
		}



		while (ch != '\n')
		{
			table.open(name + ".txt", ios_base::in);
			guodu.open("guodu.txt", ios_base::out);
			i = 0;
			ch = getWordWithoutSymbol(s);
			shuxing_name = s;
			while (strcmp(d.attrs[i].name, s.c_str()))
			{
				if (d.attrs[i].name[0] == -52) break;
				else i++;
			}
			if (ch == ' ') ch = getchar();
			int num = 0;
			char zifu[30];
			char compare[30];
			strcpy_s(zifu, "-1");
			while (!table.eof())
			{
				num = 0;
				while (num < d.attr_num)
				{
					//strcpy_s(compare, zifu);
					table.read(zifu, sizeof(zifu));
					if (table.eof()) break;
					//if (!strcmp(compare, zifu)) break;
					if (num != i)
					{
						guodu.write(zifu, sizeof(zifu));
					}
					num++;
				}
			}
			table.close();
			guodu.close();
			table.open(name + ".txt", ios::out);
			guodu.open("guodu.txt", ios::in);
			string chongxie;
			guodu >> chongxie;
			table << chongxie;
			table.close();
			guodu.close();
			if (!strcmp(d.attrs[i].name, s.c_str()))
			{
				int j = i + 1;
				while (d.attrs[j].name[0] != -52)
				{
					strcpy_s(d.attrs[i].name, d.attrs[j].name);
					i++;
					j++;
				}
				int z = 0;
				while (z < 30)
				{
					d.attrs[i].name[z] = -52;
					z++;
				}
				d.attr_num--;
				cout << "alter函数删除属性" << shuxing_name << "成功" << endl;
			}
			else
			{
				cout << "没有找到要删除的属性名" << endl;
				e = -1;
				return;
			}
		}
	}
	else
	{
		cout << "表名后加add/delete" << endl;
		e = -1;
		return;
	}
	deleteDatabaseFromFile(name);
	fstream reopen;
	reopen.open("attrData.txt", ios_base::app);
	reopen.write((char *)&d, sizeof(d));
	reopen.close();
	table.close();
	string dkj_1;
	table.open(name + ".txt", ios::in);
	table >> dkj_1;
	if (dkj_1 == "")
	{
		table.close();
		table.open(name + ".txt", ios::out);
		table << "-1";
		table.close();
	}
}

void update(string s, int &e)
{
	cout << "正在执行update函数" << endl;
	fstream table, attrData, guodu;
	string name;
	int update_yesorno = 0;
	table.open(s + ".txt", ios_base::in);
	attrData.open("attrData.txt", ios_base::in);
	name = s;
	cin >> s;
	if (s != "set")
	{
		cout << "表名后跟set" << endl;
		e = -1;
		return;
	}
	char set_ch;
	string set;
	set_ch = getWordWithoutSymbol(s);
	while (s != "where" && set_ch != '\n')
	{
		set = set + s + set_ch;
		set_ch = getWordWithoutSymbol(s);
	}
	if (set_ch == '\n')
	{
		cout << "缺少where条件(update函数)" << endl;
		e = -1;
		return;
	}
	//对where条件进行分析
	char zifu[30];
	int shuxing_num;
	int jilu_num = 0;
	int jilu_shuzu[50];
	int jishuqi = 0;
	database d;

	where(name, d, jilu_shuzu, e);
	if (e == -1)
	{
		return;
	}
	                   //对set进行分析
	string set_fenxi[10];
	int set_num = 0;
	int flag_1 = 0;
	int set_fenxi_num = 0;
	while (set[set_num] != '\0')
	{
		set_fenxi[set_fenxi_num] = "";
		while ((set[set_num] >= 'a' && set[set_num] <= 'z') || (set[set_num] >= 'A' && set[set_num] <= 'Z') || (set[set_num] >= '0' && set[set_num] <= '9'))
		{
			set_fenxi[set_fenxi_num] = set_fenxi[set_fenxi_num] + set[set_num];
			set_num++;
			flag_1 = 1;
		}
		if (flag_1 == 1)
		{
			set_fenxi_num++;
			set_fenxi[set_fenxi_num] = "";
			flag_1 = 0;
		}
		else;
		if (set[set_num] == '+' || set[set_num] == '-' || set[set_num] == '*' || set[set_num] == '/' || set[set_num] == '=')
		{
			set_fenxi[set_fenxi_num] = set[set_num];
			set_fenxi_num++;
			set_num++;
		}
		else
		{
			while (!((set[set_num] >= 'a' && set[set_num] <= 'z') || (set[set_num] >= 'A' && set[set_num] <= 'Z') || (set[set_num] >= '0' && set[set_num] <= '9') || set[set_num] == '+' || set[set_num] == '-' || set[set_num] == '*' || set[set_num] == '/' || set[set_num] == '='))
			{
				if (set[set_num] == ' ');
				else if (set[set_num] == '\0') break;
				else 
				{
					set_fenxi[set_fenxi_num] = set_fenxi[set_fenxi_num] + set[set_num];
				}
				set_num++;
			}
			set_fenxi_num++;
			if (set[set_num == '\0']) break;
			else set_num++;
		}
	}
	                  //对set_fenxi数组进行处理

	int set_chuli_num = 0;
	int set_shuxing_num = 0;
	int name_left_num;
	int name_right_num;
	int xiugai_int;
	string xiugai_name;
	int operateSymbol = 0;
	if ((set_fenxi[set_chuli_num][0] >= 'a' && set_fenxi[set_chuli_num][0] <= 'z') || (set_fenxi[set_chuli_num][0] >= 'A' && set_fenxi[set_chuli_num][0] <= 'Z'))
	{
		while (strcmp(d.attrs[set_shuxing_num].name, set_fenxi[set_chuli_num].c_str()) && d.attrs[set_shuxing_num].name[0] != -52)
		{
			set_shuxing_num++;
		}
		if (d.attrs[set_shuxing_num].name[0] == -52)
		{
			cout << "不存在要修改的属性名(update函数)" << endl;
			e = -1;
			return;
		}
		name_left_num = set_shuxing_num + 1;
		set_chuli_num++;
	}
	else
	{
		cout << "=左边必须是可以修改的左值" << endl;
		e = -1;
		return;
	}
	if (set_fenxi[set_chuli_num] == "=")
	{
		set_chuli_num++;
	}
	else
	{
		cout << "where条件之前必须是一个等式(update函数)" << endl;
		e = -1;
		return;
	}
	while (set_fenxi[set_chuli_num] != "")
	{
		set_shuxing_num = 0;
		if ((set_fenxi[set_chuli_num][0] >= 'a' && set_fenxi[set_chuli_num][0] <= 'z') || (set_fenxi[set_chuli_num][0] >= 'A' && set_fenxi[set_chuli_num][0] <= 'Z'))
		{
			xiugai_name = set_fenxi[set_chuli_num];
			while (strcmp(d.attrs[set_shuxing_num].name, set_fenxi[set_chuli_num].c_str()) && d.attrs[set_shuxing_num].name[0] != -52)
			{
				set_shuxing_num++;
			}
			if (d.attrs[set_shuxing_num].name[0] == -52)
			{
				
			}
			else
			{
				name_right_num = set_shuxing_num + 1;
				if (name_right_num == name_left_num);
				else
				{
					cout << "暂时无法处理该表达式(update函数)" << endl;
					e = -1;
					return;
				}
			}
		}
		else if (set_fenxi[set_chuli_num][0] >= '0' && set_fenxi[set_chuli_num][0] <= '9')
		{
			xiugai_int = atoi(set_fenxi[set_chuli_num].c_str());
			if (errno == ERANGE)
			{
				cout << "数太大或者太小不能转换" << endl;
			}
			else if (errno == EINVAL)
			{
				
				cout << "不能转换成数字" << endl;
			}
		}
		else if (set_fenxi[set_chuli_num][0] == '+')
		{
			operateSymbol = 1;
		}
		else if (set_fenxi[set_chuli_num][0] == '-')
		{
			operateSymbol = 2;
		}
		else if (set_fenxi[set_chuli_num][0] == '*')
		{
			operateSymbol = 3;
		}
		else if (set_fenxi[set_chuli_num][0] == '/')
		{
			operateSymbol = 4;
		}
		else
		{
			xiugai_name = set_fenxi[set_chuli_num];
		}
		set_chuli_num++;
	}
	//对文件中等于记录数组(jilu_shuzu[])中的记录进行修改放到guodu.txt中并复制回去
	int rewrite_jishuqi = 0;
	table.close();
	attrData.close();
	int guodu_jilu_num = 0;
	int guodu_jishuqi = 0;
	int guodu_shuxing_num;
	guodu.close();
	table.open(name + ".txt", ios_base::in);
	attrData.open("attrData.txt", ios_base::in);
	guodu.open("guodu.txt", ios_base::out);
	if (operateSymbol == 0)
	{
		while (!table.eof())
		{
			guodu_shuxing_num = 1;
			table.read(zifu, sizeof(zifu));
			if (table.eof()) break;
			if (guodu_jilu_num == jilu_shuzu[guodu_jishuqi])
			{
				while (guodu_shuxing_num != d.attr_num)
				{
					if (name_left_num == guodu_shuxing_num)
					{
						if (xiugai_name != "")
						{
							strcpy_s(zifu, xiugai_name.c_str());
							guodu.write(zifu, sizeof(zifu));
						}
						else
						{
							stringstream ss;
							string s1;
							ss << xiugai_int;
							ss >> s1;
							strcpy_s(zifu, s1.c_str());
							guodu.write(zifu, sizeof(zifu));
						}
					}
					else guodu.write(zifu, sizeof(zifu));
					table.read(zifu, sizeof(zifu));
					if (table.eof()) break;
					guodu_shuxing_num++;
				}
				guodu.write(zifu, sizeof(zifu));
				update_yesorno = 1;
				guodu_jishuqi++;
			}
			else
			{
				while (guodu_shuxing_num != d.attr_num)
				{
					guodu.write(zifu, sizeof(zifu));
					table.read(zifu, sizeof(zifu));
					if (table.eof()) break;
					guodu_shuxing_num++;
				}
				guodu.write(zifu, sizeof(zifu));
			}
			guodu_jilu_num++;
		}
	}

	else if (operateSymbol == 1)
	{
		while (!table.eof())
		{
			guodu_shuxing_num = 1;
			table.read(zifu, sizeof(zifu));
			if (table.eof()) break;
			if (guodu_jilu_num == jilu_shuzu[guodu_jishuqi])
			{
				while (guodu_shuxing_num != d.attr_num)
				{
					if (name_left_num == guodu_shuxing_num)
					{
							stringstream ss;
							stringstream sss;
							int convert_int;
							string s1;
							ss << zifu;
							ss >> convert_int;
							convert_int = xiugai_int + convert_int;
							sss << convert_int;
							sss >> s1;
							strcpy_s(zifu, s1.c_str());
							guodu.write(zifu, sizeof(zifu));
					}
					else guodu.write(zifu, sizeof(zifu));
					table.read(zifu, sizeof(zifu));
					if (table.eof()) break;
					guodu_shuxing_num++;
				}
				guodu.write(zifu, sizeof(zifu));
				update_yesorno = 1;
				guodu_jishuqi++;
			}
			else
			{
				while (guodu_shuxing_num != d.attr_num)
				{
					guodu.write(zifu, sizeof(zifu));
					table.read(zifu, sizeof(zifu));
					if (table.eof()) break;
					guodu_shuxing_num++;
				}
				guodu.write(zifu, sizeof(zifu));
			}
			guodu_jilu_num++;
		}
	}
	else if (operateSymbol == 2)
	{
		while (!table.eof())
		{
			guodu_shuxing_num = 1;
			table.read(zifu, sizeof(zifu));
			if (table.eof()) break;
			if (guodu_jilu_num == jilu_shuzu[guodu_jishuqi])
			{
				while (guodu_shuxing_num != d.attr_num)
				{
					if (name_left_num == guodu_shuxing_num)
					{
						stringstream ss;
						stringstream sss;
						int convert_int;
						string s1;
						ss << zifu;
						ss >> convert_int;
						convert_int = convert_int - xiugai_int;
						sss << convert_int;
						sss >> s1;
						strcpy_s(zifu, s1.c_str());
						guodu.write(zifu, sizeof(zifu));
					}
					else guodu.write(zifu, sizeof(zifu));
					table.read(zifu, sizeof(zifu));
					if (table.eof()) break;
					guodu_shuxing_num++;
				}
				guodu.write(zifu, sizeof(zifu));
				update_yesorno = 1;
				guodu_jishuqi++;
			}
			else
			{
				while (guodu_shuxing_num != d.attr_num)
				{
					guodu.write(zifu, sizeof(zifu));
					table.read(zifu, sizeof(zifu));
					if (table.eof()) break;
					guodu_shuxing_num++;
				}
				guodu.write(zifu, sizeof(zifu));
			}
			guodu_jilu_num++;
		}
	}
	else if (operateSymbol == 3)
	{
		while (!table.eof())
		{
			guodu_shuxing_num = 1;
			table.read(zifu, sizeof(zifu));
			if (table.eof()) break;
			if (guodu_jilu_num == jilu_shuzu[guodu_jishuqi])
			{
				while (guodu_shuxing_num != d.attr_num)
				{
					if (name_left_num == guodu_shuxing_num)
					{
						stringstream ss;
						stringstream sss;
						int convert_int;
						string s1;
						ss << zifu;
						ss >> convert_int;
						convert_int = xiugai_int * convert_int;
						sss << convert_int;
						sss >> s1;
						strcpy_s(zifu, s1.c_str());
						guodu.write(zifu, sizeof(zifu));
					}
					else guodu.write(zifu, sizeof(zifu));
					table.read(zifu, sizeof(zifu));
					if (table.eof()) break;
					guodu_shuxing_num++;
				}
				guodu.write(zifu, sizeof(zifu));
				update_yesorno = 1;
				guodu_jishuqi++;
			}
			else
			{
				while (guodu_shuxing_num != d.attr_num)
				{
					guodu.write(zifu, sizeof(zifu));
					table.read(zifu, sizeof(zifu));
					if (table.eof()) break;
					guodu_shuxing_num++;
				}
				guodu.write(zifu, sizeof(zifu));
			}
			guodu_jilu_num++;
		}
	}
	else if (operateSymbol == 4)
	{
		while (!table.eof())
		{
			guodu_shuxing_num = 1;
			table.read(zifu, sizeof(zifu));
			if (table.eof()) break;
			if (guodu_jilu_num == jilu_shuzu[guodu_jishuqi])
			{
				while (guodu_shuxing_num != d.attr_num)
				{
					if (name_left_num == guodu_shuxing_num)
					{
						stringstream ss;
						stringstream sss;
						int convert_int;
						string s1;
						ss << zifu;
						ss >> convert_int;
						convert_int = xiugai_int / convert_int;
						sss << convert_int;
						sss >> s1;
						strcpy_s(zifu, s1.c_str());
						guodu.write(zifu, sizeof(zifu));
					}
					else guodu.write(zifu, sizeof(zifu));
					table.read(zifu, sizeof(zifu));
					if (table.eof()) break;
					guodu_shuxing_num++;
				}
				guodu.write(zifu, sizeof(zifu));
				update_yesorno = 1;
				guodu_jishuqi++;
			}
			else
			{
				while (guodu_shuxing_num != d.attr_num)
				{
					guodu.write(zifu, sizeof(zifu));
					table.read(zifu, sizeof(zifu));
					if (table.eof()) break;
					guodu_shuxing_num++;
				}
				guodu.write(zifu, sizeof(zifu));
			}
			guodu_jilu_num++;
		}
	}
	guodu.close();
	table.close();
	guodu.open("guodu.txt", ios::in);
	table.open(name + ".txt", ios::out);
	string rewrite;
	guodu >> rewrite;
	table << rewrite;
	guodu.close();
	table.close();
	if (update_yesorno == 0)
	{
		cout << "没有修改任何记录，因为没有满足条件的记录" << endl;
	}
	else
	{
		cout << "修改记录成功" << endl;
	}
	cout << "update函数执行成功" << endl;
}

void Delete(int &e)
{
	cout << "正在执行delete函数……" << endl;
	int xiugai = 0;
	string s;
	cin >> s;
	char zifu[30];
	if (s != "from")
	{
		cout << "delete后接from" << endl;
		e = -1;
		return;
	}
	cin >> s;
	string name;
	name = s;
	fstream table, attrData, guodu;
	table.open(name + ".txt", ios_base::in);
	attrData.open("attrData.txt", ios_base::in);
	cin >> s;
	if (s != "where")
	{
		table.close();
		attrData.close();
		cout << "delete函数缺少where条件" << endl;
		e = -1; 
		return;
	}
	database d;
	int shuxing_num;
	int jilu_num = 0;
	int jilu_shuzu[50];
	int jishuqi = 0;

	where(name, d, jilu_shuzu, e);

	if (e == -1) return;
	table.close();
	table.open(name + ".txt", ios_base::in);
	guodu.open("guodu.txt", ios_base::out);
	int guodu_jilu_num = 0;
	int guodu_jishuqi = 0;
	int guodu_shuxing_num;
	while (!table.eof())
	{
		guodu_shuxing_num = 1;
		table.read(zifu, sizeof(zifu));
		if (table.eof()) break;
		if (guodu_jilu_num == jilu_shuzu[guodu_jishuqi])
		{
			while (guodu_shuxing_num != d.attr_num)
			{
				table.read(zifu, sizeof(zifu));
				if (table.eof()) break;
				guodu_shuxing_num++;
			}
			xiugai = 1;
			guodu_jishuqi++;
		}
		else
		{
			while (guodu_shuxing_num != d.attr_num)
			{
				guodu.write(zifu, sizeof(zifu));
				table.read(zifu, sizeof(zifu));
				if (table.eof()) break;
				guodu_shuxing_num++;
			}
			guodu.write(zifu, sizeof(zifu));
		}
		guodu_jilu_num++;
	}
	if (xiugai == 0)
	{
		cout << "没有任何记录被删除，因为没有符合条件的记录(delete函数)" << endl;
	}
	table.close();
	guodu.close();
	table.open(name + ".txt", ios::out);
	guodu.open("guodu.txt", ios::in);
	string guodu_s;
	guodu >> guodu_s;
	table << guodu_s;
	table.close();
	guodu.close();
	table.open(name + ".txt", ios::in);
	table >> guodu_s;
	if (guodu_s == "")
	{
		table.close();
		table.open(name + ".txt", ios::out);
		table << "-1";
	}
	table.close();
	cout << "delete函数执行成功" << endl;
}

void select(int &e)
{
	string selectQuzifu;
	string s[5];
	fstream selectGuodu, selectGuodu1;
	int selectShuxing_shuzu[5];
	int selectShuxingNameNum = 0;
	char ch;
	ch = getWordWithoutSymbol(s[selectShuxingNameNum]);
	selectShuxingNameNum++;
	while (ch == ',')
	{
		ch = getWordWithoutSymbol(s[selectShuxingNameNum]);
		selectShuxingNameNum++;
	}
	cin >> selectQuzifu;
	if (selectQuzifu != "from")
	{
		cout << "属性名后跟from关键字(select函数)" << endl;
		e = -1;
		return;
	}
	ch = getWordWithoutSymbol(selectQuzifu);
	string tableNameShuzu[5];
	string tableName;
	int tableNameNum = 0;
	while (ch == ' ') 
		ch = getchar();

	if (ch == ',')
	{
		database selectDatabase;
		strcpy_s(selectDatabase.name, "guodu");
		tableNameShuzu[tableNameNum] = selectQuzifu;
		tableNameNum++;
		while (ch == ',')
		{
			ch = getWordWithoutSymbol(selectQuzifu);
			while (ch == ' ') ch = getchar();
			tableNameShuzu[tableNameNum] = selectQuzifu;
			tableNameNum++;
		}
		cin >> selectQuzifu;
		selectQuzifu = ch + selectQuzifu;
		if (selectQuzifu != "where")
		{
			cout << "表名后跟where条件(select函数)" << endl;
			e = -1;
			return;
		}
		tableNameNum = 0;
		fstream table, attrData;
		int databaseNum = 0;
		database d[5];
		selectDatabase.attr_num = 0;

/***************************对所有的表名进行检查*************************/

		while (tableNameShuzu[tableNameNum] != "")
		{
			attrData.open("attrData.txt", ios_base::in);
			attrData.read((char *)&d[databaseNum], sizeof(database));
			while ((!attrData.eof()) && strcmp(d[databaseNum].name,tableNameShuzu[tableNameNum].c_str()))
			{
				attrData.read((char *)&d[databaseNum], sizeof(database));
				if (attrData.eof()) break;
			}
			databaseNum++;
			if (attrData.eof())
			{
				cout << "表" << tableNameShuzu[tableNameNum] << "不存在" << endl;
				e = -1;
				return;
			}
			tableNameNum++;
			attrData.close();
		}

/***************************连接各个表(主键)********************************/

		fstream guodu, guodu1;
		guodu.open("guodu.txt", ios_base::out);
		guodu1.open("guodu1.txt", ios_base::out);
		guodu.close();
		guodu1.close();
		string key[5];
		char zifu[3000];
		char zifu1[3000];
		databaseNum = 0;
		int time = 0;
		while (d[databaseNum].name[0] != -52)
		{
			int attrsNum = 0;
			int dAttrsNum = 0;
			while (d[databaseNum].attrs[dAttrsNum].name[0] != -52)
			{
				while (selectDatabase.attrs[attrsNum].name[0] != -52) attrsNum++;
				strcpy_s(selectDatabase.attrs[attrsNum].name, d[databaseNum].attrs[dAttrsNum].name);
				strcpy_s(selectDatabase.attrs[attrsNum].type, d[databaseNum].attrs[dAttrsNum].type);
				strcpy_s(selectDatabase.attrs[attrsNum].is_key, d[databaseNum].attrs[dAttrsNum].is_key);
				strcpy_s(selectDatabase.attrs[attrsNum].is_null, d[databaseNum].attrs[dAttrsNum].is_null);
				selectDatabase.attrs[attrsNum].attr_length = d[databaseNum].attrs[dAttrsNum].attr_length;
				dAttrsNum++;
			}
			//两个文件做笛卡尔积
			table.close();
			if (time == 0)
			{
				table.open(tableNameShuzu[databaseNum] + ".txt", ios::in);
				string str;
				table >> str;
				guodu.open("guodu.txt", ios::out);
				guodu << str;
				guodu.close();
				table.close();
				selectDatabase.attr_num = d[databaseNum].attr_num;
			}
			else
			{
				guodu.open("guodu.txt", ios_base::in);
				while (!guodu.eof())
				{
					guodu.read(zifu, sizeof(char[30]) * selectDatabase.attr_num);
					if (guodu.eof()) break;
					table.close();
					table.open(tableNameShuzu[databaseNum] + ".txt", ios_base::in);
					guodu1.open("guodu1.txt", ios_base::app);
					while (!table.eof())
					{
						table.read(zifu1, sizeof(char[30])*d[databaseNum].attr_num);
						if (table.eof()) break;
						guodu1.write(zifu, sizeof(char[30])*selectDatabase.attr_num);
						guodu1.write(zifu1, sizeof(char[30])*d[databaseNum].attr_num);
					}
					guodu1.close();
				}
				selectDatabase.attr_num = selectDatabase.attr_num + d[databaseNum].attr_num;
			}
			databaseNum++;
			time++;
			guodu.close();
			string s;
			if (time == 1);
			else
			{
				guodu1.open("guodu1.txt", ios::in);
				guodu.open("guodu.txt", ios::out);
				guodu1 >> s;
				guodu << s;
				guodu.close();
				guodu1.close();
				guodu1.open("guodu1.txt", ios::out);
				guodu1.close();
			}
		}
		attrData.open("attrData.txt", ios_base::in);
		selectGuodu1.open("guodu1.txt", ios::out);
		string s1;
		attrData >> s1;
		selectGuodu1 << s1;
		selectGuodu1.close();
		attrData.close();
		attrData.open("attrData.txt", ios_base::app);
		attrData.write((char *)&selectDatabase, sizeof(database));
		attrData.close();


		selectShuxingNameNum = 0;
		int databaseShuxingNum = 0;
		int shuxing_shuzuNum = 0;
		while (s[selectShuxingNameNum] != "")
		{
			databaseShuxingNum = 0;
			while (strcmp(selectDatabase.attrs[databaseShuxingNum].name, s[selectShuxingNameNum].c_str()))
			{
				databaseShuxingNum++;
				if (selectDatabase.attrs[databaseShuxingNum].name[0] == -52) break;
			}
			if (selectDatabase.attrs[databaseShuxingNum].name[0] == -52)
			{
				cout << "在" << tableName << "表中没有找到" << s[selectShuxingNameNum] << "属性,在结果中不予显示" << endl;
			}
			else
			{
				selectShuxing_shuzu[shuxing_shuzuNum] = databaseShuxingNum;
				shuxing_shuzuNum++;
			}
			selectShuxingNameNum++;
		}

		int jilu_shuzu[100];
		where("guodu", selectDatabase, jilu_shuzu, e);

		if (e == -1) return;
		table.close();
		table.open("guodu.txt", ios_base::in);
		int jishuqi = 0;
		int shuxing_num = 0;
		int jilu_num = 0;
		char zifu2[30];
		while (!table.eof())
		{
			shuxing_num = 0;
			if (jilu_num == jilu_shuzu[jishuqi])
			{
				while (shuxing_num < selectDatabase.attr_num)
				{
					table.read(zifu2, sizeof(char[30]));
					if (table.eof()) break;
					shuxing_shuzuNum = 0;
					while (selectShuxing_shuzu[shuxing_shuzuNum] != shuxing_num && selectShuxing_shuzu[shuxing_shuzuNum] >= 0)
					{
						shuxing_shuzuNum++;
					}
					if (selectShuxing_shuzu[shuxing_shuzuNum] == shuxing_num)
					{
						cout << zifu2 << "  ";
					}
					shuxing_num++;
				}
				jishuqi++;
				cout << endl;
			}
			else
			{
				while (shuxing_num < selectDatabase.attr_num)
				{
					table.read(zifu2, sizeof(char[30]));
					if (table.eof())break;
					shuxing_num++;
				}
			}
			jilu_num++;
		}
		string str;
//		printTable("guodu", e);
		attrData.open("attrData.txt", ios::out);
		selectGuodu1.open("guodu1.txt", ios::in);
		selectGuodu1 >> str;
		attrData << str;
		selectGuodu1.close();
		attrData.close();
	}
	else
	{
		tableName = selectQuzifu;
		fstream table, attrData;
		table.open(tableName + ".txt", ios::in);
		string panduanSelect;
		table >> panduanSelect;
		if (panduanSelect == "")
		{
			cout << "要查询的表不存在(select函数)" << endl;
			e = -1;
			return;
		}
		else if (panduanSelect == "-1")
		{
			cout << "表中没有任何数据(select函数)" << endl;
			e = -1;
			return;
		}
		table.close();

		attrData.open("attrData.txt", ios_base::in);
		database selectDatabase;
		while (!attrData.eof())
		{
			attrData.read((char *)&selectDatabase, sizeof(database));
			if (attrData.eof()) break;
			if (!strcmp(selectDatabase.name, tableName.c_str())) break;
		}
		if (attrData.eof())
		{
			cout << "在系统表中没有对应的database(select函数)" << endl;
			attrData.close();
			e = -1;
			return;
		}

		selectShuxingNameNum = 0;
		int databaseShuxingNum = 0;
		int shuxing_shuzuNum = 0;
		while (s[selectShuxingNameNum] != "")
		{
			databaseShuxingNum = 0;
			while (strcmp(selectDatabase.attrs[databaseShuxingNum].name, s[selectShuxingNameNum].c_str()))
			{
				databaseShuxingNum++;
				if (selectDatabase.attrs[databaseShuxingNum].name[0] == -52) break;
			}
			if (selectDatabase.attrs[databaseShuxingNum].name[0] == -52)
			{
				cout << "在" << tableName << "表中没有找到" << s[selectShuxingNameNum] << "属性,在结果中不予显示" << endl;
			}
			else
			{
				selectShuxing_shuzu[shuxing_shuzuNum] = databaseShuxingNum;
				shuxing_shuzuNum++;
			}
			selectShuxingNameNum++;
		}

		cin >> selectQuzifu;
		selectQuzifu = ch + selectQuzifu;
		if (selectQuzifu != "where")
		{
			cout << "缺少where条件(select函数)" << endl;
			e = -1;
			return;
		}

		database d;
		char zifu[30];
		int shuxing_num;
		int jilu_num = 0;
		int jilu_shuzu[50];
		int jishuqi = 0;

		where(tableName, d, jilu_shuzu, e);

		if (e == -1) return;
		table.close();
		table.open(tableName + ".txt", ios_base::in);
		jishuqi = 0;
		shuxing_num = 0;
		jilu_num = 0;
		while (!table.eof())
		{
			shuxing_num = 0;
			if (jilu_num == jilu_shuzu[jishuqi])
			{
				while (shuxing_num < selectDatabase.attr_num)
				{
					table.read(zifu, sizeof(zifu));
					if (table.eof()) break;
					shuxing_shuzuNum = 0;
					while (selectShuxing_shuzu[shuxing_shuzuNum] != shuxing_num && selectShuxing_shuzu[shuxing_shuzuNum] >= 0)
					{
						shuxing_shuzuNum++;
					}
					if (selectShuxing_shuzu[shuxing_shuzuNum] == shuxing_num)
					{
						cout << zifu << "  ";
					}
					shuxing_num++;
				}
				jishuqi++;
				cout << endl;
			}
			else
			{
				while (shuxing_num < selectDatabase.attr_num)
				{
					table.read(zifu, sizeof(zifu));
					if (table.eof())break;
					shuxing_num++;
				}
			}
			jilu_num++;
		}
	}
}

void PretendMain()
{
	char pd;
	int e = 10;
	string s;
	database d[100];
	int database_num;
	database_num = 0;
	while (e != 0)
	{
		cifa(e, s);
		if (e == 1)
		{
			cin >> s;
			if (s == "table")
			{
				getWordWithoutSymbol(s);
				createTable(d[database_num], s, e);
				database_num++;
			}
			else if (s == "view")
			{
				getWordWithoutSymbol(s);
//				createView(s);
			}
			else if (s == "index")
			{
				getWordWithoutSymbol(s);
//				createIndex(s);
			}
			else if (s == "user")
			{
				getWordWithoutSymbol(s);
//				createView(s);
			}
			else
			{
				cout << "create后必须跟table/view/index/user" << endl;
				e = -1;
			}
		}
		else if (e == 2)
		{
			cin >> s;
			if (s == "table")
			{
				cin >> s;
				dropTable(s);
			}
			else if (s == "view")
			{
				cin >> s;
//				dropView(s);
			}
			else if (s == "index")
			{
				cin >> s;
//				dropIndex(s);
			}
			else
			{
				cout << "drop后必须接table/view/index" << endl;
				e = -1;
			}
		}
		else if (e == 3)
		{
			cin >> s;
			if (s == "table")
			{
				cin >> s;
				alterTable(s, e);
			}
			else
			{
				cout << "alter后必须接table" << endl;
				e = -1;
			}
		}
		else if (e == 4)
		{
			cin >> s;
			if (s == "into")
			{
				getWordWithoutSymbol(s);
				insertInto(s, e);
			}
			else
			{
				cout << "insert后必须接into" << endl;
				e = -1;
			}
		}
		else if (e == 5)
		{
			Delete(e);
		}
		else if (e == 6)
		{
			cin >> s;
			update(s,e);
		}
		else if (e == 7)
		{
			select(e);
		}
		else if (e == 8)
		{
//			grant();
		}
		else if (e == 9)
		{
//			revoke();
		}
		else if (e == 0)
		{
			break;
		}
		else if (e == 30)
		{
			cin >> s;
			printTable(s,e);
		}
		else
		{
			cout << "第一个单词有错误" << endl;
			e = -1;
		}
		if (e == -1)
		{
			if (flag == 1) flag = 0;
			else
			{
				pd = getchar();
				while (pd != '\n') pd = getchar();
			}
			cout << "执行失败,请检查" << endl;
		}
	}
}

void main()
{
	PretendMain();
	system("pause");
}
