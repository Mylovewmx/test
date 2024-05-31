#include "head.h"


void IntoSuperStack()  // free������볬��ջ
{
	for(int i=0;i<INDEX_LIST_LENGTH;i++) // ��������ÿ�����
	{
		int param = myFileSystem.free_list[next_free_list_index][i];// ����������  ʹ�õ�ʱ���С����   ��ʹ�����ó�-1
		// ��һ��Ҫʹ�õ�����  0~INDEX_LIST_NUMBER-1 next_free_list_index
		myFileSystem.superStack.push(param);
		myFileSystem.free_list[next_free_list_index][i] = -1;  //�����õ�������Ϊ-1
	}

	super_stack_number = INDEX_LIST_LENGTH;

	if(next_free_list_index < INDEX_LIST_NUMBER)  // ���û�����һ���+1
	{
		next_free_list_index++;
	}
	
}

int AllocDataBlock()   //�������ݿ�
{
	if(myFileSystem.superStack.empty())
	{
		IntoSuperStack();   // ��free����볬��ջ
	}
	int result = myFileSystem.superStack.top();
	myFileSystem.superStack.pop();
	super_stack_number--;
	return result;

}
/*��δ��뿴������һ���򵥵��ļ�ϵͳ�����ڹ������ݿ�Ĳ��֡�������ϸ����һ�����Ĺ��ܺͿ��ܵĸĽ��㡣

1. IntoSuperStack() ����
��������������ǽ������б��е�һ�����ݿ�����һ����Ϊ superStack ��ջ�У��Ա��Ժ������ļ���������Ҫ���ݿ�Ĳ��֡�

���ܣ�
����һ���������ݿ�������������������� superStack ջ�С�
����Щ���ݿ�������������б��б��Ϊ��ʹ�ã�ͨ������Ӧ������λ������Ϊ -1����
����ȫ�ֱ��� next_free_list_index����ָ����һ���������ݿ顣
���ܵĸĽ��㣺
�ڽ����ݿ����� superStack ǰ��Ӧ�ü��ջ�Ƿ��������Ա���ջ�����
�ڸ��� next_free_list_index ֮ǰ��Ӧ��ȷ�������ᳬ�������������Χ������ᵼ������Խ�����
2. AllocDataBlock() ����
����������ڴ� superStack ջ�з���һ�����ݿ��������

���ܣ�
��� superStack ջ��Ϊ�գ���ջ������һ�����ݿ��������
�� super_stack_number ��һ����ʾջ�е����ݿ�����������һ����
���ص��������ݿ��������
���ܵĸĽ��㣺
�ڴ� superStack �е������ݿ�����֮ǰ��Ӧ�ü��ջ�Ƿ�Ϊ�գ��Ա��Ⳣ�Դӿ�ջ�е������ݿ�������
�ܽ�
��δ���ʵ����һ���򵥵����ݿ����ϵͳ�������ļ�ϵͳ�е����ݴ洢��Ȼ������������һЩǱ�ڵ�������Ҫ���������ջ���������Խ��ķ��ա���ˣ�������ʹ����Щ����֮ǰ����ʵ��Ĵ�����ͱ߽���������ȷ������Ľ�׳�Ժ��ȶ��ԡ�



*/