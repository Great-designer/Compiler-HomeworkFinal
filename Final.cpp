#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char token[2048];//当前字符串常量（44），或者标识符（51）
int num;//当前无符号整数（41，语法分析中允许取负） 
double dou;//当前无符号浮点数（42，语法分析中允许取负） 
char ch;//当前字符常量（43） 

int reser()//关键字表，共10个 
{
	if(strcmp(token,"as")==0)
	{
		return 1;
	}
	else if(strcmp(token,"break")==0)
	{
		return 2;
	}
	else if(strcmp(token,"const")==0)
	{
		return 3;
	}
	else if(strcmp(token,"continue")==0)
	{
		return 4;
	}
	else if(strcmp(token,"else")==0)
	{
		return 5;
	}
	else if(strcmp(token,"fn")==0)
	{
		return 6;
	}
	else if(strcmp(token,"if")==0)
	{
		return 7;
	}
	else if(strcmp(token,"let")==0)
	{
		return 8;
	}
	else if(strcmp(token,"return")==0)
	{
		return 9;
	}
	else if(strcmp(token,"while")==0)
	{
		return 10;
	}
	else//标识符 
	{
		return 0;
	}
}

FILE *in;//流指针 

int getToken()//返回下一个token的类别码，注释视为Token 
{
	int symbol;//待返回类别码 
	char cc=' ';//光标，先置入一个空白字符 
	memset(token,0,sizeof(token));//每次调用，token必须清空 
	while(isspace(cc))//读字符，跳空格、换行和Tab 
	{
		cc=fgetc(in);
	}
	if(isalpha(cc)||cc=='_')//标识符或关键字 
	{
		while(isalpha(cc)||isdigit(cc)||cc=='_')//将字符拼接成字符串 
		{
			strncat(token,&cc,1);
			cc=fgetc(in); 
		}
		ungetc(cc,in);//指针后退一个字符
		int resultValue=reser();//resultValue查找保留字的返回值 
		if(resultValue==0)//token中字符串为标识符 
		{
			symbol=51;
		}
		else//token中字符串为保留字 
		{
			symbol=resultValue;
		}
	}
	else if(isdigit(cc))//整数和浮点数 
	{
		while(isdigit(cc))//将字符拼接成整数 
		{
			strncat(token,&cc,1);
			cc=fgetc(in);
		}
		if(cc='.')//有小数点
		{
			cc=fgetc(in);//先不急着拼接，再读一个 
			if(!isdigit(cc))//没有数字，证明不是浮点数 
			{
				ungetc(cc,in);//退回非数字 
				ungetc(cc,in);//退回小数点
				num=atoi(token);//将token中的字符串转换为整数 
				symbol=41;//此时识别的单词是整数 
			}
			else//有数字，那么至少这部分已经是一个浮点数 
			{
				char poi='.'; 
				strncat(token,&poi,1);//先接一个小数点，因为cc已经是数字了 
				while(isdigit(cc))
				{
					strncat(token,&cc,1);
					cc=fgetc(in);
				}
				if(cc=='e'||cc=='E')//还有可能，后面接E或e
				{
					cc=fgetc(in);//先不急着拼接，再读一个
					if(cc=='+')//有可能是+ 
					{
						cc=fgetc(in);//先不急着拼接，再读一个
						if(!isdigit(cc))//非数字，证明此部分无效 
						{
							ungetc(cc,in);//退回非数字 
							ungetc(cc,in);//退回符号 
							ungetc(cc,in);//退回e
							dou=atof(token);//将token中的字符串转换为浮点数 
							symbol=42;//此时识别的单词是浮点数 
						}
						else//是数字，这部分有效 
						{
							char eee='e'; 
							strncat(token,&eee,1);
							char fff='+';
							strncat(token,&fff,1);
							while(isdigit(cc))
							{
								strncat(token,&cc,1);
								cc=fgetc(in);
							}
							ungetc(cc,in);//退回字符 
							dou=atof(token);//将token中的字符串转换为浮点数 
							symbol=42;//此时识别的单词是浮点数 
						}
					}
					else if(cc=='-')//有可能是-
					{
						cc=fgetc(in);//先不急着拼接，再读一个
						if(!isdigit(cc))//非数字，证明此部分无效 
						{
							ungetc(cc,in);//退回非数字 
							ungetc(cc,in);//退回符号 
							ungetc(cc,in);//退回e
							dou=atof(token);//将token中的字符串转换为浮点数 
							symbol=42;//此时识别的单词是浮点数 
						}
						else//是数字，这部分有效 
						{
							char eee='e'; 
							strncat(token,&eee,1);
							char fff='-';
							strncat(token,&fff,1);
							while(isdigit(cc))
							{
								strncat(token,&cc,1);
								cc=fgetc(in);
							}
							ungetc(cc,in);//退回字符 
							dou=atof(token);//将token中的字符串转换为浮点数 
							symbol=42;//此时识别的单词是浮点数 
						}
					}
					else if(!isdigit(cc))//非数字，证明此部分无效 
					{
						ungetc(cc,in);//退回非数字 
						ungetc(cc,in);//退回e
						dou=atof(token);//将token中的字符串转换为浮点数 
						symbol=42;//此时识别的单词是浮点数 
					}
					else//是数字，这部分有效 
					{
						char eee='e'; 
						strncat(token,&eee,1);//先接一个e，因为cc已经是数字了 
						while(isdigit(cc))
						{
							strncat(token,&cc,1);
							cc=fgetc(in);
						}
					}
				}
			}
		}
		else if(cc=='e'||cc=='E')//还有可能，后面接E或e
		{
			cc=fgetc(in);//先不急着拼接，再读一个
			if(cc=='+')//有可能是+ 
			{
				cc=fgetc(in);//先不急着拼接，再读一个
				if(!isdigit(cc))//非数字，证明此部分无效 
				{
					ungetc(cc,in);//退回非数字 
					ungetc(cc,in);//退回符号 
					ungetc(cc,in);//退回e
					num=atoi(token);//将token中的字符串转换为整数 
					symbol=41;//此时识别的单词是整数 
				}
				else//是数字，这部分有效 
				{
					char eee='e'; 
					strncat(token,&eee,1);
					char fff='+';
					strncat(token,&fff,1);
					while(isdigit(cc))
					{
						strncat(token,&cc,1);
						cc=fgetc(in);
					}
					ungetc(cc,in);//退回字符 
					dou=atof(token);//将token中的字符串转换为浮点数 
					symbol=42;//此时识别的单词是浮点数 
				}
			}
			else if(cc=='-')//有可能是-
			{
				cc=fgetc(in);//先不急着拼接，再读一个
				if(!isdigit(cc))//非数字，证明此部分无效 
				{
					ungetc(cc,in);//退回非数字 
					ungetc(cc,in);//退回符号 
					ungetc(cc,in);//退回e
					num=atoi(token);//将token中的字符串转换为整数 
					symbol=41;//此时识别的单词是整数 
				}
				else//是数字，这部分有效 
				{
					char eee='e'; 
					strncat(token,&eee,1);
					char fff='-';
					strncat(token,&fff,1);
					while(isdigit(cc))
					{
						strncat(token,&cc,1);
						cc=fgetc(in);
					}
					ungetc(cc,in);//退回字符 
					dou=atof(token);//将token中的字符串转换为浮点数 
					symbol=42;//此时识别的单词是浮点数 
				}
			}
			else if(!isdigit(cc))//非数字，证明此部分无效 
			{
				ungetc(cc,in);//退回非数字 
				ungetc(cc,in);//退回e
				num=atoi(token);//将token中的字符串转换为整数 
				symbol=41;//此时识别的单词是整数 
			}
			else//是数字，这部分有效 
			{
				char eee='e'; 
				strncat(token,&eee,1);//先接一个e，因为cc已经是数字了 
				while(isdigit(cc))
				{
					strncat(token,&cc,1);
					cc=fgetc(in);
				}
				ungetc(cc,in);//退回字符 
				dou=atof(token);//将token中的字符串转换为浮点数 
				symbol=42;//此时识别的单词是浮点数 
			}
		}
		else//没有小数点，也没有E或e
		{
			ungetc(cc,in);//退回字符 
			num=atoi(token);//将token中的字符串转换为整数 
			symbol=41;//此时识别的单词是整数 
		}
	}
	else if(cc=='\'')//单引号情形，要判断是否合法 
	{
		cc=fgetc(in);
		if(cc=='\''||cc=='\n'||cc=='\t'||cc=='\r')
		{
			exit(-1);//出错 
		}
		else if(cc=='\\')
		{
			cc=fgetc(in);//这时候有可能出错，还要预读 
			if(cc=='\''||cc=='\"'||cc=='\\'||cc=='n'||cc=='t'||cc=='r')
			{
				char tttt=cc;//暂存
				cc=fgetc(in);
				if(cc=='\'')//单引号 
				{
					ch=tttt;//合法
					symbol=43;
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
			cc=fgetc(in);//预读
			if(cc=='\'')//合法
			{
				ch=tttt;
				symbol=43;
			}
			else//非法 
			{
				exit(-1);//出错 
			}
		}
	}
	else if(cc=='\"')//双引号
	{
		cc=fgetc(in);
		while(cc!='\"')//只要不是双引号就要继续读 
		{
			if(cc=='\n'||cc=='\t'||cc=='\r'||cc=='\0')
			{
				exit(-1);//出错 
			}
			else if(cc=='\\')//可能是转义 
			{
				cc=fgetc(in);//这时候有可能出错，还要预读 
				if(cc=='\''||cc=='\"'||cc=='\\'||cc=='n'||cc=='t'||cc=='r')
				{
					strncat(token,&cc,1);
				}
				else
				{
					exit(-1);//出错 
				}
			}
			else//合法
			{
				strncat(token,&cc,1);
			}
			cc=fgetc(in);//循环结束时再读一个 
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
				cc=fgetc(in);
				if(cc=='=')
				{
					symbol=30;
				}
				else
				{
					ungetc(cc,in);
					exit(-1);
				}
			break;
			case'-':
				cc=fgetc(in);
				if(cc=='>')
				{
					symbol=36;
				}
				else
				{
					ungetc(cc,in);
					symbol=31;
				}
			break;
			case'/':
				cc=fgetc(in);
				if(cc=='/')
				{
					while(cc!='\n')
					{
						cc=fgetc(in);
					}
					symbol=-2;//-2是注释 
				}
				else
				{
					ungetc(cc,in);
					symbol=32;
				}
			break;
			case'=':
				cc=fgetc(in);
				if(cc=='=')
				{
					symbol=37;
				}
				else
				{
					ungetc(cc,in);
					symbol=33;
				}
			break;
			case'<':
				cc=fgetc(in);
				if(cc=='=')
				{
					symbol=38;
				}
				else
				{
					ungetc(cc,in);
					symbol=34;
				}
			break;
			case'>':
				cc=fgetc(in);
				if(cc=='=')
				{
					symbol=39;
				}
				else
				{
					ungetc(cc,in);
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

//token为字符串（44）或标识符（51），都存储在token
char tokenPre[2048];//预读的字符串常量（44），或者标识符（51）

//token为整数（41）、浮点数（42）或字符常量（43），存储在num、dou和ch 
int numPre;//无符号整数（41，语法分析中允许取负） 
double douPre;//无符号浮点数（42，语法分析中允许取负） 
char chPre;//字符常量（43） 

//token为关键字、运算符和文档结尾（-1）的时候，直接看返回的编号即可
int symPre;
int preValid; 

int nextToken()//返回下一个token的类别码，注释不视为Token。只要使用nextToken，上一个状态就丢弃了 
{
	int sym;//待返回 
	if(preValid==1)//执行过unreadToken。还原之前预读结果，并置valid为0
	{
		sym=symPre;
		preValid=0;
		switch(sym)
		{
			case 41://整数 
				num=numPre;
			break;
			case 42://浮点数 
				dou=douPre;
			break;
			case 43://字符 
				ch=chPre;
			break;
			case 44://字符串 
				strcpy(token,tokenPre);
			break;
			case 51://标识符 
				strcpy(token,tokenPre);
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
		symPre=sym;
		switch(sym)
		{
			case 41://整数 
				numPre=num;
			break;
			case 42://浮点数 
				douPre=dou;
			break;
			case 43://字符 
				chPre=ch;
			break;
			case 44://字符串 
				strcpy(tokenPre,token);
			break;
			case 51://标识符 
				strcpy(tokenPre,token);
			break;
			default://其他情况，什么都不用做 
			break;
		}
	}
	return sym;
}

void unreadToken()//将当前的情形压回栈中。至多只能保存一步预读情形，上一步丢失。禁止连续使用两次。
{
	if(preValid==1)//预读已经有效，证明当前位置在预读前，无法再回退 
	{
		exit(-1); 
	}
	else
	{
		preValid=1;//置预读为有效 
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
	if(strcmp(token,"void")==0)
	{
		return 0;
	}
	else if(strcmp(token,"int")==0)
	{
		return 1;
	}
	else if(strcmp(token,"double")==0)
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

// 类型转换表达式，子表达式开头，有子表达式，只会涉及到整数int和浮点数double之间的互相转换，将左侧表达式表示的值转换成右侧类型表示的值。优先级第二高 
// as_expr -> expr 'as'（1） ty

// 以下五个最高 

// 取反表达式，减号（31）开头，相反数，有子表达式 
// negate_expr -> '-' expr

// 括号表达式，开头左小括号（23），优先计算 
// group_expr -> '(' expr ')'

// 这三个视作整体 

// 字面量表达式，开头（41）（42）
// literal_expr -> UINT_LITERAL | DOUBLE_LITERAL

// 标识符表达式，只有标识符（51）开头，后空。语义是标识符对应的局部或全局变量。标识符表达式的类型与标识符的类型相同
// ident_expr -> IDENT

// 函数调用表达式，标识符（51）开头，下一token左括号（23），有子表达式，由函数名和调用参数列表组成的表达式
// 函数必须在调用前声明过，标准库中的函数在调用前不需要声明 
// call_expr -> IDENT '(' call_param_list? ')'
// call_param_list -> expr (',' expr)*

//# ( + - * / ) 整数（41）和浮点数（42）同一类
//#只能是分号;（29）或左大括号{（25），一定不是EOF 
int f[8]={0,0,2,2,4,4,5,5};//栈顶
int g[8]={0,5,1,1,3,3,0,5};//读入

//8a+b，共有6个非法状态，5个特殊状态，1个调用状态（左标识符右左括号，为8*标识符7+1=57） 
int error[6]={0,6,8,49,55,63};
int special[5]={11,19,27,35,43}; 

int translate(int t)//token翻译器，必须是上述7种符号才能进入翻译器，仅查表时用到 
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

void expr();

void call_param_list()//已经读过了ident和左括号 
{
	expr(); 
	int next=nextToken();
	while(next!=24)//右括号结束，逗号表示没结束
	{
		if(next==27)
		{
			expr(); 
		}
		else
		{
			exit(-1);
		}
		next=nextToken();//右括号被读了 
	}
}

//expr -> operator_expr| negate_expr| as_expr| call_expr| literal_expr| ident_expr| group_expr
void expr()//表达式，7种可能。expr有可能调用expr，因此它涉及的全局变量需要改为申请。开头不得预读。 
{
	int aaa,bbb;//自变量。n代表不区分的非终结符，为-2 
	int *expstack=(int *)malloc(sizeof(int)*2048);//栈里面永远是标准编号 
	int expstacktop=0;//expstacktop总指向栈顶元素的下一个位置，即expstacktop-1才是栈顶元素 
	int next=nextToken();//读入
	if(next==1)//as是特殊字符，读入as的时候特判 
	{
		exit(-1);//这时候肯定不对 
	}
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
			for(i=0;i<5;i++)//先查5个special
			{
				if(count==special[i])//处理特殊减号 
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
				if(count==error[i])
				{
					exit(-1);//无法判断优先级关系
				}
			}
			if(count==57)//标识符加左括号。这时候应当触发函数调用
			{
				call_param_list();//触发函数调用。结束后右括号已经被读了 
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
			if(f[aaa]>g[bbb])//仅大于的时候才规约，其他时候读入。仅规约跳过最后读入部分 
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
		if(next==25||next==27||next==29)//读入了尾字符的时候，不能再读了 
		{
			unreadToken();//此时会倒退一个。但是next保持为0，然后由于continue，此分支将无法进入 
		}
	}
	free(expstack);
}

// 未完成 
// 造一条：比较运算符的运行结果是布尔类型，只能出现在 if 和 while 语句的条件表达式中。运算符的两侧必须是相同类型的数据 
// 但是while和if里不止可以出现这个。相当于优先级最低，顺序左到右 
// bool_expr -> expr '==' | '!=' | '<' | '>' | '<=' | '>=' expr
void bool_expr()
{
	
}

// 赋值表达式和左值表达式，标识符（51）开头，有子表达式 ，值类型void，不能被使用。相当于优先级最低，顺序右到左 
// assign_expr -> l_expr '=' expr
// l_expr -> IDENT
void assign_expr()
{
	
}

// 补一条：字符串表达式和字符表达式 
// STRING_LITERAL | CHAR_LITERAL
// （43）（44），只会在 putstr 调用中出现，语义是对应的全局常量的编号

//const_decl_stmt -> 'const' IDENT ':' ty '=' expr ';'
void const_decl_stmt()//常量，以const（3）开头。规定开头调用前已经被读了，下一个默认是标识符（51）
{
	int tok=nextToken();
	if(tok!=51)
	{
		exit(-1);
	}
	//此处应处理标识符（51）
	tok=nextToken();
	if(tok!=28)//冒号 
	{
		exit(-1);
	}
	int typpp=ty();//类型 
	//此处应处理类型
	tok=nextToken();
	if(tok!=33)//等号 
	{
		exit(-1);
	}
	expr();//表达式
	//此处应处理表达式 
	tok=nextToken();
	if(tok!=29)//分号 
	{
		exit(-1);
	}
}

//let_decl_stmt -> 'let' IDENT ':' ty ('=' expr)? ';'
void let_decl_stmt()//变量，以let（8）开头。规定开头调用前已经被读了，下一个默认是标识符（51）
{
	int tok=nextToken();
	if(tok!=51)
	{
		exit(-1);
	}
	//此处应处理标识符（51）
	tok=nextToken();
	if(tok!=28)//冒号 
	{
		exit(-1);
	}
	int typpp=ty();
	//此处应处理类型
	tok=nextToken();
	if(tok==33)//等于部分可以选择省略
	{
		expr();
		//此处应处理表达式 
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
		return;
	}
	else
	{
		exit(-1);
	}
}

//未完成 
//function -> 'fn' IDENT '(' function_param_list? ')' '->' ty block_stmt
//function_param_list -> function_param (',' function_param)*
//function_param -> 'const'? IDENT ':' ty
void function()//函数，以fn（6）开头。规定开头调用前已经被读了，下一个默认是标识符（51） 
{
	int tok=nextToken();
	if(tok!=51)
	{
		exit(-1);
	}
	//此处应处理标识符（51）
	tok=nextToken();
	if(tok!=23)//左小括号 
	{
		exit(-1);
	}
	
	
	
}

//program -> item*
//item -> function | decl_stmt
//decl_stmt -> let_decl_stmt | const_decl_stmt
void program()//程序，必然是常量（3）、变量（8）或函数（6）
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
	preValid=0;//预读无效 
}

int main(int argc,char *argv[])
{
	in=fopen(argv[1],"r");
	init(); 
	
	fclose(in);
	return 0;
}

