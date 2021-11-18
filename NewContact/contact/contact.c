#include "contact.h"
static int FindByName(Contact* pc, char name[])
{
	int i = 0;
	for (i = 0; i < pc->sz; i++)
	{
		if (strcmp(pc->data[i].name, name) == 0)
		{
			return i;
		}

	}
	return -1;  //找不到
}

void CheckCapacity(Contact* pc)
{
	if (pc->sz == pc->capacity)
	{
		PeoInfo* ptr = realloc(pc->data, (pc->capacity + INC_SZ) * sizeof(PeoInfo));
		if (ptr != NULL)
		{
			pc->data = ptr;
			pc->capacity += INC_SZ;
			printf("增容成功\n");
		}
		else
		{
			perror("AddContact");
			printf("增加联系人失败");
			return;
		}
	}
}

void LoadContact(Contact* pc)
{
	FILE* pf = fopen("contact.dat","r");
	if (pf == NULL)
	{
		perror("LoadContact");
		return; 
	}
	PeoInfo tmp = { 0 };
	while (fread(&tmp, sizeof(PeoInfo), 1, pf))
	{
		//判断容量
		CheckCapacity(pc);
		//往内存中放数据
		pc->data[pc->sz] = tmp;
		pc->sz++;
	}

	fclose(pf);
	pf = NULL;

}


//静态版本初始化
void InitContact(Contact* pc)
{
	pc->data = (PeoInfo*)malloc(DEFAULT_SZ*sizeof(PeoInfo));
	if (pc->data == NULL)
	{
		perror("InitContact");
		return;
	}
	pc->sz = 0;//初始化之后默认是0
	pc->capacity = DEFAULT_SZ;


	//加载文件
	LoadContact(pc);

	

}

void AddContact(Contact* pc)
{
	//增加容量
	CheckCapacity(pc);
	// 增加一个人的信息
	printf("输入名字;>");
	scanf("%s", pc->data[pc->sz].name);
	printf("输入年龄:>");
	scanf("%d", &pc->data[pc->sz].age);
	printf("输入性别:>");
	scanf("%s", pc->data[pc->sz].sex);
	printf("输入电话:>");
	scanf("%s", pc->data[pc->sz].tele);
	printf("输入地址:>");
	scanf("%s", pc->data[pc->sz].addr);
	pc->sz++;
	printf("增加成功\n");
}

void PrintContact(const Contact* pc)
{
	int i = 0;
	//打印标题
	printf("%20s\t %5s\t %5s\t %12s\t %20s\n","name","age","sex","tele","addr");
	for (i = 0; i < pc->sz; i++)
	{
		printf("%20s\t %5d\t %5s\t %12s\t %20s\n",
			pc->data[i].name,
			pc->data[i].age,
			pc->data[i].sex,
			pc->data[i].tele,
			pc->data[i].addr   );

	}

}
void DelContact(Contact* pc)
{
	char name[MAX_NAME] = { 0 };

	if (pc->sz == 0)
	{
		printf("通讯录为空,无需删除\n");
		return;
	}
	printf("请输入要删除人的名字:>");
	scanf("%s",name);
	//查找
	int pos = FindByName(pc, name);
	//yes/no
	if (pos == -1)
	{
		printf("要删除的人不存在\n");
	}
	else
	{      //删除
		int i = 0;
		for (i = pos; i < pc->sz - 1; i++)
		{
			pc->data[i] = pc->data[i + 1];
		}
		pc->sz--;
		printf("删除成功\n");
	}
	

}


void SearchContact(Contact* pc)
{
	char name[MAX_NAME] = { 0 };
	printf("请输入要查找人的名字:>");
	scanf("%s", name);
	int pos = FindByName(pc, name);
	if (pos == -1)
	{
		printf("要查找的人不存在\n");
	}
	else
	{
		int i = 0;
		//打印标题
		printf("%20s\t %5s\t %5s\t %12s\t %20s\n", "name", "age", "sex", "tele", "addr");
		
		
		printf("%20s\t %5d\t %5s\t %12s\t %20s\n",
				pc->data[pos].name,
				pc->data[pos].age,
				pc->data[pos].sex,
				pc->data[pos].tele,
				pc->data[pos].addr);

		
	}
		
		
}


void ModifyContact(Contact* pc)
{
	char name[MAX_NAME] = { 0 };

	
	printf("请输入要修改人的名字:>");
	scanf("%s", name);
	//查找
	int pos = FindByName(pc, name);
	//yes/no
	if (pos == -1)
	{
		printf("要修改的人不存在\n");
	}
	else
	{      //修改
		// 增加一个人的信息
		printf("输入名字;>");
		scanf("%s", pc->data[pos].name);
		printf("输入年龄:>");
		scanf("%d", &pc->data[pos].age);
		printf("输入性别:>");
		scanf("%s", pc->data[pos].sex);
		printf("输入电话:>");
		scanf("%s", pc->data[pos].tele);
		printf("输入地址;>");
		scanf("%s", pc->data[pos].addr);
		printf("修改成功\n");
	}

}


void DestoryContact(Contact* pc)
{



	free(pc->data);
	pc->data = NULL;
	pc->sz = 0;
	pc->capacity = 0;
}



void SaveContact(Contact* pc)
{
	FILE* pf = fopen("contact.dat","w");
	if (pf == NULL)
	{
		perror("SaveContact");
		return;
	}

	//写入数据
	int i = 0;
	for (i = 0; i < pc->sz; i++)
	{
		fwrite(pc->data+i, sizeof(PeoInfo), 1, pf);

	}
	//关闭文件
	fclose(pf);
	pf = NULL;
}
