#include "head.h"

user current_user;

bool CheckUser(string name, string password) // �����û��Ƿ��ǳ�ʼ�����û�
{
	for (int i = 0; i < MAX_User_NUMBER; i++)
	{
		if (myFileSystem.user_info[i].name == name && myFileSystem.user_info[i].password == password)
		{
			return true;
		}

	}
	return false;
}

bool LoginIn()    //��¼ģ��
{

	int chance = 5;
	string name;
	string password;
	while (chance > 0)
	{
		
		cout << "Please enter your username:";
		cin >> name;
		
		cout << "Please enter your password:";
		cin >> password;
		if (CheckUser(name, password))
		{
			current_user.name = name;
			current_user.password = password;
			return true;
		}
		else
		{
			
			cout << "Incorrect username or password, you still have" << --chance << "chance(s)" << endl;
			print();
		}
	}
	return false;


}//dongle
/*CheckUser ���������ļ�ϵͳ�д洢���û���Ϣ������֤�ṩ���û����������Ƿ����κ��ѳ�ʼ�����û�ƥ�䡣����ҵ�ƥ����򷵻� true�����򷵻� false��

LoginIn �����ṩ��һ����¼���棬�û������������������ǵ��û��������롣�������û��ж�� 5 �λ�����������ȷ��ƾ�ݡ�����������κ��ѳ�ʼ�����û�ƥ�䣬��ȫ�ֱ��� current_user ����Ϊ�ѵ�¼���û������� true������û��ڸ����Ļ�����δ�ܳɹ���¼���򷵻� false��

�ܵ���˵����Щ�������ļ�ϵͳ��ʵ�����û������֤�͵�¼���ܡ�*/

