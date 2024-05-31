#include"head.h"
#include <stdlib.h>
#include <stdio.h>
#include <sec_api/string_s.h>

fileSystem myFileSystem;
int memory_index;
char memory[MAX_FILE_LENGTH][DATA_BLOCK_LENGTH];
int current_director_index;
int next_free_list_index;
int super_stack_number;

void Initialize_dataBlock()  //��ʼ�����ݿ�
{
	for (int i = 0; i < DATA_BLOCK_NUMBER; i++)
	{
		dataBlock temp;
		temp.next = -1;
		temp.used = 0;
		for (int j = 0; j < DATA_BLOCK_LENGTH + 1; j++)
		{
			temp.content[j] = '\0';//��ʱ����������Ϊ0
		}
		myFileSystem.dataArea.push_back(temp);//��vectorβ����������
		
	}
	
	cout << "Successfully   initialized data field��" << endl;
	return;
}


void Initialize_Index_List()  //��ʼ��������
{

	next_free_list_index = 0;
	super_stack_number = 0;
	while (!myFileSystem.superStack.empty())//�������ջ���գ���ջ������ȫ��pop��ȥ
	{
		myFileSystem.superStack.pop();
	}
	for (int i = 0; i < INDEX_LIST_NUMBER; i++)
	{
		for (int j = INDEX_LIST_LENGTH - 1; j >= 0; j--)
		{
			myFileSystem.free_list[i][j] = i * INDEX_LIST_LENGTH + INDEX_LIST_LENGTH - j - 1;
			//cout<<i<<","<<j<<myFileSystem.free_list[i][j]<<endl;
		}
	}
	cout << "Successfully   initialized group chain��" << endl;
	return;
}


void Initialize_User_Info()   // ��ʼ���û���Ϣ
{
	char temp[6];
	strcpy_s(temp, "user");
	for (int i = 0; i < MAX_User_NUMBER; i++)
	{
		temp[4] = (char)i + 49;
		temp[5] = '\0';
		myFileSystem.user_info[i].name = temp;
		myFileSystem.user_info[i].password = temp;
		
	}
	cout << "Successfully   initialized user information!" << endl;
}


void Initialize_Vector_Director()   //��ʼ��Ŀ¼��Ϣ
{
	myFileSystem.vector_director.clear();
	director first;
	first.last_director = -1;
	first.id = 0;
	first.name = "home";
	first.owner = "empty";
	myFileSystem.vector_director.push_back(first);
	cout << "Successfully   initialized directory information!" << endl;
}




void Initialize_Memory()  // ��ʼ���ڴ�
{
	memory_index = 0;
	for (int i = 0; i < MAX_FILE_LENGTH; i++)
	{
		for (int j = 0; j < DATA_BLOCK_LENGTH; j++)
		{
			memory[i][j] = '\0';
		}
	}
	
}


bool Initialize()  // ��ʼ��
{
	

	Initialize_Vector_Director();   // ��ʼ���ļ�����Ϣ

	current_director_index = 0;
	open_file_list.clear();
	myFileSystem.vector_file.clear();

	Initialize_dataBlock();		 // ��ʼ�����ݿ�
	Initialize_Index_List();		// ��ʼ��������
	Initialize_User_Info();			// ��ʼ���û���Ϣ

	print();
	return true;

}



/*��δ������ļ�ϵͳ�ĳ�ʼ�����֣������ļ�ϵͳ�ĸ�����ɲ��ֳ�ʼ��Ϊ��ʼ״̬��

Initialize_dataBlock()
���������ʼ�������ݿ飬���ļ�ϵͳ�����ڴ洢�ļ����ݵĿ顣����ÿ�����ݿ��������գ���������Ϊδʹ��״̬��

Initialize_Index_List()
���������ʼ���˳����������ļ�ϵͳ�����ڹ���������ݿ�������ṹ�����������б��е�ÿ�������ʼ��Ϊ���������ݿ���������������ջ��ա�

Initialize_User_Info()
���������ʼ�����û���Ϣ���������ļ�ϵͳ�е�Ĭ���û���Ϣ��Ĭ������£�ʹ���߱��Ϊ"user1"��"user2"�ȣ�����Ҳ���û�����ͬ��

Initialize_Vector_Director()
���������ʼ����Ŀ¼��Ϣ���������ļ�ϵͳ�ĸ�Ŀ¼ "home"�����������ļ����ļ��е���ʼ�㡣

Initialize_Memory()
���������ʼ�����ڴ棬�������ļ�ϵͳ������������ʱ�洢�ļ����ݡ������ڴ��е�����λ����ա�

Initialize()
��������������������г�ʼ��������������ļ�ϵͳ�������ʼ�����̣�����ӡ����ʼ���ɹ�����Ϣ��

�ܵ���˵����Щ���������ļ�ϵͳ�ĸ�����������Ϊ��ʼ״̬���Ա�������ļ�ϵͳ������



*/