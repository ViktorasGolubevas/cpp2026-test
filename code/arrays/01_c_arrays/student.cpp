// student_01.cpp - C stiliaus masyvai su objektais
// Demonstracija: Tik default konstruktorius, rankinis duomenų keitimas

#include <iostream>
#include <cstring>

class Student {
public:
    char name[50];
    int age;
    double grade;
    
    // Default konstruktorius
    Student() {
        strcpy(name, "Unknown");
        age = 0;
        grade = 0.0;
        std::cout << "📚 Student konstruktorius: " << name << std::endl;
    }
    
    // Parametrinis konstruktorius (nebus naudojamas masyve!)
    Student(const char* n, int a, double g) {
        strcpy(name, n);
        age = a;
        grade = g;
        std::cout << "📚 Student konstruktorius: " << name << std::endl;
    }
    
    // Destruktorius
    ~Student() {
        std::cout << "🗑️ Student destruktorius: " << name << std::endl;
    }
    
    void print() const {
        std::cout << "Student: " << name << ", Age: " << age 
                  << ", Grade: " << grade << std::endl;
    }
};

int main() {
    std::cout << "=== C stiliaus masyvas su objektais ===\n\n";
    
    // 💥 PROBLEMA #1: Tik default konstruktorius!
    Student students[3];  // Visi objektai sukurti su default konstruktoriumi
    
    std::cout << "\n--- Pradinis masyvas ---\n";
    for (int i = 0; i < 3; i++) {
        students[i].print();
    }
    
    // Reikia rankiniu būdu keisti duomenis
    std::cout << "\n--- Keičiame duomenis rankiniu būdu ---\n";
    strcpy(students[0].name, "Jonas");
    students[0].age = 20;
    students[0].grade = 8.5;
    
    strcpy(students[1].name, "Petras");
    students[1].age = 21;
    students[1].grade = 9.0;
    
    strcpy(students[2].name, "Marija");
    students[2].age = 19;
    students[2].grade = 8.8;
    
    std::cout << "\n--- Po duomenų keitimo ---\n";
    for (int i = 0; i < 3; i++) {
        students[i].print();
    }
    
    // 💥 PROBLEMA #2: Masyvo tipo painiava
    std::cout << "\n--- Masyvo tipo problema ---\n";
    std::cout << "sizeof(students) = " << sizeof(students) << " bytes\n";
    std::cout << "sizeof(Student) = " << sizeof(Student) << " bytes\n";
    std::cout << "Elementų skaičius = " << sizeof(students) / sizeof(Student) << "\n";
    
    std::cout << "\n--- Destruktoriai (atvirkščia tvarka) ---\n";
    return 0;
}