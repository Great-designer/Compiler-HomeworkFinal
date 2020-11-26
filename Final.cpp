#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char token[2048];//存储当前字符串常量（44），或者标识符（51）
int num;//无符号整数（41，语法分析中允许取反） 
double dou;//无符号浮点数（42，语法分析中允许取反） 
char ch;//字符常量（43） 

int reserver()//关键字表，共10个 
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
		int resultValue=reserver();//resultValue查找保留字的返回值 
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

int nextToken()//返回下一个token的类别码，注释不视为Token 
{
	int sym=getToken();
	while(sym==-2)//发现注释，只好再读一个 
	{
		sym=getToken();
	}
	return sym;
}

//目前的情形：
//token为关键字、运算符和文档结尾（-1）的时候，直接看返回的编号即可
//token为整数（41）、浮点数（42）或字符常量（43），存储在num、dou和ch 
//token为字符串（44）或标识符（51），都存储在token
//对于41、42、43、44、51情形，需要找一个token栈表来存储它们，这样才能实现unreadToken功能
//unreadToken，可以直接将token压入token栈表 
//需要修改nextToken函数。如果token栈表中有token，就从栈表中取。token栈表清空了，才会继续getToken 

//实现了unreadToken，然后才能开始做语法分析 

int main(int argc,char *argv[])
{
	in=fopen(argv[1],"r");
	
	fclose(in);
	return 0;
}

