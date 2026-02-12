// student_04.cpp - Rule of Three
// Demonstracija: Deep copy, destruktorius, assignment operatorius

#include <iostream>
#include <string>

class Student {
private:
    std::string name;
    int age;
    double grade;
    
public:
    Student() : name("Unknown"), age(0), grade(0.0) {}
    
    Student(const std::string& n, int a, double g) 
        : name(n), age(a), grade(g) {}
    
    ~Student() {
        std::cout << "🗑️ Student destruktorius: " << name << std::endl;
    }
    
    void print() const {
        std::cout << "Student: " << name << ", Age: " << age 
                  << ", Grade: " << grade << std::endl;
    }
    
    void set_data(const std::string& n, int a, double g) {
        name = n; age = a; grade = g;
    }
};

class StudentManager {
private:
    Student* students;
    int capacity;
    int count;
    
public:
    // 1. Konstruktorius
    StudentManager(int initial_capacity) 
        : capacity(initial_capacity), count(0) {
        std::cout << "🏗️ StudentManager konstruktorius (capacity: " 
                  << capacity << ")\n";
        students = new Student[capacity];
    }
    
    // 2. Destruktorius
    ~StudentManager() {
        std::cout << "🗑️ StudentManager destruktorius\n";
        delete[] students;
    }
    
    // 3. Copy konstruktorius (deep copy)
    StudentManager(const StudentManager& other) 
        : capacity(other.capacity), count(other.count) {
        std::cout << "📋 StudentManager copy konstruktorius\n";
        
        students = new Student[capacity];  // Naujas masyvas
        
        // Kopijuojame duomenis
        for (int i = 0; i < count; i++) {
            students[i] = other.students[i];
        }
    }
    
    // 4. Assignment operatorius
    StudentManager& operator=(const StudentManager& other) {
        std::cout << "📝 StudentManager assignment operatorius\n";
        
        if (this == &other) {  // Self-assignment apsauga
            return *this;
        }
        
        // Išvalome seną atmintį
        delete[] students;
        
        // Kopijuojame naują
        capacity = other.capacity;
        count = other.count;
        students = new Student[capacity];
        
        for (int i = 0; i < count; i++) {
            students[i] = other.students[i];
        }
        
        return *this;
    }
    
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

int main() {
    std::cout << "=== Rule of Three ===\n\n";
    
    // Originalus objektas
    std::cout << "--- Originalus objektas ---\n";
    StudentManager manager1(2);
    manager1.add_student("Jonas", 20, 8.5);
    manager1.add_student("Petras", 21, 9.0);
    manager1.print_all();
    
    // Copy konstruktorius testas
    std::cout << "\n=== Copy konstruktorius ===\n";
    StudentManager manager2 = manager1;  // Copy konstruktorius
    manager2.print_all();
    
    // Assignment operatorius testas
    std::cout << "\n=== Assignment operatorius ===\n";
    StudentManager manager3(1);
    manager3.add_student("Marija", 19, 8.8);
    manager3.print_all();
    
    std::cout << "\n--- Assignment: manager3 = manager1 ---\n";
    manager3 = manager1;  // Assignment operatorius
    manager3.print_all();
    
    // Self-assignment testas
    std::cout << "\n=== Self-assignment testas ===\n";
    manager1 = manager1;  // Turi būti saugus
    std::cout << "✅ Self-assignment necrash'ino!\n";
    
    std::cout << "\n=== Destruktoriai ===\n";
    return 0;
}