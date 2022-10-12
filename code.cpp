#include <iostream>
#include <string>
#include <fstream>
using namespace std;
struct elem                               //
{
	int type;                                     
	string token;
	struct elem* next;
};
struct table
{
	int total;
	struct elem* head;
	struct elem* tail;
};
struct table t;
string text;
ifstream f;
ofstream fout;
int total_char = 0;
int total_line = 1;
int c[6] = { 0 };
string key_word[] = { "auto","break","case","char","const","continue","default","do","double","else",
"enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof"
,"static","struct","switch","typedef","union","unsigned","void","volatile","while" };

void init(void)                             //初始化
{
	t.total = 0;
	struct elem* temp = new elem;
	t.head = temp;
	t.tail = t.head;
	temp->next = NULL;
	fout.open("out.txt", ios::out);
}
void get(char& c)                         //从文件读取一个字符
{
	c = f.get();
	total_char++;
	if (c == '\n')
		total_line++;
}
void retract(char& c)                        //回退一个字符
{
	f.seekg(-1, ios_base::cur);
	total_char--;
	if (c == '\n')
		total_line--;
}
void get_nbc(char &c)                      //跳过空格
{
	while (c == ' ')
	{
		c = f.get();
	}
}
bool isletter(char c)           
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return true;
	else
		return false;
}
bool isdigit(char c) 
{
	if (c >= '0' && c <= '9')
		return true;
	else
		return false;
}
 
void return_token(string token,int type)
{
	if (token != " ")
	{
		cout << token << " " << type << endl;
		fout << token << " " << type << endl;
		c[type]++;
	}
}

bool reserve(string token)                       //查关键字码表
{
	for (int i = 0; i < 32; i++)
	{
		if (token.compare(key_word[i]) == 0)
			return true;
	}
	return false;
}
string table_insert(string token,int type)              //插入符号表
{
	struct elem* temp = new elem;
	if (!temp)
	{
		cout << "space error\n";
		exit(-1);
	}
	temp->type = 5;
	temp->token = token;
	temp->next = NULL;
	t.tail->next = temp;
	t.tail = temp;
	t.total++;
	char* p = &temp->token[0];
	string t = p;
	return t;
}
void deal_error(char &c)                             //错误处理
{
	cout << "lines " << total_line << " error\n";
	fout << "lines " << total_line << " error\n";
	while (c != ' ' && !f.eof())c = f.get();
}
void analyze_word(void)                          //词法分析
{
	string FileName;
	string token;
	char c;
	int iskey;
	cout << "输入文件名\n";
	cin >> FileName;
	f.open(FileName, ios::in);
	int state = 0;
	do
	{
		switch (state)
		{
		case 0:
			token = "";
			get(c);
			get_nbc(c);
			switch (c)
			{
			case 'a':case 'b':case 'c':case 'd':case 'e':case 'f':case 'g':case 'h':case 'i':case 'j':
			case 'k':case 'l':case 'm':case 'n':case 'o':case 'p':case 'q':case 'r':case 's':case 't':
			case 'u':case 'v':case 'w':case 'x':case 'y':case 'z':
			case 'A':case 'B':case 'C':case 'D':case 'E':case 'F':case 'G':case 'H':case 'I':case 'J':
			case 'K':case 'L':case 'M':case 'N':case 'O':case 'P':case 'Q':case 'R':case 'S':case 'T':
			case 'U':case 'V':case 'W':case 'X':case 'Y':case 'Z':
				state = 1;
				break;
			case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
				state = 2;
				break;
			case'<':
				state = 8;
				break;
			case'>':
				state = 9;
				break;
			case'!':
				state = 10;
				break;
			case'/':
				state = 11;
				break;
			case'=':
				state = 10;
				break;
			case'+':
				state = 0;
				return_token("+", 4);
				break;
			case '-':
				state = 0;
				return_token("-", 4);
				break;
			case'*':
				state = 0;
				return_token("*", 4);
				break;
			case'(':
				state = 0;
				return_token("(", 5);
				break;
			case')':
				state = 0;
				return_token(")", 5);
				break;
			case';':
				state = 0;
				return_token(";", 5);
				break;
			case'\\':
				state = 0;
				return_token("\\", 5);
				break;
			case'\'':
				state = 0;
				return_token("\'", 5);
				break;
			case',':
				state = 0;
				return_token(",", 5);
				break;
			case'[':
				state = 0;
				return_token("[", 5);
				break;
			case']':
				state = 0;
				return_token("]", 5);
				break;
			case'{':
				state = 0;
				return_token("{", 5);
				break;
			case'\"':
				state = 0;
				return_token("\"", 5);
				break;
			case'%':
				state = 0;
				return_token("%", 5);
				break;
			case '\n':
				state = 0;
				break;
			default:
				state = 13;
				break;
			}
			break;
		case 1:
			token = token + c;
			get(c);;
			if (isletter(c) || isdigit(c))
				state = 1;
			else
			{
				retract(c);
				state = 0;
				iskey = reserve(token);
				if (iskey == 1)
					return_token(token, 1);
				else
				{
					string identry = table_insert(token,1);
						return_token(token, 2);
				}
			}
			break;
		case 2:
			token += c;
			get(c);
			switch (c)
			{
			case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
				state = 2;
				break;
			case '.':
				state = 3;
				break;
			case'E':
				state = 5;
				break;
			default:
				if (isletter(c))
				{
					state = 13;
				}
				else {
					retract(c);
					state = 0;
					return_token(token, 3);
				}
				break;
			}
			break;
		case 3:
			token += c;
			c = f.get();
			if (isdigit(c))state = 4;
			else
			{
				deal_error(c);
				state = 0;
			}
			break;
		case 4:
			token += c;
			get(c);
			switch (c)
			{
			case '0':case'1':case'2':case '3':case'4':case'5':case '6':case'7':case '8':case'9':
				state = 4;
				break;
			case 'E':
				state = 5;
				break;
			default:
				retract(c);
				state = 0;
				return_token(token, 3);
				break;
			}
			break;
		case 5:
			token += c;
			c = f.get();
			switch (c)
			{
			case '0':case'1':case'2':case '3':case'4':case'5':case '6':case'7':case '8':case'9':
				state = 7;
				break;
			case'+':case'-':
				state = 6;
				break;
			default:
				retract(c);
				state = 0;
				deal_error(c);
				break;
			}
			break;
		case 6:
			token += c;
			get(c);
			if (isdigit(c))state = 7;
			else
			{
				retract(c);
				deal_error(c);
				state = 0;
			}
			break;
		case 7:
			token += c;
			get(c);
			if (isdigit(c))
			{
				state = 7;
				return_token(token, 3);
			}
			break;
		case 8:
			token += c;
			get(c);
			switch (c)
			{
			case '=':
				token += c;
				state = 0;
				return_token(token,4);
				break;
			case'>':
				token += c;
				state = 0;
				return_token(token, 4);
				break;
			default:
				retract(c);
				state = 0;
				return_token(token, 4);
				break;
			}
			break;
		case 9:
			token += c;
			get(c);
			if (c == '=')
			{
				token += c;
				state = 0;
				return_token(token,4);
			}
			else
			{
				retract(c);
				state = 0;
				return_token(token, 4);
			}
			break;
		case 10:
			token += c;
			get(c);
			if (c == '=')
			{
				token += c;
				state = 0;
				return_token(token, 4);
			}
			else
			{
				retract(c);
				state = 0;
				return_token(token, 4);
			}
			break;
		case 11:
			token += c;
			get(c);
			if (c == '*')
				state = 12;
			else
			{
				retract(c);
				state = 0;
				return_token("/", 4);
			}
			break;
		case 12:
			get(c);
			while (c != '*')get(c);
			get(c);
			if (c == '/')state = 0;
			else state = 12;
			break;
		case 13:
			deal_error(c);
			state = 0;
			break;
			default:
				deal_error(c);
				state = 0;
			break;
		}
	} while (!f.eof());
	f.close();
}
void output()                                 //输出
{ 
	cout << total_line << " lines\n";
	cout << total_char << " chars\n";
	cout << "关键词数量：" << c[1] << "\n";
	cout << "符号变量数量：" << c[2] << "\n";
	cout << "常量数量：" << c[3] << "\n";
	cout << "运算符数量：" << c[4] << "\n";
	cout << "界符数量：" << c[5] << "\n";
}
void free_space(void)               //释放空间
{
	struct elem* t1;
	t1 = t.head ;
	while(t1)
	{
		t.head = t.head->next;
		delete t1;
		t1 = NULL;
		t1 = t.head;
	}
}
int main()
{
	init();
	analyze_word();
	output();
	free_space();
	fout.close();
	return 0;
}

