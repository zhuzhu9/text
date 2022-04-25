#include <cstdio>
#include <cstring>
#include <iostream>
using std::cout;
using std::endl;
const int offset = sizeof(int);

/*****************用string类实现copy on write（写时复制）**********************/
/********************************string类申明*********************************/
class String {
public:
    class Charproxy {
    public:
        Charproxy(String& s, int index) : _string(s), _index(index) {
        }

        //写操作
        Charproxy& operator=(const char& c) {
            char* temp = new char[_string.size() + 1];
            strcpy(temp, _string.c_str());

            _string.decreaseRefcnt();
            char* temp2   = new char();
            _string._pstr = new char[4 + strlen(temp) + 1];
            _string.initRefcnt();
            strcpy(_string.c_str(), temp);
            _string.c_str()[_index] = c;

            delete[] temp;
            delete[] temp2;
            return *this;
        }

        //读操作
        operator char() {
            return _string.c_str()[_index];
        }

    private:
        String& _string;
        int     _index;
    };

public:
    String();
    String(const char*);
    String(const String&);
    ~String();

    String& operator=(const char*);
    String& operator=(const String&);

    //运算符[] 交给Charproxy代理进行处理
    Charproxy operator[](int index) {
        return Charproxy(*this, index);
    }

    char* c_str();
    void  increaseRefcnt();
    void  decreaseRefcnt();
    void  initRefcnt();
    void  release();
    int   Refcnt();
    int   size();

private:
    char* _pstr;
};

/********************************string类定义*********************************/

#if 0
//注意运算符[]，系统并不能判断是要进行读操作还是写操作，所以此处统一按写操作来
char &String::operator[](int index)
{
	if (index < 0 || index >= size())
	{
		static char c = '\0';
		return c;
	}
	else
	{
		if (Refcnt() == 1)
		{
			return _pstr[4 + index];
		}
		else
		{
			decreaseRefcnt();
			char *temp = _pstr;
			_pstr = new char[size() + 4 + 1];
			initRefcnt();
			strcpy(_pstr + 4, temp + 4);
			return _pstr[4 + index];
		}
	}
}
#endif
//

String& String::operator=(const String& lhs) {
    if (this != &lhs) {
        decreaseRefcnt();
        _pstr = lhs._pstr;
        increaseRefcnt();
    }
    return *this;
}

String& String::operator=(const char* str) {
    decreaseRefcnt();
    _pstr = new char[4 + strlen(str) + 1];
    initRefcnt();
    strcpy(_pstr + 4, str);
    return *this;
}

String::String() : _pstr(new char[4]) {
    initRefcnt();
}

//构造函数:initRefcnt
String::String(const char* str) : _pstr(new char[4 + strlen(str) + 1]) {
    initRefcnt();
    strcpy(_pstr + 4, str);
}

//拷贝构造函数:increaseRefcnt
String::String(const String& lhs) {
    _pstr = lhs._pstr;
    increaseRefcnt();
}

String::~String() {
    --(*_pstr);
    if ((*_pstr) == 0) release();
}

char* String::c_str() {
    return _pstr + 4;
}

int String::Refcnt() {
    return (int)*_pstr;
}

void String::release() {
    if (_pstr != nullptr) {
        delete[] _pstr;
        _pstr = nullptr;
    }
}

void String::decreaseRefcnt() {
    (*_pstr)--;
    if ((*_pstr) == 0) {
        release();
    }
}

void String::increaseRefcnt() {
    (*_pstr)++;
}

void String::initRefcnt() {
    int val = 1;
    memcpy(_pstr, (void*)&val, offset);
}

int String::size() {
    return strlen(_pstr + 4);
}

/********************************测试函数*********************************/

void test0() {
    String s1("s1");
    // cout << s1.c_str() << endl;
    String s2(s1);
    // cout << s2.c_str() << endl;
    // cout << s1.Refcnt() << endl;
    // cout << s2.Refcnt() << endl;
}

void test1() {
    String s1("s1");
    String s2(s1);
    cout << s2.c_str() << endl;
    cout << s2.Refcnt() << endl;
    String s3("s3");
    s2 = s3;
    cout << s2.c_str() << endl;
    cout << s2.Refcnt() << endl;
    cout << s1.c_str() << endl;
    cout << s1.Refcnt() << endl;
}

void test2() {
    String s;
    s = "s";
    cout << s.c_str() << endl;
}

void test3() {
    String s1("s1");
    cout << s1.c_str() << endl;
    printf("s1:%p\n", s1.c_str());

    String s2(s1);
    cout << s2.c_str() << endl;
    printf("s2:%p\n", s2.c_str());

    // s2[0] = 'S';
    cout << s2.c_str() << endl;
    printf("s2:%p\n", s2.c_str());
}

void test4() {
    String s1("s1");
    String s2(s1);
    String s3(s2);
    // cout << "s1[0] = " << s1[1] << endl;
    // cout << "s1:" << s1.c_str() << endl;
    // cout << "s1.refcnt:" << s1.Refcnt() << endl;
    // printf("s1:%p\n", s1.c_str());
    // cout << "s2:" << s2.c_str() << endl;
    // cout << "s2.refcnt:" << s2.Refcnt() << endl;
    // printf("s2:%p\n", s2.c_str());
    // cout << "s3:" << s3.c_str() << endl;
    // cout << "s3.refcnt:" << s3.Refcnt() << endl;
    // printf("s3:%p\n", s3.c_str());

    // cout << "after write=======================" << endl;
    // s1[0] = 'S';
    // cout << "s1[0] = " << s1[0] << endl;
    // cout << "s1[0] = " << s1[1] << endl;
    // cout << "s1:" << s1.c_str() << endl;
    // cout << "s1.refcnt:" << s1.Refcnt() << endl;
    // printf("s1:%p\n", s1.c_str());
    // cout << "s2:" << s2.c_str() << endl;
    // cout << "s2.refcnt:" << s2.Refcnt() << endl;
    // printf("s2:%p\n", s2.c_str());
    // cout << "s3:" << s3.c_str() << endl;
    // cout << "s3.refcnt:" << s3.Refcnt() << endl;
    // printf("s3:%p\n", s3.c_str());
}

int main() {
    test0();
    // std::string s1("aaa");
    // std::string s2(s1);
    // std::string s3(s2);
    return 0;
}
