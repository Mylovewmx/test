#include "head.h"

void dir()
{
	list<int>::iterator director_p = myFileSystem.vector_director[current_director_index].director_list.begin();
	cout << "Ŀ¼�б�:" << endl;
	while (director_p != myFileSystem.vector_director[current_director_index].director_list.end())
	{
		int index = *director_p;
		if (index != -1)      // �������
		{
			cout << myFileSystem.vector_director[index].name << '\t';
		}
		director_p++;
	}
	cout << endl;
	list<int>::iterator file_p = myFileSystem.vector_director[current_director_index].file_list.begin();
	cout << "�ļ��б�:" << endl;
	while (file_p != myFileSystem.vector_director[current_director_index].file_list.end())
	{
		int index = *file_p;
		if (index != -1)  //�������
		{
			cout << myFileSystem.vector_file[index].file_name << '\t';
		}

		file_p++;
	}
	cout << endl;
}
/*
ChatGPT
��δ���ʵ������ʾ��ǰĿ¼�е��ļ�����Ŀ¼�б�Ĺ��ܡ�����������һ�£�

dir() ����
�������������ʾ��ǰĿ¼���ļ�����Ŀ¼�б�

���ȣ���������ǰĿ¼����Ŀ¼�б����ÿ����Ŀ¼�����ơ�
Ȼ����������ǰĿ¼���ļ��б����ÿ���ļ������ơ�
������б�ʱ��ֻ���������Ϊ -1 �����Ϊ -1 ��ʾ������ã��ѱ�ɾ������
���ܵĸĽ��㣺
������б�ʱ�����Կ���ʹ�÷�Χѭ���﷨��ʹ������Ӽ�ࡣ
������������й��ļ�����Ŀ¼����Ϣ�������ļ���С������޸�ʱ��ȣ����ṩ��ȫ�����Ϣ��
���Ƕ�����ĸ�ʽ�����Ż���ʹ��������Ķ�����⣬���������������еȡ�*/