// student_02.cpp - Inicializacijos sąrašas (C++11)
// Demonstracija: Parametriniai konstruktoriai, std::string

#include <iostream>
#include <string>

class Student {
private:
    std::string name;
    int age;
    double grade;
    
public:
    // Default konstruktorius
    Student() : name("Unknown"), age(0), grade(0.0) {
        std::cout << "📚 Default konstruktorius: " << name << std::endl;
    }
    
    // Parametrinis konstruktorius
    Student(const std::string& n, int a, double g) 
        : name(n), age(a), grade(g) {
        std::cout << "📚 Parametrinis konstruktorius: " << name << std::endl;
    }
    
    // Copy konstruktorius
    Student(const Student& other) 
        : name(other.name), age(other.age), grade(other.grade) {
        std::cout << "📋 Copy konstruktorius: " << name << std::endl;
    }
    
    // Destruktorius
    ~Student() {
        std::cout << "🗑️ Destruktorius: " << name << std::endl;
    }
    
    void print() const {
        std::cout << "Student: " << name << ", Age: " << age 
                  << ", Grade: " << grade << std::endl;
    }
    
    const std::string& get_name() const { return name; }
};

int main() {
    std::cout << "=== Inicializacijos sąrašas (C++11) ===\n\n";
    
    // ✅ C++11 inicializacijos sąrašas - parametriniai konstruktoriai!
    Student students[] = {
        Student("Jonas", 20, 8.5),
        Student("Petras", 21, 9.0),
        Student("Marija", 19, 8.8)
    };
    
    const int count = sizeof(students) / sizeof(students[0]);
    std::cout << "\nMasyvo dydis: " << count << " elementai\n";
    
    std::cout << "\n--- Visi studentai ---\n";
    for (int i = 0; i < count; i++) {
        std::cout << (i + 1) << ". ";
        students[i].print();
    }
    
    // Masyvo tipo demonstracija
    std::cout << "\n--- Dydžio informacija ---\n";
    std::cout << "sizeof(students) = " << sizeof(students) << " bytes\n";
    std::cout << "sizeof(Student) = " << sizeof(Student) << " bytes\n";
    
    // 💥 LIKO PROBLEMA: Negalima keisti masyvo dydžio
    std::cout << "\n--- Liko problemų ---\n";
    std::cout << "❌ Dydis fiksuotas compile time\n";
    std::cout << "❌ Negalima pridėti/pašalinti elementų\n";
    
    std::cout << "\n--- Destruktoriai ---\n";
    return 0;
}