#include "head.h"

// 删除文件的时候，并不是把 myFileSystem.file_list中的文件删除，只是将其id改成-1，做标记，标示不可用。如果删除，对应的索引结构就全乱了。

bool delfile(string file_name) //删除文件
{

	int pos = IsFileInCurrentDirector(file_name);
	if (pos == -1)
	{
		cout << "当前目录中不包含该文件，删除失败" << endl;
		return false;
	}

	if (myFileSystem.vector_file[pos].owner != current_user.name && myFileSystem.vector_file[pos].owner != "empty")
	{
		cout << "您没有该文件夹的操作权限!" << endl;
		return false;
	}

	list<int>::iterator p_list = myFileSystem.vector_director[current_director_index].file_list.begin();
	while (p_list != myFileSystem.vector_director[current_director_index].file_list.end())
	{
		int index = *p_list;
		if (index != -1 && myFileSystem.vector_file[index].file_name == file_name)
		{
			*p_list = -1;   // 标示为不可用
			ReleaseDataBlock(index);
			break;
		}
		p_list++;
	}


	cout << "删除文件" << file_name << "成功" << endl;
	return true;
}
/*
ChatGPT
这段代码实现了删除文件的功能。让我来详细解释一下：

delfile() 函数
这个函数用于删除文件。

首先，它检查当前目录中是否包含指定名称的文件，以及当前用户是否有删除权限。
如果文件存在且用户有权限，则遍历当前目录的文件列表，找到匹配的文件名，将其索引改为 -1，表示文件不可用。
然后，调用 ReleaseDataBlock() 函数释放文件占用的数据块。
最后，输出删除成功的消息，并返回 true。
可能的改进点：
在删除文件之前，应该检查文件索引的有效性，以避免因索引无效而导致的错误。
在释放数据块之前，应该确保文件确实占用了数据块，以避免意外释放未被占用的数据块。
在函数中添加一些错误处理机制，例如在遍历文件列表时，检查索引是否有效，以及对用户的操作进行友好的提示。

*/