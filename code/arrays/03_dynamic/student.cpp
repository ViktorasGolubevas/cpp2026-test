// student_03.cpp - Dinaminiai masyvai (new/delete)
// Demonstracija: Runtime dydis, memory management problemos

#include <iostream>
#include <string>

class Student {
private:
    std::string name;
    int age;
    double grade;
    
public:
    Student() : name("Unknown"), age(0), grade(0.0) {
        std::cout << "📚 Default konstruktorius: " << name << std::endl;
    }
    
    Student(const std::string& n, int a, double g) 
        : name(n), age(a), grade(g) {
        std::cout << "📚 Parametrinis konstruktorius: " << name << std::endl;
    }
    
    ~Student() {
        std::cout << "🗑️ Destruktorius: " << name << std::endl;
    }
    
    void print() const {
        std::cout << "Student: " << name << ", Age: " << age 
                  << ", Grade: " << grade << std::endl;
    }
    
    // Setter metodai dinaminiam užpildymui
    void set_data(const std::string& n, int a, double g) {
        name = n;
        age = a;
        grade = g;
    }
};

class StudentManager {
private:
    Student* students;  // Rodyklė į dinaminį masyvą
    int capacity;
    int count;
    
public:
    StudentManager(int initial_capacity) 
        : capacity(initial_capacity), count(0) {
        std::cout << "🏗️ StudentManager konstruktorius (capacity: " 
                  << capacity << ")\n";
        students = new Student[capacity];  // 💥 Tik default konstruktoriai!
    }
    
    ~StudentManager() {
        std::cout << "🗑️ StudentManager destruktorius\n";
        delete[] students;  // ✅ Automatiškai iškviečia destruktorius
    }
    
    // 💥 PROBLEMA: Nėra copy konstruktoriaus - shallow copy!
    // StudentManager(const StudentManager&) = delete;  // Geriau uždrausti
    
    void add_student(const std::string& name, int age, double grade) {
        if (count >= capacity) {
            std::cout << "❌ Masyvas pilnas!\n";
            return;
        }
        
        students[count].set_data(name, age, grade);
        count++;
    }
    
    void print_all() const {
        std::cout << "\n--- StudentManager (" << count << "/" 
                  << capacity << ") ---\n";
        for (int i = 0; i < count; i++) {
            students[i].print();
        }
    }
};

void test_dynamic_array() {
    std::cout << "\n=== Funkcijos scope testas ===\n";
    
    StudentManager manager(2);
    manager.add_student("Tomas", 22, 7.8);
    manager.add_student("Ona", 20, 9.2);
    manager.print_all();
    
    std::cout << "\n--- Funkcija baigiasi - manager sunaikinamas ---\n";
}

int main() {
    std::cout << "=== Dinaminiai masyvai ===\n\n";
    
    // Paprastas dinaminis masyvas
    std::cout << "--- Runtime dydžio įvedimas ---\n";
    int size = 3;  // Hardcoded vietoj std::cin
    std::cout << "Studentų skaičius: " << size << "\n\n";
    
    Student* students = new Student[size];  // Default konstruktoriai
    
    // Užpildymas duomenimis
    std::cout << "--- Užpildymas duomenimis ---\n";
    students[0].set_data("Jonas", 20, 8.5);
    students[1].set_data("Petras", 21, 9.0);
    students[2].set_data("Marija", 19, 8.8);
    
    std::cout << "\n--- Dinaminis masyvas ---\n";
    for (int i = 0; i < size; i++) {
        students[i].print();
    }
    
    std::cout << "\n--- delete[] iškvietimas ---\n";
    delete[] students;  // ✅ Destruktoriai iškviečiami
    
    // Objekto su dinaminiu masyvu testas
    test_dynamic_array();
    
    // 💥 SHALLOW COPY DEMONSTRACIJA
    std::cout << "\n=== Shallow copy problema ===\n";
    std::cout << "❌ Jei sukurtume kopiją - double delete crash!\n";
    std::cout << "❌ Reikia Rule of Three!\n";
    
    return 0;
}