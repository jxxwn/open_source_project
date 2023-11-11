#include<iostream>
#include<string>
using namespace std;

class Kiosk { //Kiosk Class�� queue ����
	int t_number;
	int size;
	int queuemoney = 0;
	string name;
public:
	Kiosk* queue;
	Kiosk();
	Kiosk(int size_in);
	~Kiosk();
	static int AllMoney;
	void Money(int Money, int index);
	void push_drink(string name_in, int table);
};
int Kiosk::AllMoney = 0; //��ü �����
Kiosk::Kiosk(int size_in) {
	this->size = size_in;
	queue = new Kiosk[size];
}
Kiosk::~Kiosk() {
	delete[]queue;
}
void Kiosk::Money(int Money,int index) {
	AllMoney += Money;
	queue[index].queuemoney = Money;
}
void Kiosk::push_drink(string name_in, int table) {
	queue[table].name = name_in;
}

class Menu :public Kiosk {
	int index;
	int price;
	int number;
	string name; 
public:
	Menu(int index_in, string menu_in, int price_in);
	void Menu_list();
	void Menu_select(int table_num_in, Menu& M_selc, int number);
};

Menu::Menu(int index_in, string menu_in, int price_in) {
	this->index = index_in;
	this->name = menu_in;
	this->price = price_in;
}
void Menu::Menu_list() {
	cout << "###### MENU_LIST #####" << endl;
	cout << "Number	Menu	Price" << endl;
	cout << "#1	Ice Americano	\4500" << endl;
	cout << "#2	Ice Latte	\5000" << endl;
	cout << "#3	Ice Tea	\5000" << endl;
	cout << "#4	Chamomile	\6000" << endl;
	cout << "#5	Caramel Macchiato	\6500" << endl;
	cout << "######################" << endl;
	cout << "1. �ֹ��Է�\n2. �ֹ���Ȳ\n3. �ֹ�����\n#####################" << endl;
	cout << "��ȣ�� �Է��Ͻÿ� >> ";
}
void Menu::Menu_select(int table_num_in, Menu& M_selc, int number) {
	int price = 0;
	if (number == 1)
	{
		price = M_selc.price;
		push_drink(M_selc.name, table_num_in-1);
		Money(price, table_num_in - 1);
	}
	
}

int main() 
{
	Menu M[5] = { Menu(1,"Ice Americano",4500),Menu(2,"Ice Latte",5000),Menu(3,"Ice tea",5000),Menu(4,"Chamomile",6000),Menu(5,"Caramel Macchiato",6500) };
	Menu* M_ptr;
	M_ptr = M;
	int select;
	int table_num; //�մ� �̸�
	int number;// �ֹ� ��(���� ����)
	int price; //����
	int cafe_num; //�����ȣ
	string name[10];
	string name_sum;
	Kiosk queue(10);//�ִ� �ֹ� �� 10��, queue ������ 10
	while (1)
	{
		int x = 0;
		M_ptr->Menu_list(); //�޴��� ȣ��
		cin >> select; //��ȣ �Է�
		if (select == 1)
		{
			cout << "���̺� ��ȣ�� �Է����ּ��� >> ";
			cin >> table_num;
			cout << "�� ���� �ֹ��Ͻðڽ��ϱ�? >> ";
			cin >> number; //����
			++x;
			if (number > 1 && number < 11)
			{
				for (int i = 0; i < number; i++)
				{
					cout << "���� ��ȣ�� �޴��� �ۼ����ּ��� >>";
					cin >> cafe_num >> name[i];
					name_sum += name[i];
					M_ptr[cafe_num - 1].Menu_select(table_num, M_ptr[cafe_num - 1], x);
				}
				queue.queue[table_num - 1].push_drink(name_sum, table_num - 1);
			}
			else if (number == 1)
			{
				cout << "���� ��ȣ�� �Է����ּ��� >> ";
				cin >> cafe_num;
				M_ptr[cafe_num - 1].Menu_select(table_num, M_ptr[cafe_num - 1], x);
			}
		}
	}
	
}