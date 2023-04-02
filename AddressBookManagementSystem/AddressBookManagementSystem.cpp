#include <iostream>
#include <string>
#define MAX 1000
using namespace std;

//��ϵ�˽ṹ��
struct Person {
	string m_name;  //����
	int m_sex;  //�Ա� 1�� 2Ů
	int m_age;  //����
	string m_phone;  //�绰
	string m_address;  //סַ
};

//ͨѶ¼�ṹ��
struct AddressBooks {
	struct Person personArray[MAX];  //ͨѶ¼�б������ϵ������
	int m_size;  //ͨѶ¼�е�ǰ��¼��ϵ�˸���
};

//�˵�����
void showMenu(){
	cout << "***************************" << endl;
	cout << "*****  1�������ϵ��  *****" << endl;
	cout << "*****  2����ʾ��ϵ��  *****" << endl;
	cout << "*****  3��ɾ����ϵ��  *****" << endl;
	cout << "*****  4��������ϵ��  *****" << endl;
	cout << "*****  5���޸���ϵ��  *****" << endl;
	cout << "*****  6�������ϵ��  *****" << endl;
	cout << "*****  0���˳�ͨѶ¼  *****" << endl;
	cout << "***************************" << endl;
}

//1�������ϵ��
void addPerson(AddressBooks * abs) {
	//�ж�ͨѶ¼�Ƿ��������������������
	if (abs->m_size == MAX) {
		cout << "ͨѶ¼�������޷���ӣ�" << endl;
		return;
	}
	else {
		//��Ӿ�����ϵ��
		//����
		string name;
		cout << "������������" << endl;
		cin >> name;
		abs->personArray[abs->m_size].m_name = name;

		//�Ա�
		cout << "�������Ա�" << endl;
		cout << "1--��\t2--Ů" << endl;
		int sex = 0;
		while (true)
		{
			//������1/2�������˳�ѭ������������������������
			cin >> sex;
			if (sex == 1 || sex == 2) {
				abs->personArray[abs->m_size].m_sex = sex;
				break;
			}
			cout << "�����������������룡" << endl;
		}

		//����
		cout << "���������䣺" << endl;
		int age = 0;
		while (true)
		{
			//���������䳬����Χ����������
			cin >> age;
			if (age > 0 && age < 120) {
				abs->personArray[abs->m_size].m_age = age;
				break;
			}
			cout << "�����������������룡" << endl;
		}

		//�绰
		cout << "��������ϵ�绰��" << endl;
		string phone;
		cin >> phone;
		abs->personArray[abs->m_size].m_phone = phone;
		
		//סַ
		cout << "������סַ��" << endl;
		string address;
		cin >> address;
		abs->personArray[abs->m_size].m_address = address;

		//����ͨѶ¼����
		abs->m_size++;
		cout << "��ӳɹ���" << endl;

		system("pause");  //�밴���������
		system("cls");  //��������
		
	}
}

//2����ʾ��ϵ��
void showPerson(AddressBooks * abs) {
	//�ж�ͨѶ¼�Ƿ�Ϊ��
	if (abs->m_size == 0) {
		cout << "��ǰ��¼Ϊ�գ�" << endl;
	}
	else {
		for (int i = 0; i < abs->m_size; i++){
			cout << "������" << abs->personArray[i].m_name
				 << "\t�Ա�" << (abs->personArray[i].m_sex == 1 ? "��" : "Ů")
				 << "\t���䣺" << abs->personArray[i].m_age
				 << "\t��ϵ�绰��" << abs->personArray[i].m_phone
				 << "\t��ַ��" << abs->personArray[i].m_address << endl;
		}
	}
	system("pause");  //�����������
	system("cls");  //��������
}

//�����ϵ���Ƿ���ڣ���������
int isExist(AddressBooks* abs, string name) {
	for (int i = 0; i < abs->m_size; i++)
	{
		if (abs->personArray[i].m_name == name)
			return i;  //�ҵ��򷵻ش����������е��±���
	}
	return -1;  //���������δ�ҵ�������-1
}

//3��ɾ����ϵ��(������)
void deletePerson(AddressBooks * abs) {
	cout << "��������Ҫɾ������ϵ�ˣ�" << endl;
	string name;
	cin >> name;
	int ret = isExist(abs, name);  //ret == -1 δ�鵽

	if (ret != -1) {
		//���ҵ���ϵ�ˣ�����ɾ������
		for (int i = ret; i < abs->m_size-1; i++)
		{
			//����ǰ��
			abs->personArray[i] = abs->personArray[i+1];
		}
		abs->m_size--;  //����ͨѶ¼�еļ�¼��
		cout << "ɾ���ɹ�" << endl;
	}else {
		cout << "���޴���" << endl;
	}
	system("pause");  //�����������
	system("cls");  //��������
}

//4������ָ����ϵ��(������)
void findPerson(AddressBooks * abs) {
	cout << "��������Ҫ���ҵ���ϵ�ˣ�" << endl;
	string name;
	cin >> name;
	//�ж�ָ����ϵ���Ƿ����
	int ret = isExist(abs, name);
	if (ret != -1) {  //�ҵ���ϵ��
		cout << "������" << abs->personArray[ret].m_name
			 << "\t�Ա�" << (abs->personArray[ret].m_sex == 1 ? "��" : "Ů")
			 << "\t���䣺" << abs->personArray[ret].m_age
			 << "\t��ϵ�绰��" << abs->personArray[ret].m_phone
			 << "\tסַ��" << abs->personArray[ret].m_address << endl;
	}
	else {  //δ�ҵ���ϵ��
		cout << "���޴���" << endl;
	}
	system("pause");  //�����������
	system("cls");  //��������
}

//5���޸���ϵ�ˣ���������
void modifyPerson(AddressBooks * abs) {
	cout << "��������Ҫ�޸ĵ���ϵ�ˣ�" << endl;
	string name;
	cin >> name;
	//�ж����޸���ϵ���Ƿ����
	int ret = isExist(abs, name);
	if (ret != -1) {  //���ҵ�������ϵ�˽����޸�
		//����
		string name;
		cout << "������������" << endl;
		cin >> name;
		abs->personArray[ret].m_name = name;

		//�Ա�
		cout << "�������Ա�" << endl;
		cout << "1--��\t2--Ů" << endl;
		int sex = 0;
		while (true)
		{
			//������1/2�������˳�ѭ������������������������
			cin >> sex;
			if (sex == 1 || sex == 2) {
				abs->personArray[ret].m_sex = sex;
				break;
			}
			cout << "�����������������룡" << endl;
		}

		//����
		cout << "���������䣺" << endl;
		int age = 0;
		while (true)
		{
			//���������䳬����Χ����������
			cin >> age;
			if (age > 0 && age < 120) {
				abs->personArray[ret].m_age = age;
				break;
			}
			cout << "�����������������룡" << endl;
		}

		//�绰
		cout << "��������ϵ�绰��" << endl;
		string phone;
		cin >> phone;
		abs->personArray[ret].m_phone = phone;

		//סַ
		cout << "������סַ��" << endl;
		string address;
		cin >> address;
		abs->personArray[ret].m_address = address;

		cout << "�޸ĳɹ���" << endl;
	}else {  //δ���ҵ�
		cout << "���޴���" << endl;
	}
	system("pause");  //�����������
	system("cls");  //��������
}

//6�����������ϵ��
void cleanPerson(AddressBooks* abs) {
	abs->m_size = 0;  //����ϵ��������Ϊ0�����߼���ռ���
	cout << "ͨѶ¼�����" << endl;
	system("pause");  //�����������
	system("cls");  //��������
}

int main() {
	AddressBooks abs;  //����ͨѶ¼�ṹ�����
	abs.m_size = 0;  //��ʼ��ͨѶ¼�е�ǰ��Ա����
	int select = 0;  //�����û�ѡ������ı���

	while (true)
	{
		//�˵��������
		showMenu();

		cin >> select;

		switch (select)
		{
		case 1:  //1�������ϵ��
			addPerson(&abs);  //���õ�ַ���ݣ������޸�ʵ��
			break;
		case 2:  //2����ʾ��ϵ��
			showPerson(&abs);
			break;
		case 3:  //3��ɾ����ϵ��
			deletePerson(&abs);
			break;
		case 4:  //4��������ϵ��
			findPerson(&abs);
			break;
		case 5:  //5���޸���ϵ��
			modifyPerson(&abs);
			break;
		case 6:  //0���˳�ͨѶ¼
			cleanPerson(&abs);
			break;
		case 0:
			cout << "��ӭ�´�ʹ�ã�" << endl;
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