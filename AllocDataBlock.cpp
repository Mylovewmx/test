#include "head.h"


void IntoSuperStack()  // free数组进入超级栈
{
	for(int i=0;i<INDEX_LIST_LENGTH;i++) // 成组链中每组个数
	{
		int param = myFileSystem.free_list[next_free_list_index][i];// 成组链数组  使用的时候从小到大   被使用了置成-1
		// 下一组要使用的组数  0~INDEX_LIST_NUMBER-1 next_free_list_index
		myFileSystem.superStack.push(param);
		myFileSystem.free_list[next_free_list_index][i] = -1;  //正在用的那组置为-1
	}

	super_stack_number = INDEX_LIST_LENGTH;

	if(next_free_list_index < INDEX_LIST_NUMBER)  // 如果没到最后一块就+1
	{
		next_free_list_index++;
	}
	
}

int AllocDataBlock()   //分配数据块
{
	if(myFileSystem.superStack.empty())
	{
		IntoSuperStack();   // 从free组进入超级栈
	}
	int result = myFileSystem.superStack.top();
	myFileSystem.superStack.pop();
	super_stack_number--;
	return result;

}
/*这段代码看起来是一个简单的文件系统中用于管理数据块的部分。让我详细解释一下它的功能和可能的改进点。

1. IntoSuperStack() 函数
这个函数的作用是将自由列表中的一组数据块推入一个名为 superStack 的栈中，以便稍后分配给文件或其他需要数据块的部分。

功能：
遍历一组自由数据块的索引，将其依次推入 superStack 栈中。
将这些数据块的索引从自由列表中标记为已使用（通过将相应的索引位置设置为 -1）。
更新全局变量 next_free_list_index，以指向下一组自由数据块。
可能的改进点：
在将数据块推入 superStack 前，应该检查栈是否已满，以避免栈溢出。
在更新 next_free_list_index 之前，应该确保它不会超出数组的索引范围，否则会导致数组越界错误。
2. AllocDataBlock() 函数
这个函数用于从 superStack 栈中分配一个数据块的索引。

功能：
如果 superStack 栈不为空，从栈顶弹出一个数据块的索引。
将 super_stack_number 减一，表示栈中的数据块数量减少了一个。
返回弹出的数据块的索引。
可能的改进点：
在从 superStack 中弹出数据块索引之前，应该检查栈是否为空，以避免尝试从空栈中弹出数据块索引。
总结
这段代码实现了一个简单的数据块管理系统，用于文件系统中的数据存储。然而，它还存在一些潜在的问题需要解决，包括栈溢出和数组越界的风险。因此，建议在使用这些函数之前添加适当的错误检查和边界条件，以确保代码的健壮性和稳定性。



*/