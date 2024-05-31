#include "head.h"
#include <string.h>

bool ParsePath(string path)  // ��·����������
{
	int begin = 0;
	int ending = 0;
	string accessed;  // �Ѿ�����·��
	bool flag = true;  // ��ʾ�Ƿ��ǵ�һ��Ŀ¼
	while (ending < strlen(path.c_str()))
	{
		if (path[ending] == '\\')
		{
			string director = path.substr(begin, ending - begin);
			if (flag)
			{
				if (director != "home")             // ��Ŀ¼������home
				{
					cout << "�����·������ȷ��" << endl;
					cout << "���������·�����磺home\\one\\two" << endl;
					return false;
				}
				accessed += director;
				flag = false;
			}
			else
			{
				if (!ntdir(director))  //����һĿ¼
				{
					cout << "�޷�����" << accessed << "·���µ�" << director << "�ļ���" << endl;
					return false;
				}
				accessed += director;
			}

			begin = ending + 1;
			

		}
		ending++;
	}
	string director = path.substr(begin, ending - begin);
	if (!ntdir(director))
	{
		cout << "�޷�����" << accessed << "·���µ�" << director << "�ļ���" << endl;
		return false;
	}
	cout << "��ת��" << path << "�ɹ���" << endl;
	return true;
}


void CopyDirector(int pos, int limit)   //����pos����Ŀ¼   limit��Ϊ�˷�ֹ �½���Ŀ¼���ظ��½� �������Ҫ�½���Ŀ¼�������ڻ����
	//limit�Ͳ������½���
{
	//��pos��Ŀ¼�����������ļ���ȫ���½�������last_director

	director current = myFileSystem.vector_director[pos];
	director temp;
	temp.id = myFileSystem.vector_director.size();

	temp.name = current.name;
	temp.owner = current.owner;
	temp.last_director = current_director_index;   //����last_director



	list<int>::iterator p = current.file_list.begin();  //�ļ���������ͬ  
	while (p != current.file_list.end())
	{
		temp.file_list.push_back(*p);
		p++;
	}


	myFileSystem.vector_director[current_director_index].director_list.push_back(temp.id);  // �ڵ�ǰĿ¼�м����µ�Ŀ¼
	myFileSystem.vector_director.push_back(temp);//��Ŀ¼��Ϣ�м����µ�Ŀ¼
	current_director_index = temp.id;	//���µ�ǰĿ¼

	p = current.director_list.begin();  // �ڵ�ǰĿ¼����Ŀ¼�м�������
	while (p != current.director_list.end())
	{
		if (*p != -1 && *p < limit)
		{
			CopyDirector(*p, limit);
		}
		p++;
	}


}

bool copy(string name, string path)
{
	int strore_director = current_director_index;  //�ݴ�
	//current_director_index = 0;
	int pos = IsFileInCurrentDirector(name);
	if (pos == -1)
	{
		pos = IsDirectorInCurrentDirector(name);
		if (pos == -1)
		{
			cout << "��ǰĿ¼û��" << name << "���ļ����ļ���" << endl;
			cout << "����ʧ�ܣ�" << endl;
			return false;
		}
		else// ���Ƶ����ļ���
		{
			if (myFileSystem.vector_director[pos].owner != current_user.name && myFileSystem.vector_director[pos].owner != "empty")//��֤Ȩ��
			{
				cout << "��û�в���" << name << "�ļ��е�Ȩ��" << endl;
				cout << "����ʧ��!" << endl;
				return false;
			}

			if (!ParsePath(path))  //��ת��Ҫ���Ƶ���Ŀ¼��
			{
				cout << "����ʧ�ܣ�" << endl;
				return false;
			}
			CopyDirector(pos, myFileSystem.vector_director.size());


		}
	}
	else  // ���Ƶ����ļ�
	{
		if (myFileSystem.vector_file[pos].owner != current_user.name && myFileSystem.vector_file[pos].owner != "empty")//��֤Ȩ��
		{
			cout << "��û�в���" << name << "�ļ��е�Ȩ��" << endl;
			cout << "����ʧ��!" << endl;
			return false;
		}

		if (!ParsePath(path))    //��ת��Ҫ���Ƶ���Ŀ¼��
		{
			cout << "����ʧ�ܣ�" << endl;
			return false;
		}
		myFileSystem.vector_director[current_director_index].file_list.push_back(pos);     //�ڸ�Ŀ¼����Ӷ�Ӧ�ļ�����������
	}

	cout << "���Ƴɹ�!" << endl;
	current_director_index = strore_director;  //�ָ���ǰĿ¼
	return true;
}
/*��δ��뿴������һ���򵥵��ļ����ƹ��ܵ�ʵ�֡�����������һ�������߼��Ϳ��ܵĸĽ��㡣

ParsePath() ����
����������ڽ���·���ַ�����������·�����е�����

���ܣ�
��ͨ�� \ �ָ�·���ַ��������������е�ÿ��Ŀ¼���ơ�
���ÿ��Ŀ¼�����Ƿ���ڣ�����֤·������Ч�ԡ�
���·����Ч��������ɹ���Ϣ�������� true��
���ܵĸĽ��㣺
����·���ָ����Ĵ���������ʹ����Ӳ����ķ�ʽ��ֻ֧�� \ ��Ϊ·���ָ��������ַ�ʽ������Ӧ�ÿ��Ǽ����������ܵ�·���ָ��������� /��
���ַ�������ʱ��ʹ���� strlen() ������ȡ�ַ������ȣ����ַ������� C++ �� std::string ������˵�������ѡ�񣬿���ֱ��ʹ�� path.length() ��ȡ�ַ������ȡ�
CopyDirector() ����
����������ڸ���Ŀ¼��

���ܣ�
����ָ��Ŀ¼����������Ŀ¼���ļ���
����Ŀ¼��Ϣ�������ļ��б����Ŀ¼�б�
�ݹ�ظ���������Ŀ¼��
���ܵĸĽ��㣺
������ʹ����ȫ�ֱ��� current_director_index�������������ܵ��º����Ŀ������Խ��͡����齫����Ϊ�������ݽ�����������ߺ����Ķ����ԺͿ���ֲ�ԡ�
�ڱ���Ŀ¼�б�ʱ��ʹ�����ֶ������������Կ���ʹ�÷�Χѭ���﷨��ʹ�������ࡣ
copy() ����
����������ڸ����ļ���Ŀ¼��

���ܣ�
���ȣ���ͨ�� IsFileInCurrentDirector(name) �� IsDirectorInCurrentDirector(name) ���������Ҫ���ƵĶ����Ƿ�����ڵ�ǰĿ¼�С�
���ݶ�������ͣ��ļ���Ŀ¼����ִ����Ӧ�ĸ��Ʋ�����
�ڸ���Ŀ¼ʱ���������� ParsePath() ����������Ŀ��·��������Ŀ��Ŀ¼�д���������
�ڸ����ļ�ʱ�������ļ���������ӵ�Ŀ��Ŀ¼���ļ��б��С�
���ܵĸĽ��㣺
�����Ĳ����б���û��ָ��·�������ͣ����޷�ȷ�� path ������Ŀ¼·�������ļ�·��������ܵ��µ����ߴ���ؽ��ļ�·�����ݸ��������Ӷ������������Ϊ���������һ������Ĳ�����ָʾ·�������͡�
�ڸ����ļ���Ŀ¼֮ǰ��Ӧ�ü��Ŀ��·���Ƿ���Ч���Ա��⸴�Ƶ������ڵ�Ŀ¼��Ŀ¼Ȩ�޲���������
�ܽ�
��δ���ʵ�����ļ���Ŀ¼�ĸ��ƹ��ܣ����Դ���һЩǱ�ڵĸĽ��㣬��·�����������ԡ�ȫ�ֱ�����ʹ�á�������������Ƶȡ�ͨ���Դ�������ʵ����ع��͸Ľ���������ߴ���Ŀɶ��ԡ���ά���ԺͿ���չ�ԡ�



*/