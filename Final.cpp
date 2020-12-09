#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char TOKEN[128];//当前字符串常量（44），或者标识符（51）
int NUM;//当前无符号整数（41，语法分析中允许取负） 
double DOU;//当前无符号浮点数（42，语法分析中允许取负） 

int reser()//关键字表，共10个 
{
	if(strcmp(TOKEN,"as")==0)
	{
		return 1;
	}
	else if(strcmp(TOKEN,"break")==0)
	{
		return 2;
	}
	else if(strcmp(TOKEN,"const")==0)
	{
		return 3;
	}
	else if(strcmp(TOKEN,"continue")==0)
	{
		return 4;
	}
	else if(strcmp(TOKEN,"else")==0)
	{
		return 5;
	}
	else if(strcmp(TOKEN,"fn")==0)
	{
		return 6;
	}
	else if(strcmp(TOKEN,"if")==0)
	{
		return 7;
	}
	else if(strcmp(TOKEN,"let")==0)
	{
		return 8;
	}
	else if(strcmp(TOKEN,"return")==0)
	{
		return 9;
	}
	else if(strcmp(TOKEN,"while")==0)
	{
		return 10;
	}
	else//标识符 
	{
		return 0;
	}
}

FILE *IN;//流指针 

int getToken()//返回下一个TOKEN的类别码，注释视为Token 
{
	int symbol;//待返回类别码 
	char cc=' ';//光标，先置入一个空白字符 
	memset(TOKEN,0,sizeof(TOKEN));//每次调用，TOKEN必须清空 
	while(isspace(cc))//读字符，跳空格、换行和Tab 
	{
		cc=fgetc(IN);
	}
	if(isalpha(cc)||cc=='_')//标识符或关键字 
	{
		while(isalpha(cc)||isdigit(cc)||cc=='_')//将字符拼接成字符串 
		{
			strncat(TOKEN,&cc,1);
			cc=fgetc(IN); 
		}
		ungetc(cc,IN);//指针后退一个字符
		int resultValue=reser();//resultValue查找保留字的返回值 
		if(resultValue==0)//TOKEN中字符串为标识符 
		{
			symbol=51;
		}
		else//TOKEN中字符串为保留字 
		{
			symbol=resultValue;
		}
	}
	else if(isdigit(cc))//整数和浮点数 
	{
		while(isdigit(cc))//将字符拼接成整数 
		{
			strncat(TOKEN,&cc,1);
			cc=fgetc(IN);
		}
		if(cc='.')//有小数点
		{
			cc=fgetc(IN);//先不急着拼接，再读一个 
			if(!isdigit(cc))//没有数字，证明不是浮点数 
			{
				ungetc(cc,IN);//退回非数字 
				ungetc(cc,IN);//退回小数点
				NUM=atoi(TOKEN);//将TOKEN中的字符串转换为整数 
				symbol=41;//此时识别的单词是整数 
			}
			else//有数字，那么至少这部分已经是一个浮点数 
			{
				char poi='.'; 
				strncat(TOKEN,&poi,1);//先接一个小数点，因为cc已经是数字了 
				while(isdigit(cc))
				{
					strncat(TOKEN,&cc,1);
					cc=fgetc(IN);
				}
				if(cc=='e'||cc=='E')//还有可能，后面接E或e
				{
					cc=fgetc(IN);//先不急着拼接，再读一个
					if(cc=='+')//有可能是+ 
					{
						cc=fgetc(IN);//先不急着拼接，再读一个
						if(!isdigit(cc))//非数字，证明此部分无效 
						{
							ungetc(cc,IN);//退回非数字 
							ungetc(cc,IN);//退回符号 
							ungetc(cc,IN);//退回e
							DOU=atof(TOKEN);//将TOKEN中的字符串转换为浮点数 
							symbol=42;//此时识别的单词是浮点数 
						}
						else//是数字，这部分有效 
						{
							char eee='e'; 
							strncat(TOKEN,&eee,1);
							char fff='+';
							strncat(TOKEN,&fff,1);
							while(isdigit(cc))
							{
								strncat(TOKEN,&cc,1);
								cc=fgetc(IN);
							}
							ungetc(cc,IN);//退回字符 
							DOU=atof(TOKEN);//将TOKEN中的字符串转换为浮点数 
							symbol=42;//此时识别的单词是浮点数 
						}
					}
					else if(cc=='-')//有可能是-
					{
						cc=fgetc(IN);//先不急着拼接，再读一个
						if(!isdigit(cc))//非数字，证明此部分无效 
						{
							ungetc(cc,IN);//退回非数字 
							ungetc(cc,IN);//退回符号 
							ungetc(cc,IN);//退回e
							DOU=atof(TOKEN);//将TOKEN中的字符串转换为浮点数 
							symbol=42;//此时识别的单词是浮点数 
						}
						else//是数字，这部分有效 
						{
							char eee='e'; 
							strncat(TOKEN,&eee,1);
							char fff='-';
							strncat(TOKEN,&fff,1);
							while(isdigit(cc))
							{
								strncat(TOKEN,&cc,1);
								cc=fgetc(IN);
							}
							ungetc(cc,IN);//退回字符 
							DOU=atof(TOKEN);//将TOKEN中的字符串转换为浮点数 
							symbol=42;//此时识别的单词是浮点数 
						}
					}
					else if(!isdigit(cc))//非数字，证明此部分无效 
					{
						ungetc(cc,IN);//退回非数字 
						ungetc(cc,IN);//退回e
						DOU=atof(TOKEN);//将TOKEN中的字符串转换为浮点数 
						symbol=42;//此时识别的单词是浮点数 
					}
					else//是数字，这部分有效 
					{
						char eee='e'; 
						strncat(TOKEN,&eee,1);//先接一个e，因为cc已经是数字了 
						while(isdigit(cc))
						{
							strncat(TOKEN,&cc,1);
							cc=fgetc(IN);
						}
					}
				}
			}
		}
		else if(cc=='e'||cc=='E')//还有可能，后面接E或e
		{
			cc=fgetc(IN);//先不急着拼接，再读一个
			if(cc=='+')//有可能是+ 
			{
				cc=fgetc(IN);//先不急着拼接，再读一个
				if(!isdigit(cc))//非数字，证明此部分无效 
				{
					ungetc(cc,IN);//退回非数字 
					ungetc(cc,IN);//退回符号 
					ungetc(cc,IN);//退回e
					NUM=atoi(TOKEN);//将TOKEN中的字符串转换为整数 
					symbol=41;//此时识别的单词是整数 
				}
				else//是数字，这部分有效 
				{
					char eee='e'; 
					strncat(TOKEN,&eee,1);
					char fff='+';
					strncat(TOKEN,&fff,1);
					while(isdigit(cc))
					{
						strncat(TOKEN,&cc,1);
						cc=fgetc(IN);
					}
					ungetc(cc,IN);//退回字符 
					DOU=atof(TOKEN);//将TOKEN中的字符串转换为浮点数 
					symbol=42;//此时识别的单词是浮点数 
				}
			}
			else if(cc=='-')//有可能是-
			{
				cc=fgetc(IN);//先不急着拼接，再读一个
				if(!isdigit(cc))//非数字，证明此部分无效 
				{
					ungetc(cc,IN);//退回非数字 
					ungetc(cc,IN);//退回符号 
					ungetc(cc,IN);//退回e
					NUM=atoi(TOKEN);//将TOKEN中的字符串转换为整数 
					symbol=41;//此时识别的单词是整数 
				}
				else//是数字，这部分有效 
				{
					char eee='e'; 
					strncat(TOKEN,&eee,1);
					char fff='-';
					strncat(TOKEN,&fff,1);
					while(isdigit(cc))
					{
						strncat(TOKEN,&cc,1);
						cc=fgetc(IN);
					}
					ungetc(cc,IN);//退回字符 
					DOU=atof(TOKEN);//将TOKEN中的字符串转换为浮点数 
					symbol=42;//此时识别的单词是浮点数 
				}
			}
			else if(!isdigit(cc))//非数字，证明此部分无效 
			{
				ungetc(cc,IN);//退回非数字 
				ungetc(cc,IN);//退回e
				NUM=atoi(TOKEN);//将TOKEN中的字符串转换为整数 
				symbol=41;//此时识别的单词是整数 
			}
			else//是数字，这部分有效 
			{
				char eee='e'; 
				strncat(TOKEN,&eee,1);//先接一个e，因为cc已经是数字了 
				while(isdigit(cc))
				{
					strncat(TOKEN,&cc,1);
					cc=fgetc(IN);
				}
				ungetc(cc,IN);//退回字符 
				DOU=atof(TOKEN);//将TOKEN中的字符串转换为浮点数 
				symbol=42;//此时识别的单词是浮点数 
			}
		}
		else//没有小数点，也没有E或e
		{
			ungetc(cc,IN);//退回字符 
			NUM=atoi(TOKEN);//将TOKEN中的字符串转换为整数 
			symbol=41;//此时识别的单词是整数 
		}
	}
	else if(cc=='\'')//单引号情形，要判断是否合法 
	{
		cc=fgetc(IN);
		if(cc=='\''||cc=='\n'||cc=='\t'||cc=='\r')
		{
			exit(-1);//出错 
		}
		else if(cc=='\\')
		{
			cc=fgetc(IN);//这时候有可能出错，还要预读 
			if(cc=='\''||cc=='\"'||cc=='\\'||cc=='n'||cc=='t'||cc=='r')
			{
				char tttt=cc;//暂存
				cc=fgetc(IN);
				if(cc=='\'')//单引号 
				{
					NUM=tttt;//合法
					symbol=41;
				}
				else
				{
					exit(-1);//出错 
				}
			}
			else
			{
				exit(-1);//出错 
			}
		}
		else//既不是出错，也不是转义 
		{
			char tttt=cc;//暂存
			cc=fgetc(IN);//预读
			if(cc=='\'')//合法
			{
				NUM=tttt;
				symbol=41;
			}
			else//非法 
			{
				exit(-1);//出错 
			}
		}
	}
	else if(cc=='\"')//双引号
	{
		cc=fgetc(IN);
		while(cc!='\"')//只要不是双引号就要继续读 
		{
			if(cc=='\n'||cc=='\t'||cc=='\r'||cc=='\0')
			{
				exit(-1);//出错 
			}
			else if(cc=='\\')//可能是转义 
			{
				cc=fgetc(IN);//这时候有可能出错，还要预读 
				if(cc=='\''||cc=='\"'||cc=='\\'||cc=='n'||cc=='t'||cc=='r')
				{
					strncat(TOKEN,&cc,1);
				}
				else
				{
					exit(-1);//出错 
				}
			}
			else//合法
			{
				strncat(TOKEN,&cc,1);
			}
			cc=fgetc(IN);//循环结束时再读一个 
		}
		symbol=44;//结束时cc为双引号，故不必unread 
	}
	else//运算符表，14个单目运算符（9+5），5个双目运算符（1+4），还有注释和EOF也在其中 
	{
		switch(cc)
		{
			case'+'://判断是否加号
				symbol=21;
			break;
			case'*'://判断是否星号
				symbol=22;
			break;
			case'('://判断是否左小括号
				symbol=23;
			break;
			case')'://判断是否右小括号
				symbol=24;
			break;
			case'{'://判断是否左大括号
				symbol=25;
			break;
			case'}'://判断是否右大括号
				symbol=26;
			break;
			case','://判断是否逗号 
				symbol=27;
			break;
			case':'://判断是否冒号
				symbol=28;
			break;
			case';'://判断是否分号 
				symbol=29;
			break;
			case'!':
				cc=fgetc(IN);
				if(cc=='=')
				{
					symbol=30;
				}
				else
				{
					ungetc(cc,IN);
					exit(-1);
				}
			break;
			case'-':
				cc=fgetc(IN);
				if(cc=='>')
				{
					symbol=36;
				}
				else
				{
					ungetc(cc,IN);
					symbol=31;
				}
			break;
			case'/':
				cc=fgetc(IN);
				if(cc=='/')
				{
					while(cc!='\n')
					{
						cc=fgetc(IN);
					}
					symbol=-2;//-2是注释 
				}
				else
				{
					ungetc(cc,IN);
					symbol=32;
				}
			break;
			case'=':
				cc=fgetc(IN);
				if(cc=='=')
				{
					symbol=37;
				}
				else
				{
					ungetc(cc,IN);
					symbol=33;
				}
			break;
			case'<':
				cc=fgetc(IN);
				if(cc=='=')
				{
					symbol=38;
				}
				else
				{
					ungetc(cc,IN);
					symbol=34;
				}
			break;
			case'>':
				cc=fgetc(IN);
				if(cc=='=')
				{
					symbol=39;
				}
				else
				{
					ungetc(cc,IN);
					symbol=35;
				}
			break;
			case EOF://结尾为-1 
				symbol=-1;
			break;
			default://错误
				exit(-1);
		}
	}
	return symbol;
}

//TOKEN为字符串（44）或标识符（51），都存储在TOKEN
char TOKENPRE[128];//预读的字符串常量（44），或者标识符（51）

//TOKEN为整数（41）、浮点数（42）或，存储在NUM、DOU
int NUMPRE;//无符号整数（41，语法分析中允许取负） 
double DOUPRE;//无符号浮点数（42，语法分析中允许取负） 

//TOKEN为关键字、运算符和文档结尾（-1）的时候，直接看返回的编号即可
int SYMPRE;
int PREVALID; 

int nextToken()//返回下一个TOKEN的类别码，注释不视为Token。只要使用nextToken，上一个状态就丢弃了 
{
	int sym;//待返回 
	if(PREVALID==1)//执行过unreadToken。还原之前预读结果，并置valid为0
	{
		sym=SYMPRE;
		PREVALID=0;
		switch(sym)
		{
			case 41://整数 
				NUM=NUMPRE;
			break;
			case 42://浮点数 
				DOU=DOUPRE;
			break;
			case 44://字符串 
				strcpy(TOKEN,TOKENPRE);
			break;
			case 51://标识符 
				strcpy(TOKEN,TOKENPRE);
			break;
			default://其他情况，什么都不用做 
			break;
		}
	}
	else//未执行unreadToken。读入并保存为暂时无效的预读结果 
	{
		sym=getToken();
		while(sym==-2)//发现注释，只好再读一个 
		{
			sym=getToken();
		}
		SYMPRE=sym;
		switch(sym)
		{
			case 41://整数 
				NUMPRE=NUM;
			break;
			case 42://浮点数 
				DOUPRE=DOU;
			break;
			case 44://字符串 
				strcpy(TOKENPRE,TOKEN);
			break;
			case 51://标识符 
				strcpy(TOKENPRE,TOKEN);
			break;
			default://其他情况，什么都不用做 
			break;
		}
	}
	return sym;
}

void unreadToken()//将当前的情形压回栈中。至多只能保存一步预读情形，上一步丢失。禁止连续使用两次。
{
	if(PREVALID==1)//预读已经有效，证明当前位置在预读前，无法再回退 
	{
		exit(-1); 
	}
	else
	{
		PREVALID=1;//置预读为有效 
	}
}

//ty -> IDENT
//必然为void（0）、int（1）或double（2）其一
int ty()//类型：仍旧为标识符（51）。不做开头，不得预读
{
	int tok=nextToken();
	if(tok!=51)
	{
		exit(-1);
	}
	if(strcmp(TOKEN,"void")==0)
	{
		return 0;
	}
	else if(strcmp(TOKEN,"int")==0)
	{
		return 1;
	}
	else if(strcmp(TOKEN,"double")==0)
	{
		return 2;
	}
	else
	{
		exit(-1);
	}
}

struct symbolstack//栈式符号表结构体 
{
	int istop;//1表示这一格是栈顶，新函数开始的前一格。默认为0 
	int destination;//在全局表中的下标。为-1表示未初始化，为-2表示类型为void（或纯字符串）。不给纯字符串变量入口 
	int isfunction;//是函数名的时候设成1。函数名作为全局变量永远不弹出栈 
};

struct symbolstack STACK[128];//符号表 
int STACKTOP;//栈顶下标

struct symboltable//最终符号表结构体。所有的函数名字都要存进去。必须初始化才能放入本表。类型不能为void 
{
	char name[128];//名字，除了纯字符串外不可重复。type为3时有效 
	char isconst;//是常数为1，否则为0（输出长度为8） 
	int type;//1为int，2为double，3为字符串（函数名或者字符串） 
	int value1;//type为1时有效 
	double value2;//type为2时有效 
}; 

struct symboltable TABLE[128];//符号表 
int TABLETOP;//表顶下标 

int find_all(char sss[])//根据变量名查全部符号表栈。查到返回在全局的下标，未查到返回-1。 
{
	int i;
	for(i=STACKTOP-1;i>=0;i--)//倒序查表 
	{
		if(strcmp(TABLE[STACK[i].destination].name,sss)==0)
		{
			return STACK[i].destination;
		}
	}
	return -1;
}

int find_now(char sss[])//根据变量名查当前层符号表栈。查到返回在栈中下标，未查到返回-1。 
{
	int i;
	for(i=STACKTOP-1;STACK[i].istop!=1&&i>=0;i--)//倒序查表 
	{
		if(strcmp(TABLE[STACK[i].destination].name,sss)==0)
		{
			return STACK[i].destination;
		}
	}
	return -1;
}

struct functionlist//全局函数表 
{
	int name;//在全局符号表的位置
	int type;//类型决定返回值有多少个8字节。void为0，int为4，double为8 
	int param;//参数列表决定多少个8字节。int为4，double为8，求和。
	int local;//局部变量有多少个8字节
	int count;//指令数 
	char instr[128];//指令集 
};

struct functionlist FUNCTIONLIST[128];
int FUNCTIONLISTTOP;

// 运算符表达式 operator_expr、取反表达式 negate_expr 和类型转换表达式 as_expr 可以使用局部的算符优先文法

// 运算符表达式，子表达式开头，有子表达式，这只处理算数运算符。运算符的两侧必须是相同类型的数据 
// 优先级和顺序
// * /	左到右
// + -	左到右
// operator_expr -> expr binary_operator expr
// binary_operator -> '+' | '-' | '*' | '/' 

// 以下最高 

// 括号表达式，开头左小括号（23），优先计算 
// group_expr -> '(' expr ')'

// 以下视作整体 

// 字面量表达式，开头整数（41）浮点数（42）
// literal_expr -> UINT_LITERAL | DOUBLE_LITERAL

// 标识符表达式，只有标识符（51）开头，后空。语义是标识符对应的局部或全局变量。标识符表达式的类型与标识符的类型相同
// ident_expr -> IDENT

//# ( + - * / ) 整数（41）和浮点数（42）同一类
//#只能是分号;（29）或左大括号{（25），一定不是EOF 
int F[8]={0,0,2,2,4,4,5,5};//栈顶
int G[8]={0,5,1,1,3,3,0,5};//读入

//8a+b，共有6个非法状态，5个特殊状态，1个调用状态（左标识符右左括号，为8*标识符7+1=57） 
int ERROR[6]={0,6,8,49,55,63};
int SPECIAL[5]={11,19,27,35,43}; 

int translate(int t)//TOKEN翻译器，必须是上述7种符号才能进入翻译器，仅查表时用到 
{
	switch(t)
	{
		case '25'://左大括号 
		{
			return 0;
		}
		case '27'://逗号
		{
			return 0;
		}
		case '29'://分号
		{
			return 0;
		}
		case '30'://不等于号
		{
			return 0;
		}
		case '34'://小于号
		{
			return 0;
		}
		case '35'://大于号
		{
			return 0;
		}
		case '37'://等于等于号
		{
			return 0;
		}
		case '38'://小于等于号
		{
			return 0;
		}
		case '39'://大于等于号
		{
			return 0;
		}
		case '23'://左括号 
		{
			return 1;
		}
		case '21'://加号 
		{
			return 2;
		}
		case '31'://减号 
		{
			return 3;
		}
		case '22'://乘号 
		{
			return 4;
		}
		case '32'://除号 
		{
			return 5;
		}
		case '24'://右括号 
		{
			return 6;
		}
		case '41'://整数 
		{
			return 7;
		}
		case '42'://浮点数 
		{
			return 7;
		}
		case '51'://标识符 
		{
			return 7;
		}
		default://非法读入报错 
		{
			return -1;
		}
	}
}

//读进来的非终结符记作-2。总共只有e+e、e-e、e*e、e/e、(e)、整数（41）、浮点数（42）和标识符（51）五种可能 
int merging(int expstack[],int expstacktop)//返回expstacktop应该减去的值 
{
	if(expstacktop==0)//栈为空 
	{
		return -1;
	}
	if(expstack[expstacktop-1]==41||expstack[expstacktop-1]==42||expstack[expstacktop-1]==51)//整数（41）、浮点数（42）和标识符（51）
	{
		return 1;
	}
	if(expstacktop<3)//后面的规则要求栈里至少有3个字符，即012的位置必须有字符，expstacktop至少是3，避免下溢出错误 
	{
		return -1;
	}
	if(expstack[expstacktop-1]==-2&&expstack[expstacktop-2]==21&&expstack[expstacktop-3]==-2)//e+e
	{
		return 3;
	}
	if(expstack[expstacktop-1]==-2&&expstack[expstacktop-2]==31&&expstack[expstacktop-3]==-2)//e-e
	{
		return 3;
	}
	if(expstack[expstacktop-1]==-2&&expstack[expstacktop-2]==22&&expstack[expstacktop-3]==-2)//e*e
	{
		return 3;
	}
	if(expstack[expstacktop-1]==-2&&expstack[expstacktop-2]==32&&expstack[expstacktop-3]==-2)//e/e
	{
		return 3;
	}
	if(expstack[expstacktop-1]==24&&expstack[expstacktop-2]==-2&&expstack[expstacktop-3]==23)//(e)
	{
		return 3;
	}
	return -1;
}

//四个特判 

// 取反表达式，减号（31）开头，相反数，有子表达式 
// negate_expr -> '-' expr

// 类型转换表达式，子表达式开头，有子表达式，只会涉及到整数int和浮点数double之间的互相转换，将左侧表达式表示的值转换成右侧类型表示的值。优先级第二高 
// as_expr -> expr 'as'（1） ty

// 赋值表达式和左值表达式，标识符（51）开头，有子表达式 ，值类型void，不能被使用。相当于优先级最低，顺序右到左 
// assign_expr -> l_expr '=' expr
// l_expr -> IDENT

// 函数调用表达式，标识符（51）开头，下一TOKEN左括号（23），有子表达式，由函数名和调用参数列表组成的表达式
// 函数必须在调用前声明过，标准库中的函数在调用前不需要声明 
// call_expr -> IDENT '(' call_param_list? ')'
// call_param_list -> expr (',' expr)*

// 补一条：字符串表达式
// STRING_LITERAL（44）
//（44），只会在putstr("")调用（44）中出现，语义是对应的全局常量的编号

//表达式，7种可能，含赋值表达式即8种可能。expr有可能调用expr，因此它涉及的全局变量需要改为申请。
//开头为标识符（51）、减号（31）、左小括号（23）、整数（41）和浮点数（42），不得预读。
//expr -> operator_expr| negate_expr| as_expr| call_expr| literal_expr| ident_expr| group_expr
void expr()
{
	int aaa,bbb;//自变量。n代表不区分的非终结符，为-2 
	int *expstack=(int *)malloc(sizeof(int)*128);//栈里面永远是标准编号 
	int expstacktop=0;//expstacktop总指向栈顶元素的下一个位置，即expstacktop-1才是栈顶元素 
	int next=nextToken();//读入
	while(1)//减少用else，每个分支末尾尽可能continue或者break
	{
		bbb=translate(next);//读入不一定合法
		if(bbb==-1)
		{
			exit(-1);//出错
		}
		if(expstacktop!=0)//栈非空
		{
			aaa=expstack[expstacktop-1];//此时栈顶一定是合法字符的整数 
			if(aaa==-2)//栈顶是非终结符
			{
				if(expstacktop==1)//栈里只有一个元素 
				{
					aaa=0;//表示前一个位置应该是sharp 
				}
				else
				{
					aaa=expstack[expstacktop-2];
					if(aaa==-2)//每一步非终结符都不能相邻，再前面一个应该是终结符才对 
					{
						exit(-1);//违反规则
					}
					else
					{
						aaa=translate(aaa);//一定合法 
					}
				}
			}
			else
			{
				aaa=translate(aaa);//一定合法 
			}
			if(aaa==0&&bbb==0&&expstack[expstacktop-1]==-2&&expstacktop==1)//整个程序顺利结束 
			{
				break;
			}
			if(aaa==0&&next==24&&expstack[expstacktop-1]==-2&&expstacktop==1)//栈只剩下一个非终结符号，但是读入是右括号。由于被list调用，这是可能的 
			{
				unreadToken();//把右括号退回去。前面的情形已经退过了 
				break;
			}
			int count=8*aaa+bbb;//查错误表 
			int flag=0;//置一个特殊减号处理标记 
			int i;
			for(i=0;i<5;i++)//先查5个SPECIAL
			{
				if(count==SPECIAL[i])//处理特殊减号 
				{
					if(expstack[expstacktop-1]!=-2)//栈一定不是空的。仅当前面没有非终结符才是特殊减号 
					{
						flag=1;//置入特殊减号标记 
					}
				}
			}
			if(flag==1)
			{
				while(flag==1)//处理特殊减号，只有预读下一个 
				{
					next=nextToken();//读入。
					if(next!=31)
					{
						flag=0;//连续减号结束 
					}
				}//根据优先级，后面的合法情形只能是括号，函数调用或者标识符，而其他的一定是不对的 
				if(next==23||next==41||next==42||next==51)//左括号，整型，浮点，标识符或者函数调用
				{
					bbb=translate(next);//重新计算读入值 
					count=8*aaa+bbb;//重新计算错误表 
				}
				else
				{
					exit(-1);
				}
			}
			for(i=0;i<6;i++)//再查6个错误 
			{
				if(count==ERROR[i])
				{
					exit(-1);//无法判断优先级关系
				}
			}
			if(count==57)//标识符加左括号。这时候应当触发函数调用
			{
				expr();//已经读过了ident和左括号 
				int next=nextToken();//触发函数调用。结束后右括号已经被读了
				while(next!=24)//右括号结束，逗号表示没结束
				{
					if(next==27)//逗号 
					{
						expr(); 
					}
					else
					{
						exit(-1);
					}
					next=nextToken();//右括号被读了 
				}
				int rr=merging(expstack,expstacktop);
				if(rr==-1)
				{
					exit(-1);//规约失败
				}
				expstacktop-=rr;//规约成功弹栈 
				expstack[expstacktop]=-2;//压入非终结符号 
				expstacktop++;//压入非终结符号 
				continue;//仅规约跳过最后读入部分 
			}
			if(F[aaa]>G[bbb])//仅大于的时候才规约，其他时候读入。仅规约跳过最后读入部分 
			{
				int rr=merging(expstack,expstacktop);
				if(rr==-1)
				{
					exit(-1);//规约失败
				}
				expstacktop-=rr;//规约成功弹栈 
				expstack[expstacktop]=-2;//压入非终结符号 
				expstacktop++;//压入非终结符号 
				continue;//仅规约跳过最后读入部分 
			}
		}
		expstack[expstacktop]=next;//压入标准序号，应为next 
		expstacktop++;//压入标准序号
		next=nextToken();//读一个 
		if(next==33)
		{
			if(expstacktop==1&&expstack[expstacktop-1]==51)//栈里面只有一个IDENT就对了 
			{
				expr();//此时读过了IDENT和等号，剩余的部分刚好是一个expr
				//此处处理赋值 
				break; 
			}
			else
			{
				exit(-1);
			}
		}
		while(next==1)//读入as的时候特判。根据优先级，栈顶应该必须是非终结符、标识符类或者右括号
		{
			if(expstack[expstacktop-1]==24||expstack[expstacktop-1]==41||expstack[expstacktop-1]==42||expstack[expstacktop-1]==51)//右括号，整型，浮点，标识符
			{
				int rr=merging(expstack,expstacktop);//先规约 
				if(rr==-1)
				{
					exit(-1);//规约失败
				}
				expstacktop-=rr;//规约成功弹栈 
				expstack[expstacktop]=-2;//压入非终结符号 
				expstacktop++;//压入非终结符号 
			}
			if(expstack[expstacktop-1]!=-2)//不是非终结符 
			{
				exit(-1);//则退出 
			}
			int tyty=ty();//读入
			//此处应当先处理as情形 
			next=nextToken();//再读一个，看还是不是1 
		}
		if(next==25||next==27||next==29||next==30||next==34||next==35||next==37||next==38||next==39)//读入了尾字符的时候，不能再读了 
		{
			unreadToken();//此时会倒退一个。但是next保持为0，然后由于continue，此分支将无法进入 
		}
	}
	free(expstack);
}

// 造一条：比较运算符的运行结果是布尔类型，只能出现在 if 和 while 语句的条件表达式中。运算符的两侧必须是相同类型的数据 
// 但是while和if里不止可以出现这个。相当于优先级最低，顺序左到右 
// bool_expr -> expr '==' | '!=' | '<' | '>' | '<=' | '>=' expr
void bool_expr()
{
	expr();
	int next=nextToken();
	if(next==30||next==34||next==35||next==37||next==38||next==39)//可能是就一个表达式 
	{
		expr();
	}
	else
	{
		unreadToken();
	}
}

//表达式语句，开头为左小括号（23）、减号（31）、标识符（51）、整数（41）和浮点数（42），不得预读。
//expr_stmt -> expr ';'
void expr_stmt()
{
	expr();
	int next=nextToken();
	if(next!=29)//分号 
	{
		exit(-1);
	}
}

//未完成expr部分 
//常量语句，以const（3）开头。规定开头调用前已经被读了，下一个默认是标识符（51）
//const_decl_stmt -> 'const' IDENT ':' ty '=' expr ';'
void const_decl_stmt()
{
	int tok=nextToken();
	if(tok!=51)
	{
		exit(-1);
	}
	char* iii=(char *)malloc(sizeof(char)*128);
	strcpy(iii,TOKEN);
	int fff=find_all(iii);
	if(fff!=-1)//表里能查到 
	{
		exit(-1);//语义错误 
	}
	tok=nextToken();
	if(tok!=28)//冒号 
	{
		exit(-1);
	}
	int typpp=ty();//类型 
	tok=nextToken();
	if(tok!=33)//等号 
	{
		exit(-1);
	}
	expr();//表达式
	//此处应处理表达式 
	int intint;//假设int表达式的值存在这里 
	double doudou;//假设double表达式的值存在这里 
	tok=nextToken();
	if(tok!=29)//分号 
	{
		exit(-1);
	}
	if(typpp==1)//int时 
	{
		memset(&STACK[STACKTOP],0,sizeof(struct symbolstack));//填之前先清空这一格，以免出错 
		STACK[STACKTOP].destination=TABLETOP;
		STACKTOP++;
		memset(&TABLE[TABLETOP],0,sizeof(struct symboltable));//填之前先清空这一格，以免出错 
		strcpy(TABLE[TABLETOP].name,iii);
		TABLE[TABLETOP].isconst=1;
		TABLE[TABLETOP].type=1;
		TABLE[TABLETOP].value1=intint;
		TABLETOP++;
	}
	else if(typpp==2)//double时 
	{
		memset(&STACK[STACKTOP],0,sizeof(struct symbolstack));//填之前先清空这一格，以免出错 
		STACK[STACKTOP].destination=TABLETOP;
		STACKTOP++;
		memset(&TABLE[TABLETOP],0,sizeof(struct symboltable));//填之前先清空这一格，以免出错 
		strcpy(TABLE[TABLETOP].name,iii);
		TABLE[TABLETOP].isconst=1;
		TABLE[TABLETOP].type=2;
		TABLE[TABLETOP].value1=doudou;
		TABLETOP++;
	}
	else//其他不得声明 
	{
		exit(-1); 
	}
	free(iii);
}

//expr未处理 
//变量，以let（8）开头。规定开头调用前已经被读了，下一个默认是标识符（51）
//let_decl_stmt -> 'let' IDENT ':' ty ('=' expr)? ';'
void let_decl_stmt()
{
	int tok=nextToken();
	if(tok!=51)
	{
		exit(-1);
	}
	char* iii=(char *)malloc(sizeof(char)*128);
	strcpy(iii,TOKEN);
	int fff=find_now(iii);
	if(fff!=-1)//表里能查到 
	{
		exit(-1);//语义错误 
	}
	tok=nextToken();
	if(tok!=28)//冒号 
	{
		exit(-1);
	}
	int typpp=ty();
	tok=nextToken();
	memset(&STACK[STACKTOP],0,sizeof(struct symbolstack));//填之前先清空这一格，以免出错 
	memset(&TABLE[TABLETOP],0,sizeof(struct symboltable));//填之前先清空这一格，以免出错 
	strcpy(TABLE[TABLETOP].name,iii);
	if(tok==33)//等于部分可以选择省略
	{
		expr();
		//此处应处理表达式 
		int intint;//假设int表达式的值存在这里 
		double doudou;//假设double表达式的值存在这里 
		if(typpp==1)//int时 
		{
			STACK[STACKTOP].destination=TABLETOP; 
			STACKTOP++;
			TABLE[TABLETOP].type=2;
			TABLE[TABLETOP].value1=doudou;
			TABLETOP++;
		}
		else if(typpp==2)//double时 
		{
			STACK[STACKTOP].destination=TABLETOP;
			STACKTOP++;
			TABLE[TABLETOP].type=2;
			TABLE[TABLETOP].value1=doudou;
			TABLETOP++;
		}
		else//其他不得声明 
		{
			exit(-1); 
		}
		tok=nextToken();
		if(tok==29)
		{
			return;
		}
		else
		{
			exit(-1);
		}
	}
	else if(tok==29)//未初始化，不能放入全局表，只能在栈表占个位置 
	{
		STACK[STACKTOP].destination=-1;//注明没初始化 
		STACKTOP++;
		return;
	}
	else
	{
		exit(-1);
	}
	free(iii);
}

void stmt();

//block语句，以左大括号（25）开头，不得预读 
//block_stmt -> '{' stmt* '}'
void block_stmt()
{
	int next=nextToken();
	if(next!=25)
	{
		exit(-1);
	}
	next=nextToken();
	while(next!=26)//右大括号 
	{
		stmt();//零次或多次 
		next=nextToken();
	}
}

//if语句，以if（7）开头，调用bool表达式。开头被预读 
//if_stmt -> 'if' expr block_stmt ('else' 'if' expr block_stmt)* ('else' block_stmt)?
void if_stmt()
{
	bool_expr();
	int next=nextToken();//零次或多次的elseif，零次或一次的else 
	while(next==5) 
	{
		next=nextToken();
		if(next==7)//仍旧可能是if
		{
			bool_expr();
			block_stmt(); 
			next=nextToken();//再读一个 
		}
		else if(next==25)//直接block了 
		{
			unreadToken();//block不得预读 
			block_stmt();
			next=nextToken();//再读一个，末尾回退
			break; 
		}
	}
	unreadToken();//末尾一定回退 
}

//while语句，以while（10）开头，调用bool表达式。开头被预读 
//while_stmt -> 'while' expr block_stmt
void while_stmt()
{
	bool_expr();
	block_stmt();
}

//return语句，以return（9）开头 
//return_stmt -> 'return' expr? ';'

//break语句，以break（2）开头 
//break_stmt -> 'break' ';'

//continue语句，以continue（4）开头 
//continue_stmt -> 'continue' ';'

//空语句，以分号（29）开头 
//empty_stmt -> ';'

//语句，9种情况（10种情况），不得预读 
//stmt ->expr_stmt（23）（31）（41）（42）（51）| decl_stmt| if_stmt（7）| while_stmt（10）| break_stmt（2）| continue_stmt（4）| return_stmt（9）| block_stmt（25）| empty_stmt（29）
//decl_stmt -> let_decl_stmt（8） | const_decl_stmt（3） 
void stmt()
{
	int next=nextToken();
	switch(next)
	{
		case 3://不回退 
			const_decl_stmt();
		break;
		case 8://不回退 
			let_decl_stmt();
		break;
		case 7://不回退 
			if_stmt();
		break;
		case 10://不回退 
			while_stmt();
		break;
		case 29://什么都不做 
		break;
		case 2://break
			next=nextToken();//分号
			if(next!=29)
			{
				exit(-1);
			}
		break;
		case 4://continue
			next=nextToken();//分号
			if(next!=29)
			{
				exit(-1);
			}
		break;
		case 9://return
			next=nextToken();//分号或expr 
			if(next!=29)
			{
				expr();
				next=nextToken();//分号
				if(next!=29)
				{
					exit(-1);
				}
			}
		break;
		case 25://block_stmt，回退 
			unreadToken();
			block_stmt(); 
		break;
		case 23:
			unreadToken();
			expr(); 
		break;
		case 31:
			unreadToken();
			expr(); 
		break;
		case 41:
			unreadToken();
			expr(); 
		break;
		case 42:
			unreadToken();
			expr(); 
		break;
		case 51:
			unreadToken();
			expr(); 
		break;
		default:
			exit(-1);
		break; 
	}
}

//function_param -> 'const'? IDENT ':' ty
//参数列表项，const（3）或IDENT（51）开头 
void function_param()
{
	int next=nextToken();
	if(next==3)//允许一个const 
	{
		//此处处理const
		next=nextToken();
	}
	if(next!=51)//仍旧不是IDENT 
	{
		exit(-1);
	}
	//此处处理IDENT
	next=nextToken();
	if(next!=28)//冒号
	{
		exit(-1);
	}
	int tyty=ty();
	//此处处理ty 
}

//function -> 'fn' IDENT '(' function_param_list? ')' '->' ty block_stmt
//function_param_list -> function_param (',' function_param)*
void function()//函数，以fn（6）开头。规定开头调用前已经被读了，下一个默认是标识符（51） 
{
	int next=nextToken();
	if(next!=51)//标识符 
	{
		exit(-1);
	}
	//此处应处理标识符（51）
	next=nextToken();
	if(next!=23)//左小括号 
	{
		exit(-1);
	}
	next=nextToken();
	if(next!=24)//下一个不是右小括号，属于function_param。要回退 
	{
		unreadToken();
		while(next!=24)
		{
			function_param();
			next=nextToken();//右小括号或逗号
			if(next!=24&&next!=27)
			{
				exit(-1);//啥都不是 
			}
		}//结束的时候右小括号已经读过了 
	}
	next=nextToken();
	if(next!=36)
	{
		exit(-1);
	}
	int tyty=ty();
	//此处处理ty
	block_stmt();
}

//program -> item*
//item -> function | decl_stmt
//decl_stmt -> let_decl_stmt | const_decl_stmt
void program()//程序，必然是常量语句（3）、变量语句（8）或函数（6）
{
	int tok=nextToken();
	if(tok==-1)
	{
		return;
	}
	if(tok!=3&&tok!=8&&tok!=6)
	{
		exit(-1);
	}
	while(tok==3||tok==8||tok==6)
	{
		if(tok==3)
		{
			const_decl_stmt();
		}
		else if(tok==8)
		{
			let_decl_stmt();
		}
		else if(tok==6)
		{
			function();
		}
		else
		{
			exit(-1);
		}
		tok=nextToken();
	}
	if(tok==-1)
	{
		return;
	}
	if(tok!=3&&tok!=8&&tok!=6)
	{
		exit(-1);
	}
}

void init()//全局变量初始化 
{
	PREVALID=0;//预读无效 
	STACKTOP=0;//表清空
	TABLETOP=0;//全体全局变量个数 
	FUNCTIONLISTTOP=0;//函数表个数
}

void lastcheck()//设置入口点。假设之前编译部分全做完了 
{
	memset(&TABLE[TABLETOP],0,sizeof(struct symboltable));//填之前先清空这一格，以免出错 
	strcpy(TABLE[TABLETOP].name,"_start");
	TABLE[TABLETOP].isconst=1;
	TABLE[TABLETOP].type=3;
	memset(&FUNCTIONLIST[FUNCTIONLISTTOP],0,sizeof(struct functionlist));//填之前先清空这一格，以免出错 
	FUNCTIONLIST[FUNCTIONLISTTOP].name=TABLETOP;
	TABLETOP++;
	FUNCTIONLIST[FUNCTIONLISTTOP].type=0;//无返回值
	FUNCTIONLIST[FUNCTIONLISTTOP].param=0;//无参数 
	FUNCTIONLIST[FUNCTIONLISTTOP].local=0;//无局部变量
	FUNCTIONLIST[FUNCTIONLISTTOP].count=1;//只有一个指令 
	char chte[10];
	strcpy(chte,"main");
	int temp=find_all(chte);//返回函数名称main在全局变量中的位置
	FUNCTIONLIST[FUNCTIONLISTTOP].instr[0]=(char)0x4a;//callname 
	FUNCTIONLIST[FUNCTIONLISTTOP].instr[1]=(char)((temp>>24) & 0x000000ff);//大端 
	FUNCTIONLIST[FUNCTIONLISTTOP].instr[2]=(char)((temp>>16) & 0x000000ff);
	FUNCTIONLIST[FUNCTIONLISTTOP].instr[3]=(char)((temp>> 8) & 0x000000ff);
	FUNCTIONLIST[FUNCTIONLISTTOP].instr[4]=(char)((temp>> 0) & 0x000000ff);
}

FILE *OUT; 

char OUTINT[4];

void outint(int temp)
{
	OUTINT[0]=(char)((temp>>24) & 0x000000ff);
    OUTINT[1]=(char)((temp>>16) & 0x000000ff);
    OUTINT[2]=(char)((temp>> 8) & 0x000000ff);
    OUTINT[3]=(char)((temp>> 0) & 0x000000ff);
    fwrite(OUTINT,sizeof(char),4,OUT);
}

char OUTDOUBLE[8];

void outdouble(double *temp)
{
	long long* pr=(long long*)temp;
	OUTDOUBLE[0]=(char)((*pr>>56) & 0x00000000000000ffLL);
    OUTDOUBLE[1]=(char)((*pr>>48) & 0x00000000000000ffLL);
    OUTDOUBLE[2]=(char)((*pr>>40) & 0x00000000000000ffLL);
    OUTDOUBLE[3]=(char)((*pr>>32) & 0x00000000000000ffLL);
	OUTDOUBLE[4]=(char)((*pr>>24) & 0x00000000000000ffLL);
    OUTDOUBLE[5]=(char)((*pr>>16) & 0x00000000000000ffLL);
    OUTDOUBLE[6]=(char)((*pr>> 8) & 0x00000000000000ffLL);
    OUTDOUBLE[7]=(char)((*pr>> 0) & 0x00000000000000ffLL);
    fwrite(OUTDOUBLE,sizeof(char),8,OUT);
}

int main(int argc,char *argv[])
{
//	IN=fopen(argv[1],"r");
	IN=fopen("in.txt","r");
	init(); 
	//这里是编译主体 
	lastcheck(); 
	FILE *outfp;  
	OUT=fopen("o0.bin","wb");
	int temp=0x72303b3e;
	outint(temp);//魔数
	temp=0x00000001;
	outint(temp);//版本号
	outint(TABLETOP);//全局变量个数 
	int i;
	for(i=0;i<TABLETOP;i++)//正序输出全局变量表 
	{
		fwrite(&TABLE[i].isconst,sizeof(char),1,OUT);//是否常量 
		if(TABLE[i].type==1)//是整数 
		{
			int len=4;
			outint(len);
			outint(TABLE[i].value1);
		}
		else if(TABLE[i].type==2)//是浮点数 
		{
			int len=8;
			outint(len);
			outdouble(&TABLE[i].value2);
		}
		else if(TABLE[i].type==3)//是函数名或者字符串 
		{
			int len=strlen(&TABLE[i].value3);
			outint(len);
			fwrite(&TABLE[i].name,sizeof(char),len,OUT);
		}
		else
		{
			exit(-1);
		}
	}
	outint(FUNCTIONLISTTOP);//函数个数 
	for(i=FUNCTIONLISTTOP-1;i>=0;i--)//倒序输出函数表
	{
		outint(FUNCTIONLIST[i].name);//名 
		outint(FUNCTIONLIST[i].type);//型
		outint(FUNCTIONLIST[i].param);//参
		outint(FUNCTIONLIST[i].local);//局
		outint(FUNCTIONLIST[i].count);//数
		int len=strlen(FUNCTIONLIST[i].instr);
		fwrite(FUNCTIONLIST[i].instr,sizeof(char),len,OUT);
	}
	fclose(OUT);
	fclose(IN);
	return 0;
}

