#include "head.h"

void mkdir(string director_name)    // 创建目录
{

	if (IsFileInCurrentDirector(director_name) != -1)
	{
		cout << "本目录中已存在名为" << director_name << "的文件" << endl;
		cout << "文件创建失败" << endl;
		return;
	}

	int pos = IsDirectorInCurrentDirector(director_name);
	if (pos != -1)
	{
		cout << "当前目录中已包含名为" << director_name << "的文件夹" << endl;
		cout << "创建失败!" << endl;
		return;	
	}
	director temp;
	temp.name = director_name;
	temp.last_director = current_director_index;
	temp.owner = current_user.name;
	temp.id = myFileSystem.vector_director.size();
	myFileSystem.vector_director.push_back(temp);
	
	myFileSystem.vector_director[current_director_index].director_list.push_back(temp.id);
	cout << "创建目录" << director_name << "成功" << endl;
	return;
}
