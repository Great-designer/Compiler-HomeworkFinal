#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char TOKEN[128];//��ǰ�ַ���������44�������߱�ʶ����51��
long long NUM;//��ǰ�޷���������41���﷨����������ȡ���� 
double DOU;//��ǰ�޷��Ÿ�������42���﷨����������ȡ���� 

int reser()//�ؼ��ֱ���10�� 
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
	else//��ʶ�� 
	{
		return 0;
	}
}

FILE *IN;//��ָ�� 

int getToken()//������һ��TOKEN������룬ע����ΪToken 
{
	int symbol;//����������� 
	char cc=' ';//��꣬������һ���հ��ַ� 
	memset(TOKEN,0,sizeof(TOKEN));//ÿ�ε��ã�TOKEN������� 
	while(isspace(cc))//���ַ������ո񡢻��к�Tab 
	{
		cc=fgetc(IN);
	}
	if(isalpha(cc)||cc=='_')//��ʶ����ؼ��� 
	{
		while(isalpha(cc)||isdigit(cc)||cc=='_')//���ַ�ƴ�ӳ��ַ��� 
		{
			strncat(TOKEN,&cc,1);
			cc=fgetc(IN); 
		}
		ungetc(cc,IN);//ָ�����һ���ַ�
		int resultValue=reser();//resultValue���ұ����ֵķ���ֵ 
		if(resultValue==0)//TOKEN���ַ���Ϊ��ʶ�� 
		{
			symbol=51;
		}
		else//TOKEN���ַ���Ϊ������ 
		{
			symbol=resultValue;
		}
	}
	else if(isdigit(cc))//�����͸����� 
	{
		while(isdigit(cc))//���ַ�ƴ�ӳ����� 
		{
			strncat(TOKEN,&cc,1);
			cc=fgetc(IN);
		}
		if(cc='.')//��С����
		{
			cc=fgetc(IN);//�Ȳ�����ƴ�ӣ��ٶ�һ�� 
			if(!isdigit(cc))//û�����֣�֤�����Ǹ����� 
			{
				ungetc(cc,IN);//�˻ط����� 
				ungetc(cc,IN);//�˻�С����
				NUM=atoll(TOKEN);//��TOKEN�е��ַ���ת��Ϊ���� 
				symbol=41;//��ʱʶ��ĵ��������� 
			}
			else//�����֣���ô�����ⲿ���Ѿ���һ�������� 
			{
				char poi='.'; 
				strncat(TOKEN,&poi,1);//�Ƚ�һ��С���㣬��Ϊcc�Ѿ��������� 
				while(isdigit(cc))
				{
					strncat(TOKEN,&cc,1);
					cc=fgetc(IN);
				}
				if(cc=='e'||cc=='E')//���п��ܣ������E��e
				{
					cc=fgetc(IN);//�Ȳ�����ƴ�ӣ��ٶ�һ��
					if(cc=='+')//�п�����+ 
					{
						cc=fgetc(IN);//�Ȳ�����ƴ�ӣ��ٶ�һ��
						if(!isdigit(cc))//�����֣�֤���˲�����Ч 
						{
							ungetc(cc,IN);//�˻ط����� 
							ungetc(cc,IN);//�˻ط��� 
							ungetc(cc,IN);//�˻�e
							DOU=atof(TOKEN);//��TOKEN�е��ַ���ת��Ϊ������ 
							symbol=42;//��ʱʶ��ĵ����Ǹ����� 
						}
						else//�����֣��ⲿ����Ч 
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
							ungetc(cc,IN);//�˻��ַ� 
							DOU=atof(TOKEN);//��TOKEN�е��ַ���ת��Ϊ������ 
							symbol=42;//��ʱʶ��ĵ����Ǹ����� 
						}
					}
					else if(cc=='-')//�п�����-
					{
						cc=fgetc(IN);//�Ȳ�����ƴ�ӣ��ٶ�һ��
						if(!isdigit(cc))//�����֣�֤���˲�����Ч 
						{
							ungetc(cc,IN);//�˻ط����� 
							ungetc(cc,IN);//�˻ط��� 
							ungetc(cc,IN);//�˻�e
							DOU=atof(TOKEN);//��TOKEN�е��ַ���ת��Ϊ������ 
							symbol=42;//��ʱʶ��ĵ����Ǹ����� 
						}
						else//�����֣��ⲿ����Ч 
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
							ungetc(cc,IN);//�˻��ַ� 
							DOU=atof(TOKEN);//��TOKEN�е��ַ���ת��Ϊ������ 
							symbol=42;//��ʱʶ��ĵ����Ǹ����� 
						}
					}
					else if(!isdigit(cc))//�����֣�֤���˲�����Ч 
					{
						ungetc(cc,IN);//�˻ط����� 
						ungetc(cc,IN);//�˻�e
						DOU=atof(TOKEN);//��TOKEN�е��ַ���ת��Ϊ������ 
						symbol=42;//��ʱʶ��ĵ����Ǹ����� 
					}
					else//�����֣��ⲿ����Ч 
					{
						char eee='e'; 
						strncat(TOKEN,&eee,1);//�Ƚ�һ��e����Ϊcc�Ѿ��������� 
						while(isdigit(cc))
						{
							strncat(TOKEN,&cc,1);
							cc=fgetc(IN);
						}
					}
				}
			}
		}
		else if(cc=='e'||cc=='E')//���п��ܣ������E��e
		{
			cc=fgetc(IN);//�Ȳ�����ƴ�ӣ��ٶ�һ��
			if(cc=='+')//�п�����+ 
			{
				cc=fgetc(IN);//�Ȳ�����ƴ�ӣ��ٶ�һ��
				if(!isdigit(cc))//�����֣�֤���˲�����Ч 
				{
					ungetc(cc,IN);//�˻ط����� 
					ungetc(cc,IN);//�˻ط��� 
					ungetc(cc,IN);//�˻�e
					NUM=atoll(TOKEN);//��TOKEN�е��ַ���ת��Ϊ���� 
					symbol=41;//��ʱʶ��ĵ��������� 
				}
				else//�����֣��ⲿ����Ч 
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
					ungetc(cc,IN);//�˻��ַ� 
					DOU=atof(TOKEN);//��TOKEN�е��ַ���ת��Ϊ������ 
					symbol=42;//��ʱʶ��ĵ����Ǹ����� 
				}
			}
			else if(cc=='-')//�п�����-
			{
				cc=fgetc(IN);//�Ȳ�����ƴ�ӣ��ٶ�һ��
				if(!isdigit(cc))//�����֣�֤���˲�����Ч 
				{
					ungetc(cc,IN);//�˻ط����� 
					ungetc(cc,IN);//�˻ط��� 
					ungetc(cc,IN);//�˻�e
					NUM=atoll(TOKEN);//��TOKEN�е��ַ���ת��Ϊ���� 
					symbol=41;//��ʱʶ��ĵ��������� 
				}
				else//�����֣��ⲿ����Ч 
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
					ungetc(cc,IN);//�˻��ַ� 
					DOU=atof(TOKEN);//��TOKEN�е��ַ���ת��Ϊ������ 
					symbol=42;//��ʱʶ��ĵ����Ǹ����� 
				}
			}
			else if(!isdigit(cc))//�����֣�֤���˲�����Ч 
			{
				ungetc(cc,IN);//�˻ط����� 
				ungetc(cc,IN);//�˻�e
				NUM=atoll(TOKEN);//��TOKEN�е��ַ���ת��Ϊ���� 
				symbol=41;//��ʱʶ��ĵ��������� 
			}
			else//�����֣��ⲿ����Ч 
			{
				char eee='e'; 
				strncat(TOKEN,&eee,1);//�Ƚ�һ��e����Ϊcc�Ѿ��������� 
				while(isdigit(cc))
				{
					strncat(TOKEN,&cc,1);
					cc=fgetc(IN);
				}
				ungetc(cc,IN);//�˻��ַ� 
				DOU=atof(TOKEN);//��TOKEN�е��ַ���ת��Ϊ������ 
				symbol=42;//��ʱʶ��ĵ����Ǹ����� 
			}
		}
		else//û��С���㣬Ҳû��E��e
		{
			ungetc(cc,IN);//�˻��ַ� 
			NUM=atoll(TOKEN);//��TOKEN�е��ַ���ת��Ϊ���� 
			symbol=41;//��ʱʶ��ĵ��������� 
		}
	}
	else if(cc=='\'')//���������Σ�Ҫ�ж��Ƿ�Ϸ� 
	{
		cc=fgetc(IN);
		if(cc=='\''||cc=='\n'||cc=='\t'||cc=='\r')
		{
			exit(-1);//���� 
		}
		else if(cc=='\\')
		{
			cc=fgetc(IN);//��ʱ���п��ܳ�����ҪԤ�� 
			if(cc=='\''||cc=='\"'||cc=='\\'||cc=='n'||cc=='t'||cc=='r')
			{
				char tttt=cc;//�ݴ�
				cc=fgetc(IN);
				if(cc=='\'')//������ 
				{
					NUM=tttt;//�Ϸ�
					symbol=41;
				}
				else
				{
					exit(-1);//���� 
				}
			}
			else
			{
				exit(-1);//���� 
			}
		}
		else//�Ȳ��ǳ���Ҳ����ת�� 
		{
			char tttt=cc;//�ݴ�
			cc=fgetc(IN);//Ԥ��
			if(cc=='\'')//�Ϸ�
			{
				NUM=tttt;
				symbol=41;
			}
			else//�Ƿ� 
			{
				exit(-1);//���� 
			}
		}
	}
	else if(cc=='\"')//˫����
	{
		cc=fgetc(IN);
		while(cc!='\"')//ֻҪ����˫���ž�Ҫ������ 
		{
			if(cc=='\n'||cc=='\t'||cc=='\r'||cc=='\0')
			{
				exit(-1);//���� 
			}
			else if(cc=='\\')//������ת�� 
			{
				cc=fgetc(IN);//��ʱ���п��ܳ�����ҪԤ�� 
				if(cc=='\''||cc=='\"'||cc=='\\'||cc=='n'||cc=='t'||cc=='r')
				{
					strncat(TOKEN,&cc,1);
				}
				else
				{
					exit(-1);//���� 
				}
			}
			else//�Ϸ�
			{
				strncat(TOKEN,&cc,1);
			}
			cc=fgetc(IN);//ѭ������ʱ�ٶ�һ�� 
		}
		symbol=44;//����ʱccΪ˫���ţ��ʲ���unread 
	}
	else//�������14����Ŀ�������9+5����5��˫Ŀ�������1+4��������ע�ͺ�EOFҲ������ 
	{
		switch(cc)
		{
			case'+'://�ж��Ƿ�Ӻ�
				symbol=21;
			break;
			case'*'://�ж��Ƿ��Ǻ�
				symbol=22;
			break;
			case'('://�ж��Ƿ���С����
				symbol=23;
			break;
			case')'://�ж��Ƿ���С����
				symbol=24;
			break;
			case'{'://�ж��Ƿ��������
				symbol=25;
			break;
			case'}'://�ж��Ƿ��Ҵ�����
				symbol=26;
			break;
			case','://�ж��Ƿ񶺺� 
				symbol=27;
			break;
			case':'://�ж��Ƿ�ð��
				symbol=28;
			break;
			case';'://�ж��Ƿ�ֺ� 
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
					symbol=-2;//-2��ע�� 
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
			case EOF://��βΪ-1 
				symbol=-1;
			break;
			default://����
				exit(-1);
		}
	}
	return symbol;
}

//TOKENΪ�ַ�����44�����ʶ����51�������洢��TOKEN
char TOKENPRE[128];//Ԥ�����ַ���������44�������߱�ʶ����51��

//TOKENΪ������41������������42���򣬴洢��NUM��DOU
long long NUMPRE;//�޷���������41���﷨����������ȡ���� 
double DOUPRE;//�޷��Ÿ�������42���﷨����������ȡ���� 

//TOKENΪ�ؼ��֡���������ĵ���β��-1����ʱ��ֱ�ӿ����صı�ż���
int SYMPRE;
int PREVALID; 

int nextToken()//������һ��TOKEN������룬ע�Ͳ���ΪToken��ֻҪʹ��nextToken����һ��״̬�Ͷ����� 
{
	int sym;//������ 
	if(PREVALID==1)//ִ�й�unreadToken����ԭ֮ǰԤ�����������validΪ0
	{
		sym=SYMPRE;
		PREVALID=0;
		switch(sym)
		{
			case 41://���� 
				NUM=NUMPRE;
			break;
			case 42://������ 
				DOU=DOUPRE;
			break;
			case 44://�ַ��� 
				strcpy(TOKEN,TOKENPRE);
			break;
			case 51://��ʶ�� 
				strcpy(TOKEN,TOKENPRE);
			break;
			default://���������ʲô�������� 
			break;
		}
	}
	else//δִ��unreadToken�����벢����Ϊ��ʱ��Ч��Ԥ����� 
	{
		sym=getToken();
		while(sym==-2)//����ע�ͣ�ֻ���ٶ�һ�� 
		{
			sym=getToken();
		}
		SYMPRE=sym;
		switch(sym)
		{
			case 41://���� 
				NUMPRE=NUM;
			break;
			case 42://������ 
				DOUPRE=DOU;
			break;
			case 44://�ַ��� 
				strcpy(TOKENPRE,TOKEN);
			break;
			case 51://��ʶ�� 
				strcpy(TOKENPRE,TOKEN);
			break;
			default://���������ʲô�������� 
			break;
		}
	}
	return sym;
}

void unreadToken()//����ǰ������ѹ��ջ�С�����ֻ�ܱ���һ��Ԥ�����Σ���һ����ʧ����ֹ����ʹ�����Ρ�
{
	if(PREVALID==1)//Ԥ���Ѿ���Ч��֤����ǰλ����Ԥ��ǰ���޷��ٻ��� 
	{
		exit(-1); 
	}
	else
	{
		PREVALID=1;//��Ԥ��Ϊ��Ч 
	}
}

//ty -> IDENT
//��ȻΪvoid��0����int��1����double��2����һ
int ty()//���ͣ��Ծ�Ϊ��ʶ����51����������ͷ������Ԥ��
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
	else if(strcmp(TOKEN,"int")==0)//64λ��ʵ������long long 
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

// ��������ʽ operator_expr��ȡ�����ʽ negate_expr ������ת�����ʽ as_expr ����ʹ�þֲ�����������ķ�

// ��������ʽ���ӱ��ʽ��ͷ�����ӱ��ʽ����ֻ���������������������������������ͬ���͵����� 
// ���ȼ���˳��
// * /	����
// + -	����
// operator_expr -> expr binary_operator expr
// binary_operator -> '+' | '-' | '*' | '/' 

// ������� 

// ���ű��ʽ����ͷ��С���ţ�23�������ȼ��� 
// group_expr -> '(' expr ')'

// ������������ 

// ���������ʽ����ͷ������41����������42��
// literal_expr -> UINT_LITERAL | DOUBLE_LITERAL

// ��ʶ�����ʽ��ֻ�б�ʶ����51����ͷ����ա������Ǳ�ʶ����Ӧ�ľֲ���ȫ�ֱ�������ʶ�����ʽ���������ʶ����������ͬ
// ident_expr -> IDENT

//# ( + - * / ) ������41���͸�������42��ͬһ��
//#ֻ���Ƿֺ�;��29�����������{��25����һ������EOF 
int F[8]={0,0,2,2,4,4,5,5};//ջ��
int G[8]={0,5,1,1,3,3,0,5};//����

//8a+b������6���Ƿ�״̬��5������״̬��1������״̬�����ʶ���������ţ�Ϊ8*��ʶ��7+1=57�� 
int ERROR[6]={0,6,8,49,55,63};
int SPECIAL[5]={11,19,27,35,43}; 

int translate(int t)//TOKEN������������������7�ַ��Ų��ܽ��뷭�����������ʱ�õ� 
{
	switch(t)
	{
		case 25://������� 
		{
			return 0;
		}
		case 27://����
		{
			return 0;
		}
		case 29://�ֺ�
		{
			return 0;
		}
		case 30://�����ں�
		{
			return 0;
		}
		case 34://С�ں�
		{
			return 0;
		}
		case 35://���ں�
		{
			return 0;
		}
		case 37://���ڵ��ں�
		{
			return 0;
		}
		case 38://С�ڵ��ں�
		{
			return 0;
		}
		case 39://���ڵ��ں�
		{
			return 0;
		}
		case 23://������ 
		{
			return 1;
		}
		case 21://�Ӻ� 
		{
			return 2;
		}
		case 31://���� 
		{
			return 3;
		}
		case 22://�˺� 
		{
			return 4;
		}
		case 32://���� 
		{
			return 5;
		}
		case 24://������ 
		{
			return 6;
		}
		case 41://���� 
		{
			return 7;
		}
		case 42://������ 
		{
			return 7;
		}
		case 51://��ʶ�� 
		{
			return 7;
		}
		default://�Ƿ����뱨�� 
		{
			return -1;
		}
	}
}

struct instruction//ָ��ṹ�� 
{
	char list[1024];//ָ������
	char count;//ָ����� 
	int length;//ָ��� 
}; 

struct instruction instrcat(struct instruction A,struct instruction B)//ָ��ƴ�� 
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

//navm ��ָ��ʹ�� 8 λ��1 �ֽڣ��޷���������ʶ 
void storeint(int temp,char chttt[],int i)//��˷���32λ��4�ֽڣ�ָ�����ָ��λ�� 
{
	chttt[i]=(char)((temp>>24) & 0x000000ff);
    chttt[i+1]=(char)((temp>>16) & 0x000000ff);
    chttt[i+2]=(char)((temp>> 8) & 0x000000ff);
    chttt[i+3]=(char)((temp>> 0) & 0x000000ff);
}

void storelong(long long *pr,char chttt[],int i)//��˷���64λ��8�ֽڣ�ָ�����ָ��λ�á������ַ 
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

void storedouble(double *temp,char chttt[],int i)//��˷���64λ��8�ֽڣ�ָ�����ָ��λ�á������ַ 
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

struct expression//���ʽ�ṹ��
{
	int type;//�������͡�0Ϊvoid��1Ϊint��2Ϊdouble 
	struct instruction instr;//���ʽ��ָ���� 
};

//0x0a	loca	off:u32	-	1:addr	���� off �� slot ���ֲ������ĵ�ַ����loc0��ʼ 
//0x0b	arga	off:u32	-	1:addr	���� off �� slot ������/����ֵ�ĵ�ַ������ֵ��arg0��voidû�У���������arg1��arg0��void��arg1����ʼ��
//������Ҫ��ʼ��������ֵû�����֣�����ʹ�ã���Ϊδ��ʼ�� 
//0x0c	globa	n:u32	-	1:addr	���ص� n ��ȫ�ֱ���/�����ĵ�ַ��������ȫ�֡������Ͷ����Զ��� 
//��Ҫһ��ȫ�ֱ���ȫ�ֱ��������������ַ���������ʱ����������ջ���棬����Ҫջ 

struct symboltable//���ṹ�塣
{
	char name[64];//���֣����˴��ַ����ⲻ���ظ���typeΪ0ʱ��Ч����Ҫд��ȫ�ֳ�ʼ�����֡�����strlen 
	char isconst;//�ǳ���Ϊ1�����ǳ���Ϊ0���������Ϊ8�� 
	int valid;//δ��ʼ��Ϊ0����ʼ��Ϊ1 
	int type;//1Ϊint��2Ϊdouble������64����0Ϊvoid�ַ����������������ַ�������int��double�ĳ�ʼ������_start�� 
}; 

struct symboltable TABLE[128];//ȫ�ֱ����еĺ������ֶ�Ҫ���ȥ�������ó�ʼ�����Ͳ��ô�ֵ  
int TABLETOP;//���±� 

int find_table(char sss[])//���ݱ�������˳���ȫ�ַ��ű��鵽�����ڱ����±꣬δ�鵽����-1��
{
	int i;
	for(i=0;i<TABLETOP;i++)//���赹��
	{
		if(strcmp(TABLE[i].name,sss)==0)
		{
			return i;
		}
	}
	return -1;
}

//��Ҫһ�������������Ľṹ
//��������ȫ�ֱ�λ�� 
//����ֵ��arg0��void��û�У�ռ���ٸ�8�ֽڡ�ֻ��Ϊ0��1�����arg0�Ƿ񷵻�ֵ���� 
//������arg1��ʼ��void��arg0��ʼ��ռ���ٸ�8�ֽڡ�
//�����Ҫ����ֵ/��������¼ÿ������ֵ/�������Ƿ񷵻�ֵ�����͡��Ƿ�const�����֡�����ֵֻ�����ͣ�û��const������ 
//�ֲ�������loc0��ʼ������ռ���ٸ�8�ֽ�
//�ֲ�����ջ������ֲ����������������Ƕ�ס�����������ǿ��break��continue�����while������������·����飨���if��else��
//body�ж�����ָ���bodyָ�����instruction�ṹ�� 

struct symbolstack//�ֲ�����ջ�ṹ�� 
{
	int istop;//1��ʾ��һ����ջ�����º�����ʼ��ǰһ��Ĭ��Ϊ0 
	int destination;//�ھֲ��������е��±ꡣ
};

struct function//ȫ�ֺ����� 
{
	int name;//��ȫ�ַ��ű��λ��
	int type;//���;�������ֵ�ж��ٸ�8�ֽڣ��Լ���������ʼλ�á�voidΪ0��int��double��Ϊ8���˴���¼0��1��2 
	struct symboltable param[16];//���16�������뷵��ֵ��
	int paramtop;//����ջ����typeΪ1����2��ʱ��ջ��������һλ 
	int paramcount;//���������������������ٸ�8�ֽڡ�int��double��Ϊ8���ʳ�8���ɡ�
	struct symboltable localtable[32];//�ֲ�������
	int localtabletop;//�ֲ���������ָʾ�ж��ٸ�8�ֽ�
	struct symbolstack localstack[32];//�ֲ�����ջ������ֲ�������
	int localstacktop;//�ֲ�����ջ��
	struct instruction instr;//������ָ���� 
};

struct function FUNCLIST[64];//���64�������ɣ���ָ���һ�� 
int FUNCLISTTOP;

int find_func(char sss[])
{
	int i;
	for(i=0;i<FUNCLISTTOP;i++)//���赹��
	{
		if(strcmp(TABLE[FUNCLIST[i].name].name,sss)==0)
		{
			return i;//ֻ����������
		}
	}
	return -1;
}

int find_param(char sss[],int func)//���Ҳ�������Ҫ֪�����ĸ��������������Ϊ��������š�˳������ȫ�ֱ����֡�δ�鵽����-1��
{
	int i;
	for(i=0;i<FUNCLIST[func].paramtop;i++)//���赹��
	{
		if(type!=0&&i==0)//����ֵû�����֣����� 
		{
			continue;
		}
		if(strcmp(FUNCLIST[func].param[i].name,sss)==0)
		{
			return i;//�鵽�����ڲ��������±�
		}
	}
	return -1;
}

int find_all(char sss[],int func)//���ݱ�������ȫ�����ű�ջ���鵽������ջ���±꣬δ�鵽����-1��
{
	int i;
	for(i=FUNCLIST[func].localstacktop-1;i>=0;i--)//������ 
	{
		if(strcmp(FUNCLIST[func].localtable[FUNCLIST[func].localstack[i].destination].name,sss)==0)
		{
			return FUNCLIST[func].localstack[i].destination;
		}
	}
	return -1;
}

int find_now(char sss[],int func)//���ݱ������鵱ǰ����ű�ջ���鵽������ջ���±꣬δ�鵽����-1�� 
{
	int i;
	for(i=FUNCLIST[func].localstacktop-1;FUNCLIST[func].localstack[i].istop!=1&&i>=0;i--)//������ 
	{
		if(strcmp(FUNCLIST[func].localtable[FUNCLIST[func].localstack[i].destination].name,sss)==0)
		{
			return FUNCLIST[func].localstack[i].destination;
		}
	}
	return -1;
}

//���������Ҫ��ȫ�ֱ���������ں����У���Ҫ�鵱ǰ�����Ĳ��������鷵��ֵ�������ھֲ�����ջ�еľֲ������� 
//����������Ƕ��ԭ�򣬲���ʱ�Ȳ鵱ǰ���ٵ��򣬶���ɸ��ǡ��ֲ��������ǲ�������������ȫ�ֱ�����
//������ֻ�鵱ǰ�㡣��˶���ȫ�ֱ���ֻ��ȫ�ֱ������������ֻ�����������ֲ�����ֻ�鵱ǰblock������ȫ�ֱ�������һ���ֲ�����blockҪһ��������ȫ����
//������Ŵ�0��ʼ������0����_start������ζ�Ŷ������������_start��Ȼ���������������˱������ĺ�����Ų������������������� 
//ʹ�ò����������в㡣�ȵ���鵱ǰ�����ֲ�����block���ٲ鵱ǰ�����������ٲ�ȫ��ȫ�ֱ���

//ȫ�ֱ�����ţ����ֱ������������һ�£�˳����� 
//���ú�����ֻʹ��callnameָ�� 

//��init��ʱ���Ȱ�8����׼�⺯�����ӽ�ȫ�ֱ�������0��7�ֱ��ǣ�
//getchar(0)getdouble(1)getint(2)putchar(4)putdouble(5)putint(6)putln(7)putstr(8)
//����������ֻ��ȫ�ֱ����� 
//�������ò�������б�׼�⺯�����������б�׼�⣨ֱ�Ӹ������μ��ز�����callname��Ӧ��ţ����ٲ麯����ĺ�������ַ 

//�������ķ��ս������-2���ܹ�ֻ��e+e��e-e��e*e��e/e��(e)��������41������������42���ͱ�ʶ����51�����ֿ��� 

//�ĸ����� 

// ȡ�����ʽ�����ţ�31����ͷ���෴�������ӱ��ʽ 
// negate_expr -> '-' expr

// ����ת�����ʽ���ӱ��ʽ��ͷ�����ӱ��ʽ��ֻ���漰������int�͸�����double֮��Ļ���ת�����������ʽ��ʾ��ֵת�����Ҳ����ͱ�ʾ��ֵ�����ȼ��ڶ��� 
// as_expr -> expr 'as'��1�� ty

// ��ֵ���ʽ����ֵ���ʽ����ʶ����51����ͷ�����ӱ��ʽ ��ֵ����void�����ܱ�ʹ�á��൱�����ȼ���ͣ�˳���ҵ��� 
// assign_expr -> l_expr '=' expr
// l_expr -> IDENT

// �������ñ��ʽ����ʶ����51����ͷ����һTOKEN�����ţ�23�������ӱ��ʽ���ɺ������͵��ò����б���ɵı��ʽ
// ���������ڵ���ǰ����������׼���еĺ����ڵ���ǰ����Ҫ���� 
// call_expr -> IDENT '(' call_param_list? ')'
// call_param_list -> expr (',' expr)*

// ��һ�����ַ������ʽ
// STRING_LITERAL��44��
//��44����ֻ����putstr("")���ã�44���г��֣������Ƕ�Ӧ��ȫ�ֳ����ı��

//���ʽ��7�ֿ��ܣ�����ֵ���ʽ��8�ֿ��ܡ�expr�п��ܵ���expr��������漰��ȫ�ֱ�����Ҫ��Ϊ���롣
//��ͷΪ��ʶ����51�������ţ�31������С���ţ�23����������41���͸�������42��������Ԥ����
//expr -> operator_expr| negate_expr| as_expr| call_expr| literal_expr| ident_expr| group_expr

int OVERALL;//����Ƿ�ȫ������״̬�����뺯��ʱ����Ϊ1���˳���Ϊ0���⽫������ʲô�� 
int FUNCNUM;//��ǰ���������ڱ���������ĸ������С����뺯��blockʱ���� 

struct expression expr();//����������� 

//��δ��ɱ�ʶ�����������ú͸�ֵ���� 
struct expression parse_primary()//����һԪ���ʽ�����ﴦ�������š��������á�ǰ��-����������߲����������ȼ�������˳����Դ���ֵ���֣���Ԥ���� 
{
	int peek=nextToken();
	if(peek==23)//������ 
	{
		struct expression temp=expr();
		peek=nextToken();
		if(peek!=24)//���������žͲ�ƥ�� 
		{
			exit(-1);
		}
		return temp;//ֱ�����Ե���temp 
	}
	else if(op==31)//���ſ�ͷ 
	{
		struct expression temp=expr();//���� 
		char nene;//ȡ��ָ�� 
		if(temp.type==1)//���� 
		{
			nene=0x34;
		}
		else if(temp.type==2)//����
		{
			nene=0x35;
		}
		temp.instr.list[temp.instr.length]=nene;
		temp.instr.count++;
		temp.instr.length++;
		return temp;//ֻ��type���� 
	}
	else if(op==41)//���� 
	{
		char nene=0x01;//pushָ�� 
		struct expression temp;
		memset(&temp,0,sizeof(struct expression));//���� 
		temp.instr.list[temp.instr.length]=nene;
		temp.instr.count++;
		temp.instr.length++;//������ƶ����ܷ�long 
		temp.type=1;//���� 
		storelong(&NUM,temp.instr.list,temp.instr.length);
		temp.instr.length+=8;//һ��64λռ8��char 
		return temp;
	}
	else if(op==42)//������ 
	{
		char nene=0x01;//pushָ�� 
		struct expression temp;
		memset(&temp,0,sizeof(struct expression));//���� 
		temp.instr.list[temp.instr.length]=nene;
		temp.instr.count++;
		temp.instr.length++;//������ƶ����ܷ�long 
		temp.type=2;//������ 
		storedouble(&DOU,temp.instr.list,temp.instr.length);
		temp.instr.length+=8;//һ��64λռ8��char 
		return temp;
	}
	else if(op==51)//��ʶ��������鷳���ˣ�Ҫ��������ʲô���͵ı�������������Ҳ���ⲿ�֣�Ԥ��������ֵҲ���ⲿ�� 
	{
		char ebeb[2048];//�Ȱ�TOKEN����� 
		strcpy(ebeb,TOKEN);
		int veve=nextToken();//Ԥ��һλ
		if(veve==33)//�ȺŸ�ֵ 
		{
			struct expression returning;//ϣ�����صı��ʽ 
			memset(&returning,0,sizeof(struct expression));//��� 
			struct expression vdvd=expr();//���沿����һ��������expression 
			if(OVERALL!=1)//��������ȫ��̬��ȫ��ֻ���г���������ͺ��� 
			{
				exit(-1);
			}
			else//����̬ 
			{
				int finding=find_all(ebeb,FUNCNUM);//�Ȳ�ֲ���Ҫ��ȫ�� 
				if(finding==-1)//û�鵽
				{
					finding=find_param(ebeb,FUNCNUM);//�ٲ������
					if(finding==-1)//û�鵽
					{
						finding=find_table(ebeb);//����ȫ�ֱ�
						if(finding==-1)//��û�鵽
						{
							exit(-1);//��ֵ�������ڵı���������� 
						}
						else//��ȫ�ֱ� 
						{
							if(TABLE[finding].isconst==1)
							{
								exit(-1);//�������ܸ�ֵ 
							}
							if(TABLE[finding].type==0||vdvd.type==0||TABLE[finding].type!=vdvd.type)//�ȼ����������Ƿ�һ�¡�ֻ��ֵһ�Σ�����type 
							{
								exit(-1);//��ֵ����������� 
							}
							char intj=0x0c;//����ȫ��ָ�� 
							returning.instr.list[returning.instr.length]=intj;
							returning.instr.count++;
							returning.instr.length++;//������ƶ�
							storeint(finding,returning.instr.list,returning.instr.length);
							returning.instr.length+=4;//һ��32λռ4��char 
							returning.instr=instrcat(returning.instr,vdvd.instr);//��ַ�������exprһ�� 
							intj=0x17;//����ָ�� 
							returning.instr.list[returning.instr.length]=intj;
							returning.instr.count++;
							returning.instr.length++;
							TABLE[finding].valid=1;//�Ѹ�ֵ����Ч 
							return returning;
						}
					}
					else//�ڲ����� 
					{
						if(FUNCLIST[FUNCNUM].param[finding].isconst==1)
						{
							exit(-1);//�������ܸ�ֵ 
						}
						if(FUNCLIST[FUNCNUM].param[finding].type==0||vdvd.type==0||FUNCLIST[FUNCNUM].param[finding].type!=vdvd.type)//�ȼ����������Ƿ�һ�¡�ֻ��ֵһ�Σ�����type 
						{
							exit(-1);//��ֵ����������� 
						}
						char intj=0x0b;//���ز���ָ�� 
						returning.instr.list[returning.instr.length]=intj;
						returning.instr.count++;
						returning.instr.length++;//������ƶ�
						storeint(finding,returning.instr.list,returning.instr.length);
						returning.instr.length+=4;//һ��32λռ4��char 
						returning.instr=instrcat(returning.instr,vdvd.instr);//��ַ�������exprһ�� 
						intj=0x17;//����ָ�� 
						returning.instr.list[returning.instr.length]=intj;
						returning.instr.count++;
						returning.instr.length++;
						FUNCLIST[FUNCNUM].param[finding].valid=1;//�Ѹ�ֵ����Ч 
						return returning;
					}
				}
				else//�ھֲ��� 
				{
					if(FUNCLIST[FUNCNUM].localtable[finding].isconst==1)
					{
						exit(-1);//�������ܸ�ֵ 
					}
					if(FUNCLIST[FUNCNUM].localtable[finding].type==0||vdvd.type==0||FUNCLIST[FUNCNUM].localtable[finding].type!=vdvd.type)//�ȼ����������Ƿ�һ�¡�ֻ��ֵһ�Σ�����type 
					{
						exit(-1);//��ֵ����������� 
					}
					char intj=0x0a;//���ؾֲ�����ָ�� 
					returning.instr.list[returning.instr.length]=intj;
					returning.instr.count++;
					returning.instr.length++;//������ƶ�
					storeint(finding,returning.instr.list,returning.instr.length);
					returning.instr.length+=4;//һ��32λռ4��char 
					returning.instr=instrcat(returning.instr,vdvd.instr);//��ַ�������exprһ�� 
					intj=0x17;//����ָ�� 
					returning.instr.list[returning.instr.length]=intj;
					returning.instr.count++;
					returning.instr.length++;
					FUNCLIST[FUNCNUM].localtable[finding].valid=1;//�Ѹ�ֵ����Ч 
					return returning;
				}
			}
		}
		else if(veve==23)//�����ź������á�����뺯���������е�����Ƿ�һ�� 
		{
			struct expression returning;
			memset(&returning,0,sizeof(expression));//��� 
			if(strcmp(ebeb,"getchar")==0)//0�ź����޲�������Ҫ�ȿճ�һ������ֵ 
			{
				int riri=nextToken();//������
				if(riri!=24)
				{
					exit(-1);
				}
				returning.type=1;//����int 
				char caca=0x01;//pushָ�� 
				returning.instr.list[returning.instr.length]=nene;
				returning.instr.count++;
				returning.instr.length++;
				long long zeze=0;//push0��Ϊ����ֵ 
				storelong(&zeze,returning.instr.list,returning.instr.length);
				returning.instr.length+=8;//һ��64λռ8��char 
				caca=0x4a;//callname
				returning.instr.list[returning.instr.length]=caca;
				returning.instr.count++;
				returning.instr.length++;
				int bsbs=0;//0�ź��� 
				storeint(bsbs,returning.instr.list,returning.instr.length);
				returning.instr.length+=4;//һ��32λռ4��char 
				return returning;
			}
			else if(strcmp(ebeb,"getdouble")==0)//1�ź����޲�������Ҫ�ȿճ�һ������ֵ 
			{
				int riri=nextToken();//������
				if(riri!=24)
				{
					exit(-1);
				}
				returning.type=2;//����double
				char caca=0x01;//pushָ�� 
				returning.instr.list[returning.instr.length]=nene;
				returning.instr.count++;
				returning.instr.length++;
				long long zeze=0;//push0��Ϊ����ֵ 
				storelong(&zeze,returning.instr.list,returning.instr.length);
				returning.instr.length+=8;//һ��64λռ8��char 
				caca=0x4a;//callname
				returning.instr.list[returning.instr.length]=caca;
				returning.instr.count++;
				returning.instr.length++;
				int bsbs=1;//1�ź��� 
				storeint(bsbs,returning.instr.list,returning.instr.length);
				returning.instr.length+=4;//һ��32λռ4��char 
				return returning;
			}
			else if(strcmp(ebeb,"getdouble")==0)//2�ź����޲�������Ҫ�ȿճ�һ������ֵ 
			{
				int riri=nextToken();//������
				if(riri!=24)
				{
					exit(-1);
				}
				returning.type=1;//����int 
				char caca=0x01;//pushָ�� 
				returning.instr.list[returning.instr.length]=nene;
				returning.instr.count++;
				returning.instr.length++;
				long long zeze=0;//push0��Ϊ����ֵ 
				storelong(&zeze,returning.instr.list,returning.instr.length);
				returning.instr.length+=8;//һ��64λռ8��char 
				caca=0x4a;//callname
				returning.instr.list[returning.instr.length]=caca;
				returning.instr.count++;
				returning.instr.length++;
				int bsbs=2;//2�ź��� 
				storeint(bsbs,returning.instr.list,returning.instr.length);
				returning.instr.length+=4;//һ��32λռ4��char 
				return returning;
			}
			else if(strcmp(ebeb,"putchar")==0)//3�ź�����һ������Ϊint����expr���޷���ֵ 
			{
				struct expression ysys=expr();//����һ����������expr 
				if(ysys.type!=1)
				{
					exit(-1);
				}
				int riri=nextToken();//������
				if(riri!=24)
				{
					exit(-1);
				}
				returning.instr=instrcat(returning.instr,ysys.instr);//�㶨ջ�� 
				char caca=0x4a;//callname
				returning.instr.list[returning.instr.length]=caca;
				returning.instr.count++;
				returning.instr.length++;
				int bsbs=3;//3�ź��� 
				storeint(bsbs,returning.instr.list,returning.instr.length);
				returning.instr.length+=4;//һ��32λռ4��char 
				return returning;
			}
			else if(strcmp(ebeb,"putdouble")==0)//4�ź�����һ��double�������޷���ֵ 
			{
				struct expression ysys=expr();//����һ������������expr 
				if(ysys.type!=2)
				{
					exit(-1);
				}
				int riri=nextToken();//������
				if(riri!=24)
				{
					exit(-1);
				}
				returning.instr=instrcat(returning.instr,ysys.instr);//�㶨ջ�� 
				char caca=0x4a;//callname
				returning.instr.list[returning.instr.length]=caca;
				returning.instr.count++;
				returning.instr.length++;
				int bsbs=5;//5�ź��� 
				storeint(bsbs,returning.instr.list,returning.instr.length);
				returning.instr.length+=4;//һ��32λռ4��char 
				return returning;
			}
			else if(strcmp(ebeb,"putint")==0)//5�ź�����һ��int�������޷���ֵ 
			{
				struct expression ysys=expr();//����һ����������expr 
				if(ysys.type!=1)
				{
					exit(-1);
				}
				int riri=nextToken();//������
				if(riri!=24)
				{
					exit(-1);
				}
				returning.instr=instrcat(returning.instr,ysys.instr);//�㶨ջ�� 
				char caca=0x4a;//callname
				returning.instr.list[returning.instr.length]=caca;
				returning.instr.count++;
				returning.instr.length++;
				int bsbs=5;//5�ź��� 
				storeint(bsbs,returning.instr.list,returning.instr.length);
				returning.instr.length+=4;//һ��32λռ4��char 
				return returning;
			}
			else if(strcmp(ebeb,"putln")==0)//6�ź����޲������޷���ֵ 
			{
				int riri=nextToken();//������
				if(riri!=24)
				{
					exit(-1);
				}
				char caca=0x4a;//callname
				returning.instr.list[returning.instr.length]=caca;
				returning.instr.count++;
				returning.instr.length++;
				int bsbs=6;//6�ź��� 
				storeint(bsbs,returning.instr.list,returning.instr.length);
				returning.instr.length+=4;//һ��32λռ4��char 
				return returning;
			}
			else if(strcmp(ebeb,"putstr")==0)//7�ź�����Ψһ���ַ����������޷���ֵ 
			{
				int riri=nextToken();//һ���ַ�������ʱ��Ӧ�ð����ŵ����� 
				if(riri!=44)
				{
					exit(-1);
				}
				long long lololo=TABLETOP;//��ס���һ���� 
				strcpy(TABLE[TABLETOP].name,TOKEN);
				TABLE[TABLETOP].isconst=1;//�ַ������ǳ��� 
				TABLE[TABLETOP].type=0;//void
				TABLE[TABLETOP].valid=1;//�ѳ�ʼ�� 
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
				int bsbs=7;//7�ź��� 
				storeint(bsbs,returning.instr.list,returning.instr.length);
				returning.instr.length+=4;//һ��32λռ4��char 
				return returning;
			}
			int wewe=find_func(ebeb);
			if(wewe==-1)//�����˲����ڵĺ��� 
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
		else//�������������������ζ�ž���һ����ͨ�ı�ʶ�������ʱ��Ҫ��ֵȡ�����ŵ�ջ�� 
		{
			unreadToken();//�˻ء��������Ծ�Ҫ��� 
			struct expression returning;
			memset(&returning,0,sizeof(expression));//��� 
			if(OVERALL==0)//ȫ��̬����ʱֻ��Ҫ��ȫ�ֱ������� 
			{
				int finding=find_table(ebeb);
				if(finding==-1)
				{
					exit(-1);
				}
				else
				{
					if(TABLE[finding].type==0||TABLE[finding].valid==0)//�ȼ��������ͣ��Լ��Ƿ���Ч 
					{
						exit(-1);
					}
					returning.type=TABLE[finding].type;//���expr��type 
					char intj=0x0c;//����ȫ��ָ�� 
					returning.instr.list[returning.instr.length]=intj;
					returning.instr.count++;
					returning.instr.length++;//������ƶ�
					storeint(finding,returning.instr.list,returning.instr.length);
					returning.instr.length+=4;//һ��32λռ4��char 
					intj=0x13;//ȡֵѹջָ�� 
					returning.instr.list[returning.instr.length]=intj;
					returning.instr.count++;
					returning.instr.length++;
					return returning;
				}
			}
			else if(OVERALL==1)//����̬����ʱȫ��Ҫ�� 
			{
				int finding=find_all(ebeb,FUNCNUM);//�Ȳ�ֲ���Ҫ��ȫ��
				if(finding==-1)//û�鵽
				{
					finding=find_param(ebeb,FUNCNUM);//�ٲ������
					if(finding==-1)//û�鵽
					{
						finding=find_table(ebeb);//����ȫ�ֱ�
						if(finding==-1)//��û�鵽
						{
							exit(-1);
						}
						else//��ȫ�ֱ� 
						{
							if(TABLE[finding].type==0||TABLE[finding].valid==0)//�ȼ��������ͣ��Լ��Ƿ���Ч 
							{
								exit(-1);
							}
							returning.type=TABLE[finding].type;//���expr��type 
							char intj=0x0c;//����ȫ��ָ�� 
							returning.instr.list[temp.instr.length]=intj;
							returning.instr.count++;
							returning.instr.length++;//������ƶ�
							storeint(finding,returning.instr.list,returning.instr.length);
							returning.instr.length+=4;//һ��32λռ4��char 
							intj=0x13;//ȡֵѹջָ�� 
							returning.instr.list[temp.instr.length]=intj;
							returning.instr.count++;
							returning.instr.length++;
							return returning;
						}
					}
					else//�ڲ�����
					{
						if(FUNCLIST[FUNCNUM].param[finding].type==0||FUNCLIST[FUNCNUM].param[finding].valid==0)//�ȼ��������ͣ��Լ��Ƿ���Ч 
						{
							exit(-1);
						}
						returning.type=FUNCLIST[FUNCNUM].param[finding].type;//���expr��type 
						char intj=0x0b;//���ز���ָ�� 
						returning.instr.list[returning.instr.length]=intj;
						returning.instr.count++;
						returning.instr.length++;//������ƶ�
						storeint(finding,returning.instr.list,returning.instr.length);
						returning.instr.length+=4;//һ��32λռ4��char 
						intj=0x13;//ȡֵѹջָ�� 
						returning.instr.list[returning.instr.length]=intj;
						returning.instr.count++;
						returning.instr.length++;
						return returning;
					}
				}
				else//�ھֲ���
				{
					if(FUNCLIST[FUNCNUM].localtable[finding].type==0||FUNCLIST[FUNCNUM].localtable[finding].valid==0)//�ȼ��������ͣ��Լ��Ƿ���Ч 
					{
						exit(-1);
					}
					returning.type=FUNCLIST[FUNCNUM].localtable[finding].type;//���expr��type 
					char intj=0x0a;//���ؾֲ�ָ�� 
					returning.instr.list[returning.instr.length]=intj;
					returning.instr.count++;
					returning.instr.length++;//������ƶ�
					storeint(finding,returning.instr.list,returning.instr.length);
					returning.instr.length+=4;//һ��32λռ4��char 
					intj=0x13;//ȡֵѹջָ�� 
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
		exit(-1);//������ 
	}
}

struct expression combine(struct expression lhs,int op,struct expression rhs)//combine����������ϡ����ﴦ������ 
{
	if(lhs.type!=rhs.type||lhs.type==0||rhs.type==0)//�ȼ����������type�Ƿ�һ�»��Ƿ�Ϊ0 
	{
		exit(-1);//������ 
	}
	else if(op==21)//�� 
	{
		char nene;//��ָ��
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
		memset(&temp,0,sizeof(struct expression));//���� 
		temp.type=lhs.type;
		temp.instr=instrcat(lhs.instr,rhs.instr);//ָ���ֱ��ƴ�ӽ��� 
		temp.instr.list[temp.instr.length]=nene;
		temp.instr.count++;
		temp.instr.length++;
	}
	else if(op==31)//�� 
	{
		char nene;//��ָ��
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
		memset(&temp,0,sizeof(struct expression));//���� 
		temp.type=lhs.type;
		temp.instr=instrcat(lhs.instr,rhs.instr);//ָ���ֱ��ƴ�ӽ��� 
		temp.instr.list[temp.instr.length]=nene;
		temp.instr.count++;
		temp.instr.length++;
	}
	else if(op==22)//�� 
	{
		char nene;//��ָ�� 
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
		memset(&temp,0,sizeof(struct expression));//���� 
		temp.type=lhs.type;
		temp.instr=instrcat(lhs.instr,rhs.instr);//ָ���ֱ��ƴ�ӽ��� 
		temp.instr.list[temp.instr.length]=nene;
		temp.instr.count++;
		temp.instr.length++;
	}
	else if(op==32)//�� 
	{
		char nene;//��ָ�� 
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
		memset(&temp,0,sizeof(struct expression));//���� 
		temp.type=lhs.type;
		temp.instr=instrcat(lhs.instr,rhs.instr);//ָ���ֱ��ƴ�ӽ��� 
		temp.instr.list[temp.instr.length]=nene;
		temp.instr.count++;
		temp.instr.length++;
	}
	else
	{
		exit(-1);//������ 
	}
}
    
int prec(int op)//������������ȼ� 
{
	if(op==33)
	{
		return 1;//��ֵ����� 
	}
	else if(op==30||op==34||op==35||op==37||op==38||op==39)
	{
		return 2;//�Ƚ���������ŵڶ�
	}
	else if(op==21||op==31)
	{
		return 3;//�Ӽ����ŵ��� 
	}
	else if(op==22||op==32)
	{
		return 4;//�˳����ŵ��� 
	}
	else if(op==1)
	{
		return 5;//as���ŵ��� 
	}
	else
	{
		exit(-1);//������ 
	}
}

struct expression parse_opg(struct expression lhs,int prec)//lhs���󲿣�prec�������ȼ���ÿ�ε��������ʱ����һ����Ӧ�����������asӦ������������ 
{
	int peek=nextToken();//Ԥ����һ���������prec�����ȼ�
	while(peek==1)//�Ǹ�as
	{
		if(lhs.type!=1&&lhs.type!=2)
		{
			exit(-1);
		}
		int tyty=ty();//����
		if(tyty!=1&&tyty!=2)
		{
			exit(-1);
		}
		if(lhs.type==1&&tyty==2)//ҪתΪ����
		{
			char nene=0x36;
			lhs.instr.list[lhs.instr.length]=nene;
			lhs.instr.count++;
			lhs.instr.length++;
		}
		else if(lhs.type==2&&tyty==1)//ҪתΪ����
		{
			char nene=0x37;
			lhs.instr.list[lhs.instr.length]=nene;
			lhs.instr.count++;
			lhs.instr.length++;
		}
		lhs.type=tyty;
		peek=nextToken();//���� 
	}
	while(is_binary_op(peek)&&prec(peek)>=prec)//peek�Ƕ�Ԫ�������peek���ȼ����ڵ����󲿾����ȼ���Ҫ��Լ 
	{
		int op=peek;
		struct expression rhs=parse_primary();//�Ҳ���һ��������ĳ������
		peek=nextToken();//��Ԥ����һ����������Ƚ���������������ȼ� 
		while(peek==1)//�Ǹ�as
		{
			if(rhs.type!=1&&rhs.type!=2)
			{
				exit(-1);
			}
			int tyty=ty();//����
			if(tyty!=1&&tyty!=2)
			{
				exit(-1);
			}
			if(rhs.type==1&&tyty==2)//ҪתΪ����
			{
				char nene=0x36;
				rhs.instr.list[rhs.instr.length]=nene;
				rhs.instr.count++;
				rhs.instr.length++;
			}
			else if(rhs.type==2&&tyty==1)//ҪתΪ����
			{
				char nene=0x37;
				rhs.instr.list[rhs.instr.length]=nene;
				rhs.instr.count++;
				rhs.instr.length++;
			}
			rhs.type=tyty;
			peek=nextToken();//���� 
		}
		while(is_binary_op(peek)&&prec(peek)>prec(op))//peek�Ƕ�Ԫ�������peek���ȼ�����op���ȼ�����Ϊ��ֵֻ�ܳ���һ�Σ������ȼ���ͣ������迼���ҽ�� 
		{
			rhs=parse_opg(rhs,prec(peek));//�����ұ� 
			peek=nextToken();
			while(peek==1)//�Ǹ�as
			{
				if(rhs.type!=1&&rhs.type!=2)
				{
					exit(-1);
				}
				int tyty=ty();//����
				if(tyty!=1&&tyty!=2)
				{
					exit(-1);
				}
				if(rhs.type==1&&tyty==2)//ҪתΪ����
				{
					char nene=0x36;
					rhs.instr.list[rhs.instr.length]=nene;
					rhs.instr.count++;
					rhs.instr.length++;
				}
				else if(rhs.type==2&&tyty==1)//ҪתΪ����
				{
					char nene=0x37;
					rhs.instr.list[rhs.instr.length]=nene;
					rhs.instr.count++;
					rhs.instr.length++;
				}
				rhs.type=tyty;
				peek=nextToken();//���� 
			}
		}
		lhs=combine(lhs,op,rhs);//��ʾ��Լ 
	}
	return lhs;
}

struct expression expr()//�������ʽ 
{
	struct expression lhs=parse_primary();
	return parse_opg(lhs,0);//0��ʾ���Ƿ��ս�� 
}
 
// ��һ�����Ƚ�����������н���ǲ������ͣ�ֻ�ܳ����� if �� while �����������ʽ�С�������������������ͬ���͵�����
// ����while��if�ﲻֹ���Գ���������൱�����ȼ���ͣ�˳������ 
// bool_expr -> expr '==' | '!=' | '<' | '>' | '<=' | '>=' expr
struct instruction bool_expr()//�Ƚϵı��ʽ��ֱ��ָ��� 
{
	struct expression lhs=expr();
	int next=nextToken();
	if(next==30||next==34||next==35||next==37||next==38||next==39)//�����Ǿ�һ�����ʽ 
	{
		struct expression rhs=expr();
		if(lhs.type!=rhs.type||lhs.type==0||rhs.type==0)//�ȼ����������type�Ƿ�һ�»��Ƿ�Ϊ0 
		{
			exit(-1);//������ 
		}
		char nene;//�Ƚ�ָ�����ʱ���������ջ��������С�ں�����-1 
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
		memset(&temp,0,sizeof(struct instruction));//���� 
		temp=instrcat(lhs.instr,rhs.instr);//ָ���ֱ��ƴ�ӽ��� 
		temp.list[temp.instr.length]=nene;
		temp.count++;
		temp.length++;
		if(next==30)//�����ڡ�ջ����1��-1��Ϊ1������Ϊ0����ת����0�ͷ�0���ʲ��ù� 
		{
			return temp;
		}
		else if(next==34)//С�ڡ�ջ����-1��Ϊ1������Ϊ0������С��0��ʱ��Ϊ1 
		{
			nene=0x39;
			temp.list[temp.instr.length]=nene;
			temp.count++;
			temp.length++;
			return temp;
		}
		else if(next==35)//���ڡ�ջ����1��Ϊ1������Ϊ0����������0��ʱ��Ϊ1 
		{
			nene=0x3a;
			temp.list[temp.instr.length]=nene;
			temp.count++;
			temp.length++;
			return temp;
		}
		else if(next==37)//���ڡ�ջ����0��Ϊ1������Ϊ0 
		{
			nene=0x2e;//��ȡ����ĩλ�̶� 
			temp.list[temp.instr.length]=nene;
			temp.count++;
			temp.length++;
			nene=0x01;//��pushһ��1��ȥ 
			temp.list[temp.instr.length]=nene;
			temp.count++;
			temp.length++;//������ƶ����ܷ�long 
			long long phph=1; 
			storelong(&phph,temp.list,temp.length);
			temp.length+=8;//һ��64λռ8��char 
			nene=0x2b;//���λ�� 
			temp.list[temp.instr.length]=nene;
			temp.count++;
			temp.length++;
			return temp;
		}
		else if(next==38)//С�ڵ��ڡ�ջ����0��-1��Ϊ1������Ϊ0 
		{
			nene=0x01;//pushһ��1��ȥ 
			temp.list[temp.instr.length]=nene;
			temp.count++;
			temp.length++;//������ƶ����ܷ�long 
			long long phph=1; 
			storelong(&phph,temp.list,temp.length);
			temp.length+=8;//һ��64λռ8��char 
			nene=0x2d;//Ȼ��λ��� 
			temp.list[temp.instr.length]=nene;
			temp.count++;
			temp.length++;
			return temp;
		}
		else if(next==39)//���ڵ��ڡ�ջ����0��1��Ϊ1������Ϊ0 
		{
			nene=0x2e;//ֱ��ȡ�� 
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
		unreadToken();//�˻� 
		if(lhs.type==0)
		{
			exit(-1);
		}
		struct instruction temp=lhs.instr;//����0Ҳ��0�����п����з���λ���������1λ
		nene=0x01;//Ҫ��pushһ��1��ȥ 
		temp.list[temp.instr.length]=nene;
		temp.count++;
		temp.length++;//������ƶ����ܷ�long 
		long long phph=1; 
		storelong(&phph,temp.list,temp.length);
		temp.length+=8;//һ��64λռ8��char 
		char nene=0x29;//���� 
		temp.list[temp.instr.length]=nene;
		temp.count++;
		temp.length++;
	}
}

//���ʽ��䣬��ͷΪ��С���ţ�23�������ţ�31������ʶ����51����������41���͸�������42��������Ԥ����
//expr_stmt -> expr ';'
struct instruction expr_stmt()
{
	struct instruction temp=expr().instr;
	int next=nextToken();
	if(next!=29)//�ֺ� 
	{
		exit(-1);
	}
	return temp;
}

//������䲻�ԡ�expr��������Ӧ����һ��������У���˲�Ӧ����ʼ���� 
//�����Ƿ�ȫ��״̬�����а�����ű� 
//δ���expr���� 
//������䣬��const��3����ͷ���涨��ͷ����ǰ�Ѿ������ˣ���һ��Ĭ���Ǳ�ʶ����51��
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
	if(fff!=-1)//�����ܲ鵽 
	{
		exit(-1);//������� 
	}
	tok=nextToken();
	if(tok!=28)//ð�� 
	{
		exit(-1);
	}
	int typpp=ty();//���� 
	tok=nextToken();
	if(tok!=33)//�Ⱥ� 
	{
		exit(-1);
	}
	expr();//���ʽ
	//�˴�Ӧ������ʽ 
	long long intint;//����int���ʽ��ֵ�������� 
	double doudou;//����double���ʽ��ֵ�������� 
	tok=nextToken();
	if(tok!=29)//�ֺ� 
	{
		exit(-1);
	}
	if(typpp==1)//intʱ 
	{
		memset(&STACK[STACKTOP],0,sizeof(struct symbolstack));//��֮ǰ�������һ��������� 
		STACK[STACKTOP].destination=TABLETOP;
		STACKTOP++;
		memset(&TABLE[TABLETOP],0,sizeof(struct symboltable));//��֮ǰ�������һ��������� 
		strcpy(TABLE[TABLETOP].name,iii);
		TABLE[TABLETOP].isconst=1;
		TABLE[TABLETOP].type=1;
		TABLE[TABLETOP].value1=intint;
		TABLETOP++;
	}
	else if(typpp==2)//doubleʱ 
	{
		memset(&STACK[STACKTOP],0,sizeof(struct symbolstack));//��֮ǰ�������һ��������� 
		STACK[STACKTOP].destination=TABLETOP;
		STACKTOP++;
		memset(&TABLE[TABLETOP],0,sizeof(struct symboltable));//��֮ǰ�������һ��������� 
		strcpy(TABLE[TABLETOP].name,iii);
		TABLE[TABLETOP].isconst=1;
		TABLE[TABLETOP].type=2;
		TABLE[TABLETOP].value1=doudou;
		TABLETOP++;
	}
	else//������������ 
	{
		exit(-1); 
	}
	free(iii);
}

//exprδ���� 
//��������let��8����ͷ���涨��ͷ����ǰ�Ѿ������ˣ���һ��Ĭ���Ǳ�ʶ����51��
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
	if(fff!=-1)//�����ܲ鵽 
	{
		exit(-1);//������� 
	}
	tok=nextToken();
	if(tok!=28)//ð�� 
	{
		exit(-1);
	}
	int typpp=ty();
	tok=nextToken();
	memset(&STACK[STACKTOP],0,sizeof(struct symbolstack));//��֮ǰ�������һ��������� 
	memset(&TABLE[TABLETOP],0,sizeof(struct symboltable));//��֮ǰ�������һ��������� 
	strcpy(TABLE[TABLETOP].name,iii);
	if(tok==33)//���ڲ��ֿ���ѡ��ʡ��
	{
		expr();
		//�˴�Ӧ������ʽ 
		long long intint;//����int���ʽ��ֵ�������� 
		double doudou;//����double���ʽ��ֵ�������� 
		if(typpp==1)//intʱ 
		{
			STACK[STACKTOP].destination=TABLETOP; 
			STACKTOP++;
			TABLE[TABLETOP].type=2;
			TABLE[TABLETOP].value1=doudou;
			TABLETOP++;
		}
		else if(typpp==2)//doubleʱ 
		{
			STACK[STACKTOP].destination=TABLETOP;
			STACKTOP++;
			TABLE[TABLETOP].type=2;
			TABLE[TABLETOP].value1=doudou;
			TABLETOP++;
		}
		else//������������ 
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
	else if(tok==29)//δ��ʼ�������ܷ���ȫ�ֱ�ֻ����ջ��ռ��λ�� 
	{
		STACK[STACKTOP].invalid=1;//ע��û��ʼ�� 
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

//block��䣬��������ţ�25����ͷ������Ԥ�� 
//block_stmt -> '{' stmt* '}'
void block_stmt()
{
	int next=nextToken();
	if(next!=25)
	{
		exit(-1);
	}
	next=nextToken();
	while(next!=26)//�Ҵ����� 
	{
		stmt();//��λ��� 
		next=nextToken();
	}
}

//if��䣬��if��7����ͷ������bool���ʽ����ͷ��Ԥ�� 
//if_stmt -> 'if' expr block_stmt ('else' 'if' expr block_stmt)* ('else' block_stmt)?
void if_stmt()
{
	bool_expr();
	int next=nextToken();//��λ��ε�elseif����λ�һ�ε�else 
	while(next==5) 
	{
		next=nextToken();
		if(next==7)//�Ծɿ�����if
		{
			bool_expr();
			block_stmt(); 
			next=nextToken();//�ٶ�һ�� 
		}
		else if(next==25)//ֱ��block�� 
		{
			unreadToken();//block����Ԥ�� 
			block_stmt();
			next=nextToken();//�ٶ�һ����ĩβ����
			break; 
		}
	}
	unreadToken();//ĩβһ������ 
}

//while��䣬��while��10����ͷ������bool���ʽ����ͷ��Ԥ�� 
//while_stmt -> 'while' expr block_stmt
void while_stmt()
{
	bool_expr();
	block_stmt();
}

//return��䣬��return��9����ͷ 
//return_stmt -> 'return' expr? ';'

//break��䣬��break��2����ͷ 
//break_stmt -> 'break' ';'

//continue��䣬��continue��4����ͷ 
//continue_stmt -> 'continue' ';'

//����䣬�Էֺţ�29����ͷ 
//empty_stmt -> ';'

//��䣬9�������10�������������Ԥ�� 
//stmt ->expr_stmt��23����31����41����42����51��| decl_stmt| if_stmt��7��| while_stmt��10��| break_stmt��2��| continue_stmt��4��| return_stmt��9��| block_stmt��25��| empty_stmt��29��
//decl_stmt -> let_decl_stmt��8�� | const_decl_stmt��3�� 
void stmt()
{
	int next=nextToken();
	switch(next)
	{
		case 3://������ 
			const_decl_stmt();
		break;
		case 8://������ 
			let_decl_stmt();
		break;
		case 7://������ 
			if_stmt();
		break;
		case 10://������ 
			while_stmt();
		break;
		case 29://ʲô������ 
		break;
		case 2://break
			next=nextToken();//�ֺ�
			if(next!=29)
			{
				exit(-1);
			}
		break;
		case 4://continue
			next=nextToken();//�ֺ�
			if(next!=29)
			{
				exit(-1);
			}
		break;
		case 9://return
			next=nextToken();//�ֺŻ�expr 
			if(next!=29)
			{
				expr();
				next=nextToken();//�ֺ�
				if(next!=29)
				{
					exit(-1);
				}
			}
		break;
		case 25://block_stmt������ 
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
//�����б��const��3����IDENT��51����ͷ 
void function_param()
{
	int next=nextToken();
	if(next==3)//����һ��const 
	{
		//�˴�����const
		next=nextToken();
	}
	if(next!=51)//�Ծɲ���IDENT 
	{
		exit(-1);
	}
	//�˴�����IDENT
	next=nextToken();
	if(next!=28)//ð��
	{
		exit(-1);
	}
	int tyty=ty();
	//�˴�����ty 
}

//δ����block�ڲ����� 
//function -> 'fn' IDENT '(' function_param_list? ')' '->' ty block_stmt
//function_param_list -> function_param (',' function_param)*
void function()//��������fn��6����ͷ���涨��ͷ����ǰ�Ѿ������ˣ���һ��Ĭ���Ǳ�ʶ����51�� 
{

//	int type;//���;�������ֵ�ж��ٸ�8�ֽڡ�voidΪ0��int��double��Ϊ8���˴���¼0��1��2 

//	int param[16];//���16������������Ϊ1��ʾint��2��ʾdouble 
//	int paramtop;//�����б�������ٸ�8�ֽڡ�int��double��Ϊ8���ʳ�8���ɡ�
//	int local;//�ֲ������ж��ٸ�8�ֽ�
//	struct instruction instr[1024];//������ָ���� 

//	FUNCTIONLIST[FUNCTIONLISTTOP].type=0;//�޷���ֵ

//	FUNCTIONLIST[FUNCTIONLISTTOP].param=0;//�޲��� 
//	FUNCTIONLIST[FUNCTIONLISTTOP].local=0;//�޾ֲ�����
//	FUNCTIONLIST[FUNCTIONLISTTOP].count=1;//ֻ��һ��ָ�� 
//	char chte[10];
//	strcpy(chte,"main");
//	int temp=find_now(chte);//���غ�������main��ȫ�ֱ����е�λ��
//	FUNCTIONLIST[FUNCTIONLISTTOP].instr[0]=(char)0x4a;//callname 
//	FUNCTIONLIST[FUNCTIONLISTTOP].instr[1]=(char)((temp>>24) & 0x000000ff);//��� 
//	FUNCTIONLIST[FUNCTIONLISTTOP].instr[2]=(char)((temp>>16) & 0x000000ff);
//	FUNCTIONLIST[FUNCTIONLISTTOP].instr[3]=(char)((temp>> 8) & 0x000000ff);
//	FUNCTIONLIST[FUNCTIONLISTTOP].instr[4]=(char)((temp>> 0) & 0x000000ff);
//	FUNCTIONLISTTOP++; 
	int next=nextToken();
	if(next!=51)//��ʶ�� 
	{
		exit(-1);
	}
	char* iii=(char *)malloc(sizeof(char)*128);//�����ʶ����51��
	strcpy(iii,TOKEN);
	int fff=find_now(iii);
	if(fff!=-1)//�����ܲ鵽 
	{
		exit(-1);//������� 
	}
	memset(&TABLE[TABLETOP],0,sizeof(struct symboltable));//��֮ǰ�������һ��������� 
	strcpy(TABLE[TABLETOP].name,iii);
	TABLE[TABLETOP].isconst=1;
	TABLE[TABLETOP].type=3;
	memset(&FUNCTIONLIST[FUNCTIONLISTTOP],0,sizeof(struct functionlist));//��֮ǰ�������һ��������� 
	FUNCTIONLIST[FUNCTIONLISTTOP].name=TABLETOP;
	TABLETOP++;//�����˺����� 
	next=nextToken();
	if(next!=23)//��С���� 
	{
		exit(-1);
	}
	next=nextToken();
	if(next!=24)//��һ��������С���ţ�����function_param��Ҫ���� 
	{
		unreadToken();
		while(next!=24)
		{
			function_param();//ִ�к����Ĳ����б��� 
			next=nextToken();//��С���Ż򶺺�
			if(next!=24&&next!=27)
			{
				exit(-1);//ɶ������ 
			}
		}//������ʱ����С�����Ѿ������� 
	}
	next=nextToken();
	if(next!=36)
	{
		exit(-1);
	}
	int tyty=ty();
	//�˴�����ty
	block_stmt();
}

//program -> item*
//item -> function | decl_stmt
//decl_stmt -> let_decl_stmt | const_decl_stmt
void program()//���򣬱�Ȼ�ǳ�����䣨3����������䣨8��������6��
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

//��Ҫһ��ʼ��˳��Ž���7����׼�� 
void init()//ȫ�ֱ�����ʼ�� 
{
	PREVALID=0;//Ԥ����Ч 
	STACKTOP=0;//�����
	TABLETOP=0;//ȫ��ȫ�ֱ������� 
	FUNCTIONLISTTOP=0;//���������
}

void lastcheck()//������ڵ㡣����֮ǰ���벿��ȫ������ 
{
	memset(&TABLE[TABLETOP],0,sizeof(struct symboltable));//��֮ǰ�������һ��������� 
	strcpy(TABLE[TABLETOP].name,"_start");
	TABLE[TABLETOP].isconst=1;
	TABLE[TABLETOP].type=3;
	memset(&FUNCTIONLIST[FUNCTIONLISTTOP],0,sizeof(struct functionlist));//��֮ǰ�������һ��������� 
	FUNCTIONLIST[FUNCTIONLISTTOP].name=TABLETOP;
	TABLETOP++;
	FUNCTIONLIST[FUNCTIONLISTTOP].type=0;//�޷���ֵ
	FUNCTIONLIST[FUNCTIONLISTTOP].param=0;//�޲��� 
	FUNCTIONLIST[FUNCTIONLISTTOP].local=0;//�޾ֲ�����
	FUNCTIONLIST[FUNCTIONLISTTOP].count=1;//ֻ��һ��ָ�� 
	char chte[10];
	strcpy(chte,"main");
	int temp=find_now(chte);//���غ�������main��ȫ�ֱ����е�λ��
	FUNCTIONLIST[FUNCTIONLISTTOP].instr[0]=(char)0x4a;//callname 
	FUNCTIONLIST[FUNCTIONLISTTOP].instr[1]=(char)((temp>>24) & 0x000000ff);//��� 
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
	//�����Ǳ������� 
	lastcheck(); 
	FILE *outfp;  
	OUT=fopen("o0.bin","wb");
	int temp=0x72303b3e;
	outint(temp);//ħ��
	temp=0x00000001;
	outint(temp);//�汾��
	outint(TABLETOP);//ȫ�ֱ������� 
	int i;
	for(i=0;i<TABLETOP;i++)//�������ȫ�ֱ����� 
	{
		fwrite(&TABLE[i].isconst,sizeof(char),1,OUT);//�Ƿ��� 
		if(TABLE[i].type==1)//������ 
		{
			int len=8;
			outint(len);
			fwrite(&TABLE[i].value1,sizeof(long long),1,OUT);
		}
		else if(TABLE[i].type==2)//�Ǹ����� 
		{
			int len=8;
			outint(len);
			fwrite(&TABLE[i].value2,sizeof(double),1,OUT);
		}
		else if(TABLE[i].type==3)//�Ǻ����������ַ��� 
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
	outint(FUNCTIONLISTTOP);//�������� 
	for(i=FUNCTIONLISTTOP-1;i>=0;i--)//�������������
	{
		outint(FUNCTIONLIST[i].name);//�� 
		if(FUNCTIONLIST[i].type==0)//��
		{
			int ttt=0;
			outint(ttt);
		}
		else if(FUNCTIONLIST[i].type==1)//��
		{
			int ttt=8;
			outint(ttt);
		}
		else if(FUNCTIONLIST[i].type==2)//��
		{
			int ttt=8;
			outint(ttt);
		}
		outint(8*FUNCTIONLIST[i].paramtop);//��
		outint(FUNCTIONLIST[i].local);//��
		outint(FUNCTIONLIST[i].count);//��
		int len=strlen(FUNCTIONLIST[i].instr);
		fwrite(FUNCTIONLIST[i].instr,sizeof(char),len,OUT);
	}
	fclose(OUT);
	fclose(IN);
	return 0;
}

