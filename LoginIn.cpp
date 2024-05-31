#include "head.h"

user current_user;

bool CheckUser(string name, string password) // 检查该用户是否是初始化的用户
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

bool LoginIn()    //登录模块
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
/*CheckUser 函数遍历文件系统中存储的用户信息，以验证提供的用户名和密码是否与任何已初始化的用户匹配。如果找到匹配项，则返回 true；否则返回 false。

LoginIn 函数提供了一个登录界面，用户可以在其中输入他们的用户名和密码。它允许用户有多达 5 次机会来输入正确的凭据。如果输入与任何已初始化的用户匹配，则将全局变量 current_user 设置为已登录的用户并返回 true。如果用户在给定的机会内未能成功登录，则返回 false。

总的来说，这些函数在文件系统中实现了用户身份验证和登录功能。*/

