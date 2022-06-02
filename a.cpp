#include <iostream>

class Teacher;

class Student {
private:
    ::std::string        m_name;
    ::std::string        m_className;
    ::std::string        m_studentNumber;
    static ::std::string m_schoolName;
    static int           m_count;

public:
    Student() = delete;

    explicit Student(::std::string name, ::std::string className, ::std::string studentNumber) noexcept :
            m_name(name), m_className(className), m_studentNumber(studentNumber) {
        m_count++;
        ::std::cout << "构造函数被调用啦！" << ::std::endl;
    }

    ~Student() {
        if (m_count > 0) m_count--;
        ::std::cout << "析构函数被调用啦！" << ::std::endl;
    }

    explicit Student(const Student& student) noexcept :
            m_name(student.m_name), m_className(student.m_className), m_studentNumber(student.m_studentNumber) {
        ::std::cout << "拷贝构造函数被调用啦！" << ::std::endl;
    }

    static int getNumber() {
        return m_count;
    }

    static ::std::string getSchool() {
        return m_schoolName;
    }

    void show() {
        ::std::cout << "我叫" << m_name << "，我的学号是" << m_studentNumber << "，我来自" << m_schoolName << "学校"
                    << m_className << "班。" << ::std::endl;
    }

    friend ::std::ostream& operator<<(::std::ostream& os, const Student& student) {
        os << "我叫" << student.m_name << "，我的学号是" << student.m_studentNumber << "，我来自" << m_schoolName
           << "学校" << student.m_className << "班。" << ::std::endl;
        ::std::cout << "输出运算符被调用啦！" << ::std::endl;
        return os;
    }

    bool operator>(const Student& student) {
        ::std::cout << ">运算符被调用啦！" << ::std::endl;
        return m_studentNumber > student.m_studentNumber;
    }

    bool operator<(const Student& student) {
        ::std::cout << "<运算符被调用啦！" << ::std::endl;
        return m_studentNumber < student.m_studentNumber;
    }

    bool operator==(const Student& student) {
        ::std::cout << "==运算符被调用啦！" << ::std::endl;
        return m_studentNumber == student.m_studentNumber;
    }

    friend class Teacher;
};

class Teacher {
public:
    void getStudent(const Student& student) {
        std::cout << "学生姓名是" << student.m_name << std::endl;
    }
};

int           Student::m_count      = 0;
::std::string Student::m_schoolName = "北林";

int main(int argc, char* argv[]) {
    Student student1("张三", "计算机1", "001");
    Student student2("李四", "计算机2", "002");
    Student student3(student1);

    student1.show();
    student2.show();
    student3.show();

    ::std::cout << student1 << ::std::endl;
    ::std::cout << student2 << ::std::endl;
    ::std::cout << student3 << ::std::endl;

    ::std::cout << "学生总数：" << Student::getNumber() << ::std::endl;

    ::std::cout << ::std::boolalpha << (student1 > student2) << ::std::endl;
    ::std::cout << ::std::boolalpha << (student1 < student2) << ::std::endl;
    ::std::cout << ::std::boolalpha << (student1 == student2) << ::std::endl;

    Teacher teacher;
    teacher.getStudent(student1);

    return 0;
}