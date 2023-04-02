#include <iostream>
#include <string>
#define MAX 1000
using namespace std;

//联系人结构体
struct Person {
	string m_name;  //姓名
	int m_sex;  //性别 1男 2女
	int m_age;  //年龄
	string m_phone;  //电话
	string m_address;  //住址
};

//通讯录结构体
struct AddressBooks {
	struct Person personArray[MAX];  //通讯录中保存的联系人数组
	int m_size;  //通讯录中当前记录联系人个数
};

//菜单界面
void showMenu(){
	cout << "***************************" << endl;
	cout << "*****  1、添加联系人  *****" << endl;
	cout << "*****  2、显示联系人  *****" << endl;
	cout << "*****  3、删除联系人  *****" << endl;
	cout << "*****  4、查找联系人  *****" << endl;
	cout << "*****  5、修改联系人  *****" << endl;
	cout << "*****  6、清空联系人  *****" << endl;
	cout << "*****  0、退出通讯录  *****" << endl;
	cout << "***************************" << endl;
}

//1、添加联系人
void addPerson(AddressBooks * abs) {
	//判断通讯录是否已满，若满了则不再添加
	if (abs->m_size == MAX) {
		cout << "通讯录已满，无法添加！" << endl;
		return;
	}
	else {
		//添加具体联系人
		//姓名
		string name;
		cout << "请输入姓名：" << endl;
		cin >> name;
		abs->personArray[abs->m_size].m_name = name;

		//性别
		cout << "请输入性别：" << endl;
		cout << "1--男\t2--女" << endl;
		int sex = 0;
		while (true)
		{
			//若输入1/2，可以退出循环；若输入有误，则重新输入
			cin >> sex;
			if (sex == 1 || sex == 2) {
				abs->personArray[abs->m_size].m_sex = sex;
				break;
			}
			cout << "输入有误，请重新输入！" << endl;
		}

		//年龄
		cout << "请输入年龄：" << endl;
		int age = 0;
		while (true)
		{
			//若输入年龄超出范围则重新输入
			cin >> age;
			if (age > 0 && age < 120) {
				abs->personArray[abs->m_size].m_age = age;
				break;
			}
			cout << "输入有误，请重新输入！" << endl;
		}

		//电话
		cout << "请输入联系电话：" << endl;
		string phone;
		cin >> phone;
		abs->personArray[abs->m_size].m_phone = phone;
		
		//住址
		cout << "请输入住址：" << endl;
		string address;
		cin >> address;
		abs->personArray[abs->m_size].m_address = address;

		//更新通讯录人数
		abs->m_size++;
		cout << "添加成功！" << endl;

		system("pause");  //请按任意键继续
		system("cls");  //清屏操作
		
	}
}

//2、显示联系人
void showPerson(AddressBooks * abs) {
	//判断通讯录是否为空
	if (abs->m_size == 0) {
		cout << "当前记录为空！" << endl;
	}
	else {
		for (int i = 0; i < abs->m_size; i++){
			cout << "姓名：" << abs->personArray[i].m_name
				 << "\t性别：" << (abs->personArray[i].m_sex == 1 ? "男" : "女")
				 << "\t年龄：" << abs->personArray[i].m_age
				 << "\t联系电话：" << abs->personArray[i].m_phone
				 << "\t地址：" << abs->personArray[i].m_address << endl;
		}
	}
	system("pause");  //按任意键继续
	system("cls");  //清屏操作
}

//检查联系人是否存在（按姓名）
int isExist(AddressBooks* abs, string name) {
	for (int i = 0; i < abs->m_size; i++)
	{
		if (abs->personArray[i].m_name == name)
			return i;  //找到则返回此人在数组中的下标编号
	}
	return -1;  //若遍历结果未找到，返回-1
}

//3、删除联系人(按姓名)
void deletePerson(AddressBooks * abs) {
	cout << "请输入您要删除的联系人：" << endl;
	string name;
	cin >> name;
	int ret = isExist(abs, name);  //ret == -1 未查到

	if (ret != -1) {
		//查找到联系人，进行删除操作
		for (int i = ret; i < abs->m_size-1; i++)
		{
			//数据前移
			abs->personArray[i] = abs->personArray[i+1];
		}
		abs->m_size--;  //更新通讯录中的记录数
		cout << "删除成功" << endl;
	}else {
		cout << "查无此人" << endl;
	}
	system("pause");  //按任意键继续
	system("cls");  //清屏操作
}

//4、查找指定联系人(按姓名)
void findPerson(AddressBooks * abs) {
	cout << "请输入您要查找的联系人：" << endl;
	string name;
	cin >> name;
	//判断指定联系人是否存在
	int ret = isExist(abs, name);
	if (ret != -1) {  //找到联系人
		cout << "姓名：" << abs->personArray[ret].m_name
			 << "\t性别：" << (abs->personArray[ret].m_sex == 1 ? "男" : "女")
			 << "\t年龄：" << abs->personArray[ret].m_age
			 << "\t联系电话：" << abs->personArray[ret].m_phone
			 << "\t住址：" << abs->personArray[ret].m_address << endl;
	}
	else {  //未找到联系人
		cout << "查无此人" << endl;
	}
	system("pause");  //按任意键继续
	system("cls");  //清屏操作
}

//5、修改联系人（按姓名）
void modifyPerson(AddressBooks * abs) {
	cout << "请输入您要修改的联系人：" << endl;
	string name;
	cin >> name;
	//判断所修改联系人是否存在
	int ret = isExist(abs, name);
	if (ret != -1) {  //查找到，对联系人进行修改
		//姓名
		string name;
		cout << "请输入姓名：" << endl;
		cin >> name;
		abs->personArray[ret].m_name = name;

		//性别
		cout << "请输入性别：" << endl;
		cout << "1--男\t2--女" << endl;
		int sex = 0;
		while (true)
		{
			//若输入1/2，可以退出循环；若输入有误，则重新输入
			cin >> sex;
			if (sex == 1 || sex == 2) {
				abs->personArray[ret].m_sex = sex;
				break;
			}
			cout << "输入有误，请重新输入！" << endl;
		}

		//年龄
		cout << "请输入年龄：" << endl;
		int age = 0;
		while (true)
		{
			//若输入年龄超出范围则重新输入
			cin >> age;
			if (age > 0 && age < 120) {
				abs->personArray[ret].m_age = age;
				break;
			}
			cout << "输入有误，请重新输入！" << endl;
		}

		//电话
		cout << "请输入联系电话：" << endl;
		string phone;
		cin >> phone;
		abs->personArray[ret].m_phone = phone;

		//住址
		cout << "请输入住址：" << endl;
		string address;
		cin >> address;
		abs->personArray[ret].m_address = address;

		cout << "修改成功！" << endl;
	}else {  //未查找到
		cout << "查无此人" << endl;
	}
	system("pause");  //按任意键继续
	system("cls");  //清屏操作
}

//6、清空所有联系人
void cleanPerson(AddressBooks* abs) {
	abs->m_size = 0;  //将联系人数量置为0，做逻辑清空即可
	cout << "通讯录已清空" << endl;
	system("pause");  //按任意键继续
	system("cls");  //清屏操作
}

int main() {
	AddressBooks abs;  //创建通讯录结构体变量
	abs.m_size = 0;  //初始化通讯录中当前人员个数
	int select = 0;  //创建用户选择输入的变量

	while (true)
	{
		//菜单界面调用
		showMenu();

		cin >> select;

		switch (select)
		{
		case 1:  //1、添加联系人
			addPerson(&abs);  //利用地址传递，可以修改实参
			break;
		case 2:  //2、显示联系人
			showPerson(&abs);
			break;
		case 3:  //3、删除联系人
			deletePerson(&abs);
			break;
		case 4:  //4、查找联系人
			findPerson(&abs);
			break;
		case 5:  //5、修改联系人
			modifyPerson(&abs);
			break;
		case 6:  //0、退出通讯录
			cleanPerson(&abs);
			break;
		case 0:
			cout << "欢迎下次使用！" << endl;
			system("pause");
			return 0;
			break;
		default:
			break;
		}
	}


	system("pause");
	return 0;
}