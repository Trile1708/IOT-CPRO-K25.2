#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <iomanip>

class Student {
 private:
   static int next_id;
   int id;
   std::string name;
   float score;
      
public:
    //Constructor
    Student(const std::string& n, float s) {
        if (score <0.0f || score >10.0f) {
            throw std::invalid_argument("Diem phai nam trong khoang 0-10.");
        }
        id=next_id++;
        name=n;
        score=s;
    }

    //Getter &Setter
    int getId() const {return id; }
    const std::string& getName() const { return name;}
    float getScore() const { return score;}

    void setName(const std::string& n) { name=n;}
    void setScore(float s) {
        if (s<0.0f || s>10.0f) {
            throw std::invalid_argument("Diem phai  nam trong khoang 0-10.");
        }
        score=s;
    }

    //Toán tử so sánh theo ID(optional)
    bool operator==(int other_Id) const {
        return id==other_Id;
    }

    //In thong tin sinh vien 
    friend std::ostream& operator<<(std::ostream& os,const Student& st) {
        os << "ID:" <<st.id <<" | Ten: "<<st.name 
           <<" | Diem: "<<std::fixed<<std::setprecision(2)<<st.score;
           return os;

    }
};

//Khoi tao bien static
int Student::next_id=1;

//---------------------STUDENT LIBRARY-------------------------------------------
class StudentList{
private:
    std::vector<Student> students;
    
public:
    //Them sinh vien
    void addStudent(const std::string& name, float score) {
        students.emplace_back(name, score);
    }

    //Sửa thông tin (tìm theo ID)
    void editStudent(int id, const std::string& newName, float newScore){
        for (auto& st : students) {
            if (st==id) {
                st.setName(newName);
                st.setScore(newScore);
                return;
            }
        }
        throw std::runtime_error("Khong tim thay sinh vien co ID nay.");
    }
    
    //Xóa sinh viên 
    void removeStudent(int id) {
        for (auto it=students.begin(); it !=students.end(); ++it) {
            if (*it == id) {
                students.erase(it);
                return;
            }
        }
        throw std::runtime_error("Khong tim thay sinh vien de xoa.");
    }

    //Toán tử [] để truy cập theo index
    Student& operator[] (size_t index) {
        if (index >= students.size()) {
            throw std::out_of_range("Index vuot qua pham vi.");
        }
        return students[index];
    }
     const Student& operator[](size_t index) const {
        if (index >= students.size()) {
            throw std::out_of_range("Index out of range");
        }
        return students[index];
    }

    // nạp chồng toán tử << để in toàn bộ danh sách
    friend std::ostream& operator<<(std::ostream& os, const StudentList& sl) {
        if (sl.students.empty()) {
            os<< "Danh sach rong.\n";
        } else {
            for (const auto& st : sl.students) {
                os<<st<<"\n";
            }
        }
        return os;
    }

    //Friend function prototype: tinh diem trung binh
    friend float averageScore(const StudentList& sl);
    };

 //Hàm friend function defination
 float averageScore(const StudentList& sl) {
    if (sl.students.empty()) 
      return 0.0f;
    float sum=0.0f;
    for(const auto& st: sl.students) {
        sum += st.getScore(); //truy cap vao private score
    }
    return sum / sl.students.size();
 } 
//------------------MAIN(Menu console)--------------------

int main () {
    StudentList list;
    int choice;
    do {
        std::cout << "\n===== MENU =====\n";
        std::cout << "1. Them sinh vien\n";
        std::cout << "2. Sua thong tin sinh vien\n";
        std::cout << "3. Xoa sinh vien\n";
        std::cout << "4. In danh sach sinh vien\n";
        std::cout << "5. In diem trung binh\n";
        std::cout << "0. Thoat\n";
        std::cout << "Lua chon: ";
        std::cin >> choice;

        try{
            if (choice==1) {
                std::string name;
                float score;
                std::cout << "Nhap ten: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Nhap diem: ";
                std::cin >> score;
                list.addStudent(name, score);
            }
            else if(choice ==2) {
                int id;
                std::string name;
                float score;
                std::cout << "Nhap ID can sua: ";
                std::cin >> id;
                std::cout << "Nhap ten moi: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Nhap diem moi: ";
                std::cin >> score;
                list.editStudent(id, name, score);
            }
             else if (choice == 3) {
                int id;
                std::cout << "Nhap ID can xoa: ";
                std::cin >> id;
                list.removeStudent(id);
            }
             else if (choice == 4) {
                std::cout << list;
            }
            else if (choice == 5) {
                std::cout << "Diem trung binh: " 
                          << std::fixed << std::setprecision(2) 
                          << averageScore(list) << "\n";
            }
        }
        catch (std::exception& e) {
            std::cerr << "Loi: " <<e.what() << "\n";
        }
    } while (choice !=0);
    return 0;
}