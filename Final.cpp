#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char token[2048];//�洢��ǰ�ַ���������44�������߱�ʶ����51��
int num;//�޷���������41���﷨����������ȡ���� 
double dou;//�޷��Ÿ�������42���﷨����������ȡ���� 
char ch;//�ַ�������43�� 

int reserver()//�ؼ��ֱ���10�� 
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
		int resultValue=reserver();//resultValue���ұ����ֵķ���ֵ 
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

int nextToken()//������һ��token������룬ע�Ͳ���ΪToken 
{
	int sym=getToken();
	while(sym==-2)//����ע�ͣ�ֻ���ٶ�һ�� 
	{
		sym=getToken();
	}
	return sym;
}

//Ŀǰ�����Σ�
//tokenΪ�ؼ��֡���������ĵ���β��-1����ʱ��ֱ�ӿ����صı�ż���
//tokenΪ������41������������42�����ַ�������43�����洢��num��dou��ch 
//tokenΪ�ַ�����44�����ʶ����51�������洢��token
//����41��42��43��44��51���Σ���Ҫ��һ��tokenջ�����洢���ǣ���������ʵ��unreadToken����
//unreadToken������ֱ�ӽ�tokenѹ��tokenջ�� 
//��Ҫ�޸�nextToken���������tokenջ������token���ʹ�ջ����ȡ��tokenջ������ˣ��Ż����getToken 

//ʵ����unreadToken��Ȼ����ܿ�ʼ���﷨���� 

int main(int argc,char *argv[])
{
	in=fopen(argv[1],"r");
	
	fclose(in);
	return 0;
}

