#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>

int main()
{
	MYSQL *mysql = NULL;
	//初始化mysql句柄
	mysql = mysql_init(NULL);
	if(mysql ==NULL)
	{
		printf("mysql init error\n");
		return -1;
	}
	if(mysql_real_connect(mysql,"127.0.0.1","root","qwer@wu.888","vod_system",0,NULL,0)==NULL)
	{printf("connect mysql failed:%s\n",mysql_error(mysql));
	//句柄，服务器IP，用户名，密码，库名称，端口，套接字文件，客户端标志
	    return -1;
} 
//设置字符集 （句柄，字符集名称）
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
	//保存结果到本地MYSQL_RES*mysql_store_result(句柄);
	MYSQL_RES*res = mysql_store_result(mysql);
	if(res ==NULL)
	{
	printf("store result failed:%s\n",mysql_error(mysql));
	return -1;
	}
	//获取结果集条数 mysql_num_rows(结果集)
	//获取结果集列数 mysql_num_fields(结果集)
	int row_num = mysql_num_rows(res);
	int col_num = mysql_num_fields(res);
	for (int i = 0;i<row_num ;i++ )
	{
		//逐条遍历获取结果集 mysql_fetch_row(res);
		MYSQL_ROW row = mysql_fetch_row(res);
		for (int j=0;j<col_num ;j++ )

		{
			printf("%s\t",row[j]);
		}
		printf("\n");
	}
	//释放结果集   mysql_free_result(结果集)
	mysql_free_result(res);

	mysql_close(mysql);
	return 0;
	}