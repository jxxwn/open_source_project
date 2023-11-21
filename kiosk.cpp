#include<iostream>
#include<string>
#include<Windows.h>
#define MAX_SIZE 3
using namespace std;
void timer(int);
void timer2(int);
void name_sum_clear(string*);
int ff = 0;
class Kiosk { //Kiosk Class가 queue 역할
    int t_number;
    string name;
public:
    int queuemoney = 0;
    Kiosk();
    ~Kiosk();
    static int AllMoney;
    static int front; //front : queue의 앞 요소를 가리킴
    static int rear; //rear : queue 마지막 요소 가리킴
    static int real_size(); //queue 현재 사이즈
    void Money(int Money, int table);
    void Name(string name, int talbe);
    void clear_name();
    void push_drink();
    int t_num_show(); //현재 주문 현황 real_size를 이용하기
    void bring_menu();
    string Return_name();
    bool Menu_payment(char check_in);
    bool isfull();
    bool isfull2();
    bool isEmpty();
};
int Kiosk::AllMoney = 0; //전체 매출액
int Kiosk::front = 0;
int Kiosk::rear = 0;
Kiosk::Kiosk() {
    t_number = 0;
    name = "";
    queuemoney = 0;
}
Kiosk::~Kiosk() {
}
void Kiosk::Money(int Money, int table) { //완료
    this->queuemoney = 0;
    AllMoney += Money; //전체 매출액
    this->queuemoney += Money;
    this->t_number = table;
}
void Kiosk::Name(string name, int table) { //완료
    this->name = " ";
    this->name = name;
    this->t_number = table;
}
void Kiosk::clear_name() {
    this->name = "주문 완료하였습니다.";
}
int Kiosk::real_size() {
    return(front > rear ? front - rear : rear - front);
}
int Kiosk::t_num_show() {
    return this->t_number;
}
string Kiosk::Return_name() {
    return this->name;
}
void Kiosk::push_drink() { //enqueue
    if (isfull()) {
        cout << "메뉴를 더 이상 주문 할 수 없습니다." << endl;
    }
    else {
        rear = (rear + 1) % MAX_SIZE; //rear값을 계속 초기화
    }
}
void Kiosk::bring_menu() {
    if (!isEmpty()) {
        front = (front + 1) % MAX_SIZE;
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
    if ((rear+1) % MAX_SIZE == front)
        return true;
    else
        return false;
}
bool Kiosk::isfull2() {
    if (front % MAX_SIZE == 0)
        return true;
    else
        return false;
}
bool Kiosk::Menu_payment(char check_in) {
    if (check_in == 'Y' || check_in == 'y')
    {
        cout << this->t_number << "번 테이블의 총 결제 금액은 " << this->queuemoney << "원입니다." << endl;
        return true;
    }
    else
    {
        cout << "다시 결제 해주세요 " << endl;
        return false;
    }
}
class Menu{
    int index;
    int table;
    int price;
    int number;
    string name;
    Kiosk* q;
    Kiosk* ch;
public:
    Menu(int size);
    Menu(int index_in, string menu_in, int price_in);
    void Menu_list();
    int price_get();
    void Menu_select(int table_num_in,int price_in, string q_name);
    void push_drink();
    bool check_price(char C);
    void bring_menu();
    void show();
    ~Menu();
    //void Moneyshow();
};
Menu::Menu(int size) {
    q = new Kiosk[size];
}
Menu::Menu(int index_in, string menu_in, int price_in) {
    this->index = index_in;
    this->name = menu_in;
    this->price = price_in;
}
int Menu::price_get() {
    return this->price;
}
void Menu::Menu_select(int table_num_in, int price_in, string q_name) {
    price = 0;
    price = price_in;
    q[Kiosk::rear].Money(price, table_num_in);//가격
    q[Kiosk::rear].Name(q_name, table_num_in); //메뉴 이름
}
void Menu::push_drink() {
    q[Kiosk::rear].push_drink();
}
bool Menu::check_price(char C) {
    int check = 0;
    check = q[Kiosk::front].Menu_payment(C);
    return check;
}
void Menu::bring_menu() {
    q[Kiosk::front].bring_menu();
}
void Menu::show() {
    if (ch->isfull2())
    {
        for (int i = 0; i < MAX_SIZE; i++)
        {
            cout << q[i].t_num_show() << "번 테이블 음료 나왔습니다 : " << q[i].Return_name() << endl;
            timer2(1);
            q[i].clear_name();
        }
    }
    else
    {
        for (int i = 0; i <MAX_SIZE; i++)
        {
            cout << q[i].t_num_show() << "번 테이블 음료 준비중입니다 : " << q[i].Return_name() << endl;
        }
    }
  
}
Menu::~Menu() {
    delete[]q;
}
void Menu::Menu_list() {
    cout << "###########################################" << endl;
    cout << endl;
    cout << "##       ##   #######   ##    #   #       #" << endl;
    cout << "# #     # #   #         # #   #   #       #" << endl;
    cout << "#  #   #  #   #######   #  #  #   #       #" << endl;
    cout << "#   # #   #   #         #   # #   #       #" << endl;
    cout << "#    #    #   #######   #    ##   ######### " << endl;
    cout << endl;
    cout << "############################################" << endl;
    cout << "#       Number     Menu    Price           #" << endl;
    cout << "#       #1   아이스아메리카노   4500       #" << endl;
    cout << "#       #2   아이스 라떼   5000            #" << endl;
    cout << "#       #3   아이스티   5500               #" << endl;
    cout << "#       #4   카모마일   6000               #" << endl;
    cout << "#       #5   카라멜 마끼아또   6500        #" << endl;
    cout << "############################################" << endl;
    cout << endl;
    cout << "1. 주문입력\n2. 주문현황\n3. 가게 매출\n4. 프로그램 종료\n" << endl;
    cout << "번호를 입력하시오 >> ";
}
void name_sum_clear(string* name) {
    for (int i = 0; i < MAX_SIZE; i++) {
        name[i] = "";
    }
}
void timer(int time) {
    int endtime_ = time;
    int starttime_ = 0;
    cout << "잠시만 기다려주세요 ";
    while (1)
    {
        endtime_ - starttime_;
        Sleep(1000);//1초
        cout << ". ";
        endtime_--;
        if (endtime_ - starttime_ == 0)
            break;
    }
}
void timer2(int time) {
    int endtime_ = time;
    int starttime_ = 0;
    while (1)
    {
        endtime_ - starttime_;
        Sleep(1000);//1초
        cout << endl;
        endtime_--;
        if (endtime_ - starttime_ == 0)
            break;
    }
}
int main()
{
    Menu M[5] = { Menu(1,"아이스 아메리카노",4500),Menu(2,"아이스 라떼",5000),Menu(3,"아이스티",5500),Menu(4,"카모마일",6000),Menu(5,"카라멜 마끼아또",6500) };
    Menu* M_ptr;
    Menu q(MAX_SIZE);
    M_ptr = M;
    int select;
    int table_num; //손님 이름
    int number;// 주문 수(음료 갯수)
    int cafe_num; //음료번호
    string name[10];
    string name_sum;
    string comma = ", ";

    while (1)
    {
        int price = 0;
        name_sum = ""; //초기화
        name_sum_clear(name); //name 초기화
        M_ptr->Menu_list(); //메뉴판 호출
        cin >> select; //번호 입력
        if (select == 1)
        {
            cout << "테이블 번호를 입력해주세요 >> ";
            cin >> table_num;
            cout << "몇 잔을 주문하시겠습니까? >> ";
            cin >> number; //갯수
            if (number > 1 && number < 11)
            {
                for (int i = 0; i < number; i++)
                {
                    cout << "음료 번호와 메뉴 이름을 작성해주세요 >>";
                    cin >> cafe_num;
                    getline(cin, name[i]);
                    name_sum += name[i];
                    price += M_ptr[cafe_num - 1].price_get();
                }
                q.Menu_select(table_num, price, name_sum);
                q.push_drink(); //rear 값 변경
                system("cls");
            }
            else if (number == 1)
            {
                string name_1 = "";
                cout << "음료 번호와 메뉴 이름을 작성해주세요 >> ";
                cin >> cafe_num;
                getline(cin, name_1);
                price = M_ptr[cafe_num - 1].price_get();
                q.Menu_select(table_num, price, name_1);
                q.push_drink();
                system("cls");
            }
            char check;
        restart:
            cout << "주문 결제 하시겠습니까? ( Y / N ) >> ";
            cin >> check;
            int skip = q.check_price(check);
            if (skip == 1)
            {
                q.bring_menu();
                cout << "결제가 완료 되었습니다." << endl;
                timer(5);
                cout << endl;
               // cout << table_num << "번 테이블 " << bring_menu << " 나왔습니다." << endl;
                //timer2(3);
                system("cls");
            }
            else if (skip == 0)
                goto restart;
        }
        else if (select == 2)
        {
            system("cls");
            q.show(); //실시간 주문현황
            timer2(3);
            system("cls");
        }
        else if (select == 3)
        {
            system("cls");
            cout << "전체 매출액 : " << Kiosk::AllMoney << " 원 입니다." << endl;
            timer2(3);
            system("cls");
        }
        else if (select == 4)
        {
            cout << "종료" << endl;
            break;
            
        }
        
    }
    return 0;
}