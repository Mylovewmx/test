#include "head.h"

int IsFileInCurrentDirector(string file_name)   // �ж�һ�ļ����Ƿ�����ڵ�ǰĿ¼�����ļ���  �����ڷ��ض�Ӧ������ �����ڷ���-1
{
	list<int>::iterator p = myFileSystem.vector_director[current_director_index].file_list.begin();
	while (p != myFileSystem.vector_director[current_director_index].file_list.end())
	{
		int index = *p;
		if (index != -1 && myFileSystem.vector_file[index].file_name == file_name)
		{

			return index;
		}
		p++;
	}

	return -1;
}

int IsDirectorInCurrentDirector(string file_name)  // �ж�һ�ļ����Ƿ���ڵĵ�ǰĿ¼����Ŀ¼��
{
	bool flag = false;
	list<int>::iterator p = myFileSystem.vector_director[current_director_index].file_list.begin();

	p = myFileSystem.vector_director[current_director_index].director_list.begin();
	while (p != myFileSystem.vector_director[current_director_index].director_list.end())
	{
		int index = *p;
		if (index != -1 && myFileSystem.vector_director[index].name == file_name)
		{

			return *p;
		}
		p++;
	}
	return -1;
}

bool IsDataAreaFull()   // �ж��������Ƿ�����
{
	if (myFileSystem.superStack.empty() && myFileSystem.free_list[INDEX_LIST_NUMBER - 1][0] == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool create(string file_name)         // �����ļ�
{
	if (IsFileInCurrentDirector(file_name) != -1)
	{
		cout << "��Ŀ¼���Ѵ�����Ϊ" << file_name << "���ļ�" << endl;
		cout << "�ļ�����ʧ��" << endl;
		return false;
	}

	if (IsDirectorInCurrentDirector(file_name) != -1)
	{
		cout << "��Ŀ¼���Ѵ�����Ϊ" << file_name << "���ļ���" << endl;
		cout << "�ļ�����ʧ��" << endl;
		return false;
	}

	if (IsDataAreaFull())
	{
		cout << "������������û���㹻�ռ䴴���ļ�" << endl;
		return false;
	}

	file temp;
	temp.id = myFileSystem.vector_file.size();
	temp.file_length = 1;
	temp.owner = current_user.name;
	temp.file_name = file_name;
	temp.begining_in_memory = 0;
	temp.beginning_in_dataArea = AllocDataBlock();
	cout << "���ļ�����������ݿ���ǣ�" << temp.beginning_in_dataArea << endl;
	myFileSystem.vector_file.push_back(temp);
	myFileSystem.vector_director[current_director_index].file_list.push_back(temp.id);
	return true;

}
/*��δ�������˼�����������Ҫ�����ļ�ϵͳ�е��ļ���Ŀ¼����������һ������

1. IsFileInCurrentDirector() ����
����������ڼ��ָ���ļ����Ƿ�����ڵ�ǰĿ¼�����ļ��б��С�

������ǰĿ¼�����ļ��б���һ�Ƚ��ļ�����
����ҵ�ƥ����ļ������򷵻ظ��ļ����ļ��б��е�������
���δ�ҵ�ƥ����ļ������򷵻� -1����ʾ�ļ��������ڵ�ǰĿ¼��
2. IsDirectorInCurrentDirector() ����
����������ڼ��ָ��Ŀ¼���Ƿ�����ڵ�ǰĿ¼����Ŀ¼�б��С�

������ǰĿ¼����Ŀ¼�б���һ�Ƚ�Ŀ¼����
����ҵ�ƥ���Ŀ¼�����򷵻ظ�Ŀ¼��Ŀ¼�б��е�������
���δ�ҵ�ƥ���Ŀ¼�����򷵻� -1����ʾĿ¼�������ڵ�ǰĿ¼��
3. IsDataAreaFull() ����
����������ڼ���������Ƿ�������

�������ջΪ�������һ��������ĵ�һ������Ϊ -1������Ϊ���������������� true��
���򣬷��� false����ʾ���������пռ���á�
4. create() ����
����������ڴ����ļ���

���ȣ�����鵱ǰĿ¼���Ƿ����ͬ���ļ���Ŀ¼��������ڣ������������Ϣ������ false��
���ţ�������������Ƿ���������������������������Ϣ������ false��
���������һ�����ļ�����������ӵ��ļ��б�͵�ǰĿ¼���ļ��б��С�
���ܵĸĽ��㣺
�� create() �����У������� AllocDataBlock() �������ݿ�ʱ��Ӧ�ü������Ƿ�ɹ����������ʧ�ܣ���Ӧ�ûع�֮ǰ�Ĳ������Ա����ļ�ϵͳ״̬��һ�¡�
�� IsFileInCurrentDirector() �� IsDirectorInCurrentDirector() �����У�ѭ�������б�ʱ�����Կ���ʹ�÷�Χѭ���﷨��ʹ�������ࡣ
���� create() ������������Ҫ����Ĵ�������ƣ������ڴ����ļ�ʱ���Ȩ�޻��ļ�������Ч�Եȡ�


*/