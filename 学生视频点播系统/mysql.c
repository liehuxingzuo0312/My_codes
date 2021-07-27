#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>

int main()
{
	MYSQL *mysql = NULL;
	//��ʼ��mysql���
	mysql = mysql_init(NULL);
	if(mysql ==NULL)
	{
		printf("mysql init error\n");
		return -1;
	}
	if(mysql_real_connect(mysql,"127.0.0.1","root","qwer@wu.888","vod_system",0,NULL,0)==NULL)
	{printf("connect mysql failed:%s\n",mysql_error(mysql));
	//�����������IP���û��������룬�����ƣ��˿ڣ��׽����ļ����ͻ��˱�־
	    return -1;
} 
//�����ַ��� ��������ַ������ƣ�
int ret;
ret=mysql_set_character_set(mysql,"utf8");
if(ret!=0){
	printf("set character failed:%s\n",mysql_error(mysql));
	return -1;
}
	char *select = "select * from tb_video;";
	ret = mysql_query(mysql,select);
	if(ret !=0)
	{
	printf("query sql failed:%s\n",mysql_error(mysql));
	return -1;
	}
	//������������MYSQL_RES*mysql_store_result(���);
	MYSQL_RES*res = mysql_store_result(mysql);
	if(res ==NULL)
	{
	printf("store result failed:%s\n",mysql_error(mysql));
	return -1;
	}
	//��ȡ��������� mysql_num_rows(�����)
	//��ȡ��������� mysql_num_fields(�����)
	int row_num = mysql_num_rows(res);
	int col_num = mysql_num_fields(res);
	for (int i = 0;i<row_num ;i++ )
	{
		//����������ȡ����� mysql_fetch_row(res);
		MYSQL_ROW row = mysql_fetch_row(res);
		for (int j=0;j<col_num ;j++ )

		{
			printf("%s\t",row[j]);
		}
		printf("\n");
	}
	//�ͷŽ����   mysql_free_result(�����)
	mysql_free_result(res);

	mysql_close(mysql);
	return 0;
	}