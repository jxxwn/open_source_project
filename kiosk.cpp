#include<iostream>
#include<string>
#include<Windows.h>
#define MAX_SIZE 3
using namespace std;
void timer(int);
void timer2(int);
void name_sum_clear(string*);
int ff = 0;
class Kiosk { //Kiosk Class�� queue ����
    int t_number;
    string name;
public:
    int queuemoney = 0;
    Kiosk();
    ~Kiosk();
    static int AllMoney;
    static int front; //front : queue�� �� ��Ҹ� ����Ŵ
    static int rear; //rear : queue ������ ��� ����Ŵ
    static int real_size(); //queue ���� ������
    void Money(int Money, int table);
    void Name(string name, int talbe);
    void clear_name();
    void push_drink();
    int t_num_show(); //���� �ֹ� ��Ȳ real_size�� �̿��ϱ�
    void bring_menu();
    string Return_name();
    bool Menu_payment(char check_in);
    bool isfull();
    bool isfull2();
    bool isEmpty();
};
int Kiosk::AllMoney = 0; //��ü �����
int Kiosk::front = 0;
int Kiosk::rear = 0;
Kiosk::Kiosk() {
    t_number = 0;
    name = "";
    queuemoney = 0;
}
Kiosk::~Kiosk() {
}
void Kiosk::Money(int Money, int table) { //�Ϸ�
    this->queuemoney = 0;
    AllMoney += Money; //��ü �����
    this->queuemoney += Money;
    this->t_number = table;
}
void Kiosk::Name(string name, int table) { //�Ϸ�
    this->name = " ";
    this->name = name;
    this->t_number = table;
}
void Kiosk::clear_name() {
    this->name = "�ֹ� �Ϸ��Ͽ����ϴ�.";
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
        cout << "�޴��� �� �̻� �ֹ� �� �� �����ϴ�." << endl;
    }
    else {
        rear = (rear + 1) % MAX_SIZE; //rear���� ��� �ʱ�ȭ
    }
}
void Kiosk::bring_menu() {
    if (!isEmpty()) {
        front = (front + 1) % MAX_SIZE;
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
        cout << this->t_number << "�� ���̺��� �� ���� �ݾ��� " << this->queuemoney << "���Դϴ�." << endl;
        return true;
    }
    else
    {
        cout << "�ٽ� ���� ���ּ��� " << endl;
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
    q[Kiosk::rear].Money(price, table_num_in);//����
    q[Kiosk::rear].Name(q_name, table_num_in); //�޴� �̸�
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
            cout << q[i].t_num_show() << "�� ���̺� ���� ���Խ��ϴ� : " << q[i].Return_name() << endl;
            timer2(1);
            q[i].clear_name();
        }
    }
    else
    {
        for (int i = 0; i <MAX_SIZE; i++)
        {
            cout << q[i].t_num_show() << "�� ���̺� ���� �غ����Դϴ� : " << q[i].Return_name() << endl;
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
    cout << "#       #1   ���̽��Ƹ޸�ī��   4500       #" << endl;
    cout << "#       #2   ���̽� ��   5000            #" << endl;
    cout << "#       #3   ���̽�Ƽ   5500               #" << endl;
    cout << "#       #4   ī����   6000               #" << endl;
    cout << "#       #5   ī��� �����ƶ�   6500        #" << endl;
    cout << "############################################" << endl;
    cout << endl;
    cout << "1. �ֹ��Է�\n2. �ֹ���Ȳ\n3. ���� ����\n4. ���α׷� ����\n" << endl;
    cout << "��ȣ�� �Է��Ͻÿ� >> ";
}
void name_sum_clear(string* name) {
    for (int i = 0; i < MAX_SIZE; i++) {
        name[i] = "";
    }
}
void timer(int time) {
    int endtime_ = time;
    int starttime_ = 0;
    cout << "��ø� ��ٷ��ּ��� ";
    while (1)
    {
        endtime_ - starttime_;
        Sleep(1000);//1��
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
        Sleep(1000);//1��
        cout << endl;
        endtime_--;
        if (endtime_ - starttime_ == 0)
            break;
    }
}
int main()
{
    Menu M[5] = { Menu(1,"���̽� �Ƹ޸�ī��",4500),Menu(2,"���̽� ��",5000),Menu(3,"���̽�Ƽ",5500),Menu(4,"ī����",6000),Menu(5,"ī��� �����ƶ�",6500) };
    Menu* M_ptr;
    Menu q(MAX_SIZE);
    M_ptr = M;
    int select;
    int table_num; //�մ� �̸�
    int number;// �ֹ� ��(���� ����)
    int cafe_num; //�����ȣ
    string name[10];
    string name_sum;
    string comma = ", ";

    while (1)
    {
        int price = 0;
        name_sum = ""; //�ʱ�ȭ
        name_sum_clear(name); //name �ʱ�ȭ
        M_ptr->Menu_list(); //�޴��� ȣ��
        cin >> select; //��ȣ �Է�
        if (select == 1)
        {
            cout << "���̺� ��ȣ�� �Է����ּ��� >> ";
            cin >> table_num;
            cout << "�� ���� �ֹ��Ͻðڽ��ϱ�? >> ";
            cin >> number; //����
            if (number > 1 && number < 11)
            {
                for (int i = 0; i < number; i++)
                {
                    cout << "���� ��ȣ�� �޴� �̸��� �ۼ����ּ��� >>";
                    cin >> cafe_num;
                    getline(cin, name[i]);
                    name_sum += name[i];
                    price += M_ptr[cafe_num - 1].price_get();
                }
                q.Menu_select(table_num, price, name_sum);
                q.push_drink(); //rear �� ����
                system("cls");
            }
            else if (number == 1)
            {
                string name_1 = "";
                cout << "���� ��ȣ�� �޴� �̸��� �ۼ����ּ��� >> ";
                cin >> cafe_num;
                getline(cin, name_1);
                price = M_ptr[cafe_num - 1].price_get();
                q.Menu_select(table_num, price, name_1);
                q.push_drink();
                system("cls");
            }
            char check;
        restart:
            cout << "�ֹ� ���� �Ͻðڽ��ϱ�? ( Y / N ) >> ";
            cin >> check;
            int skip = q.check_price(check);
            if (skip == 1)
            {
                q.bring_menu();
                cout << "������ �Ϸ� �Ǿ����ϴ�." << endl;
                timer(5);
                cout << endl;
               // cout << table_num << "�� ���̺� " << bring_menu << " ���Խ��ϴ�." << endl;
                //timer2(3);
                system("cls");
            }
            else if (skip == 0)
                goto restart;
        }
        else if (select == 2)
        {
            system("cls");
            q.show(); //�ǽð� �ֹ���Ȳ
            timer2(3);
            system("cls");
        }
        else if (select == 3)
        {
            system("cls");
            cout << "��ü ����� : " << Kiosk::AllMoney << " �� �Դϴ�." << endl;
            timer2(3);
            system("cls");
        }
        else if (select == 4)
        {
            cout << "����" << endl;
            break;
            
        }
        
    }
    return 0;
}