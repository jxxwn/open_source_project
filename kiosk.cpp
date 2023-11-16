#include<iostream>
#include<string>

using namespace std;

class Kiosk { //Kiosk Class�� queue ����
	int t_number;
	int size;
	string name;
public:
	int queuemoney = 0;
	Kiosk* queue;
	Kiosk();
	Kiosk(int size_in);
	~Kiosk();
	static int AllMoney;
	static int front; //front : queue�� �� ��Ҹ� ����Ŵ
	static int rear; //rear : queue ������ ��� ����Ŵ
	static int real_size; //queue ���� ������
	void Money(int Money, int index);
	void push_drink(string name_in, int table);
	void show(); //���� �ֹ� ��Ȳ real_size�� �̿��ϱ�
	string bring_menu();
	bool Menu_payment(char check_in, int table_num_in);
	bool isfull();
	bool isEmpty();
};
int Kiosk::AllMoney = 0; //��ü �����
int Kiosk::front = 0;
int Kiosk::rear = 0;
int Kiosk::real_size= 0;
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
void Kiosk::push_drink(string name_in, int table) { //enqueue
	if (isfull()) {
		cout << "�޴��� �� �̻� �ֹ� �� �� �����ϴ�." << endl;
	}
	else {
		queue[rear].name = name_in; //queue(rear��ȣ)�� ���� �̸��� ����
		rear = (rear + 1) % this->size; //rear���� ��� �ʱ�ȭ
	}
}
string Kiosk::bring_menu() {
	if (!isEmpty()) {
		return queue[front].name;
		front = (front + 1) % this->size;
	}
	else
		cout << "�޴��� �����ϴ�." << endl;
}
bool Kiosk::isEmpty() {
	if (front == rear)
		return true;
	else
		return false;
}
bool Kiosk::isfull() {
	if (rear + 1 % size == front)
		return true;
	else
		return false;	
}
bool Kiosk::Menu_payment(char check_in, int table_num_in) {
	if (check_in == 'Y' || check_in == 'y')
	{
		cout << "�� ���� �ݾ��� " << queue[table_num_in - 1].queuemoney << "���Դϴ�." << endl;
		return true;
	}
	else
	{
		cout << "�ٽ� ���� ���ּ��� " << endl;
		return false;
	}
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
	cout << "#1	Ice Americano	4500" << endl;
	cout << "#2	Ice Latte	5000" << endl;
	cout << "#3	Ice Tea	5000" << endl;
	cout << "#4	Chamomile	6000" << endl;
	cout << "#5	Caramel Macchiato	6500" << endl;
	cout << "#####################" << endl;
	cout << "1. �ֹ��Է�\n2. �ֹ���Ȳ\n3. �ֹ��Ϸ�\n#####################" << endl;
	cout << "��ȣ�� �Է��Ͻÿ� >> ";
}
void Menu::Menu_select(int table_num_in, Menu& M_selc, int number) {
	int price = 0;
	price = M_selc.price;
	Money(price, table_num_in - 1);
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
					cout << "���� ��ȣ�� �޴� �̸��� �ۼ����ּ��� >>";
					cin >> cafe_num >> name[i];
					name_sum += name[i];
					M_ptr[cafe_num - 1].Menu_select(table_num, M_ptr[cafe_num - 1], x);
				}
				queue.queue[table_num - 1].push_drink(name_sum, table_num - 1);
			}
			else if (number == 1)
			{
				string name_1;
				cout << "���� ��ȣ�� �޴� �̸��� �ۼ����ּ��� >> ";
				cin >> cafe_num >> name_1;
				M_ptr[cafe_num - 1].Menu_select(table_num, M_ptr[cafe_num - 1], x);
				queue.queue[table_num - 1].push_drink(name_1, table_num - 1);
			}
			char check;
			restart:
			cout << "�ֹ� ���� �Ͻðڽ��ϱ�? ( Y / N ) >> ";
			cin >> check;
			int skip = queue.queue[table_num - 1].Menu_payment(check, table_num);
			if (skip == 1)
			{
				cout << "������ �Ϸ� �Ǿ����ϴ�. �ڸ��� �ɾ� ��ø� ��ٷ��ּ���. " << endl;
			}
			else if (skip == 0)
				goto restart;

		}
		else if (select == 2)
		{

		}
	}
	
}