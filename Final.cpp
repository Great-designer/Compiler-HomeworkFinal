#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char TOKEN[128];//当前字符串常量（44），或者标识符（51）
long long NUM;//当前无符号整数（41，语法分析中允许取负） 
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
				NUM=atoll(TOKEN);//将TOKEN中的字符串转换为整数 
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
					NUM=atoll(TOKEN);//将TOKEN中的字符串转换为整数 
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
					NUM=atoll(TOKEN);//将TOKEN中的字符串转换为整数 
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
				NUM=atoll(TOKEN);//将TOKEN中的字符串转换为整数 
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
			NUM=atoll(TOKEN);//将TOKEN中的字符串转换为整数 
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
long long NUMPRE;//无符号整数（41，语法分析中允许取负） 
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
	else if(strcmp(TOKEN,"int")==0)//64位。实际上是long long 
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
		case 25://左大括号 
		{
			return 0;
		}
		case 27://逗号
		{
			return 0;
		}
		case 29://分号
		{
			return 0;
		}
		case 30://不等于号
		{
			return 0;
		}
		case 34://小于号
		{
			return 0;
		}
		case 35://大于号
		{
			return 0;
		}
		case 37://等于等于号
		{
			return 0;
		}
		case 38://小于等于号
		{
			return 0;
		}
		case 39://大于等于号
		{
			return 0;
		}
		case 23://左括号 
		{
			return 1;
		}
		case 21://加号 
		{
			return 2;
		}
		case 31://减号 
		{
			return 3;
		}
		case 22://乘号 
		{
			return 4;
		}
		case 32://除号 
		{
			return 5;
		}
		case 24://右括号 
		{
			return 6;
		}
		case 41://整数 
		{
			return 7;
		}
		case 42://浮点数 
		{
			return 7;
		}
		case 51://标识符 
		{
			return 7;
		}
		default://非法读入报错 
		{
			return -1;
		}
	}
}

struct instruction//指令结构体 
{
	char list[1024];//指令序列
	char count;//指令个数 
	int length;//指令长度 
}; 

struct instruction instrcat(struct instruction A,struct instruction B)//指令拼接 
{
	struct instruction temp;
	int i;
	for(i=0;i<A.length;i++)
	{
		temp.count[i]=A.count[i]; 
	}
	for(i=0;i<B.length;i++)
	{
		temp.count[i+A.length]=B.count[i]; 
	}
	temp.length=A.length+B.length;
	temp.count=A.count+B.count;
	return temp;
}

//navm 的指令使用 8 位（1 字节）无符号整数标识 
void storeint(int temp,char chttt[],int i)//大端法将32位（4字节）指令存入指定位置 
{
	chttt[i]=(char)((temp>>24) & 0x000000ff);
    chttt[i+1]=(char)((temp>>16) & 0x000000ff);
    chttt[i+2]=(char)((temp>> 8) & 0x000000ff);
    chttt[i+3]=(char)((temp>> 0) & 0x000000ff);
}

void storelong(long long *pr,char chttt[],int i)//大端法将64位（8字节）指令存入指定位置。这个传址 
{
	chttt[i]=(char)((*pr>>56) & 0x00000000000000ffLL);
    chttt[i+1]=(char)((*pr>>48) & 0x00000000000000ffLL);
    chttt[i+2]=(char)((*pr>>40) & 0x00000000000000ffLL);
    chttt[i+3]=(char)((*pr>>32) & 0x00000000000000ffLL);
	chttt[4]=(char)((*pr>>24) & 0x00000000000000ffLL);
    chttt[5]=(char)((*pr>>16) & 0x00000000000000ffLL);
    chttt[6]=(char)((*pr>> 8) & 0x00000000000000ffLL);
    chttt[7]=(char)((*pr>> 0) & 0x00000000000000ffLL);
}

void storedouble(double *temp,char chttt[],int i)//大端法将64位（8字节）指令存入指定位置。这个传址 
{
	long long* pr=(long long*)temp;
	chttt[i]=(char)((*pr>>56) & 0x00000000000000ffLL);
    chttt[i+1]=(char)((*pr>>48) & 0x00000000000000ffLL);
    chttt[i+2]=(char)((*pr>>40) & 0x00000000000000ffLL);
    chttt[i+3]=(char)((*pr>>32) & 0x00000000000000ffLL);
	chttt[4]=(char)((*pr>>24) & 0x00000000000000ffLL);
    chttt[5]=(char)((*pr>>16) & 0x00000000000000ffLL);
    chttt[6]=(char)((*pr>> 8) & 0x00000000000000ffLL);
    chttt[7]=(char)((*pr>> 0) & 0x00000000000000ffLL);
}

struct expression//表达式结构体
{
	int type;//返回类型。0为void，1为int，2为double 
	struct instruction instr;//表达式的指令列 
};

//0x0a	loca	off:u32	-	1:addr	加载 off 个 slot 处局部变量的地址，从loc0开始 
//0x0b	arga	off:u32	-	1:addr	加载 off 个 slot 处参数/返回值的地址。返回值是arg0（void没有），参数从arg1（arg0，void从arg1）开始。
//参数均要初始化。返回值没有名字，不可使用，认为未初始化 
//0x0c	globa	n:u32	-	1:addr	加载第 n 个全局变量/常量的地址。常量在全局、参数和都可以定义 
//需要一个全局表，放全局变量、函数名和字符串。查找时遍历，不在栈里面，不需要栈 

struct symboltable//量结构体。
{
	char name[64];//名字，除了纯字符串外不可重复。type为0时有效，需要写进全局初始化部分。可以strlen 
	char isconst;//是常数为1，不是常数为0（输出长度为8） 
	int valid;//未初始化为0，初始化为1 
	int type;//1为int，2为double（都是64），0为void字符串（函数名或者字符串）。int和double的初始化都在_start中 
}; 

struct symboltable TABLE[128];//全局表。所有的函数名字都要存进去。均不用初始化，就不用存值  
int TABLETOP;//表顶下标 

int find_table(char sss[])//根据变量名，顺序查全局符号表。查到返回在表中下标，未查到返回-1。
{
	int i;
	for(i=0;i<TABLETOP;i++)//无需倒序
	{
		if(strcmp(TABLE[i].name,sss)==0)
		{
			return i;
		}
	}
	return -1;
}

//需要一个函数表。函数的结构
//函数名在全局表位置 
//返回值（arg0，void就没有）占多少个8字节。只能为0或1，检查arg0是否返回值即可 
//参数（arg1开始，void从arg0开始）占多少个8字节。
//因此需要返回值/参数表，记录每个返回值/参数：是否返回值、类型、是否const，名字。返回值只有类型，没有const和名字 
//局部变量表（loc0开始），并占多少个8字节
//局部变量栈，管理局部变量表。完成作用域嵌套、变量声明增强、break和continue（针对while）、函数返回路径检查（针对if和else）
//body有多少条指令和body指令表。用instruction结构体 

struct symbolstack//局部变量栈结构体 
{
	int istop;//1表示这一格是栈顶，新函数开始的前一格。默认为0 
	int destination;//在局部变量表中的下标。
};

struct function//全局函数表 
{
	int name;//在全局符号表的位置
	int type;//类型决定返回值有多少个8字节，以及参数表起始位置。void为0，int和double都为8。此处记录0，1和2 
	struct symboltable param[16];//最多16个参数与返回值。
	int paramtop;//参数栈顶。type为1或者2的时候，栈顶先增加一位 
	int paramcount;//真正参数个数，决定多少个8字节。int和double都为8，故乘8即可。
	struct symboltable localtable[32];//局部变量表
	int localtabletop;//局部变量表顶，指示有多少个8字节
	struct symbolstack localstack[32];//局部变量栈，管理局部变量表
	int localstacktop;//局部变量栈顶
	struct instruction instr;//函数的指令列 
};

struct function FUNCLIST[64];//最多64个函数吧，让指令集长一点 
int FUNCLISTTOP;

int find_func(char sss[])
{
	int i;
	for(i=0;i<FUNCLISTTOP;i++)//无需倒序
	{
		if(strcmp(TABLE[FUNCLIST[i].name].name,sss)==0)
		{
			return i;//只给编译器用
		}
	}
	return -1;
}

int find_param(char sss[],int func)//查找参数表，需要知道是哪个函数，函数序号为编译器序号。顺序查表，查全局表名字。未查到返回-1。
{
	int i;
	for(i=0;i<FUNCLIST[func].paramtop;i++)//无需倒序
	{
		if(type!=0&&i==0)//返回值没有名字，跳过 
		{
			continue;
		}
		if(strcmp(FUNCLIST[func].param[i].name,sss)==0)
		{
			return i;//查到返回在参数表中下标
		}
	}
	return -1;
}

int find_all(char sss[],int func)//根据变量名查全体层符号表栈。查到返回在栈中下标，未查到返回-1。
{
	int i;
	for(i=FUNCLIST[func].localstacktop-1;i>=0;i--)//倒序查表 
	{
		if(strcmp(FUNCLIST[func].localtable[FUNCLIST[func].localstack[i].destination].name,sss)==0)
		{
			return FUNCLIST[func].localstack[i].destination;
		}
	}
	return -1;
}

int find_now(char sss[],int func)//根据变量名查当前层符号表栈。查到返回在栈中下标，未查到返回-1。 
{
	int i;
	for(i=FUNCLIST[func].localstacktop-1;FUNCLIST[func].localstack[i].istop!=1&&i>=0;i--)//倒序查表 
	{
		if(strcmp(FUNCLIST[func].localtable[FUNCLIST[func].localstack[i].destination].name,sss)==0)
		{
			return FUNCLIST[func].localstack[i].destination;
		}
	}
	return -1;
}

//变量查表，需要查全局变量表。如果在函数中，就要查当前函数的参数表（不查返回值），和在局部变量栈中的局部变量表 
//根据作用域嵌套原则，查找时先查当前层再倒序，定义可覆盖。局部变量表覆盖参数表，参数表覆盖全局变量表
//定义查表，只查当前层。因此定义全局变量只查全局变量表，定义参数只查参数表，定义局部变量只查当前block。区分全局变量和哪一个局部变量block要一个编译器全局量
//函数编号从0开始，并且0号是_start。这意味着定义完了最后定义_start，然后倒序输出函数表。因此编译器的函数编号不适用于虚拟机函数编号 
//使用查表，倒序查所有层。先倒序查当前函数局部变量block，再查当前函数参数表，再查全体全局变量

//全局变量编号，保持编译器与虚拟机一致，顺序输出 
//调用函数，只使用callname指令 

//在init的时候，先把8个标准库函数名扔进全局变量表，即0到7分别是：
//getchar(0)getdouble(1)getint(2)putchar(4)putdouble(5)putint(6)putln(7)putstr(8)
//函数定义查表，只查全局变量表 
//函数调用查表，先特判标准库函数。即先特判标准库（直接根据情形加载参数并callname对应序号），再查函数表的函数名地址 

//读进来的非终结符记作-2。总共只有e+e、e-e、e*e、e/e、(e)、整数（41）、浮点数（42）和标识符（51）五种可能 

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

int OVERALL;//标记是否全局声明状态。进入函数时设置为1，退出则为0。这将决定查什么表 
int FUNCNUM;//当前编译器处于编译器编号哪个函数中。进入函数block时设置 

struct expression expr();//会调用主程序 

//仅未完成标识符、函数调用和赋值部分 
struct expression parse_primary()//解析一元表达式。这里处理左括号、函数调用、前置-。因此这三者不用设置优先级。这里顺便可以处理赋值部分（需预读） 
{
	int peek=nextToken();
	if(peek==23)//左括号 
	{
		struct expression temp=expr();
		peek=nextToken();
		if(peek!=24)//不是右括号就不匹配 
		{
			exit(-1);
		}
		return temp;//直接无脑弹出temp 
	}
	else if(op==31)//减号开头 
	{
		struct expression temp=expr();//重来 
		char nene;//取反指令 
		if(temp.type==1)//整数 
		{
			nene=0x34;
		}
		else if(temp.type==2)//浮点
		{
			nene=0x35;
		}
		temp.instr.list[temp.instr.length]=nene;
		temp.instr.count++;
		temp.instr.length++;
		return temp;//只有type不变 
	}
	else if(op==41)//整数 
	{
		char nene=0x01;//push指令 
		struct expression temp;
		memset(&temp,0,sizeof(struct expression));//清零 
		temp.instr.list[temp.instr.length]=nene;
		temp.instr.count++;
		temp.instr.length++;//光标先移动才能放long 
		temp.type=1;//整数 
		storelong(&NUM,temp.instr.list,temp.instr.length);
		temp.instr.length+=8;//一个64位占8个char 
		return temp;
	}
	else if(op==42)//浮点数 
	{
		char nene=0x01;//push指令 
		struct expression temp;
		memset(&temp,0,sizeof(struct expression));//清零 
		temp.instr.list[temp.instr.length]=nene;
		temp.instr.count++;
		temp.instr.length++;//光标先移动才能放long 
		temp.type=2;//浮点数 
		storedouble(&DOU,temp.instr.list,temp.instr.length);
		temp.instr.length+=8;//一个64位占8个char 
		return temp;
	}
	else if(op==51)//标识符。这就麻烦大了，要查表决定是什么类型的变量，函数调用也在这部分，预读决定赋值也在这部分 
	{
		char ebeb[2048];//先把TOKEN搞进来 
		strcpy(ebeb,TOKEN);
		int veve=nextToken();//预读一位
		if(veve==33)//等号赋值 
		{
			struct expression returning;//希望返回的表达式 
			memset(&returning,0,sizeof(struct expression));//清空 
			struct expression vdvd=expr();//后面部分是一个正经的expression 
			if(OVERALL!=1)//不可能在全局态。全局只能有常变量定义和函数 
			{
				exit(-1);
			}
			else//函数态 
			{
				int finding=find_all(ebeb,FUNCNUM);//先查局部表。要查全体 
				if(finding==-1)//没查到
				{
					finding=find_param(ebeb,FUNCNUM);//再查参量表
					if(finding==-1)//没查到
					{
						finding=find_table(ebeb);//最后查全局表
						if(finding==-1)//都没查到
						{
							exit(-1);//赋值给不存在的变量语义错误 
						}
						else//在全局表 
						{
							if(TABLE[finding].isconst==1)
							{
								exit(-1);//常量不能赋值 
							}
							if(TABLE[finding].type==0||vdvd.type==0||TABLE[finding].type!=vdvd.type)//先检查变量类型是否一致。只赋值一次，不管type 
							{
								exit(-1);//赋值类型语义错误 
							}
							char intj=0x0c;//加载全局指令 
							returning.instr.list[returning.instr.length]=intj;
							returning.instr.count++;
							returning.instr.length++;//光标先移动
							storeint(finding,returning.instr.list,returning.instr.length);
							returning.instr.length+=4;//一个32位占4个char 
							returning.instr=instrcat(returning.instr,vdvd.instr);//地址上面放上expr一格 
							intj=0x17;//储存指令 
							returning.instr.list[returning.instr.length]=intj;
							returning.instr.count++;
							returning.instr.length++;
							TABLE[finding].valid=1;//已赋值，有效 
							return returning;
						}
					}
					else//在参量表 
					{
						if(FUNCLIST[FUNCNUM].param[finding].isconst==1)
						{
							exit(-1);//常量不能赋值 
						}
						if(FUNCLIST[FUNCNUM].param[finding].type==0||vdvd.type==0||FUNCLIST[FUNCNUM].param[finding].type!=vdvd.type)//先检查变量类型是否一致。只赋值一次，不管type 
						{
							exit(-1);//赋值类型语义错误 
						}
						char intj=0x0b;//加载参量指令 
						returning.instr.list[returning.instr.length]=intj;
						returning.instr.count++;
						returning.instr.length++;//光标先移动
						storeint(finding,returning.instr.list,returning.instr.length);
						returning.instr.length+=4;//一个32位占4个char 
						returning.instr=instrcat(returning.instr,vdvd.instr);//地址上面放上expr一格 
						intj=0x17;//储存指令 
						returning.instr.list[returning.instr.length]=intj;
						returning.instr.count++;
						returning.instr.length++;
						FUNCLIST[FUNCNUM].param[finding].valid=1;//已赋值，有效 
						return returning;
					}
				}
				else//在局部表 
				{
					if(FUNCLIST[FUNCNUM].localtable[finding].isconst==1)
					{
						exit(-1);//常量不能赋值 
					}
					if(FUNCLIST[FUNCNUM].localtable[finding].type==0||vdvd.type==0||FUNCLIST[FUNCNUM].localtable[finding].type!=vdvd.type)//先检查变量类型是否一致。只赋值一次，不管type 
					{
						exit(-1);//赋值类型语义错误 
					}
					char intj=0x0a;//加载局部变量指令 
					returning.instr.list[returning.instr.length]=intj;
					returning.instr.count++;
					returning.instr.length++;//光标先移动
					storeint(finding,returning.instr.list,returning.instr.length);
					returning.instr.length+=4;//一个32位占4个char 
					returning.instr=instrcat(returning.instr,vdvd.instr);//地址上面放上expr一格 
					intj=0x17;//储存指令 
					returning.instr.list[returning.instr.length]=intj;
					returning.instr.count++;
					returning.instr.length++;
					FUNCLIST[FUNCNUM].localtable[finding].valid=1;//已赋值，有效 
					return returning;
				}
			}
		}
		else if(veve==23)//左括号函数调用。检查与函数表里已有的情况是否一致 
		{
			struct expression returning;
			memset(&returning,0,sizeof(expression));//清空 
			if(strcmp(ebeb,"getchar")==0)//0号函数无参数，但要先空出一个返回值 
			{
				int riri=nextToken();//右括号
				if(riri!=24)
				{
					exit(-1);
				}
				returning.type=1;//返回int 
				char caca=0x01;//push指令 
				returning.instr.list[returning.instr.length]=nene;
				returning.instr.count++;
				returning.instr.length++;
				long long zeze=0;//push0作为返回值 
				storelong(&zeze,returning.instr.list,returning.instr.length);
				returning.instr.length+=8;//一个64位占8个char 
				caca=0x4a;//callname
				returning.instr.list[returning.instr.length]=caca;
				returning.instr.count++;
				returning.instr.length++;
				int bsbs=0;//0号函数 
				storeint(bsbs,returning.instr.list,returning.instr.length);
				returning.instr.length+=4;//一个32位占4个char 
				return returning;
			}
			else if(strcmp(ebeb,"getdouble")==0)//1号函数无参数，但要先空出一个返回值 
			{
				int riri=nextToken();//右括号
				if(riri!=24)
				{
					exit(-1);
				}
				returning.type=2;//返回double
				char caca=0x01;//push指令 
				returning.instr.list[returning.instr.length]=nene;
				returning.instr.count++;
				returning.instr.length++;
				long long zeze=0;//push0作为返回值 
				storelong(&zeze,returning.instr.list,returning.instr.length);
				returning.instr.length+=8;//一个64位占8个char 
				caca=0x4a;//callname
				returning.instr.list[returning.instr.length]=caca;
				returning.instr.count++;
				returning.instr.length++;
				int bsbs=1;//1号函数 
				storeint(bsbs,returning.instr.list,returning.instr.length);
				returning.instr.length+=4;//一个32位占4个char 
				return returning;
			}
			else if(strcmp(ebeb,"getdouble")==0)//2号函数无参数，但要先空出一个返回值 
			{
				int riri=nextToken();//右括号
				if(riri!=24)
				{
					exit(-1);
				}
				returning.type=1;//返回int 
				char caca=0x01;//push指令 
				returning.instr.list[returning.instr.length]=nene;
				returning.instr.count++;
				returning.instr.length++;
				long long zeze=0;//push0作为返回值 
				storelong(&zeze,returning.instr.list,returning.instr.length);
				returning.instr.length+=8;//一个64位占8个char 
				caca=0x4a;//callname
				returning.instr.list[returning.instr.length]=caca;
				returning.instr.count++;
				returning.instr.length++;
				int bsbs=2;//2号函数 
				storeint(bsbs,returning.instr.list,returning.instr.length);
				returning.instr.length+=4;//一个32位占4个char 
				return returning;
			}
			else if(strcmp(ebeb,"putchar")==0)//3号函数有一个类型为int参数expr，无返回值 
			{
				struct expression ysys=expr();//接收一个整数类型expr 
				if(ysys.type!=1)
				{
					exit(-1);
				}
				int riri=nextToken();//右括号
				if(riri!=24)
				{
					exit(-1);
				}
				returning.instr=instrcat(returning.instr,ysys.instr);//搞定栈顶 
				char caca=0x4a;//callname
				returning.instr.list[returning.instr.length]=caca;
				returning.instr.count++;
				returning.instr.length++;
				int bsbs=3;//3号函数 
				storeint(bsbs,returning.instr.list,returning.instr.length);
				returning.instr.length+=4;//一个32位占4个char 
				return returning;
			}
			else if(strcmp(ebeb,"putdouble")==0)//4号函数有一个double参数，无返回值 
			{
				struct expression ysys=expr();//接收一个浮点数类型expr 
				if(ysys.type!=2)
				{
					exit(-1);
				}
				int riri=nextToken();//右括号
				if(riri!=24)
				{
					exit(-1);
				}
				returning.instr=instrcat(returning.instr,ysys.instr);//搞定栈顶 
				char caca=0x4a;//callname
				returning.instr.list[returning.instr.length]=caca;
				returning.instr.count++;
				returning.instr.length++;
				int bsbs=5;//5号函数 
				storeint(bsbs,returning.instr.list,returning.instr.length);
				returning.instr.length+=4;//一个32位占4个char 
				return returning;
			}
			else if(strcmp(ebeb,"putint")==0)//5号函数有一个int参数，无返回值 
			{
				struct expression ysys=expr();//接收一个整数类型expr 
				if(ysys.type!=1)
				{
					exit(-1);
				}
				int riri=nextToken();//右括号
				if(riri!=24)
				{
					exit(-1);
				}
				returning.instr=instrcat(returning.instr,ysys.instr);//搞定栈顶 
				char caca=0x4a;//callname
				returning.instr.list[returning.instr.length]=caca;
				returning.instr.count++;
				returning.instr.length++;
				int bsbs=5;//5号函数 
				storeint(bsbs,returning.instr.list,returning.instr.length);
				returning.instr.length+=4;//一个32位占4个char 
				return returning;
			}
			else if(strcmp(ebeb,"putln")==0)//6号函数无参数，无返回值 
			{
				int riri=nextToken();//右括号
				if(riri!=24)
				{
					exit(-1);
				}
				char caca=0x4a;//callname
				returning.instr.list[returning.instr.length]=caca;
				returning.instr.count++;
				returning.instr.length++;
				int bsbs=6;//6号函数 
				storeint(bsbs,returning.instr.list,returning.instr.length);
				returning.instr.length+=4;//一个32位占4个char 
				return returning;
			}
			else if(strcmp(ebeb,"putstr")==0)//7号函数，唯一的字符串参数，无返回值 
			{
				int riri=nextToken();//一个字符串。这时候应该把它放到表里 
				if(riri!=44)
				{
					exit(-1);
				}
				long long lololo=TABLETOP;//记住填到哪一格了 
				strcpy(TABLE[TABLETOP].name,TOKEN);
				TABLE[TABLETOP].isconst=1;//字符串都是常量 
				TABLE[TABLETOP].type=0;//void
				TABLE[TABLETOP].valid=1;//已初始化 
				char caca=0x01;//push
				returning.instr.list[returning.instr.length]=caca;
				returning.instr.count++;
				returning.instr.length++;
				storelong(&lololo,returning.instr.list,returning.instr.length);
				returning.instr.length+=8;
				caca=0x4a;//callname
				returning.instr.list[returning.instr.length]=caca;
				returning.instr.count++;
				returning.instr.length++;
				int bsbs=7;//7号函数 
				storeint(bsbs,returning.instr.list,returning.instr.length);
				returning.instr.length+=4;//一个32位占4个char 
				return returning;
			}
			int wewe=find_func(ebeb);
			if(wewe==-1)//调用了不存在的函数 
			{
				exit(-1);
			}
			
			FUNCLIST[wewe].type
			FUNCLIST[wewe].param[i].isconst
			FUNCLIST[wewe].param[i].name
			FUNCLIST[wewe].param[i].type
			FUNCLIST[wewe].param[i].valid
			FUNCLIST[wewe].paramcount
			FUNCLIST[wewe].paramtop
			FUNCLIST[wewe].name
			
			
			
			
		}
		else//不是以上两种情况，意味着就是一个普通的标识符。这个时候要把值取出来放到栈顶 
		{
			unreadToken();//退回。接下来仍旧要查表 
			struct expression returning;
			memset(&returning,0,sizeof(expression));//清空 
			if(OVERALL==0)//全局态。这时只需要查全局变量表即可 
			{
				int finding=find_table(ebeb);
				if(finding==-1)
				{
					exit(-1);
				}
				else
				{
					if(TABLE[finding].type==0||TABLE[finding].valid==0)//先检查变量类型，以及是否有效 
					{
						exit(-1);
					}
					returning.type=TABLE[finding].type;//这个expr有type 
					char intj=0x0c;//加载全局指令 
					returning.instr.list[returning.instr.length]=intj;
					returning.instr.count++;
					returning.instr.length++;//光标先移动
					storeint(finding,returning.instr.list,returning.instr.length);
					returning.instr.length+=4;//一个32位占4个char 
					intj=0x13;//取值压栈指令 
					returning.instr.list[returning.instr.length]=intj;
					returning.instr.count++;
					returning.instr.length++;
					return returning;
				}
			}
			else if(OVERALL==1)//函数态。这时全都要查 
			{
				int finding=find_all(ebeb,FUNCNUM);//先查局部表。要查全体
				if(finding==-1)//没查到
				{
					finding=find_param(ebeb,FUNCNUM);//再查参量表
					if(finding==-1)//没查到
					{
						finding=find_table(ebeb);//最后查全局表
						if(finding==-1)//都没查到
						{
							exit(-1);
						}
						else//在全局表 
						{
							if(TABLE[finding].type==0||TABLE[finding].valid==0)//先检查变量类型，以及是否有效 
							{
								exit(-1);
							}
							returning.type=TABLE[finding].type;//这个expr有type 
							char intj=0x0c;//加载全局指令 
							returning.instr.list[temp.instr.length]=intj;
							returning.instr.count++;
							returning.instr.length++;//光标先移动
							storeint(finding,returning.instr.list,returning.instr.length);
							returning.instr.length+=4;//一个32位占4个char 
							intj=0x13;//取值压栈指令 
							returning.instr.list[temp.instr.length]=intj;
							returning.instr.count++;
							returning.instr.length++;
							return returning;
						}
					}
					else//在参量表
					{
						if(FUNCLIST[FUNCNUM].param[finding].type==0||FUNCLIST[FUNCNUM].param[finding].valid==0)//先检查变量类型，以及是否有效 
						{
							exit(-1);
						}
						returning.type=FUNCLIST[FUNCNUM].param[finding].type;//这个expr有type 
						char intj=0x0b;//加载参数指令 
						returning.instr.list[returning.instr.length]=intj;
						returning.instr.count++;
						returning.instr.length++;//光标先移动
						storeint(finding,returning.instr.list,returning.instr.length);
						returning.instr.length+=4;//一个32位占4个char 
						intj=0x13;//取值压栈指令 
						returning.instr.list[returning.instr.length]=intj;
						returning.instr.count++;
						returning.instr.length++;
						return returning;
					}
				}
				else//在局部表
				{
					if(FUNCLIST[FUNCNUM].localtable[finding].type==0||FUNCLIST[FUNCNUM].localtable[finding].valid==0)//先检查变量类型，以及是否有效 
					{
						exit(-1);
					}
					returning.type=FUNCLIST[FUNCNUM].localtable[finding].type;//这个expr有type 
					char intj=0x0a;//加载局部指令 
					returning.instr.list[returning.instr.length]=intj;
					returning.instr.count++;
					returning.instr.length++;//光标先移动
					storeint(finding,returning.instr.list,returning.instr.length);
					returning.instr.length+=4;//一个32位占4个char 
					intj=0x13;//取值压栈指令 
					returning.instr.list[returning.instr.length]=intj;
					returning.instr.count++;
					returning.instr.length++;
					return returning;
				}
			}
			else
			{
				exit(-1);
			}
		}
	}
	else
	{
		exit(-1);//有问题 
	}
}

struct expression combine(struct expression lhs,int op,struct expression rhs)//combine将三部分组合。这里处理语义 
{
	if(lhs.type!=rhs.type||lhs.type==0||rhs.type==0)//先检查左右两边type是否一致或是否为0 
	{
		exit(-1);//有问题 
	}
	else if(op==21)//加 
	{
		char nene;//加指令
		if(lhs.type==1)
		{
			nene=0x20;
		}
		else if(lhs.type==2)
		{
			nene=0x24;
		}
		else
		{
			exit(-1);
		}
		struct expression temp;
		memset(&temp,0,sizeof(struct expression));//清零 
		temp.type=lhs.type;
		temp.instr=instrcat(lhs.instr,rhs.instr);//指令部分直接拼接进来 
		temp.instr.list[temp.instr.length]=nene;
		temp.instr.count++;
		temp.instr.length++;
	}
	else if(op==31)//减 
	{
		char nene;//减指令
		if(lhs.type==1)
		{
			nene=0x21;
		}
		else if(lhs.type==2)
		{
			nene=0x25;
		}
		else
		{
			exit(-1);
		} 
		struct expression temp;
		memset(&temp,0,sizeof(struct expression));//清零 
		temp.type=lhs.type;
		temp.instr=instrcat(lhs.instr,rhs.instr);//指令部分直接拼接进来 
		temp.instr.list[temp.instr.length]=nene;
		temp.instr.count++;
		temp.instr.length++;
	}
	else if(op==22)//乘 
	{
		char nene;//乘指令 
		if(lhs.type==1)
		{
			nene=0x22;
		}
		else if(lhs.type==2)
		{
			nene=0x26;
		}
		else
		{
			exit(-1);
		} 
		struct expression temp;
		memset(&temp,0,sizeof(struct expression));//清零 
		temp.type=lhs.type;
		temp.instr=instrcat(lhs.instr,rhs.instr);//指令部分直接拼接进来 
		temp.instr.list[temp.instr.length]=nene;
		temp.instr.count++;
		temp.instr.length++;
	}
	else if(op==32)//除 
	{
		char nene;//除指令 
		if(lhs.type==1)
		{
			nene=0x23;
		}
		else if(lhs.type==2)
		{
			nene=0x27;
		}
		else
		{
			exit(-1);
		} 
		struct expression temp;
		memset(&temp,0,sizeof(struct expression));//清零 
		temp.type=lhs.type;
		temp.instr=instrcat(lhs.instr,rhs.instr);//指令部分直接拼接进来 
		temp.instr.list[temp.instr.length]=nene;
		temp.instr.count++;
		temp.instr.length++;
	}
	else
	{
		exit(-1);//有问题 
	}
}
    
int prec(int op)//查找运算符优先级 
{
	if(op==33)
	{
		return 1;//赋值。最低 
	}
	else if(op==30||op==34||op==35||op==37||op==38||op==39)
	{
		return 2;//比较运算符，排第二
	}
	else if(op==21||op==31)
	{
		return 3;//加减，排第三 
	}
	else if(op==22||op==32)
	{
		return 4;//乘除，排第四 
	}
	else if(op==1)
	{
		return 5;//as，排第五 
	}
	else
	{
		exit(-1);//有问题 
	}
}

struct expression parse_opg(struct expression lhs,int prec)//lhs是左部，prec是左部优先级。每次调用这个的时候，下一个总应该是运算符。as应该在这里特判 
{
	int peek=nextToken();//预读下一个运算符，prec是优先级
	while(peek==1)//是个as
	{
		if(lhs.type!=1&&lhs.type!=2)
		{
			exit(-1);
		}
		int tyty=ty();//读入
		if(tyty!=1&&tyty!=2)
		{
			exit(-1);
		}
		if(lhs.type==1&&tyty==2)//要转为浮点
		{
			char nene=0x36;
			lhs.instr.list[lhs.instr.length]=nene;
			lhs.instr.count++;
			lhs.instr.length++;
		}
		else if(lhs.type==2&&tyty==1)//要转为整数
		{
			char nene=0x37;
			lhs.instr.list[lhs.instr.length]=nene;
			lhs.instr.count++;
			lhs.instr.length++;
		}
		lhs.type=tyty;
		peek=nextToken();//再来 
	}
	while(is_binary_op(peek)&&prec(peek)>=prec)//peek是二元运算符，peek优先级大于等于左部旧优先级就要规约 
	{
		int op=peek;
		struct expression rhs=parse_primary();//右部读一个并解析某个东西
		peek=nextToken();//再预读下一个运算符。比较两个运算符的优先级 
		while(peek==1)//是个as
		{
			if(rhs.type!=1&&rhs.type!=2)
			{
				exit(-1);
			}
			int tyty=ty();//读入
			if(tyty!=1&&tyty!=2)
			{
				exit(-1);
			}
			if(rhs.type==1&&tyty==2)//要转为浮点
			{
				char nene=0x36;
				rhs.instr.list[rhs.instr.length]=nene;
				rhs.instr.count++;
				rhs.instr.length++;
			}
			else if(rhs.type==2&&tyty==1)//要转为整数
			{
				char nene=0x37;
				rhs.instr.list[rhs.instr.length]=nene;
				rhs.instr.count++;
				rhs.instr.length++;
			}
			rhs.type=tyty;
			peek=nextToken();//再来 
		}
		while(is_binary_op(peek)&&prec(peek)>prec(op))//peek是二元运算符且peek优先级大于op优先级。因为赋值只能出现一次，且优先级最低，故无需考虑右结合 
		{
			rhs=parse_opg(rhs,prec(peek));//先做右边 
			peek=nextToken();
			while(peek==1)//是个as
			{
				if(rhs.type!=1&&rhs.type!=2)
				{
					exit(-1);
				}
				int tyty=ty();//读入
				if(tyty!=1&&tyty!=2)
				{
					exit(-1);
				}
				if(rhs.type==1&&tyty==2)//要转为浮点
				{
					char nene=0x36;
					rhs.instr.list[rhs.instr.length]=nene;
					rhs.instr.count++;
					rhs.instr.length++;
				}
				else if(rhs.type==2&&tyty==1)//要转为整数
				{
					char nene=0x37;
					rhs.instr.list[rhs.instr.length]=nene;
					rhs.instr.count++;
					rhs.instr.length++;
				}
				rhs.type=tyty;
				peek=nextToken();//再来 
			}
		}
		lhs=combine(lhs,op,rhs);//表示规约 
	}
	return lhs;
}

struct expression expr()//解析表达式 
{
	struct expression lhs=parse_primary();
	return parse_opg(lhs,0);//0表示这是非终结符 
}
 
// 造一条：比较运算符的运行结果是布尔类型，只能出现在 if 和 while 语句的条件表达式中。运算符的两侧必须是相同类型的数据
// 但是while和if里不止可以出现这个。相当于优先级最低，顺序左到右 
// bool_expr -> expr '==' | '!=' | '<' | '>' | '<=' | '>=' expr
struct instruction bool_expr()//比较的表达式，直接指令即可 
{
	struct expression lhs=expr();
	int next=nextToken();
	if(next==30||next==34||next==35||next==37||next==38||next==39)//可能是就一个表达式 
	{
		struct expression rhs=expr();
		if(lhs.type!=rhs.type||lhs.type==0||rhs.type==0)//先检查左右两边type是否一致或是否为0 
		{
			exit(-1);//有问题 
		}
		char nene;//比较指令。结束时结果储存在栈顶，先左小于后右是-1 
		if(lhs.type==1)
		{
			nene=0x30;
		}
		else if(lhs.type==2)
		{
			nene=0x32;
		}
		else
		{
			exit(-1);
		} 
		struct instruction temp;
		memset(&temp,0,sizeof(struct instruction));//清零 
		temp=instrcat(lhs.instr,rhs.instr);//指令部分直接拼接进来 
		temp.list[temp.instr.length]=nene;
		temp.count++;
		temp.length++;
		if(next==30)//不等于。栈顶是1或-1则为1，否则为0。跳转用是0和非0，故不用管 
		{
			return temp;
		}
		else if(next==34)//小于。栈顶是-1则为1，否则为0。即仅小于0的时候为1 
		{
			nene=0x39;
			temp.list[temp.instr.length]=nene;
			temp.count++;
			temp.length++;
			return temp;
		}
		else if(next==35)//大于。栈顶是1则为1，否则为0。即仅大于0的时候为1 
		{
			nene=0x3a;
			temp.list[temp.instr.length]=nene;
			temp.count++;
			temp.length++;
			return temp;
		}
		else if(next==37)//等于。栈顶是0则为1，否则为0 
		{
			nene=0x2e;//先取反，末位固定 
			temp.list[temp.instr.length]=nene;
			temp.count++;
			temp.length++;
			nene=0x01;//再push一个1进去 
			temp.list[temp.instr.length]=nene;
			temp.count++;
			temp.length++;//光标先移动才能放long 
			long long phph=1; 
			storelong(&phph,temp.list,temp.length);
			temp.length+=8;//一个64位占8个char 
			nene=0x2b;//最后按位与 
			temp.list[temp.instr.length]=nene;
			temp.count++;
			temp.length++;
			return temp;
		}
		else if(next==38)//小于等于。栈顶是0或-1则为1，否则为0 
		{
			nene=0x01;//push一个1进去 
			temp.list[temp.instr.length]=nene;
			temp.count++;
			temp.length++;//光标先移动才能放long 
			long long phph=1; 
			storelong(&phph,temp.list,temp.length);
			temp.length+=8;//一个64位占8个char 
			nene=0x2d;//然后按位异或 
			temp.list[temp.instr.length]=nene;
			temp.count++;
			temp.length++;
			return temp;
		}
		else if(next==39)//大于等于。栈顶是0或1则为1，否则为0 
		{
			nene=0x2e;//直接取反 
			temp.list[temp.instr.length]=nene;
			temp.count++;
			temp.length++;
		}
		else
		{
			exit(-1);
		}
	}
	else
	{
		unreadToken();//退回 
		if(lhs.type==0)
		{
			exit(-1);
		}
		struct instruction temp=lhs.instr;//浮点0也是0，但有可能有符号位。因此左移1位
		nene=0x01;//要先push一个1进去 
		temp.list[temp.instr.length]=nene;
		temp.count++;
		temp.length++;//光标先移动才能放long 
		long long phph=1; 
		storelong(&phph,temp.list,temp.length);
		temp.length+=8;//一个64位占8个char 
		char nene=0x29;//左移 
		temp.list[temp.instr.length]=nene;
		temp.count++;
		temp.length++;
	}
}

//表达式语句，开头为左小括号（23）、减号（31）、标识符（51）、整数（41）和浮点数（42），不得预读。
//expr_stmt -> expr ';'
struct instruction expr_stmt()
{
	struct instruction temp=expr().instr;
	int next=nextToken();
	if(next!=29)//分号 
	{
		exit(-1);
	}
	return temp;
}

//声明语句不对。expr传过来的应当是一个语句序列，因此不应当初始化。 
//根据是否全局状态来进行安插符号表 
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
	int typpp=ty();//类型 
	tok=nextToken();
	if(tok!=33)//等号 
	{
		exit(-1);
	}
	expr();//表达式
	//此处应处理表达式 
	long long intint;//假设int表达式的值存在这里 
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
		long long intint;//假设int表达式的值存在这里 
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
		STACK[STACKTOP].invalid=1;//注明没初始化 
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

//未处理block内部内容 
//function -> 'fn' IDENT '(' function_param_list? ')' '->' ty block_stmt
//function_param_list -> function_param (',' function_param)*
void function()//函数，以fn（6）开头。规定开头调用前已经被读了，下一个默认是标识符（51） 
{

//	int type;//类型决定返回值有多少个8字节。void为0，int和double都为8。此处记录0，1和2 

//	int param[16];//最多16个参数。参数为1表示int，2表示double 
//	int paramtop;//参数列表决定多少个8字节。int和double都为8，故乘8即可。
//	int local;//局部变量有多少个8字节
//	struct instruction instr[1024];//函数的指令列 

//	FUNCTIONLIST[FUNCTIONLISTTOP].type=0;//无返回值

//	FUNCTIONLIST[FUNCTIONLISTTOP].param=0;//无参数 
//	FUNCTIONLIST[FUNCTIONLISTTOP].local=0;//无局部变量
//	FUNCTIONLIST[FUNCTIONLISTTOP].count=1;//只有一个指令 
//	char chte[10];
//	strcpy(chte,"main");
//	int temp=find_now(chte);//返回函数名称main在全局变量中的位置
//	FUNCTIONLIST[FUNCTIONLISTTOP].instr[0]=(char)0x4a;//callname 
//	FUNCTIONLIST[FUNCTIONLISTTOP].instr[1]=(char)((temp>>24) & 0x000000ff);//大端 
//	FUNCTIONLIST[FUNCTIONLISTTOP].instr[2]=(char)((temp>>16) & 0x000000ff);
//	FUNCTIONLIST[FUNCTIONLISTTOP].instr[3]=(char)((temp>> 8) & 0x000000ff);
//	FUNCTIONLIST[FUNCTIONLISTTOP].instr[4]=(char)((temp>> 0) & 0x000000ff);
//	FUNCTIONLISTTOP++; 
	int next=nextToken();
	if(next!=51)//标识符 
	{
		exit(-1);
	}
	char* iii=(char *)malloc(sizeof(char)*128);//处理标识符（51）
	strcpy(iii,TOKEN);
	int fff=find_now(iii);
	if(fff!=-1)//表里能查到 
	{
		exit(-1);//语义错误 
	}
	memset(&TABLE[TABLETOP],0,sizeof(struct symboltable));//填之前先清空这一格，以免出错 
	strcpy(TABLE[TABLETOP].name,iii);
	TABLE[TABLETOP].isconst=1;
	TABLE[TABLETOP].type=3;
	memset(&FUNCTIONLIST[FUNCTIONLISTTOP],0,sizeof(struct functionlist));//填之前先清空这一格，以免出错 
	FUNCTIONLIST[FUNCTIONLISTTOP].name=TABLETOP;
	TABLETOP++;//填完了函数名 
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
			function_param();//执行函数的参数列表项 
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

//需要一开始按顺序放进入7个标准库 
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
	int temp=find_now(chte);//返回函数名称main在全局变量中的位置
	FUNCTIONLIST[FUNCTIONLISTTOP].instr[0]=(char)0x4a;//callname 
	FUNCTIONLIST[FUNCTIONLISTTOP].instr[1]=(char)((temp>>24) & 0x000000ff);//大端 
	FUNCTIONLIST[FUNCTIONLISTTOP].instr[2]=(char)((temp>>16) & 0x000000ff);
	FUNCTIONLIST[FUNCTIONLISTTOP].instr[3]=(char)((temp>> 8) & 0x000000ff);
	FUNCTIONLIST[FUNCTIONLISTTOP].instr[4]=(char)((temp>> 0) & 0x000000ff);
	FUNCTIONLISTTOP++; 
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
			int len=8;
			outint(len);
			fwrite(&TABLE[i].value1,sizeof(long long),1,OUT);
		}
		else if(TABLE[i].type==2)//是浮点数 
		{
			int len=8;
			outint(len);
			fwrite(&TABLE[i].value2,sizeof(double),1,OUT);
		}
		else if(TABLE[i].type==3)//是函数名或者字符串 
		{
			int len=strlen(TABLE[i].name);
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
		if(FUNCTIONLIST[i].type==0)//型
		{
			int ttt=0;
			outint(ttt);
		}
		else if(FUNCTIONLIST[i].type==1)//型
		{
			int ttt=8;
			outint(ttt);
		}
		else if(FUNCTIONLIST[i].type==2)//型
		{
			int ttt=8;
			outint(ttt);
		}
		outint(8*FUNCTIONLIST[i].paramtop);//参
		outint(FUNCTIONLIST[i].local);//局
		outint(FUNCTIONLIST[i].count);//数
		int len=strlen(FUNCTIONLIST[i].instr);
		fwrite(FUNCTIONLIST[i].instr,sizeof(char),len,OUT);
	}
	fclose(OUT);
	fclose(IN);
	return 0;
}

