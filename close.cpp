#include "head.h"


bool close(string file_name)
{
	int pos = IsFileInCurrentDirector(file_name);

	if (pos == -1)
	{
		cout << "当前目录不存在" << file_name << "文件" << endl;
		cout << "读文件失败！" << endl;
		return false;
	}


	list<openFile>::iterator open_file_p = IsInOpenFileList(pos);
	if (open_file_p == open_file_list.end())   // 检查文件是否已打开
	{
		cout << "该文件还未打开，无法关闭" << endl;
		return false;
	}

	file temp = myFileSystem.vector_file[pos];
	for (int i = temp.begining_in_memory; i <= temp.begining_in_memory + temp.file_length; i++)
	{
		for (int j = 0; j < DATA_BLOCK_LENGTH; j++)
		{
			if (memory[i][j] != '\0')
			{
				memory[i][j] = '\0';
			}
			else
			{
				break;
			}

		}
	}
	open_file_list.erase(open_file_p);   //从打开链表中删除
	cout << "关闭文件" << file_name << "成功" << endl;
	return true;

}
/*这段代码看起来是用于关闭文件的功能。让我来分析一下它的逻辑和可能的改进点。

close() 函数
这个函数接收一个文件名作为参数，用于关闭该文件。

功能：
首先，它调用 IsFileInCurrentDirector(file_name) 函数检查当前目录中是否存在指定的文件。如果文件不存在，则输出错误消息并返回 false。
如果文件存在，则继续检查文件是否已经被打开，通过调用 IsInOpenFileList(pos) 函数，其中 pos 是文件在文件系统中的位置。
如果文件尚未打开，则输出错误消息并返回 false。
如果文件已经打开，它会清除文件在内存中的数据，将相应的内存块置为空字符 '\0'。
然后，它从打开文件列表中删除该文件。
最后，输出关闭文件成功的消息并返回 true。
可能的改进点：
在清除文件数据之前，应该确保文件已经被打开，以避免在未打开的情况下清除无效的内存。
在遍历文件数据块并清除数据时，应该正确地控制循环边界，以避免越界访问内存。
在从打开文件列表中删除文件之前，应该确保文件已经被打开并且在打开文件列表中，以避免意外删除其他文件。
如果文件不存在于打开文件列表中，则可能需要输出一条警告消息，因为关闭文件操作可能是不必要的，除非文件确实存在于该列表中。
总结
这段代码实现了关闭文件的功能，但需要注意确保在执行操作前进行必要的检查，以避免潜在的错误和意外情况。通过添加适当的错误检查和边界条件，可以提高代码的稳健性和健壮性。*/