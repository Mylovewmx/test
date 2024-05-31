
#include "head.h"
#include <windows.h>
#include <chrono>
#include <ctime>
#include <cstdint>


void print()
{
	cout << "------------------------------------------------------------------------------------------------------------------------\n" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------\n" << endl;
}


void MainPage()   // ��ҳ��Ϣ
{
	auto now = std::chrono::system_clock::now();

	// ����ǰʱ��ת��Ϊ std::time_t ����
	//std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	cout << "-----------------------------------------------------------------------------------------------------------------------\n" << endl;
	cout << "--------------------------------------------------------command list---------------------------------------------------\n";
	cout << "||                                    close file_name----------------�ر��ļ�                                        ||\n";
	cout << "||                                    copy name des_director_name----�����ļ���ָ��Ŀ¼������·����                  ||\n";
	cout << "||                                    create file_name---------------�����ļ�                                        ||\n";
	cout << "||                                    deldir director_name-----------ɾ���ļ���                                      ||\n";
	cout << "||                                    delfile file_name--------------ɾ���ļ�                                        ||\n";
	cout << "||                                    dir----------------------------��ʾ��ǰĿ¼�е���Ŀ¼���ļ�                    ||\n";
	cout << "||                                    initi--------------------------��ʽ���ļ�ϵͳ                                  ||\n";
	cout << "||                                    ini director_name--------------��ʽ���ļ���                                    ||\n";
	cout << "||                                    logout-------------------------���������˳�ϵͳ                              ||\n";
	cout << "||                                    ltdir -------------------------������һ��Ŀ¼                                  ||\n";
	cout << "||                                    mkdir director_name------------����Ŀ¼                                        ||\n";
	cout << "||                                    ntdir director_name------------������һ��Ŀ¼                                  ||\n";
	cout << "||                                    open file_name-----------------���ļ�                                        ||\n";
	cout << "||                                    read file_name-----------------���ļ�                                          ||\n";
	cout << "||                                    rename old_name new_name-------������                                          ||\n";
	cout << "||                                    write file_name content--------д�ļ�                                          ||\n";
	cout << "||                                    wrmore file_name content time--���ļ�д��ͬһ���ݶ��                          ||\n";
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	// �����ǰʱ��
	//std::cout << "\t"<<std::ctime(&now_c);

}

void CurrentDirector()   // ��ʾ��ǰĿ¼
{
	stack<int> temp;
	director temp_director = myFileSystem.vector_director[current_director_index];
	while (temp_director.last_director != -1)
	{
		temp.push(temp_director.id);
		temp_director = myFileSystem.vector_director[temp_director.last_director];
	}
	temp.push(temp_director.id);
	while (!temp.empty())
	{
		int index = temp.top();
		cout << myFileSystem.vector_director[index].name << ">";
		temp.pop();
	}
	cout << "$";
}

void main()
{
	//Initialize_Root_Path();
	string command;
	system("color 0E");
	char ch;

	while (1)
	{
		cout << "------------------------------------------------------------------------------------------------------------------------\n" << endl;
    	//cout << "                            �Ƿ��ʼ���ļ�ϵͳ������ʼ������֮ǰ����Ϣ����ʧ!  Y/N" << endl;
		cout << "                            Do you want to initialize the system?  Y/N" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------\n" << endl;
		cin >> ch;
		if (ch == 'Y' || ch == 'y')
		{
			Initialize();
			break;
		}
		else
		{
			if (ch == 'N' || ch == 'n')
			{
				if (Load())   // ���ѳ�ʼ��
				{
					break;
				}

			}
			else
			{
				cout << "Error!Please re-enter.  Y/N" << endl;

			}
		}
		//print();
	}
	

	if (LoginIn())
	{
		//cout << "��½�ɹ�����ӭ����" << current_user.name << endl;
		cout << "Login successfully! Welcome��" << current_user.name << endl;
	}
	else
	{
		cout << "��������ε�¼ʧ�ܣ���ϵͳ�Զ��ر�" << endl;
		cout << "��������˳�" << endl;
		system("pause");
		exit(0);
	}

	MainPage();

	while (true)
	{
		//print();
		CurrentDirector();   // ��ʾ��ǰĿ¼
		cin >> command;
		string param;

		if (command == "mkdir")
		{
			cin >> param;
			mkdir(param);
			continue;
		}
		if (command == "dir")
		{
			dir();
			continue;
		}
		if (command == "ntdir")
		{
			cin >> param;
			ntdir(param);
			continue;
		}
		if (command == "ltdir")
		{
			ltdir();
			continue;
		}
		if (command == "create")
		{
			cin >> param;
			create(param);
			continue;
		}
		if (command == "delfile")
		{
			cin >> param;
			delfile(param);
			continue;
		}
		if (command == "deldir")
		{
			cin >> param;
			deldir(param);
			continue;
		}
		if (command == "write")
		{
			cin >> param;
			string temp;
			cin >> temp;
			write(param, temp);
			continue;
		}
		if (command == "wrmore")
		{
			cin >> param;
			string temp_1;
			cin >> temp_1;
			int temp_2;
			cin >> temp_2;
			wrmore(param, temp_1, temp_2);
			continue;
		}
		if (command == "open")
		{
			cin >> param;
			open(param);
			continue;
		}
		if (command == "read")
		{
			cin >> param;
			read(param);
			continue;
		}
		if (command == "close")
		{
			cin >> param;
			close(param);
			continue;
		}
		if (command == "logout")
		{
			LoginOut();
			system("pause");
			exit(0);
		}
		bool initi(string director_name);  // ��ʽ���ļ���
		if (command == "initi")
		{
			Initialize();
			continue;
		}
		if (command == "rename")
		{
			cin >> param;
			string str;
			cin >> str;
			rename(param, str);
			continue;
		}
		if (command == "ini")
		{
			cin >> param;
			initi(param);
			continue;
		}
		if (command == "copy")
		{
			cin >> param;
			string str;
			cin >> str;
			copy(param, str);
			continue;
		}
		cout << "����ָ�����������" << endl;
		while (1)    
		{
			char ch;
			ch = getchar();
			if (ch == '\n')
			{
				break;
			}
		}
	}

	system("pause");


}