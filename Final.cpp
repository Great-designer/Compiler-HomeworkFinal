#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char TOKEN[128];//��ǰ�ַ���������44�������߱�ʶ����51��
int NUM;//��ǰ�޷���������41���﷨����������ȡ���� 
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
				NUM=atoi(TOKEN);//��TOKEN�е��ַ���ת��Ϊ���� 
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
					NUM=atoi(TOKEN);//��TOKEN�е��ַ���ת��Ϊ���� 
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
					NUM=atoi(TOKEN);//��TOKEN�е��ַ���ת��Ϊ���� 
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
				NUM=atoi(TOKEN);//��TOKEN�е��ַ���ת��Ϊ���� 
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
			NUM=atoi(TOKEN);//��TOKEN�е��ַ���ת��Ϊ���� 
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
int NUMPRE;//�޷���������41���﷨����������ȡ���� 
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

struct symbolstack//ջʽ���ű�ṹ�� 
{
	int istop;//1��ʾ��һ����ջ�����º�����ʼ��ǰһ��Ĭ��Ϊ0 
	int destination;//��ȫ�ֱ��е��±ꡣΪ-1��ʾδ��ʼ����Ϊ-2��ʾ����Ϊvoid�����ַ��������������ַ���������� 
	int isfunction;//�Ǻ�������ʱ�����1����������Ϊȫ�ֱ�����Զ������ջ 
};

struct symbolstack STACK[128];//���ű� 
int STACKTOP;//ջ���±�

struct symboltable//���շ��ű�ṹ�塣���еĺ������ֶ�Ҫ���ȥ�������ʼ�����ܷ��뱾�����Ͳ���Ϊvoid 
{
	char name[128];//���֣����˴��ַ����ⲻ���ظ���typeΪ3ʱ��Ч 
	char isconst;//�ǳ���Ϊ1������Ϊ0���������Ϊ8�� 
	int type;//1Ϊint��2Ϊdouble��3Ϊ�ַ����������������ַ����� 
	int value1;//typeΪ1ʱ��Ч 
	double value2;//typeΪ2ʱ��Ч 
}; 

struct symboltable TABLE[128];//���ű� 
int TABLETOP;//���±� 

int find_all(char sss[])//���ݱ�������ȫ�����ű�ջ���鵽������ȫ�ֵ��±꣬δ�鵽����-1�� 
{
	int i;
	for(i=STACKTOP-1;i>=0;i--)//������ 
	{
		if(strcmp(TABLE[STACK[i].destination].name,sss)==0)
		{
			return STACK[i].destination;
		}
	}
	return -1;
}

int find_now(char sss[])//���ݱ������鵱ǰ����ű�ջ���鵽������ջ���±꣬δ�鵽����-1�� 
{
	int i;
	for(i=STACKTOP-1;STACK[i].istop!=1&&i>=0;i--)//������ 
	{
		if(strcmp(TABLE[STACK[i].destination].name,sss)==0)
		{
			return STACK[i].destination;
		}
	}
	return -1;
}

struct functionlist//ȫ�ֺ����� 
{
	int name;//��ȫ�ַ��ű��λ��
	int type;//���;�������ֵ�ж��ٸ�8�ֽڡ�voidΪ0��intΪ4��doubleΪ8 
	int param;//�����б�������ٸ�8�ֽڡ�intΪ4��doubleΪ8����͡�
	int local;//�ֲ������ж��ٸ�8�ֽ�
	int count;//ָ���� 
	char instr[128];//ָ� 
};

struct functionlist FUNCTIONLIST[128];
int FUNCTIONLISTTOP;

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
		case '25'://������� 
		{
			return 0;
		}
		case '27'://����
		{
			return 0;
		}
		case '29'://�ֺ�
		{
			return 0;
		}
		case '30'://�����ں�
		{
			return 0;
		}
		case '34'://С�ں�
		{
			return 0;
		}
		case '35'://���ں�
		{
			return 0;
		}
		case '37'://���ڵ��ں�
		{
			return 0;
		}
		case '38'://С�ڵ��ں�
		{
			return 0;
		}
		case '39'://���ڵ��ں�
		{
			return 0;
		}
		case '23'://������ 
		{
			return 1;
		}
		case '21'://�Ӻ� 
		{
			return 2;
		}
		case '31'://���� 
		{
			return 3;
		}
		case '22'://�˺� 
		{
			return 4;
		}
		case '32'://���� 
		{
			return 5;
		}
		case '24'://������ 
		{
			return 6;
		}
		case '41'://���� 
		{
			return 7;
		}
		case '42'://������ 
		{
			return 7;
		}
		case '51'://��ʶ�� 
		{
			return 7;
		}
		default://�Ƿ����뱨�� 
		{
			return -1;
		}
	}
}

//�������ķ��ս������-2���ܹ�ֻ��e+e��e-e��e*e��e/e��(e)��������41������������42���ͱ�ʶ����51�����ֿ��� 
int merging(int expstack[],int expstacktop)//����expstacktopӦ�ü�ȥ��ֵ 
{
	if(expstacktop==0)//ջΪ�� 
	{
		return -1;
	}
	if(expstack[expstacktop-1]==41||expstack[expstacktop-1]==42||expstack[expstacktop-1]==51)//������41������������42���ͱ�ʶ����51��
	{
		return 1;
	}
	if(expstacktop<3)//����Ĺ���Ҫ��ջ��������3���ַ�����012��λ�ñ������ַ���expstacktop������3��������������� 
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
void expr()
{
	int aaa,bbb;//�Ա�����n�������ֵķ��ս����Ϊ-2 
	int *expstack=(int *)malloc(sizeof(int)*128);//ջ������Զ�Ǳ�׼��� 
	int expstacktop=0;//expstacktop��ָ��ջ��Ԫ�ص���һ��λ�ã���expstacktop-1����ջ��Ԫ�� 
	int next=nextToken();//����
	while(1)//������else��ÿ����֧ĩβ������continue����break
	{
		bbb=translate(next);//���벻һ���Ϸ�
		if(bbb==-1)
		{
			exit(-1);//����
		}
		if(expstacktop!=0)//ջ�ǿ�
		{
			aaa=expstack[expstacktop-1];//��ʱջ��һ���ǺϷ��ַ������� 
			if(aaa==-2)//ջ���Ƿ��ս��
			{
				if(expstacktop==1)//ջ��ֻ��һ��Ԫ�� 
				{
					aaa=0;//��ʾǰһ��λ��Ӧ����sharp 
				}
				else
				{
					aaa=expstack[expstacktop-2];
					if(aaa==-2)//ÿһ�����ս�����������ڣ���ǰ��һ��Ӧ�����ս���Ŷ� 
					{
						exit(-1);//Υ������
					}
					else
					{
						aaa=translate(aaa);//һ���Ϸ� 
					}
				}
			}
			else
			{
				aaa=translate(aaa);//һ���Ϸ� 
			}
			if(aaa==0&&bbb==0&&expstack[expstacktop-1]==-2&&expstacktop==1)//��������˳������ 
			{
				break;
			}
			if(aaa==0&&next==24&&expstack[expstacktop-1]==-2&&expstacktop==1)//ջֻʣ��һ�����ս���ţ����Ƕ����������š����ڱ�list���ã����ǿ��ܵ� 
			{
				unreadToken();//���������˻�ȥ��ǰ��������Ѿ��˹��� 
				break;
			}
			int count=8*aaa+bbb;//������ 
			int flag=0;//��һ��������Ŵ����� 
			int i;
			for(i=0;i<5;i++)//�Ȳ�5��SPECIAL
			{
				if(count==SPECIAL[i])//����������� 
				{
					if(expstack[expstacktop-1]!=-2)//ջһ�����ǿյġ�����ǰ��û�з��ս������������� 
					{
						flag=1;//����������ű�� 
					}
				}
			}
			if(flag==1)
			{
				while(flag==1)//����������ţ�ֻ��Ԥ����һ�� 
				{
					next=nextToken();//���롣
					if(next!=31)
					{
						flag=0;//�������Ž��� 
					}
				}//�������ȼ�������ĺϷ�����ֻ�������ţ��������û��߱�ʶ������������һ���ǲ��Ե� 
				if(next==23||next==41||next==42||next==51)//�����ţ����ͣ����㣬��ʶ�����ߺ�������
				{
					bbb=translate(next);//���¼������ֵ 
					count=8*aaa+bbb;//���¼������� 
				}
				else
				{
					exit(-1);
				}
			}
			for(i=0;i<6;i++)//�ٲ�6������ 
			{
				if(count==ERROR[i])
				{
					exit(-1);//�޷��ж����ȼ���ϵ
				}
			}
			if(count==57)//��ʶ���������š���ʱ��Ӧ��������������
			{
				expr();//�Ѿ�������ident�������� 
				int next=nextToken();//�����������á��������������Ѿ�������
				while(next!=24)//�����Ž��������ű�ʾû����
				{
					if(next==27)//���� 
					{
						expr(); 
					}
					else
					{
						exit(-1);
					}
					next=nextToken();//�����ű����� 
				}
				int rr=merging(expstack,expstacktop);
				if(rr==-1)
				{
					exit(-1);//��Լʧ��
				}
				expstacktop-=rr;//��Լ�ɹ���ջ 
				expstack[expstacktop]=-2;//ѹ����ս���� 
				expstacktop++;//ѹ����ս���� 
				continue;//����Լ���������벿�� 
			}
			if(F[aaa]>G[bbb])//�����ڵ�ʱ��Ź�Լ������ʱ����롣����Լ���������벿�� 
			{
				int rr=merging(expstack,expstacktop);
				if(rr==-1)
				{
					exit(-1);//��Լʧ��
				}
				expstacktop-=rr;//��Լ�ɹ���ջ 
				expstack[expstacktop]=-2;//ѹ����ս���� 
				expstacktop++;//ѹ����ս���� 
				continue;//����Լ���������벿�� 
			}
		}
		expstack[expstacktop]=next;//ѹ���׼��ţ�ӦΪnext 
		expstacktop++;//ѹ���׼���
		next=nextToken();//��һ�� 
		if(next==33)
		{
			if(expstacktop==1&&expstack[expstacktop-1]==51)//ջ����ֻ��һ��IDENT�Ͷ��� 
			{
				expr();//��ʱ������IDENT�͵Ⱥţ�ʣ��Ĳ��ָպ���һ��expr
				//�˴�����ֵ 
				break; 
			}
			else
			{
				exit(-1);
			}
		}
		while(next==1)//����as��ʱ�����С��������ȼ���ջ��Ӧ�ñ����Ƿ��ս������ʶ�������������
		{
			if(expstack[expstacktop-1]==24||expstack[expstacktop-1]==41||expstack[expstacktop-1]==42||expstack[expstacktop-1]==51)//�����ţ����ͣ����㣬��ʶ��
			{
				int rr=merging(expstack,expstacktop);//�ȹ�Լ 
				if(rr==-1)
				{
					exit(-1);//��Լʧ��
				}
				expstacktop-=rr;//��Լ�ɹ���ջ 
				expstack[expstacktop]=-2;//ѹ����ս���� 
				expstacktop++;//ѹ����ս���� 
			}
			if(expstack[expstacktop-1]!=-2)//���Ƿ��ս�� 
			{
				exit(-1);//���˳� 
			}
			int tyty=ty();//����
			//�˴�Ӧ���ȴ���as���� 
			next=nextToken();//�ٶ�һ���������ǲ���1 
		}
		if(next==25||next==27||next==29||next==30||next==34||next==35||next==37||next==38||next==39)//������β�ַ���ʱ�򣬲����ٶ��� 
		{
			unreadToken();//��ʱ�ᵹ��һ��������next����Ϊ0��Ȼ������continue���˷�֧���޷����� 
		}
	}
	free(expstack);
}

// ��һ�����Ƚ�����������н���ǲ������ͣ�ֻ�ܳ����� if �� while �����������ʽ�С�������������������ͬ���͵����� 
// ����while��if�ﲻֹ���Գ���������൱�����ȼ���ͣ�˳������ 
// bool_expr -> expr '==' | '!=' | '<' | '>' | '<=' | '>=' expr
void bool_expr()
{
	expr();
	int next=nextToken();
	if(next==30||next==34||next==35||next==37||next==38||next==39)//�����Ǿ�һ�����ʽ 
	{
		expr();
	}
	else
	{
		unreadToken();
	}
}

//���ʽ��䣬��ͷΪ��С���ţ�23�������ţ�31������ʶ����51����������41���͸�������42��������Ԥ����
//expr_stmt -> expr ';'
void expr_stmt()
{
	expr();
	int next=nextToken();
	if(next!=29)//�ֺ� 
	{
		exit(-1);
	}
}

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
	int fff=find_all(iii);
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
	int intint;//����int���ʽ��ֵ�������� 
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
		int intint;//����int���ʽ��ֵ�������� 
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
		STACK[STACKTOP].destination=-1;//ע��û��ʼ�� 
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

//function -> 'fn' IDENT '(' function_param_list? ')' '->' ty block_stmt
//function_param_list -> function_param (',' function_param)*
void function()//��������fn��6����ͷ���涨��ͷ����ǰ�Ѿ������ˣ���һ��Ĭ���Ǳ�ʶ����51�� 
{
	int next=nextToken();
	if(next!=51)//��ʶ�� 
	{
		exit(-1);
	}
	//�˴�Ӧ�����ʶ����51��
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
			function_param();
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
	int temp=find_all(chte);//���غ�������main��ȫ�ֱ����е�λ��
	FUNCTIONLIST[FUNCTIONLISTTOP].instr[0]=(char)0x4a;//callname 
	FUNCTIONLIST[FUNCTIONLISTTOP].instr[1]=(char)((temp>>24) & 0x000000ff);//��� 
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
			int len=4;
			outint(len);
			outint(TABLE[i].value1);
		}
		else if(TABLE[i].type==2)//�Ǹ����� 
		{
			int len=8;
			outint(len);
			outdouble(&TABLE[i].value2);
		}
		else if(TABLE[i].type==3)//�Ǻ����������ַ��� 
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
	outint(FUNCTIONLISTTOP);//�������� 
	for(i=FUNCTIONLISTTOP-1;i>=0;i--)//�������������
	{
		outint(FUNCTIONLIST[i].name);//�� 
		outint(FUNCTIONLIST[i].type);//��
		outint(FUNCTIONLIST[i].param);//��
		outint(FUNCTIONLIST[i].local);//��
		outint(FUNCTIONLIST[i].count);//��
		int len=strlen(FUNCTIONLIST[i].instr);
		fwrite(FUNCTIONLIST[i].instr,sizeof(char),len,OUT);
	}
	fclose(OUT);
	fclose(IN);
	return 0;
}

