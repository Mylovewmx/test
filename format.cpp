#include "head.h"

bool delete_empty_dir1(string director_name, int pos);

bool delete_not_empty_dir1(string director_name, int pos)   // 删除非空文件夹
{
	director temp = myFileSystem.vector_director[current_director_index];			//当前目录值赋给临时目录
	current_director_index = myFileSystem.vector_director[pos].id;					//当前目录暂时进入该文件夹内

	list<int>::iterator p = myFileSystem.vector_director[current_director_index].file_list.begin();          // 删除子目录下所有文件
	while (p != myFileSystem.vector_director[current_director_index].file_list.end())
	{
		int index = *p;
		delfile(myFileSystem.vector_file[index].file_name);							//删除文件
		p++;
	}
	list<int>::iterator dir_p = myFileSystem.vector_director[current_director_index].director_list.begin();	//定位在目录链表的头结点，赋值给p
	while (dir_p != myFileSystem.vector_director[current_director_index].director_list.end())				//当指针没有指向链表的末尾
	{
		delete_not_empty_dir1(myFileSystem.vector_director[*dir_p].name, *dir_p);     // 删除非空子目录（递归）
		dir_p++;
	}
	current_director_index = temp.id;  // 回复当前目录（回到当前目录）
	delete_empty_dir1(director_name, pos);  // 删除已空的文件夹
	return true;
}




bool delete_empty_dir1(string director_name, int pos)  // 删除空的文件夹
{
	list<int>::iterator p_list = myFileSystem.vector_director[current_director_index].director_list.begin();	//头指针赋给p_list
	while (p_list != myFileSystem.vector_director[current_director_index].director_list.end())					//指针没有到目录最后一个节点
	{
		int index = *p_list;
		if (index != -1 && myFileSystem.vector_director[index].name == director_name)
		{
			//current_director.director_list.erase(p_list);   // 从当前目录中删除
			*p_list = -1;   // 标示成不可用
			return true;
		}
		p_list++;
	}
	return false;
}

bool initi1(string director_name, int pos)   //格式化非空文件夹
{
	director temp = myFileSystem.vector_director[current_director_index];			//当前目录值赋给临时目录
	current_director_index = myFileSystem.vector_director[pos].id;					//当前目录暂时进入该文件夹内

	list<int>::iterator p = myFileSystem.vector_director[current_director_index].file_list.begin();          // 删除子目录下所有文件
	while (p != myFileSystem.vector_director[current_director_index].file_list.end())
	{
		int index = *p;
		delfile(myFileSystem.vector_file[index].file_name);							//删除文件
		p++;
	}
	list<int>::iterator dir_p = myFileSystem.vector_director[current_director_index].director_list.begin();	//定位在目录链表的头结点，赋值给p
	while (dir_p != myFileSystem.vector_director[current_director_index].director_list.end())				//当指针没有指向链表的末尾
	{
		delete_not_empty_dir1(myFileSystem.vector_director[*dir_p].name, *dir_p);     // 删除非空子目录（递归）
		dir_p++;
	}
	current_director_index = temp.id;  // 回复当前目录（回到当前目录）
	return true;
}


bool initi(string director_name)  // 格式化文件夹
{
	int pos = IsDirectorInCurrentDirector(director_name);
	if (pos == -1)
	{
		cout << "当前目录中不包含" << director_name << "文件夹" << endl;
		cout << "删除失败" << endl;
		return false;
	}
	if (myFileSystem.vector_director[pos].owner != current_user.name && myFileSystem.vector_director[pos].owner != "empty")	//权限
	{
		cout << "您没有该文件夹的操作权限!" << endl;
		return false;
	}
	director temp = myFileSystem.vector_director[pos];			//
	if (temp.file_list.empty() && temp.director_list.empty())
	{
		cout << "格式化成功！" << endl;
	}
	else
	{
		cout << "要格式化的目录非空，是否删除其中所有文件及文件夹?Y/N" << endl;
		char input;
		cin >> input;
		if (input == 'Y' || input == 'y')
		{
			initi1(director_name, pos);  // 删除非空文件夹
		}
		else
		{
			if (input == 'N' || input == 'n')
			{
				cout << "您已取消本次格式化" << endl;
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
/*这些函数看起来是文件系统中用于格式化文件夹的操作。让我来解释一下：

delete_not_empty_dir1() 函数
这个函数用于删除非空文件夹。

首先，它保存当前目录的信息。
然后，进入指定的文件夹，并递归地删除文件夹中的所有文件和子文件夹。
最后，返回到原来的目录，并调用 delete_empty_dir1() 函数来删除已经为空的文件夹。
delete_empty_dir1() 函数
这个函数用于删除空文件夹。

遍历当前目录的子目录列表，找到指定名称的目录。
如果找到目录，则将其标记为不可用（通过将其索引置为 -1）。
initi1() 函数
这个函数用于格式化非空文件夹。

首先，它保存当前目录的信息。
然后，进入指定的文件夹，并递归地删除文件夹中的所有文件和子文件夹。
最后，返回到原来的目录。
initi() 函数
这个函数用于格式化文件夹。

首先，它检查文件夹是否存在于当前目录中，以及当前用户是否有删除权限。
如果文件夹为空，则输出格式化成功的消息。
如果文件夹非空，则询问用户是否要删除其中的所有文件和文件夹，根据用户的选择调用 initi1() 函数或取消格式化操作。
这些函数以递归的方式处理文件夹中的文件和子文件夹，以确保将所有内容都删除。*/