#include "head.h"
#include <stdio.h>
#include <sec_api/string_s.h>
// 加载顺序参照 保存的格式


const int BUFF_LENGTH = 513;
char change[BUFF_LENGTH];




bool LoadVectorDirector(FILE* fd, int director_num)  //加载目录信息
{

	for (int i = 0; i < director_num; i++)
	{
		director temp;
		fscanf_s(fd, "%d%s", &temp.id, change, BUFF_LENGTH);
		temp.name = change;
		fscanf_s(fd, "%s", change, BUFF_LENGTH);
		temp.owner = change;
		fscanf_s(fd, "%d", &temp.last_director);
		int direcotor_count;
		fscanf_s(fd, "%d", &direcotor_count);
		while (direcotor_count--)       // 载入包含的目录内容
		{
			int director_index;
			fscanf_s(fd, "%d", &director_index);
			temp.director_list.push_back(director_index);
		}
		int file_count;
		fscanf_s(fd, "%d", &file_count);
		while (file_count--)              // 载入包含的文件内容
		{
			int file_index;
			fscanf_s(fd, "%d", &file_index);
			temp.file_list.push_back(file_index);
		}
		myFileSystem.vector_director.push_back(temp);
	}
	
	cout << "Successfully   loaded directory information." << endl;
	return true;
}


bool LoadVectorFile(FILE* fd, int file_num)  //加载文件信息
{
	while (file_num--)
	{
		file temp;
		fscanf_s(fd, "%d%s", &temp.id, change, BUFF_LENGTH);
		temp.file_name = change;
		fscanf_s(fd, "%d%s", &temp.beginning_in_dataArea, change, BUFF_LENGTH);
		temp.owner = change;
		fscanf_s(fd, "%d%d", &temp.file_length, &temp.begining_in_memory);
		myFileSystem.vector_file.push_back(temp);
	}
	
	cout << "Successfully   loaded file information." << endl;
	return true;
}



bool LoadUserInfo(FILE* fd)    // 加载用户信息
{
	for (int i = 0; i < MAX_User_NUMBER; i++)
	{
		user* temp = &myFileSystem.user_info[i];
		fscanf_s(fd, "%s", change, BUFF_LENGTH);
		(*temp).name = change;
		fscanf_s(fd, "%s", change, BUFF_LENGTH);
		(*temp).password = change;
	}
	
	cout << "Successfully   loaded user information." << endl;
	return true;
}


bool LoadFreeList(FILE* fd)   // 加载成组链
{
	for (int i = 0; i < INDEX_LIST_NUMBER; i++)
	{
		for (int j = 0; j < INDEX_LIST_LENGTH; j++)
		{
			fscanf_s(fd, "%d", &myFileSystem.free_list[i][j]);
			//cout<<"读入了"<<myFileSystem.free_list[i][j]<<endl;
		}
	}
	
	cout << "Successfully   loaded group chain information." << endl;
	return true;
}

bool LoadSuperStack(FILE* fd)  // 加载超级栈信息
{
	fscanf_s(fd, "%d %d", &next_free_list_index, &super_stack_number);
	int temp = super_stack_number;
	while (temp--)
	{
		int value;
		fscanf_s(fd, "%d", &value);
		myFileSystem.superStack.push(value);
	}
	
	cout << "Successfully   loaded super stack information." << endl;
	return true;
}


bool LoadDataArea(FILE* fd)  //加载数据域信息
{
	for (int i = 0; i < DATA_BLOCK_NUMBER; i++)
	{
		int is_null;
		fscanf_s(fd, "%d", &is_null);
		dataBlock* temp = (dataBlock*)malloc(sizeof(dataBlock));
		fscanf_s(fd, "%d%d", &(*temp).next, &(*temp).used);
		if (is_null == 0)    // 如果内容不空，则读出来
		{
			fscanf_s(fd, "%s", change, BUFF_LENGTH);
			strcpy_s((*temp).content, change);
		}
		else  // 内容空则直接赋值
		{
			for (int j = 0; j < DATA_BLOCK_NUMBER + 1; j++)
			{
				(*temp).content[j] = '\0';
			}
		}

		
		myFileSystem.dataArea.push_back(*temp);
	}
	
	cout << "Successfully   loaded data domain information." << endl;
	return true;
}

bool Load()
{
	
	FILE* fd;
	if (fopen_s(&fd, root_path.c_str(), "r") != 0)
	{
		cout << "尚未建立文件系统，请先初始化!" << endl;
		return false;
	}

	Initialize_Memory();

	int director_num;
	fscanf_s(fd, "%d", &director_num);
	LoadVectorDirector(fd, director_num);
	int file_num;
	fscanf_s(fd, "%d", &file_num);
	LoadVectorFile(fd, file_num);
	LoadUserInfo(fd);
	LoadFreeList(fd);
	LoadSuperStack(fd);
	LoadDataArea(fd);
	current_director_index = 0;
	memory_index = 0;

	cout << "Successfully   loaded file system." << endl;
	fclose(fd);
	print();
	return true;


}
/*这段代码实现了文件系统的加载功能，将文件系统的各个组成部分从文件中读取并加载到内存中。

LoadVectorDirector(FILE* fd, int director_num)
这个函数用于加载目录信息。它从文件中读取目录的各个属性，并将其添加到文件系统的目录向量中。

LoadVectorFile(FILE* fd, int file_num)
这个函数用于加载文件信息。它从文件中读取文件的各个属性，并将其添加到文件系统的文件向量中。

LoadUserInfo(FILE* fd)
这个函数用于加载用户信息。它从文件中读取用户的用户名和密码，并将其添加到文件系统的用户信息数组中。

LoadFreeList(FILE* fd)
这个函数用于加载成组链信息。它从文件中读取每个索引列表的内容，并将其添加到文件系统的成组链数组中。

LoadSuperStack(FILE* fd)
这个函数用于加载超级栈信息。它从文件中读取超级栈的内容，并将其添加到文件系统的超级栈中。

LoadDataArea(FILE* fd)
这个函数用于加载数据域信息。它从文件中读取每个数据块的内容，并将其添加到文件系统的数据域向量中。

Load()
这个函数调用了上述所有加载函数，完成了文件系统的加载过程。首先打开文件，然后逐步加载文件系统的各个部分，最后关闭文件。加载完成后，设置当前目录为根目录，内存索引为0，并打印加载成功的消息。

总的来说，这些函数负责从文件中读取数据，并将其加载到文件系统中，以便后续的文件系统操作。



*/