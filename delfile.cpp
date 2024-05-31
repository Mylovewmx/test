#include "head.h"

// ɾ���ļ���ʱ�򣬲����ǰ� myFileSystem.file_list�е��ļ�ɾ����ֻ�ǽ���id�ĳ�-1������ǣ���ʾ�����á����ɾ������Ӧ�������ṹ��ȫ���ˡ�

bool delfile(string file_name) //ɾ���ļ�
{

	int pos = IsFileInCurrentDirector(file_name);
	if (pos == -1)
	{
		cout << "��ǰĿ¼�в��������ļ���ɾ��ʧ��" << endl;
		return false;
	}

	if (myFileSystem.vector_file[pos].owner != current_user.name && myFileSystem.vector_file[pos].owner != "empty")
	{
		cout << "��û�и��ļ��еĲ���Ȩ��!" << endl;
		return false;
	}

	list<int>::iterator p_list = myFileSystem.vector_director[current_director_index].file_list.begin();
	while (p_list != myFileSystem.vector_director[current_director_index].file_list.end())
	{
		int index = *p_list;
		if (index != -1 && myFileSystem.vector_file[index].file_name == file_name)
		{
			*p_list = -1;   // ��ʾΪ������
			ReleaseDataBlock(index);
			break;
		}
		p_list++;
	}


	cout << "ɾ���ļ�" << file_name << "�ɹ�" << endl;
	return true;
}
/*
ChatGPT
��δ���ʵ����ɾ���ļ��Ĺ��ܡ���������ϸ����һ�£�

delfile() ����
�����������ɾ���ļ���

���ȣ�����鵱ǰĿ¼���Ƿ����ָ�����Ƶ��ļ����Լ���ǰ�û��Ƿ���ɾ��Ȩ�ޡ�
����ļ��������û���Ȩ�ޣ��������ǰĿ¼���ļ��б��ҵ�ƥ����ļ���������������Ϊ -1����ʾ�ļ������á�
Ȼ�󣬵��� ReleaseDataBlock() �����ͷ��ļ�ռ�õ����ݿ顣
������ɾ���ɹ�����Ϣ�������� true��
���ܵĸĽ��㣺
��ɾ���ļ�֮ǰ��Ӧ�ü���ļ���������Ч�ԣ��Ա�����������Ч�����µĴ���
���ͷ����ݿ�֮ǰ��Ӧ��ȷ���ļ�ȷʵռ�������ݿ飬�Ա��������ͷ�δ��ռ�õ����ݿ顣
�ں��������һЩ��������ƣ������ڱ����ļ��б�ʱ����������Ƿ���Ч���Լ����û��Ĳ��������Ѻõ���ʾ��

*/