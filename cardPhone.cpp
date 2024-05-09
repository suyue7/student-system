#include <iostream>
#include <fstream>
#include <map>
#include <string.h>
using namespace std;

class CardPhone
{ private:
    map<string, string> phoneNumBook;	    // 电话号码本
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

void CardPhone::insert()  // 插入数据 
{   string name, phoneNumber;

    cout << endl; 
    cout << "  请输入要添加的姓名：";
	cin >> name;
	if(phoneNumBook.count(name) > 0) 
	{   cout << endl << "  《" << name << "》已存在，不能添加！请返回！" << endl;
	    return;
    }
	cout << "  请输入对应的电话号码：";
	cin >> phoneNumber;
	phoneNumBook.insert(make_pair(name, phoneNumber));
	cout << endl << "  ... 数据已添加！！！" << endl;
	modifyFlag = true;
}

void CardPhone::search()  // 根据名字查找号码
{   string name;
    map<string, string>::iterator iter;	
    cout << endl;
    cout << "  请输入需要查询的姓名：";
    cin >> name;
    iter = phoneNumBook.find(name);
    if (iter == phoneNumBook.end()) 
        cout << endl << "  无此《" << name << "》姓名！" << endl;
    else
        cout << endl << "  《" << name << "》电话号码为："  << (*iter).second << endl; 
}
                                                    	
void CardPhone::pdelete()  // 删除一个条目
{   string name;
	
    cout << "  请输入需要删除的姓名：";
    cin >> name;
    if(phoneNumBook.count(name) == 0) 
	{   cout << endl << "  《" << name << "》不存在，不能删除！请返回！" << endl;
	    return;
    }
    phoneNumBook.erase(name);
    cout << endl << "  《" << name << "》已删除！" << endl;
    modifyFlag = true;
}

void CardPhone::deleteMore()  // 删除多个条目
{	string startName, endName;
    map<string, string>::iterator beginIter, endIter;	
	
	cout << "  请输入起始姓名：";
    cin >> startName;
    cout << "  请输入截至姓名: ";
    cin >> endName;
 
    beginIter = phoneNumBook.find(startName);
    endIter = phoneNumBook.find(endName);
  
    endIter ++;	 // erase操作不删除第二个迭代器所指向的元素，所以先将迭代器向后移动一个元素
    phoneNumBook.erase(beginIter, endIter);
    cout << endl << "  《" << startName << "》" << "-->《" << endName << "》区间已删除！" << endl;
    modifyFlag = true;
}

void CardPhone::modify()  // 修改指定条目中的电话号码
{	string name, phoneNumber; 
    cout << endl;
    cout << "  请输入需修改电话号码的姓名：";
    cin >> name;
    if(phoneNumBook.count(name) == 0) 
	{   cout << endl << "  无此《" << name << "》姓名！请返回！" << endl;
	    return;
    }
    cout << "  请输入新的电话号码：";
    cin >> phoneNumber;
    phoneNumBook[name] = phoneNumber;
    cout << endl << "  《" << name << "》电话号码已更改！" << endl;
    modifyFlag = true;
}

void CardPhone::show()  // 列出电话号码本的内容
{	map<string, string>::iterator iter;
    cout << endl;
    cout << "      电话薄列表" << endl << endl;
    cout << "  -------------------" << endl;
    cout << "   姓名    电话号码  " << endl;
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
	{   cout << "文件 PhoneInfo.dat 不能建立 ！" << endl;
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

void CardPhone::printMenu()  // 输出选择菜单
{	system("CLS");
    cout << endl;
	cout << "       名 片 管 理           " << endl;
	cout << "*****************************" << endl;
	cout << "  1 - 添加	2 - 查找"       << endl;
	cout << "  3 - 删除	4 - 批删除"     << endl;
	cout << "  5 - 更改	6 - 显示"       << endl;
	cout << "  0 - 退出"                    << endl;
	cout << "*****************************" << endl;
}

void anyKey()  // 按任意键继续
{   cout << endl << "请按任意键继续 ......";
    char ch;
    ch = getchar();
    ch = getchar();
} 

int main()
{   CardPhone cp;
    
    int choice = 1;
    while (choice != 0) 
	{   cp.printMenu(); 
        cout << "请选择："; 
        cin >> choice;
		switch (choice) 
		{ case 1: cp.insert(); anyKey(); break; 
		  case 2: cp.search(); anyKey(); break;
		  case 3: cp.pdelete(); anyKey(); break;
          case 4: cp.deleteMore(); anyKey(); break;
          case 5: cp.modify(); anyKey(); break;
          case 6: cp.show(); anyKey(); break;
          case 0: cout << endl << endl << " *** 谢谢使用 ***" << endl; 
		          cp.saveInfo();
				  return 0;
        }
    }
}

