#include <iostream>
#include <fstream>
#include <map>
#include <string.h>
using namespace std;

class CardPhone
{ private:
    map<string, string> phoneNumBook;	    // �绰���뱾
    bool modifyFlag;
  public:
  	CardPhone()
  	{   loadInfo();
        modifyFlag = false; 
	}
    void insert();
    void search();
    void pdelete();
    void deleteMore();
    void modify();
    void show();
    void printMenu();
    void anyKey();
    void loadInfo(void);
    void saveInfo(void);
};

void CardPhone::insert()  // �������� 
{   string name, phoneNumber;

    cout << endl; 
    cout << "  ������Ҫ��ӵ�������";
	cin >> name;
	if(phoneNumBook.count(name) > 0) 
	{   cout << endl << "  ��" << name << "���Ѵ��ڣ�������ӣ��뷵�أ�" << endl;
	    return;
    }
	cout << "  �������Ӧ�ĵ绰���룺";
	cin >> phoneNumber;
	phoneNumBook.insert(make_pair(name, phoneNumber));
	cout << endl << "  ... ��������ӣ�����" << endl;
	modifyFlag = true;
}

void CardPhone::search()  // �������ֲ��Һ���
{   string name;
    map<string, string>::iterator iter;	
    cout << endl;
    cout << "  ��������Ҫ��ѯ��������";
    cin >> name;
    iter = phoneNumBook.find(name);
    if (iter == phoneNumBook.end()) 
        cout << endl << "  �޴ˡ�" << name << "��������" << endl;
    else
        cout << endl << "  ��" << name << "���绰����Ϊ��"  << (*iter).second << endl; 
}
                                                    	
void CardPhone::pdelete()  // ɾ��һ����Ŀ
{   string name;
	
    cout << "  ��������Ҫɾ����������";
    cin >> name;
    if(phoneNumBook.count(name) == 0) 
	{   cout << endl << "  ��" << name << "�������ڣ�����ɾ�����뷵�أ�" << endl;
	    return;
    }
    phoneNumBook.erase(name);
    cout << endl << "  ��" << name << "����ɾ����" << endl;
    modifyFlag = true;
}

void CardPhone::deleteMore()  // ɾ�������Ŀ
{	string startName, endName;
    map<string, string>::iterator beginIter, endIter;	
	
	cout << "  ��������ʼ������";
    cin >> startName;
    cout << "  �������������: ";
    cin >> endName;
 
    beginIter = phoneNumBook.find(startName);
    endIter = phoneNumBook.find(endName);
  
    endIter ++;	 // erase������ɾ���ڶ�����������ָ���Ԫ�أ������Ƚ�����������ƶ�һ��Ԫ��
    phoneNumBook.erase(beginIter, endIter);
    cout << endl << "  ��" << startName << "��" << "-->��" << endName << "��������ɾ����" << endl;
    modifyFlag = true;
}

void CardPhone::modify()  // �޸�ָ����Ŀ�еĵ绰����
{	string name, phoneNumber; 
    cout << endl;
    cout << "  ���������޸ĵ绰�����������";
    cin >> name;
    if(phoneNumBook.count(name) == 0) 
	{   cout << endl << "  �޴ˡ�" << name << "���������뷵�أ�" << endl;
	    return;
    }
    cout << "  �������µĵ绰���룺";
    cin >> phoneNumber;
    phoneNumBook[name] = phoneNumber;
    cout << endl << "  ��" << name << "���绰�����Ѹ��ģ�" << endl;
    modifyFlag = true;
}

void CardPhone::show()  // �г��绰���뱾������
{	map<string, string>::iterator iter;
    cout << endl;
    cout << "      �绰���б�" << endl << endl;
    cout << "  -------------------" << endl;
    cout << "   ����    �绰����  " << endl;
    for ( iter = phoneNumBook.begin(); iter != phoneNumBook.end(); iter++ )
    {   cout << "  -------------------" << endl;
	    cout << "   " << (*iter).first << "\t" << "   " << (*iter).second << endl;
    }
    cout << "  -------------------" << endl;
}

void CardPhone::loadInfo(void)
{   struct CInfo
    {   char uname[10];
        char uphone[10];
	} *p;
	p = new struct CInfo;
    int PLEN = sizeof(struct CInfo); 
    int pcc;
    
	fstream fi("PhoneInfo.dat", ios::in | ios::binary);
    if(!fi || fi.eof()) 
        return ;  
	fi.unsetf(ios::skipws);  
	while(!fi.eof())  
	{   fi.read((char *)p, PLEN);
	    pcc = fi.gcount();    
	    if(pcc == PLEN)  
	    {   string name(p->uname);
	        string phoneNumber(p->uphone);
		    phoneNumBook.insert(make_pair(name, phoneNumber));
	    }
    }
    delete p;
	fi.close();
}

void CardPhone::saveInfo(void)
{   if(!modifyFlag) return;
    
	struct CInfo
    {   char uname[10];
        char uphone[10];
	};
	
	fstream fo("PhoneInfo.dat", ios::out | ios::binary);
    if(!fo)
	{   cout << "�ļ� PhoneInfo.dat ���ܽ��� ��" << endl;
		exit(1);
	} 
	
    map<string, string>::iterator iter;
    for ( iter = phoneNumBook.begin(); iter != phoneNumBook.end(); iter++ )
    {   struct CInfo t;
	    strcpy(t.uname, (*iter).first.c_str());
		strcpy(t.uphone, (*iter).second.c_str()); 
		fo.write((char *)&t, sizeof(struct CInfo));
    }
	fo.close();
}

void CardPhone::printMenu()  // ���ѡ��˵�
{	system("CLS");
    cout << endl;
	cout << "       �� Ƭ �� ��           " << endl;
	cout << "*****************************" << endl;
	cout << "  1 - ���	2 - ����"       << endl;
	cout << "  3 - ɾ��	4 - ��ɾ��"     << endl;
	cout << "  5 - ����	6 - ��ʾ"       << endl;
	cout << "  0 - �˳�"                    << endl;
	cout << "*****************************" << endl;
}

void anyKey()  // �����������
{   cout << endl << "�밴��������� ......";
    char ch;
    ch = getchar();
    ch = getchar();
} 

int main()
{   CardPhone cp;
    
    int choice = 1;
    while (choice != 0) 
	{   cp.printMenu(); 
        cout << "��ѡ��"; 
        cin >> choice;
		switch (choice) 
		{ case 1: cp.insert(); anyKey(); break; 
		  case 2: cp.search(); anyKey(); break;
		  case 3: cp.pdelete(); anyKey(); break;
          case 4: cp.deleteMore(); anyKey(); break;
          case 5: cp.modify(); anyKey(); break;
          case 6: cp.show(); anyKey(); break;
          case 0: cout << endl << endl << " *** ллʹ�� ***" << endl; 
		          cp.saveInfo();
				  return 0;
        }
    }
}

