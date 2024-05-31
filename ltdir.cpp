#include "head.h"



void ltdir()  // 前往上一级目录
{
	int index = myFileSystem.vector_director[current_director_index].last_director;
	if (index != -1)
	{
		current_director_index = index;
	}
	else
	{
		cout << "您已经在根目录中，不能再向上" << endl;
	}
}
/*
ChatGPT
ltdir 函数用于将当前目录切换到上一级目录。它首先获取当前目录的上一级目录的索引，然后检查是否存在上一级目录。如果存在，它将当前目录索引更新为上一级目录的索引，从而实现切换到上一级目录。如果不存在上一级目录（即当前目录已经是根目录），则输出提示信息表示无法再向上切换。


*/