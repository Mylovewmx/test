#include"head.h"
#include <stdlib.h>
#include <stdio.h>
#include <sec_api/string_s.h>

fileSystem myFileSystem;
int memory_index;
char memory[MAX_FILE_LENGTH][DATA_BLOCK_LENGTH];
int current_director_index;
int next_free_list_index;
int super_stack_number;

void Initialize_dataBlock()  //初始化数据块
{
	for (int i = 0; i < DATA_BLOCK_NUMBER; i++)
	{
		dataBlock temp;
		temp.next = -1;
		temp.used = 0;
		for (int j = 0; j < DATA_BLOCK_LENGTH + 1; j++)
		{
			temp.content[j] = '\0';//临时变量内容置为0
		}
		myFileSystem.dataArea.push_back(temp);//在vector尾部加入数据
		
	}
	
	cout << "Successfully   initialized data field！" << endl;
	return;
}


void Initialize_Index_List()  //初始化成组链
{

	next_free_list_index = 0;
	super_stack_number = 0;
	while (!myFileSystem.superStack.empty())//如果超级栈不空，将栈内内容全都pop出去
	{
		myFileSystem.superStack.pop();
	}
	for (int i = 0; i < INDEX_LIST_NUMBER; i++)
	{
		for (int j = INDEX_LIST_LENGTH - 1; j >= 0; j--)
		{
			myFileSystem.free_list[i][j] = i * INDEX_LIST_LENGTH + INDEX_LIST_LENGTH - j - 1;
			//cout<<i<<","<<j<<myFileSystem.free_list[i][j]<<endl;
		}
	}
	cout << "Successfully   initialized group chain！" << endl;
	return;
}


void Initialize_User_Info()   // 初始化用户信息
{
	char temp[6];
	strcpy_s(temp, "user");
	for (int i = 0; i < MAX_User_NUMBER; i++)
	{
		temp[4] = (char)i + 49;
		temp[5] = '\0';
		myFileSystem.user_info[i].name = temp;
		myFileSystem.user_info[i].password = temp;
		
	}
	cout << "Successfully   initialized user information!" << endl;
}


void Initialize_Vector_Director()   //初始化目录信息
{
	myFileSystem.vector_director.clear();
	director first;
	first.last_director = -1;
	first.id = 0;
	first.name = "home";
	first.owner = "empty";
	myFileSystem.vector_director.push_back(first);
	cout << "Successfully   initialized directory information!" << endl;
}




void Initialize_Memory()  // 初始化内存
{
	memory_index = 0;
	for (int i = 0; i < MAX_FILE_LENGTH; i++)
	{
		for (int j = 0; j < DATA_BLOCK_LENGTH; j++)
		{
			memory[i][j] = '\0';
		}
	}
	
}


bool Initialize()  // 初始化
{
	

	Initialize_Vector_Director();   // 初始化文件夹信息

	current_director_index = 0;
	open_file_list.clear();
	myFileSystem.vector_file.clear();

	Initialize_dataBlock();		 // 初始化数据块
	Initialize_Index_List();		// 初始化成组链
	Initialize_User_Info();			// 初始化用户信息

	print();
	return true;

}



/*这段代码是文件系统的初始化部分，负责将文件系统的各个组成部分初始化为初始状态。

Initialize_dataBlock()
这个函数初始化了数据块，即文件系统中用于存储文件内容的块。它将每个数据块的内容清空，并将其标记为未使用状态。

Initialize_Index_List()
这个函数初始化了成组链，即文件系统中用于管理空闲数据块的索引结构。它将索引列表中的每个链表初始化为连续的数据块索引，并将超级栈清空。

Initialize_User_Info()
这个函数初始化了用户信息，设置了文件系统中的默认用户信息。默认情况下，使用者标记为"user1"、"user2"等，密码也与用户名相同。

Initialize_Vector_Director()
这个函数初始化了目录信息，创建了文件系统的根目录 "home"。这是所有文件和文件夹的起始点。

Initialize_Memory()
这个函数初始化了内存，用于在文件系统操作过程中临时存储文件内容。它将内存中的所有位置清空。

Initialize()
这个函数调用了上述所有初始化函数，完成了文件系统的整体初始化过程，并打印出初始化成功的消息。

总的来说，这些函数负责将文件系统的各个部分设置为初始状态，以便后续的文件系统操作。



*/