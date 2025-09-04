#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <limits>

using namespace std;

namespace StudentSystem {

// ==================== CLASS STUDENT ====================
class Student {
private:
    int id;
    string name;
    int age;
    float gpa;

public:
    Student(int id, const string& name, int age, float gpa)
        : id(id), name(name), age(age), gpa(gpa) {}

    int getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }
    float getGPA() const { return gpa; }

    void showInfo() const {
        cout << "ID: " << id
             << " | Name: " << name
             << " | Age: " << age
             << " | GPA: " << gpa << endl;
    }
};

// ==================== CLASS DIRECTORY ====================
class StudentDirectory {
private:
    vector<Student> students;

    // Hàm hỗ trợ: chuyển đổi string sang số nguyên
    int parseInt(const string& input) {
        try {
            size_t pos;
            int val = stoi(input, &pos);
            if (pos != input.size()) throw invalid_argument("Chuỗi chứa ký tự không hợp lệ.");
            return val;
        } catch (...) {
            throw invalid_argument("Sai định dạng số nguyên.");
        }
    }

    // Hàm hỗ trợ: chuyển đổi string sang float
    float parseFloat(const string& input) {
        try {
            size_t pos;
            float val = stof(input, &pos);
            if (pos != input.size()) throw invalid_argument("Chuỗi chứa ký tự không hợp lệ.");
            return val;
        } catch (...) {
            throw invalid_argument("Sai định dạng số thực.");
        }
    }

public:
    void addStudent(const string& idStr, const string& name, const string& ageStr, const string& gpaStr) {
        try {
            int id = parseInt(idStr);
            int age = parseInt(ageStr);
            float gpa = parseFloat(gpaStr);

            if (age < 0 || age > 100) throw out_of_range("Tuổi phải trong khoảng 0-100.");
            if (gpa < 0.0 || gpa > 10.0) throw out_of_range("GPA phải trong khoảng 0.0 - 10.0.");

            students.emplace_back(id, name, age, gpa);
            cout << ">> Thêm sinh viên thành công!\n";
        }
        catch (const exception& e) {
            cout << "Lỗi khi thêm sinh viên: " << e.what() << endl;
        }
    }

    void findById(int id) {
        for (const auto& s : students) {
            if (s.getId() == id) {
                s.showInfo();
                return;
            }
        }
        cout << ">> Không tìm thấy sinh viên với ID: " << id << endl;
    }

    void findByName(const string& name) {
        bool found = false;
        for (const auto& s : students) {
            if (s.getName() == name) {
                s.showInfo();
                found = true;
            }
        }
        if (!found) cout << ">> Không tìm thấy sinh viên tên: " << name << endl;
    }

    void showAll() {
        if (students.empty()) {
            cout << ">> Danh sách rỗng.\n";
            return;
        }
        cout << "===== DANH SÁCH SINH VIÊN =====\n";
        for (const auto& s : students) {
            s.showInfo();
        }
    }
};

} // namespace StudentSystem

// ==================== CHƯƠNG TRÌNH CHÍNH ====================
int main() {
    using namespace StudentSystem;

    StudentDirectory directory;
    int choice;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Them sinh vien\n";
        cout << "2. Tim sinh vien theo ID\n";
        cout << "3. Tim sinh vien theo Ten\n";
        cout << "4. Hien thi toan bo danh sach\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ đệm nhập

        if (choice == 1) {
            string id, name, age, gpa;
            cout << "Nhap ID: "; getline(cin, id);
            cout << "Nhap Ten: "; getline(cin, name);
            cout << "Nhap Tuoi: "; getline(cin, age);
            cout << "Nhap GPA: "; getline(cin, gpa);
            directory.addStudent(id, name, age, gpa);
        }
        else if (choice == 2) {
            int id;
            cout << "Nhap ID can tim: ";
            cin >> id;
            directory.findById(id);
        }
        else if (choice == 3) {
            string name;
            cout << "Nhap Ten can tim: ";
            getline(cin, name);
            directory.findByName(name);
        }
        else if (choice == 4) {
            directory.showAll();
        }

    } while (choice != 0);

    cout << ">> Chuong trinh ket thuc.\n";
    return 0;
}
