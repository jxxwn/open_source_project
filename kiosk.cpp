#include<iostream>
#include<string>
#define MAX_SIZE 10

using namespace std;

class Kiosk { //Kiosk Class가 queue 역할
	int t_number;
	int size;
	string name;
public:
	int queuemoney = 0;
	//Kiosk* queue;
	Kiosk(){}
	Kiosk(int size_in);
	~Kiosk();
	static int AllMoney;
	static int front; //front : queue의 앞 요소를 가리킴
	static int rear; //rear : queue 마지막 요소 가리킴
	static int real_size(); //queue 현재 사이즈
	void Money(int Money, int index);
	void push_drink(string name_in, int table, Kiosk queue[]);
	void show(); //현재 주문 현황 real_size를 이용하기
	string bring_menu();
	bool Menu_payment(char check_in, int table_num_in);
	bool isfull();
	bool isEmpty();
};
int Kiosk::AllMoney = 0; //전체 매출액
int Kiosk::front = 0;
int Kiosk::rear = 0;
Kiosk::Kiosk(int size_in) {
	this->size = size_in;
}
Kiosk::~Kiosk() {
}
void Kiosk::Money(int Money,int index) {
	AllMoney += Money; //전체 매출액
	queue[index].queuemoney = Money;
}
void Kiosk::show() {
	for (int i = 0; i < real_size(); i++)
	{
		cout << queue[(front + i) % this->size].t_number << "번 테이블 음료 제작 중입니다 : " << queue[(front + i) % this->size].name;
	}
}
int Kiosk::real_size() {
	return(front > rear ? front - rear : rear - front);
}
void Kiosk::push_drink(string name_in, int table, Kiosk queue[]) { //enqueue
	if (isfull()) {
		cout << "메뉴를 더 이상 주문 할 수 없습니다." << endl;
	}
	else {
		queue[rear].name = name_in; //queue(rear번호)에 음료 이름을 넣음
		rear = (rear + 1) % this->size; //rear값을 계속 초기화
		queue[rear].t_number = table; //table_num 저장
	}
}
string Kiosk::bring_menu() {
	if (!isEmpty()) {
		return queue[front].name;
		front = (front + 1) % this->size;
	}
	else
		cout << "메뉴가 없습니다." << endl;
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
		cout << "총 결제 금액은 " << queue[table_num_in - 1].queuemoney << "원입니다." << endl;
		return true;
	}
	else
	{
		cout << "다시 결제 해주세요 " << endl;
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
	cout << "1. 주문입력\n2. 주문현황\n3. 가게 매출\n4. 종료\n#####################" << endl;
	cout << "번호를 입력하시오 >> ";
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
	int table_num; //손님 이름
	int number;// 주문 수(음료 갯수)
	int price; //가격
	int cafe_num; //음료번호
	string name[10];
	string name_sum;
	int x = 0;
	Kiosk* q = new Kiosk[MAX_SIZE];
	while (1)
	{
		M_ptr->Menu_list(); //메뉴판 호출
		cin >> select; //번호 입력
		if (select == 1)
		{
			cout << "테이블 번호를 입력해주세요 >> ";
			cin >> table_num;
			cout << "몇 잔을 주문하시겠습니까? >> ";
			cin >> number; //갯수
			++x;
			if (number > 1 && number < 11)
			{
				for (int i = 0; i < number; i++)
				{
					cout << "음료 번호와 메뉴 이름을 작성해주세요 >>";
					cin >> cafe_num;
					getline(cin, name[i]);
					name_sum += name[i];
					M_ptr[cafe_num - 1].Menu_select(table_num, M_ptr[cafe_num - 1], x);
				}
				q[table_num - 1].push_drink(name_sum, table_num - 1, q[table_num - 1]);
			}
			else if (number == 1)
			{
				string name_1;
				cout << "음료 번호와 메뉴 이름을 작성해주세요 >> ";
				cin >> cafe_num;
				getline(cin, name_1);
				M_ptr[cafe_num - 1].Menu_select(table_num, M_ptr[cafe_num - 1], x);
				q[table_num - 1].push_drink(name_1, table_num - 1);
			}
			char check;
			restart:
			cout << "주문 결제 하시겠습니까? ( Y / N ) >> ";
			cin >> check;
			int skip = q[table_num - 1].Menu_payment(check, table_num);
			if (skip == 1)
			{
				cout << "결제가 완료 되었습니다. 잠시만 기다려주세요. " << endl;
				string bring_menu;
				bring_menu = q[table_num - 1].bring_menu();
				cout << table_num << "번 테이블 " << bring_menu << " 나왔습니다." << endl;
			}
			else if (skip == 0)
				goto restart;

		}
		else if (select == 2)
		{
			queue.show(); //실시간 주문현황
		}
		else if (select == 3)
		{
			for (int i = 0; i < x; i++)
			{
				cout << table_num << "번 테이블 판매액 : " << q[table_num - 1].queuemoney << endl;
			}
			cout << "전체 매출액 : " << queue.AllMoney << endl;
		}
		else if (select == 4)
		{
			cout << "종료" << endl;
			delete[]q; //할당 해제
			break;
		}
	}
	return 0;
}