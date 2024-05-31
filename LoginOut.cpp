#include "head.h"
#include <stdio.h>



/* 保存格式
1. vector_director的个数
2.vector_director的内容
3.vector_file的个数
4.vector_file的内容
5.user_info内容
6.free_list内容  编号有小到大
7.super_stack内容
8.data_area内容

1.int id
2.char* name
3.char* owner
4.int last_director
5.int director数目
6.int director_list
7.int file数目
8.int file_list
*/

bool SaveVectorDirector(FILE* fd)  //保存目录信息
{
	vector<director>::iterator p = myFileSystem.vector_director.begin();//返回一个迭代器，指向第一个元素

	while (p != myFileSystem.vector_director.end())
	{
		int director_num = (*p).director_list.size();
		int file_num = (*p).file_list.size();

		fprintf(fd, "%d%s\n%s\n%d\n%d\n", (*p).id, (*p).name.c_str(), (*p).owner.c_str(), (*p).last_director, director_num);

		list<int>::iterator p_list = (*p).director_list.begin();  // 写入director_list
		while (p_list != (*p).director_list.end())
		{
			fprintf(fd, "%d\n", (*p_list));
			p_list++;
		}

		fprintf(fd, "%d\n", file_num);
		p_list = (*p).file_list.begin();          // 写入file_list
		while (p_list != (*p).file_list.end())
		{
			fprintf(fd, "%d\n", (*p_list));
			p_list++;
		}

		p++;
	}
	cout << "保存目录信息成功" << endl;
	return true;
}



/*保存格式
1.int id
2.char* file_name
3.int beginning_in_dataarea
4.char* owner
5.int file_length
6.int beginning_in_memory
*/
bool SaveVectorFile(FILE* fd)  // 保存文件信息
{
	vector<file>::iterator p = myFileSystem.vector_file.begin();
	while (p != myFileSystem.vector_file.end())
	{
		fprintf(fd, "%d\n%s\n%d\n%s\n%d\n%d\n", (*p).id, (*p).file_name.c_str(), (*p).beginning_in_dataArea, (*p).owner.c_str(), (*p).file_length, (*p).begining_in_memory);
		p++;
	}
	cout << "保存文件信息成功" << endl;
	return true;
}

bool SaveUserInfo(FILE* fd)  // 保存用户信息
{

	for (int i = 0; i < MAX_User_NUMBER; i++)
	{
		user temp = myFileSystem.user_info[i];
		fprintf(fd, "%s\n%s\n", temp.name.c_str(), temp.password.c_str());
	}
	cout << "保存用户信息成功" << endl;
	return true;
}



bool SaveFreeList(FILE* fd)  //保存成组链
{
	for (int i = 0; i < INDEX_LIST_NUMBER; i++)
	{
		for (int j = 0; j < INDEX_LIST_LENGTH; j++)
		{
			fprintf(fd, "%d\n", myFileSystem.free_list[i][j]);
		}
	}
	cout << "保存成组链成功" << endl;
	return true;
}



/*
1. int next_free_list_index;   // 下一组要使用的组数  0~INDEX_LIST_NUMBER-1
2. int super_stack_number;     // 超级栈中可以使用的块数
3. int 栈中内容 逆序
*/

bool SaveSuperStack(FILE* fd)  // 保存超级栈
{
	stack<int> temp;
	fprintf(fd, "%d\n%d\n", next_free_list_index, super_stack_number);
	while (!myFileSystem.superStack.empty())   // 将内容保存到另一个栈中，逆序保存，这样加载的时候顺序才对
	{
		int top = myFileSystem.superStack.top();
		temp.push(top);
		myFileSystem.superStack.pop();
		//cout << endl;
	}
	while (!temp.empty())
	{
		fprintf(fd, "%d\n", temp.top());
		temp.pop();
	}
	cout << "保存超级栈成功" << endl;
	return true;
}




bool SaveDataArea(FILE* fd) //保存数据域内容
{
	for (int i = 0; i < DATA_BLOCK_NUMBER; i++)
	{
		int is_null = 1;    // 做个标记，1表示内容是空，0表示非空
		dataBlock temp = myFileSystem.dataArea[i];
		if (temp.content[0] != '\0')       // 如果非空，做上标记
		{
			is_null = 0;
		}
		fprintf(fd, "%d\n%d\n%d\n", is_null, temp.next, temp.used);
		if (is_null == 0)    //非空的把内容存入
		{
			fprintf(fd, "%s\n", temp.content);
		}
	}
	cout << "保存数据域内容成功" << endl;
	return true;
}

bool LoginOut()
{
	FILE* fd;
	if (fopen_s(&fd, root_path.c_str(), "w+") != 0)
	{
		cout << "打开文件" << root_path << "失败，无法保存" << endl;
		return false;
	}

	int director_num = myFileSystem.vector_director.size();
	int file_num = myFileSystem.vector_file.size();
	fprintf(fd, "%d\n", director_num);
	SaveVectorDirector(fd);      //写入vector_director内容
	fprintf(fd, "%d\n", file_num);
	SaveVectorFile(fd);
	SaveUserInfo(fd);
	SaveFreeList(fd);
	SaveSuperStack(fd);
	SaveDataArea(fd);
	cout << "文件系统保存成功!" << endl;
	print();
	fclose(fd);

	return true;
}
/*SaveVectorDirector 函数保存文件系统中的目录信息到给定的文件描述符中。它遍历 myFileSystem.vector_director 中的每个目录，并将其相关信息写入文件。对于每个目录，它写入目录的 ID、名称、所有者、上一级目录 ID、子目录列表和文件列表。

SaveVectorFile 函数保存文件系统中的文件信息到给定的文件描述符中。它遍历 myFileSystem.vector_file 中的每个文件，并将其相关信息写入文件。对于每个文件，它写入文件的 ID、文件名、在数据区的起始位置、所有者、文件长度和在内存中的起始位置。

SaveUserInfo 函数保存文件系统中的用户信息到给定的文件描述符中。它遍历 myFileSystem.user_info 中的每个用户，并将其用户名和密码写入文件。

SaveFreeList 函数保存文件系统中的成组链信息到给定的文件描述符中。它遍历 myFileSystem.free_list 中的每个索引链，并将其内容写入文件。

SaveSuperStack 函数保存文件系统中的超级栈信息到给定的文件描述符中。它将超级栈的下一个可用索引数、超级栈中可用块数和栈中内容保存到文件中。

SaveDataArea 函数保存文件系统中的数据区内容到给定的文件描述符中。它遍历 myFileSystem.dataArea 中的每个数据块，并将其内容写入文件。对于每个数据块，它写入一个标志表示内容是否为空，然后写入下一个数据块的索引、使用情况以及数据内容。

LoginOut 函数用于保存文件系统的状态。它将目录信息、文件信息、用户信息、成组链、超级栈和数据区内容保存到文件中。首先它打开文件以供写入，然后依次调用上述保存函数，并最终关闭文件。



*/