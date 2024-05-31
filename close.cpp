#include "head.h"


bool close(string file_name)
{
	int pos = IsFileInCurrentDirector(file_name);

	if (pos == -1)
	{
		cout << "��ǰĿ¼������" << file_name << "�ļ�" << endl;
		cout << "���ļ�ʧ�ܣ�" << endl;
		return false;
	}


	list<openFile>::iterator open_file_p = IsInOpenFileList(pos);
	if (open_file_p == open_file_list.end())   // ����ļ��Ƿ��Ѵ�
	{
		cout << "���ļ���δ�򿪣��޷��ر�" << endl;
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
	open_file_list.erase(open_file_p);   //�Ӵ�������ɾ��
	cout << "�ر��ļ�" << file_name << "�ɹ�" << endl;
	return true;

}
/*��δ��뿴���������ڹر��ļ��Ĺ��ܡ�����������һ�������߼��Ϳ��ܵĸĽ��㡣

close() ����
�����������һ���ļ�����Ϊ���������ڹرո��ļ���

���ܣ�
���ȣ������� IsFileInCurrentDirector(file_name) ������鵱ǰĿ¼���Ƿ����ָ�����ļ�������ļ������ڣ������������Ϣ������ false��
����ļ����ڣ����������ļ��Ƿ��Ѿ����򿪣�ͨ������ IsInOpenFileList(pos) ���������� pos ���ļ����ļ�ϵͳ�е�λ�á�
����ļ���δ�򿪣������������Ϣ������ false��
����ļ��Ѿ��򿪣���������ļ����ڴ��е����ݣ�����Ӧ���ڴ����Ϊ���ַ� '\0'��
Ȼ�����Ӵ��ļ��б���ɾ�����ļ���
�������ر��ļ��ɹ�����Ϣ������ true��
���ܵĸĽ��㣺
������ļ�����֮ǰ��Ӧ��ȷ���ļ��Ѿ����򿪣��Ա�����δ�򿪵�����������Ч���ڴ档
�ڱ����ļ����ݿ鲢�������ʱ��Ӧ����ȷ�ؿ���ѭ���߽磬�Ա���Խ������ڴ档
�ڴӴ��ļ��б���ɾ���ļ�֮ǰ��Ӧ��ȷ���ļ��Ѿ����򿪲����ڴ��ļ��б��У��Ա�������ɾ�������ļ���
����ļ��������ڴ��ļ��б��У��������Ҫ���һ��������Ϣ����Ϊ�ر��ļ����������ǲ���Ҫ�ģ������ļ�ȷʵ�����ڸ��б��С�
�ܽ�
��δ���ʵ���˹ر��ļ��Ĺ��ܣ�����Ҫע��ȷ����ִ�в���ǰ���б�Ҫ�ļ�飬�Ա���Ǳ�ڵĴ�������������ͨ������ʵ��Ĵ�����ͱ߽�������������ߴ�����Ƚ��Ժͽ�׳�ԡ�*/