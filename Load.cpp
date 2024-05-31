#include "head.h"
#include <stdio.h>
#include <sec_api/string_s.h>
// ����˳����� ����ĸ�ʽ


const int BUFF_LENGTH = 513;
char change[BUFF_LENGTH];




bool LoadVectorDirector(FILE* fd, int director_num)  //����Ŀ¼��Ϣ
{

	for (int i = 0; i < director_num; i++)
	{
		director temp;
		fscanf_s(fd, "%d%s", &temp.id, change, BUFF_LENGTH);
		temp.name = change;
		fscanf_s(fd, "%s", change, BUFF_LENGTH);
		temp.owner = change;
		fscanf_s(fd, "%d", &temp.last_director);
		int direcotor_count;
		fscanf_s(fd, "%d", &direcotor_count);
		while (direcotor_count--)       // ���������Ŀ¼����
		{
			int director_index;
			fscanf_s(fd, "%d", &director_index);
			temp.director_list.push_back(director_index);
		}
		int file_count;
		fscanf_s(fd, "%d", &file_count);
		while (file_count--)              // ����������ļ�����
		{
			int file_index;
			fscanf_s(fd, "%d", &file_index);
			temp.file_list.push_back(file_index);
		}
		myFileSystem.vector_director.push_back(temp);
	}
	
	cout << "Successfully   loaded directory information." << endl;
	return true;
}


bool LoadVectorFile(FILE* fd, int file_num)  //�����ļ���Ϣ
{
	while (file_num--)
	{
		file temp;
		fscanf_s(fd, "%d%s", &temp.id, change, BUFF_LENGTH);
		temp.file_name = change;
		fscanf_s(fd, "%d%s", &temp.beginning_in_dataArea, change, BUFF_LENGTH);
		temp.owner = change;
		fscanf_s(fd, "%d%d", &temp.file_length, &temp.begining_in_memory);
		myFileSystem.vector_file.push_back(temp);
	}
	
	cout << "Successfully   loaded file information." << endl;
	return true;
}



bool LoadUserInfo(FILE* fd)    // �����û���Ϣ
{
	for (int i = 0; i < MAX_User_NUMBER; i++)
	{
		user* temp = &myFileSystem.user_info[i];
		fscanf_s(fd, "%s", change, BUFF_LENGTH);
		(*temp).name = change;
		fscanf_s(fd, "%s", change, BUFF_LENGTH);
		(*temp).password = change;
	}
	
	cout << "Successfully   loaded user information." << endl;
	return true;
}


bool LoadFreeList(FILE* fd)   // ���س�����
{
	for (int i = 0; i < INDEX_LIST_NUMBER; i++)
	{
		for (int j = 0; j < INDEX_LIST_LENGTH; j++)
		{
			fscanf_s(fd, "%d", &myFileSystem.free_list[i][j]);
			//cout<<"������"<<myFileSystem.free_list[i][j]<<endl;
		}
	}
	
	cout << "Successfully   loaded group chain information." << endl;
	return true;
}

bool LoadSuperStack(FILE* fd)  // ���س���ջ��Ϣ
{
	fscanf_s(fd, "%d %d", &next_free_list_index, &super_stack_number);
	int temp = super_stack_number;
	while (temp--)
	{
		int value;
		fscanf_s(fd, "%d", &value);
		myFileSystem.superStack.push(value);
	}
	
	cout << "Successfully   loaded super stack information." << endl;
	return true;
}


bool LoadDataArea(FILE* fd)  //������������Ϣ
{
	for (int i = 0; i < DATA_BLOCK_NUMBER; i++)
	{
		int is_null;
		fscanf_s(fd, "%d", &is_null);
		dataBlock* temp = (dataBlock*)malloc(sizeof(dataBlock));
		fscanf_s(fd, "%d%d", &(*temp).next, &(*temp).used);
		if (is_null == 0)    // ������ݲ��գ��������
		{
			fscanf_s(fd, "%s", change, BUFF_LENGTH);
			strcpy_s((*temp).content, change);
		}
		else  // ���ݿ���ֱ�Ӹ�ֵ
		{
			for (int j = 0; j < DATA_BLOCK_NUMBER + 1; j++)
			{
				(*temp).content[j] = '\0';
			}
		}

		
		myFileSystem.dataArea.push_back(*temp);
	}
	
	cout << "Successfully   loaded data domain information." << endl;
	return true;
}

bool Load()
{
	
	FILE* fd;
	if (fopen_s(&fd, root_path.c_str(), "r") != 0)
	{
		cout << "��δ�����ļ�ϵͳ�����ȳ�ʼ��!" << endl;
		return false;
	}

	Initialize_Memory();

	int director_num;
	fscanf_s(fd, "%d", &director_num);
	LoadVectorDirector(fd, director_num);
	int file_num;
	fscanf_s(fd, "%d", &file_num);
	LoadVectorFile(fd, file_num);
	LoadUserInfo(fd);
	LoadFreeList(fd);
	LoadSuperStack(fd);
	LoadDataArea(fd);
	current_director_index = 0;
	memory_index = 0;

	cout << "Successfully   loaded file system." << endl;
	fclose(fd);
	print();
	return true;


}
/*��δ���ʵ�����ļ�ϵͳ�ļ��ع��ܣ����ļ�ϵͳ�ĸ�����ɲ��ִ��ļ��ж�ȡ�����ص��ڴ��С�

LoadVectorDirector(FILE* fd, int director_num)
����������ڼ���Ŀ¼��Ϣ�������ļ��ж�ȡĿ¼�ĸ������ԣ���������ӵ��ļ�ϵͳ��Ŀ¼�����С�

LoadVectorFile(FILE* fd, int file_num)
����������ڼ����ļ���Ϣ�������ļ��ж�ȡ�ļ��ĸ������ԣ���������ӵ��ļ�ϵͳ���ļ������С�

LoadUserInfo(FILE* fd)
����������ڼ����û���Ϣ�������ļ��ж�ȡ�û����û��������룬��������ӵ��ļ�ϵͳ���û���Ϣ�����С�

LoadFreeList(FILE* fd)
����������ڼ��س�������Ϣ�������ļ��ж�ȡÿ�������б�����ݣ���������ӵ��ļ�ϵͳ�ĳ����������С�

LoadSuperStack(FILE* fd)
����������ڼ��س���ջ��Ϣ�������ļ��ж�ȡ����ջ�����ݣ���������ӵ��ļ�ϵͳ�ĳ���ջ�С�

LoadDataArea(FILE* fd)
����������ڼ�����������Ϣ�������ļ��ж�ȡÿ�����ݿ�����ݣ���������ӵ��ļ�ϵͳ�������������С�

Load()
��������������������м��غ�����������ļ�ϵͳ�ļ��ع��̡����ȴ��ļ���Ȼ���𲽼����ļ�ϵͳ�ĸ������֣����ر��ļ���������ɺ����õ�ǰĿ¼Ϊ��Ŀ¼���ڴ�����Ϊ0������ӡ���سɹ�����Ϣ��

�ܵ���˵����Щ����������ļ��ж�ȡ���ݣ���������ص��ļ�ϵͳ�У��Ա�������ļ�ϵͳ������



*/