#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char token[2048];//��ǰ�ַ���������44�������߱�ʶ����51��
int num;//��ǰ�޷���������41���﷨����������ȡ���� 
double dou;//��ǰ�޷��Ÿ�������42���﷨����������ȡ���� 
char ch;//��ǰ�ַ�������43�� 

int reser()//�ؼ��ֱ���10�� 
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
	else//��ʶ�� 
	{
		return 0;
	}
}

FILE *in;//��ָ�� 

int getToken()//������һ��token������룬ע����ΪToken 
{
	int symbol;//����������� 
	char cc=' ';//��꣬������һ���հ��ַ� 
	memset(token,0,sizeof(token));//ÿ�ε��ã�token������� 
	while(isspace(cc))//���ַ������ո񡢻��к�Tab 
	{
		cc=fgetc(in);
	}
	if(isalpha(cc)||cc=='_')//��ʶ����ؼ��� 
	{
		while(isalpha(cc)||isdigit(cc)||cc=='_')//���ַ�ƴ�ӳ��ַ��� 
		{
			strncat(token,&cc,1);
			cc=fgetc(in); 
		}
		ungetc(cc,in);//ָ�����һ���ַ�
		int resultValue=reser();//resultValue���ұ����ֵķ���ֵ 
		if(resultValue==0)//token���ַ���Ϊ��ʶ�� 
		{
			symbol=51;
		}
		else//token���ַ���Ϊ������ 
		{
			symbol=resultValue;
		}
	}
	else if(isdigit(cc))//�����͸����� 
	{
		while(isdigit(cc))//���ַ�ƴ�ӳ����� 
		{
			strncat(token,&cc,1);
			cc=fgetc(in);
		}
		if(cc='.')//��С����
		{
			cc=fgetc(in);//�Ȳ�����ƴ�ӣ��ٶ�һ�� 
			if(!isdigit(cc))//û�����֣�֤�����Ǹ����� 
			{
				ungetc(cc,in);//�˻ط����� 
				ungetc(cc,in);//�˻�С����
				num=atoi(token);//��token�е��ַ���ת��Ϊ���� 
				symbol=41;//��ʱʶ��ĵ��������� 
			}
			else//�����֣���ô�����ⲿ���Ѿ���һ�������� 
			{
				char poi='.'; 
				strncat(token,&poi,1);//�Ƚ�һ��С���㣬��Ϊcc�Ѿ��������� 
				while(isdigit(cc))
				{
					strncat(token,&cc,1);
					cc=fgetc(in);
				}
				if(cc=='e'||cc=='E')//���п��ܣ������E��e
				{
					cc=fgetc(in);//�Ȳ�����ƴ�ӣ��ٶ�һ��
					if(cc=='+')//�п�����+ 
					{
						cc=fgetc(in);//�Ȳ�����ƴ�ӣ��ٶ�һ��
						if(!isdigit(cc))//�����֣�֤���˲�����Ч 
						{
							ungetc(cc,in);//�˻ط����� 
							ungetc(cc,in);//�˻ط��� 
							ungetc(cc,in);//�˻�e
							dou=atof(token);//��token�е��ַ���ת��Ϊ������ 
							symbol=42;//��ʱʶ��ĵ����Ǹ����� 
						}
						else//�����֣��ⲿ����Ч 
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
							ungetc(cc,in);//�˻��ַ� 
							dou=atof(token);//��token�е��ַ���ת��Ϊ������ 
							symbol=42;//��ʱʶ��ĵ����Ǹ����� 
						}
					}
					else if(cc=='-')//�п�����-
					{
						cc=fgetc(in);//�Ȳ�����ƴ�ӣ��ٶ�һ��
						if(!isdigit(cc))//�����֣�֤���˲�����Ч 
						{
							ungetc(cc,in);//�˻ط����� 
							ungetc(cc,in);//�˻ط��� 
							ungetc(cc,in);//�˻�e
							dou=atof(token);//��token�е��ַ���ת��Ϊ������ 
							symbol=42;//��ʱʶ��ĵ����Ǹ����� 
						}
						else//�����֣��ⲿ����Ч 
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
							ungetc(cc,in);//�˻��ַ� 
							dou=atof(token);//��token�е��ַ���ת��Ϊ������ 
							symbol=42;//��ʱʶ��ĵ����Ǹ����� 
						}
					}
					else if(!isdigit(cc))//�����֣�֤���˲�����Ч 
					{
						ungetc(cc,in);//�˻ط����� 
						ungetc(cc,in);//�˻�e
						dou=atof(token);//��token�е��ַ���ת��Ϊ������ 
						symbol=42;//��ʱʶ��ĵ����Ǹ����� 
					}
					else//�����֣��ⲿ����Ч 
					{
						char eee='e'; 
						strncat(token,&eee,1);//�Ƚ�һ��e����Ϊcc�Ѿ��������� 
						while(isdigit(cc))
						{
							strncat(token,&cc,1);
							cc=fgetc(in);
						}
					}
				}
			}
		}
		else if(cc=='e'||cc=='E')//���п��ܣ������E��e
		{
			cc=fgetc(in);//�Ȳ�����ƴ�ӣ��ٶ�һ��
			if(cc=='+')//�п�����+ 
			{
				cc=fgetc(in);//�Ȳ�����ƴ�ӣ��ٶ�һ��
				if(!isdigit(cc))//�����֣�֤���˲�����Ч 
				{
					ungetc(cc,in);//�˻ط����� 
					ungetc(cc,in);//�˻ط��� 
					ungetc(cc,in);//�˻�e
					num=atoi(token);//��token�е��ַ���ת��Ϊ���� 
					symbol=41;//��ʱʶ��ĵ��������� 
				}
				else//�����֣��ⲿ����Ч 
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
					ungetc(cc,in);//�˻��ַ� 
					dou=atof(token);//��token�е��ַ���ת��Ϊ������ 
					symbol=42;//��ʱʶ��ĵ����Ǹ����� 
				}
			}
			else if(cc=='-')//�п�����-
			{
				cc=fgetc(in);//�Ȳ�����ƴ�ӣ��ٶ�һ��
				if(!isdigit(cc))//�����֣�֤���˲�����Ч 
				{
					ungetc(cc,in);//�˻ط����� 
					ungetc(cc,in);//�˻ط��� 
					ungetc(cc,in);//�˻�e
					num=atoi(token);//��token�е��ַ���ת��Ϊ���� 
					symbol=41;//��ʱʶ��ĵ��������� 
				}
				else//�����֣��ⲿ����Ч 
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
					ungetc(cc,in);//�˻��ַ� 
					dou=atof(token);//��token�е��ַ���ת��Ϊ������ 
					symbol=42;//��ʱʶ��ĵ����Ǹ����� 
				}
			}
			else if(!isdigit(cc))//�����֣�֤���˲�����Ч 
			{
				ungetc(cc,in);//�˻ط����� 
				ungetc(cc,in);//�˻�e
				num=atoi(token);//��token�е��ַ���ת��Ϊ���� 
				symbol=41;//��ʱʶ��ĵ��������� 
			}
			else//�����֣��ⲿ����Ч 
			{
				char eee='e'; 
				strncat(token,&eee,1);//�Ƚ�һ��e����Ϊcc�Ѿ��������� 
				while(isdigit(cc))
				{
					strncat(token,&cc,1);
					cc=fgetc(in);
				}
				ungetc(cc,in);//�˻��ַ� 
				dou=atof(token);//��token�е��ַ���ת��Ϊ������ 
				symbol=42;//��ʱʶ��ĵ����Ǹ����� 
			}
		}
		else//û��С���㣬Ҳû��E��e
		{
			ungetc(cc,in);//�˻��ַ� 
			num=atoi(token);//��token�е��ַ���ת��Ϊ���� 
			symbol=41;//��ʱʶ��ĵ��������� 
		}
	}
	else if(cc=='\'')//���������Σ�Ҫ�ж��Ƿ�Ϸ� 
	{
		cc=fgetc(in);
		if(cc=='\''||cc=='\n'||cc=='\t'||cc=='\r')
		{
			exit(-1);//���� 
		}
		else if(cc=='\\')
		{
			cc=fgetc(in);//��ʱ���п��ܳ�����ҪԤ�� 
			if(cc=='\''||cc=='\"'||cc=='\\'||cc=='n'||cc=='t'||cc=='r')
			{
				char tttt=cc;//�ݴ�
				cc=fgetc(in);
				if(cc=='\'')//������ 
				{
					ch=tttt;//�Ϸ�
					symbol=43;
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
			cc=fgetc(in);//Ԥ��
			if(cc=='\'')//�Ϸ�
			{
				ch=tttt;
				symbol=43;
			}
			else//�Ƿ� 
			{
				exit(-1);//���� 
			}
		}
	}
	else if(cc=='\"')//˫����
	{
		cc=fgetc(in);
		while(cc!='\"')//ֻҪ����˫���ž�Ҫ������ 
		{
			if(cc=='\n'||cc=='\t'||cc=='\r'||cc=='\0')
			{
				exit(-1);//���� 
			}
			else if(cc=='\\')//������ת�� 
			{
				cc=fgetc(in);//��ʱ���п��ܳ�����ҪԤ�� 
				if(cc=='\''||cc=='\"'||cc=='\\'||cc=='n'||cc=='t'||cc=='r')
				{
					strncat(token,&cc,1);
				}
				else
				{
					exit(-1);//���� 
				}
			}
			else//�Ϸ�
			{
				strncat(token,&cc,1);
			}
			cc=fgetc(in);//ѭ������ʱ�ٶ�һ�� 
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
					symbol=-2;//-2��ע�� 
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
			case EOF://��βΪ-1 
				symbol=-1;
			break;
			default://����
				exit(-1);
		}
	}
	return symbol;
}

//tokenΪ�ַ�����44�����ʶ����51�������洢��token
char tokenPre[2048];//Ԥ�����ַ���������44�������߱�ʶ����51��

//tokenΪ������41������������42�����ַ�������43�����洢��num��dou��ch 
int numPre;//�޷���������41���﷨����������ȡ���� 
double douPre;//�޷��Ÿ�������42���﷨����������ȡ���� 
char chPre;//�ַ�������43�� 

//tokenΪ�ؼ��֡���������ĵ���β��-1����ʱ��ֱ�ӿ����صı�ż���
int symPre;
int preValid; 

int nextToken()//������һ��token������룬ע�Ͳ���ΪToken��ֻҪʹ��nextToken����һ��״̬�Ͷ����� 
{
	int sym;//������ 
	if(preValid==1)//ִ�й�unreadToken����ԭ֮ǰԤ�����������validΪ0
	{
		sym=symPre;
		preValid=0;
		switch(sym)
		{
			case 41://���� 
				num=numPre;
			break;
			case 42://������ 
				dou=douPre;
			break;
			case 43://�ַ� 
				ch=chPre;
			break;
			case 44://�ַ��� 
				strcpy(token,tokenPre);
			break;
			case 51://��ʶ�� 
				strcpy(token,tokenPre);
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
		symPre=sym;
		switch(sym)
		{
			case 41://���� 
				numPre=num;
			break;
			case 42://������ 
				douPre=dou;
			break;
			case 43://�ַ� 
				chPre=ch;
			break;
			case 44://�ַ��� 
				strcpy(tokenPre,token);
			break;
			case 51://��ʶ�� 
				strcpy(tokenPre,token);
			break;
			default://���������ʲô�������� 
			break;
		}
	}
	return sym;
}

void unreadToken()//����ǰ������ѹ��ջ�С�����ֻ�ܱ���һ��Ԥ�����Σ���һ����ʧ����ֹ����ʹ�����Ρ�
{
	if(preValid==1)//Ԥ���Ѿ���Ч��֤����ǰλ����Ԥ��ǰ���޷��ٻ��� 
	{
		exit(-1); 
	}
	else
	{
		preValid=1;//��Ԥ��Ϊ��Ч 
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

// ��������ʽ operator_expr��ȡ�����ʽ negate_expr ������ת�����ʽ as_expr ����ʹ�þֲ�����������ķ�

// ��������ʽ���ӱ��ʽ��ͷ�����ӱ��ʽ����ֻ���������������������������������ͬ���͵����� 
// ���ȼ���˳��
// * /	����
// + -	����
// operator_expr -> expr binary_operator expr
// binary_operator -> '+' | '-' | '*' | '/' 

// ����ת�����ʽ���ӱ��ʽ��ͷ�����ӱ��ʽ��ֻ���漰������int�͸�����double֮��Ļ���ת�����������ʽ��ʾ��ֵת�����Ҳ����ͱ�ʾ��ֵ�����ȼ��ڶ��� 
// as_expr -> expr 'as'��1�� ty

// ���������� 

// ȡ�����ʽ�����ţ�31����ͷ���෴�������ӱ��ʽ 
// negate_expr -> '-' expr

// ���ű��ʽ����ͷ��С���ţ�23�������ȼ��� 
// group_expr -> '(' expr ')'

// �������������� 

// ���������ʽ����ͷ��41����42��
// literal_expr -> UINT_LITERAL | DOUBLE_LITERAL

// ��ʶ�����ʽ��ֻ�б�ʶ����51����ͷ����ա������Ǳ�ʶ����Ӧ�ľֲ���ȫ�ֱ�������ʶ�����ʽ���������ʶ����������ͬ
// ident_expr -> IDENT

// �������ñ��ʽ����ʶ����51����ͷ����һtoken�����ţ�23�������ӱ��ʽ���ɺ������͵��ò����б���ɵı��ʽ
// ���������ڵ���ǰ����������׼���еĺ����ڵ���ǰ����Ҫ���� 
// call_expr -> IDENT '(' call_param_list? ')'
// call_param_list -> expr (',' expr)*

//# ( + - * / ) ������41���͸�������42��ͬһ��
//#ֻ���Ƿֺ�;��29�����������{��25����һ������EOF 
int f[8]={0,0,2,2,4,4,5,5};//ջ��
int g[8]={0,5,1,1,3,3,0,5};//����

//8a+b������6���Ƿ�״̬��5������״̬��1������״̬�����ʶ���������ţ�Ϊ8*��ʶ��7+1=57�� 
int error[6]={0,6,8,49,55,63};
int special[5]={11,19,27,35,43}; 

int translate(int t)//token������������������7�ַ��Ų��ܽ��뷭�����������ʱ�õ� 
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

void expr();

void call_param_list()//�Ѿ�������ident�������� 
{
	expr(); 
	int next=nextToken();
	while(next!=24)//�����Ž��������ű�ʾû����
	{
		if(next==27)
		{
			expr(); 
		}
		else
		{
			exit(-1);
		}
		next=nextToken();//�����ű����� 
	}
}

//expr -> operator_expr| negate_expr| as_expr| call_expr| literal_expr| ident_expr| group_expr
void expr()//���ʽ��7�ֿ��ܡ�expr�п��ܵ���expr��������漰��ȫ�ֱ�����Ҫ��Ϊ���롣��ͷ����Ԥ���� 
{
	int aaa,bbb;//�Ա�����n�������ֵķ��ս����Ϊ-2 
	int *expstack=(int *)malloc(sizeof(int)*2048);//ջ������Զ�Ǳ�׼��� 
	int expstacktop=0;//expstacktop��ָ��ջ��Ԫ�ص���һ��λ�ã���expstacktop-1����ջ��Ԫ�� 
	int next=nextToken();//����
	if(next==1)//as�������ַ�������as��ʱ������ 
	{
		exit(-1);//��ʱ��϶����� 
	}
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
			for(i=0;i<5;i++)//�Ȳ�5��special
			{
				if(count==special[i])//����������� 
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
				if(count==error[i])
				{
					exit(-1);//�޷��ж����ȼ���ϵ
				}
			}
			if(count==57)//��ʶ���������š���ʱ��Ӧ��������������
			{
				call_param_list();//�����������á��������������Ѿ������� 
				int rr=merging();
				if(rr==-1)
				{
					exit(-1);//��Լʧ��
				}
				expstacktop-=rr;//��Լ�ɹ���ջ 
				expstack[expstacktop]=-2;//ѹ����ս���� 
				expstacktop++;//ѹ����ս���� 
				continue;//����Լ���������벿�� 
			}
			if(f[aaa]>g[bbb])//�����ڵ�ʱ��Ź�Լ������ʱ����롣����Լ���������벿�� 
			{
				int rr=merging();
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
		while(next==1)//����as��ʱ�����С��������ȼ���ջ��Ӧ�ñ����Ƿ��ս������ʶ�������������
		{
			if(expstack[expstacktop-1]==24||expstack[expstacktop-1]==41||expstack[expstacktop-1]==42||expstack[expstacktop-1]==51)//�����ţ����ͣ����㣬��ʶ��
			{
				int rr=merging();//�ȹ�Լ 
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
		if(next==25||next==27||next==29)//������β�ַ���ʱ�򣬲����ٶ��� 
		{
			unreadToken();//��ʱ�ᵹ��һ��������next����Ϊ0��Ȼ������continue���˷�֧���޷����� 
		}
	}
	free(expstack);
}

// δ��� 
// ��һ�����Ƚ�����������н���ǲ������ͣ�ֻ�ܳ����� if �� while �����������ʽ�С�������������������ͬ���͵����� 
// ����while��if�ﲻֹ���Գ���������൱�����ȼ���ͣ�˳������ 
// bool_expr -> expr '==' | '!=' | '<' | '>' | '<=' | '>=' expr
void bool_expr()
{
	
}

// ��ֵ���ʽ����ֵ���ʽ����ʶ����51����ͷ�����ӱ��ʽ ��ֵ����void�����ܱ�ʹ�á��൱�����ȼ���ͣ�˳���ҵ��� 
// assign_expr -> l_expr '=' expr
// l_expr -> IDENT
void assign_expr()
{
	
}

// ��һ�����ַ������ʽ���ַ����ʽ 
// STRING_LITERAL | CHAR_LITERAL
// ��43����44����ֻ���� putstr �����г��֣������Ƕ�Ӧ��ȫ�ֳ����ı��

//const_decl_stmt -> 'const' IDENT ':' ty '=' expr ';'
void const_decl_stmt()//��������const��3����ͷ���涨��ͷ����ǰ�Ѿ������ˣ���һ��Ĭ���Ǳ�ʶ����51��
{
	int tok=nextToken();
	if(tok!=51)
	{
		exit(-1);
	}
	//�˴�Ӧ�����ʶ����51��
	tok=nextToken();
	if(tok!=28)//ð�� 
	{
		exit(-1);
	}
	int typpp=ty();//���� 
	//�˴�Ӧ��������
	tok=nextToken();
	if(tok!=33)//�Ⱥ� 
	{
		exit(-1);
	}
	expr();//���ʽ
	//�˴�Ӧ������ʽ 
	tok=nextToken();
	if(tok!=29)//�ֺ� 
	{
		exit(-1);
	}
}

//let_decl_stmt -> 'let' IDENT ':' ty ('=' expr)? ';'
void let_decl_stmt()//��������let��8����ͷ���涨��ͷ����ǰ�Ѿ������ˣ���һ��Ĭ���Ǳ�ʶ����51��
{
	int tok=nextToken();
	if(tok!=51)
	{
		exit(-1);
	}
	//�˴�Ӧ�����ʶ����51��
	tok=nextToken();
	if(tok!=28)//ð�� 
	{
		exit(-1);
	}
	int typpp=ty();
	//�˴�Ӧ��������
	tok=nextToken();
	if(tok==33)//���ڲ��ֿ���ѡ��ʡ��
	{
		expr();
		//�˴�Ӧ������ʽ 
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

//δ��� 
//function -> 'fn' IDENT '(' function_param_list? ')' '->' ty block_stmt
//function_param_list -> function_param (',' function_param)*
//function_param -> 'const'? IDENT ':' ty
void function()//��������fn��6����ͷ���涨��ͷ����ǰ�Ѿ������ˣ���һ��Ĭ���Ǳ�ʶ����51�� 
{
	int tok=nextToken();
	if(tok!=51)
	{
		exit(-1);
	}
	//�˴�Ӧ�����ʶ����51��
	tok=nextToken();
	if(tok!=23)//��С���� 
	{
		exit(-1);
	}
	
	
	
}

//program -> item*
//item -> function | decl_stmt
//decl_stmt -> let_decl_stmt | const_decl_stmt
void program()//���򣬱�Ȼ�ǳ�����3����������8��������6��
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
	preValid=0;//Ԥ����Ч 
}

int main(int argc,char *argv[])
{
	in=fopen(argv[1],"r");
	init(); 
	
	fclose(in);
	return 0;
}

