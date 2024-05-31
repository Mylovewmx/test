#include "head.h"

bool delete_empty_dir(string director_name, int pos)  // 删除空的文件夹
{
	list<int>::iterator p_list = myFileSystem.vector_director[current_director_index].director_list.begin();
	while (p_list != myFileSystem.vector_director[current_director_index].director_list.end())
	{
		int index = *p_list;
		if (index != -1 && myFileSystem.vector_director[index].name == director_name)
		{
			//current_director.director_list.erase(p_list);   // 从当前目录中删除
			*p_list = -1;   // 标示成不可用
			break;
		}
		p_list++;
	}
	cout << "删除文件夹" << director_name << "成功" << endl;
	return true;
}

bool delete_not_empty_dir(string director_name, int pos)   // 删除非空文件夹
{
	director temp = myFileSystem.vector_director[current_director_index];
	current_director_index = myFileSystem.vector_director[pos].id;  // 当前目录暂时 进入该文件夹内

	list<int>::iterator p = myFileSystem.vector_director[current_director_index].file_list.begin();          // 删除子目录下所有文件
	while (p != myFileSystem.vector_director[current_director_index].file_list.end())
	{
		int index = *p;
		delfile(myFileSystem.vector_file[index].file_name);
		p++;
	}

	list<int>::iterator dir_p = myFileSystem.vector_director[current_director_index].director_list.begin();
	while (dir_p != myFileSystem.vector_director[current_director_index].director_list.end())
	{
		delete_not_empty_dir(myFileSystem.vector_director[*dir_p].name, *dir_p);     // 删除非空子目录
		dir_p++;
	}

	current_director_index = temp.id;  // 回复当前目录
	delete_empty_dir(director_name, pos);  // 删除已空的文件夹

	return true;

}

bool deldir(string director_name)  // 删除文件夹
{
	int pos = IsDirectorInCurrentDirector(director_name);
	if (pos == -1)
	{
		cout << "当前目录中不包含" << director_name << "文件夹" << endl;
		cout << "删除失败" << endl;
		return false;
	}

	if (myFileSystem.vector_director[pos].owner != current_user.name && myFileSystem.vector_director[pos].owner != "empty")
	{
		cout << "您没有该文件夹的操作权限!" << endl;
		return false;
	}

	director temp = myFileSystem.vector_director[pos];

	if (temp.file_list.empty() && temp.director_list.empty())
	{
		delete_empty_dir(director_name, pos);  // 删除空文件夹
	}
	else
	{
		cout << "要删除的目录非空，是否删除其中所有文件及文件夹?Y/N" << endl;
		char input;
		cin >> input;
		if (input == 'Y' || input == 'y')
		{
			delete_not_empty_dir(director_name, pos);  // 删除非空文件夹
		}
		else
		{
			if (input == 'N' || input == 'n')
			{
				cout << "您已取消本次删除" << endl;
				return false;
			}
			else
			{
				cout << "请输入有效指令" << endl;
				deldir(director_name);
			}
		}
	}
	return true;
}
/*这段代码实现了删除文件夹的功能，并且提供了两种删除方式：删除空文件夹和删除非空文件夹。

1. delete_empty_dir() 函数
这个函数用于删除空文件夹。

遍历当前目录的子目录列表，找到指定名称的目录。
如果找到目录，则将其标记为不可用（通过将其索引置为 -1）。
输出删除成功的消息，并返回 true。
2. delete_not_empty_dir() 函数
这个函数用于删除非空文件夹。

首先，它保存当前目录的信息，然后进入指定的文件夹。
递归地删除文件夹中的所有文件和子文件夹。
最后，它返回到原来的目录，并调用 delete_empty_dir() 函数来删除已经为空的文件夹。
3. deldir() 函数
这个函数用于删除文件夹。

首先，它检查文件夹是否存在于当前目录中，以及当前用户是否有删除权限。
如果文件夹为空，则调用 delete_empty_dir() 函数直接删除。
如果文件夹非空，则询问用户是否要删除其中的所有文件和文件夹，根据用户的选择调用 delete_not_empty_dir() 函数或取消删除操作。
可能的改进点：
在 delete_empty_dir() 和 delete_not_empty_dir() 函数中，应该增加一些错误处理机制，例如在遍历子目录列表时，检查索引是否有效。
在 deldir() 函数中，对用户输入的处理可以更加严谨，例如检查用户输入的有效性以及提供友好的错误提示。
总体来说，这段代码实现了基本的文件夹删除功能，但在实际应用中可能需要进一步完善，以处理更多的边界情况和用户输入。



*/