#include "head.h"

void dir()
{
	list<int>::iterator director_p = myFileSystem.vector_director[current_director_index].director_list.begin();
	cout << "目录列表:" << endl;
	while (director_p != myFileSystem.vector_director[current_director_index].director_list.end())
	{
		int index = *director_p;
		if (index != -1)      // 如果可用
		{
			cout << myFileSystem.vector_director[index].name << '\t';
		}
		director_p++;
	}
	cout << endl;
	list<int>::iterator file_p = myFileSystem.vector_director[current_director_index].file_list.begin();
	cout << "文件列表:" << endl;
	while (file_p != myFileSystem.vector_director[current_director_index].file_list.end())
	{
		int index = *file_p;
		if (index != -1)  //如果可用
		{
			cout << myFileSystem.vector_file[index].file_name << '\t';
		}

		file_p++;
	}
	cout << endl;
}
/*
ChatGPT
这段代码实现了显示当前目录中的文件和子目录列表的功能。让我来解释一下：

dir() 函数
这个函数用于显示当前目录的文件和子目录列表。

首先，它遍历当前目录的子目录列表，输出每个子目录的名称。
然后，它遍历当前目录的文件列表，输出每个文件的名称。
在输出列表时，只输出索引不为 -1 的项，因为 -1 表示该项不可用（已被删除）。
可能的改进点：
在输出列表时，可以考虑使用范围循环语法，使代码更加简洁。
考虑输出更多有关文件和子目录的信息，例如文件大小、最后修改时间等，以提供更全面的信息。
考虑对输出的格式进行优化，使其更易于阅读和理解，例如对齐输出、分行等。*/