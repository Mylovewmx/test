#include "head.h"



void ltdir()  // ǰ����һ��Ŀ¼
{
	int index = myFileSystem.vector_director[current_director_index].last_director;
	if (index != -1)
	{
		current_director_index = index;
	}
	else
	{
		cout << "���Ѿ��ڸ�Ŀ¼�У�����������" << endl;
	}
}
/*
ChatGPT
ltdir �������ڽ���ǰĿ¼�л�����һ��Ŀ¼�������Ȼ�ȡ��ǰĿ¼����һ��Ŀ¼��������Ȼ�����Ƿ������һ��Ŀ¼��������ڣ�������ǰĿ¼��������Ϊ��һ��Ŀ¼���������Ӷ�ʵ���л�����һ��Ŀ¼�������������һ��Ŀ¼������ǰĿ¼�Ѿ��Ǹ�Ŀ¼�����������ʾ��Ϣ��ʾ�޷��������л���


*/