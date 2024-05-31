#include "head.h"

void mkdir(string director_name)    // ����Ŀ¼
{

	if (IsFileInCurrentDirector(director_name) != -1)
	{
		cout << "��Ŀ¼���Ѵ�����Ϊ" << director_name << "���ļ�" << endl;
		cout << "�ļ�����ʧ��" << endl;
		return;
	}

	int pos = IsDirectorInCurrentDirector(director_name);
	if (pos != -1)
	{
		cout << "��ǰĿ¼���Ѱ�����Ϊ" << director_name << "���ļ���" << endl;
		cout << "����ʧ��!" << endl;
		return;	
	}
	director temp;
	temp.name = director_name;
	temp.last_director = current_director_index;
	temp.owner = current_user.name;
	temp.id = myFileSystem.vector_director.size();
	myFileSystem.vector_director.push_back(temp);
	
	myFileSystem.vector_director[current_director_index].director_list.push_back(temp.id);
	cout << "����Ŀ¼" << director_name << "�ɹ�" << endl;
	return;
}