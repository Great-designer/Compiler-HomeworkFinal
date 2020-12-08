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

struct symboltable//符号表结构体 
{
	char name[128];//名字 
	int isconst;//是常数为1，否则为0
	int valid;//是否初始化。1表示已初始化，值有效，否则无效。 
	int type;//0为void，1为int，2为double
	int value1;//type为1时有效 
	double value2;//type为2时有效 
	int istop;//1表示这一格是栈顶，新函数开始的前一格。默认为0 
};

struct symboltable TABLE[128];//符号表 
int TABLETOP;//栈顶下标

int find_all(char sss[])//根据变量名查全部符号表。查到返回下标，未查到返回-1。 
{
	int i;
	for(i=TABLETOP-1;i>=0;i--)//倒序查表 
	{
		if(strcmp(TABLE[i],sss)==0)
		{
			return i;
		}
	}
	return -1;
}

int find_now(char sss[])//根据变量名查当前层符号表。查到返回下标，未查到返回-1。 
{
	int i;
	for(i=TABLETOP-1;TABLE[i].istop!=1&&i>=0;i--)//倒序查表 
	{
		if(strcmp(TABLE[i],sss)==0)
		{
			return i;
		}
	}
	return -1;
}

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
				int rr=merging();
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
				int rr=merging();
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
				int rr=merging();//先规约 
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
	if(ty==1)//int时 
	{
		memset(TABLE[TABLETOP],0,sizeof(struct symboltable));//填之前先清空这一格，以免出错 
		strcpy(TABLE[TABLETOP].name,iii);
		TABLE[TABLETOP].valid=1;
		TABLE[TABLETOP].isconst=1;
		TABLE[TABLETOP].type=1;
		TABLE[TABLETOP].value1=intint;
		TABLETOP++;
	}
	else if(ty==2)//double时 
	{
		memset(TABLE[TABLETOP],0,sizeof(struct symboltable));//填之前先清空这一格，以免出错 
		strcpy(TABLE[TABLETOP].name,iii);
		TABLE[TABLETOP].valid=1;
		TABLE[TABLETOP].isconst=1;
		TABLE[TABLETOP].type=2;
		TABLE[TABLETOP].value2=doudou;
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
	memset(TABLE[TABLETOP],0,sizeof(struct symboltable));//填之前先清空这一格，以免出错 
	strcpy(TABLE[TABLETOP].name,iii);
	if(tok==33)//等于部分可以选择省略
	{
		expr();
		//此处应处理表达式 
		int intint;//假设int表达式的值存在这里 
		double doudou;//假设double表达式的值存在这里 
		if(ty==1)//int时 
		{
			TABLE[TABLETOP].valid=1;
			TABLE[TABLETOP].type=1;
			TABLE[TABLETOP].value1=intint;
			TABLETOP++;
		}
		else if(ty==2)//double时 
		{
			TABLE[TABLETOP].valid=1;
			TABLE[TABLETOP].type=2;
			TABLE[TABLETOP].value2=doudou;
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
	else if(tok==29)
	{
		TABLETOP++;
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
	TABLETOP=0;//表清空
}

int main(int argc,char *argv[])
{
	IN=fopen(argv[1],"r");
	init(); 
	
//// start
//72 30 3b 3e // magic
//00 00 00 01 // version
//
//00 00 00 02 // globals.count
//
//// globals[0]
//00 // globals[0].is_const
//00 00 00 08 // globals[0].value.count
//00 00 00 00 00 00 00 00 // globals[0].value.items
//
//// globals[1]
//01 // globals[1].is_const
//00 00 00 06 // globals[1].value.count
//'_' 's' 't' 'a' 'r' 't' // globals[1].value.items
//
//00 00 00 01 // functions.count
//
//// functions[0]
//00 00 00 01 // functions[0].name
//00 00 00 00 // functions[0].ret_slots
//00 00 00 00 // functions[0].param_slots
//00 00 00 00 // functions[0].loc_slots
//00 00 00 04 // functions[0].body.count
//    // functions[0].body.items
//    01 00 00 00 00 00 00 00 01 // Push(1)
//    01 00 00 00 00 00 00 00 02 // Push(2)
//    20 // AddI
//    34 // NegI
//// finish
	
///// 整个 o0 二进制文件
//struct o0 {
//    /// 魔数
//    magic: u32 = 0x72303b3e,
//    /// 版本号，定为 1
//    version: u32 = 0x00000001,
//    /// 全局变量表
//    globals: Array<GlobalDef>,
//    /// 函数列表
//    functions: Array<FunctionDef>,
//}
//
///// 类型为 T 的通用数组的定义
//struct Array<T> {
//    /// 数组的长度
//    count: u32,
//    /// 数组所有元素的无间隔排列
//    items: T[],
//}
//
///// 单个全局变量
//struct GlobalDef {
//    /// 是否为常量？非零值视为真
//    is_const: u8,
//    /// 按字节顺序排列的变量值
//    value: Array<u8>,
//}
//
///// 函数
//struct FunctionDef {
//    /// 函数名称在全局变量中的位置
//    name: u32,
//    /// 返回值占据的 slot 数
//    return_slots: u32,
//    /// 参数占据的 slot 数
//    param_slots: u32,
//    /// 局部变量占据的 slot 数
//    loc_slots: u32,
//    /// 函数体
//    body: Array<Instruction>,
//}
//
///// 指令，可以是以下三个选择之一
//union Instruction {
//    /// 无参数的指令，占 1 字节
//    variant NoParam {
//        opcode: u8
//    },
//    /// 有 4 字节参数的指令，占 5 字节
//    variant u32Param {
//        opcode: u8,
//        param: u32,
//    }
//    /// 有 8 字节参数的指令，占 9 字节
//    variant u64Param {
//        opcode: u8,
//        param: u64
//    }
//}

//关于全局变量
//在 navm 中，每个全局变量都是多个字节组成的数组。全局变量的编号是它在全局变量表中的序号（0 开始）。
//
//用来存储数字
//使用全局变量存储数字的初始化操作建议在 _start 函数中进行，这样不用考虑字节顺序问题。如果你直接给全局变量赋初始值的话，请使用小端序存储（低位字节在前，高位字节在后）。
//
//用来存储字符串
//使用全局变量存储字符串时，直接将初始值设置为以 ASCII 存储的字符串内容（类似于 memcpy）即可。存储的字符串不需要以 \0 结尾。

//程序入口
//navm 总是会最先运行函数列表里编号为 0 的（也就是整个列表中第一个）函数，按照惯例这个函数的名称为 _start。_start 函数没有任何参数，也不返回任何值，这两项的参数会被忽略。_start 函数不能有返回指令。
//
//一般来说，程序会在 _start 中设置全局变量的值，以及进行其他的准备工作。在准备工作完成之后，_start 函数应当调用 main 函数开始正式的程序运行。如果需要，_start 函数也可以在 main 函数返回之后进行清理工作。_start 函数不需要返回。
//
//一个示例的 _start 函数如下：



	fclose(IN);
	return 0;
}

