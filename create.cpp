#include "head.h"

int IsFileInCurrentDirector(string file_name)   // 判断一文件名是否存在于当前目录的子文件中  若存在返回对应索引号 不存在返回-1
{
	list<int>::iterator p = myFileSystem.vector_director[current_director_index].file_list.begin();
	while (p != myFileSystem.vector_director[current_director_index].file_list.end())
	{
		int index = *p;
		if (index != -1 && myFileSystem.vector_file[index].file_name == file_name)
		{

			return index;
		}
		p++;
	}

	return -1;
}

int IsDirectorInCurrentDirector(string file_name)  // 判断一文件名是否存在的当前目录的子目录中
{
	bool flag = false;
	list<int>::iterator p = myFileSystem.vector_director[current_director_index].file_list.begin();

	p = myFileSystem.vector_director[current_director_index].director_list.begin();
	while (p != myFileSystem.vector_director[current_director_index].director_list.end())
	{
		int index = *p;
		if (index != -1 && myFileSystem.vector_director[index].name == file_name)
		{

			return *p;
		}
		p++;
	}
	return -1;
}

bool IsDataAreaFull()   // 判断数据域是否已满
{
	if (myFileSystem.superStack.empty() && myFileSystem.free_list[INDEX_LIST_NUMBER - 1][0] == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool create(string file_name)         // 创建文件
{
	if (IsFileInCurrentDirector(file_name) != -1)
	{
		cout << "本目录中已存在名为" << file_name << "的文件" << endl;
		cout << "文件创建失败" << endl;
		return false;
	}

	if (IsDirectorInCurrentDirector(file_name) != -1)
	{
		cout << "本目录中已存在名为" << file_name << "的文件夹" << endl;
		cout << "文件创建失败" << endl;
		return false;
	}

	if (IsDataAreaFull())
	{
		cout << "数据域已满，没有足够空间创建文件" << endl;
		return false;
	}

	file temp;
	temp.id = myFileSystem.vector_file.size();
	temp.file_length = 1;
	temp.owner = current_user.name;
	temp.file_name = file_name;
	temp.begining_in_memory = 0;
	temp.beginning_in_dataArea = AllocDataBlock();
	cout << "该文件被分配的数据块号是：" << temp.beginning_in_dataArea << endl;
	myFileSystem.vector_file.push_back(temp);
	myFileSystem.vector_director[current_director_index].file_list.push_back(temp.id);
	return true;

}
/*这段代码包含了几个函数，主要用于文件系统中的文件和目录管理。让我逐一分析：

1. IsFileInCurrentDirector() 函数
这个函数用于检查指定文件名是否存在于当前目录的子文件列表中。

遍历当前目录的子文件列表，逐一比较文件名。
如果找到匹配的文件名，则返回该文件在文件列表中的索引。
如果未找到匹配的文件名，则返回 -1，表示文件不存在于当前目录。
2. IsDirectorInCurrentDirector() 函数
这个函数用于检查指定目录名是否存在于当前目录的子目录列表中。

遍历当前目录的子目录列表，逐一比较目录名。
如果找到匹配的目录名，则返回该目录在目录列表中的索引。
如果未找到匹配的目录名，则返回 -1，表示目录不存在于当前目录。
3. IsDataAreaFull() 函数
这个函数用于检查数据域是否已满。

如果超级栈为空且最后一个索引组的第一个索引为 -1，则认为数据域已满，返回 true。
否则，返回 false，表示数据域尚有空间可用。
4. create() 函数
这个函数用于创建文件。

首先，它检查当前目录中是否存在同名文件或目录，如果存在，则输出错误消息并返回 false。
接着，它检查数据域是否已满，如果已满，则输出错误消息并返回 false。
最后，它创建一个新文件，并将其添加到文件列表和当前目录的文件列表中。
可能的改进点：
在 create() 函数中，当调用 AllocDataBlock() 分配数据块时，应该检查分配是否成功。如果分配失败，则应该回滚之前的操作，以避免文件系统状态不一致。
在 IsFileInCurrentDirector() 和 IsDirectorInCurrentDirector() 函数中，循环迭代列表时，可以考虑使用范围循环语法，使代码更简洁。
对于 create() 函数，可能需要更多的错误处理机制，例如在创建文件时检查权限或文件名的有效性等。


*/