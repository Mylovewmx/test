#include "head.h"
#include <string.h>

bool ParsePath(string path)  // 把路径解析出来
{
	int begin = 0;
	int ending = 0;
	string accessed;  // 已经过的路径
	bool flag = true;  // 表示是否是第一个目录
	while (ending < strlen(path.c_str()))
	{
		if (path[ending] == '\\')
		{
			string director = path.substr(begin, ending - begin);
			if (flag)
			{
				if (director != "home")             // 首目录必须是home
				{
					cout << "输入的路径不正确！" << endl;
					cout << "请输入绝对路径！如：home\\one\\two" << endl;
					return false;
				}
				accessed += director;
				flag = false;
			}
			else
			{
				if (!ntdir(director))  //到下一目录
				{
					cout << "无法到达" << accessed << "路径下的" << director << "文件夹" << endl;
					return false;
				}
				accessed += director;
			}

			begin = ending + 1;
			

		}
		ending++;
	}
	string director = path.substr(begin, ending - begin);
	if (!ntdir(director))
	{
		cout << "无法到达" << accessed << "路径下的" << director << "文件夹" << endl;
		return false;
	}
	cout << "跳转到" << path << "成功！" << endl;
	return true;
}


void CopyDirector(int pos, int limit)   //复制pos处的目录   limit是为了防止 新建的目录被重复新建 如果发现要新建的目录索引大于或等于
	//limit就不用再新建了
{
	//把pos处目录包含的所有文件夹全部新建，更新last_director

	director current = myFileSystem.vector_director[pos];
	director temp;
	temp.id = myFileSystem.vector_director.size();

	temp.name = current.name;
	temp.owner = current.owner;
	temp.last_director = current_director_index;   //更新last_director



	list<int>::iterator p = current.file_list.begin();  //文件的索引相同  
	while (p != current.file_list.end())
	{
		temp.file_list.push_back(*p);
		p++;
	}


	myFileSystem.vector_director[current_director_index].director_list.push_back(temp.id);  // 在当前目录中加入新的目录
	myFileSystem.vector_director.push_back(temp);//在目录信息中加入新的目录
	current_director_index = temp.id;	//更新当前目录

	p = current.director_list.begin();  // 在当前目录的子目录中继续复制
	while (p != current.director_list.end())
	{
		if (*p != -1 && *p < limit)
		{
			CopyDirector(*p, limit);
		}
		p++;
	}


}

bool copy(string name, string path)
{
	int strore_director = current_director_index;  //暂存
	//current_director_index = 0;
	int pos = IsFileInCurrentDirector(name);
	if (pos == -1)
	{
		pos = IsDirectorInCurrentDirector(name);
		if (pos == -1)
		{
			cout << "当前目录没有" << name << "的文件或文件夹" << endl;
			cout << "复制失败！" << endl;
			return false;
		}
		else// 复制的是文件夹
		{
			if (myFileSystem.vector_director[pos].owner != current_user.name && myFileSystem.vector_director[pos].owner != "empty")//验证权限
			{
				cout << "您没有操作" << name << "文件夹的权限" << endl;
				cout << "复制失败!" << endl;
				return false;
			}

			if (!ParsePath(path))  //跳转到要复制到的目录中
			{
				cout << "复制失败！" << endl;
				return false;
			}
			CopyDirector(pos, myFileSystem.vector_director.size());


		}
	}
	else  // 复制的是文件
	{
		if (myFileSystem.vector_file[pos].owner != current_user.name && myFileSystem.vector_file[pos].owner != "empty")//验证权限
		{
			cout << "您没有操作" << name << "文件夹的权限" << endl;
			cout << "复制失败!" << endl;
			return false;
		}

		if (!ParsePath(path))    //跳转到要复制到的目录中
		{
			cout << "复制失败！" << endl;
			return false;
		}
		myFileSystem.vector_director[current_director_index].file_list.push_back(pos);     //在该目录下添加对应文件的索引即可
	}

	cout << "复制成功!" << endl;
	current_director_index = strore_director;  //恢复当前目录
	return true;
}
/*这段代码看起来是一个简单的文件复制功能的实现。让我来分析一下它的逻辑和可能的改进点。

ParsePath() 函数
这个函数用于解析路径字符串，并根据路径进行导航。

功能：
它通过 \ 分隔路径字符串，并遍历其中的每个目录名称。
检查每个目录名称是否存在，并验证路径的有效性。
如果路径有效，则输出成功消息，并返回 true。
可能的改进点：
对于路径分隔符的处理，代码中使用了硬编码的方式，只支持 \ 作为路径分隔符。这种方式不够灵活，应该考虑兼容其他可能的路径分隔符，例如 /。
在字符串操作时，使用了 strlen() 函数获取字符串长度，这种方法对于 C++ 的 std::string 类型来说不是最佳选择，可以直接使用 path.length() 获取字符串长度。
CopyDirector() 函数
这个函数用于复制目录。

功能：
复制指定目录及其所有子目录和文件。
更新目录信息，包括文件列表和子目录列表。
递归地复制所有子目录。
可能的改进点：
函数中使用了全局变量 current_director_index，这种做法可能导致函数的可重用性降低。建议将其作为参数传递进函数，以提高函数的独立性和可移植性。
在遍历目录列表时，使用了手动迭代器，可以考虑使用范围循环语法，使代码更简洁。
copy() 函数
这个函数用于复制文件或目录。

功能：
首先，它通过 IsFileInCurrentDirector(name) 和 IsDirectorInCurrentDirector(name) 函数来检查要复制的对象是否存在于当前目录中。
根据对象的类型（文件或目录），执行相应的复制操作。
在复制目录时，它调用了 ParsePath() 函数来解析目标路径，并在目标目录中创建副本。
在复制文件时，它将文件的索引添加到目标目录的文件列表中。
可能的改进点：
函数的参数列表中没有指定路径的类型，即无法确定 path 参数是目录路径还是文件路径。这可能导致调用者错误地将文件路径传递给函数，从而导致意外的行为。建议添加一个额外的参数来指示路径的类型。
在复制文件或目录之前，应该检查目标路径是否有效，以避免复制到不存在的目录或目录权限不足的情况。
总结
这段代码实现了文件和目录的复制功能，但仍存在一些潜在的改进点，如路径处理的灵活性、全局变量的使用、函数参数的设计等。通过对代码进行适当的重构和改进，可以提高代码的可读性、可维护性和可扩展性。



*/