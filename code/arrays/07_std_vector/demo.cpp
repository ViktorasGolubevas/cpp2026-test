// demo_07.cpp - STL std::vector
// Demonstracija: Dinaminis masyvas, RAII, STL algoritmai

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
    
    Student(const Student& other) 
        : name(other.name), age(other.age), grade(other.grade) {
        std::cout << "📋 Copy konstruktorius: " << name << std::endl;
    }
    
    Student(Student&& other) noexcept
        : name(std::move(other.name)), age(other.age), grade(other.grade) {
        std::cout << "🚚 Move konstruktorius: " << name << std::endl;
    }
    
    ~Student() {
        std::cout << "🗑️ Destruktorius: " << name << std::endl;
    }
    
    void print() const {
        std::cout << "Student: " << name << ", Age: " << age 
                  << ", Grade: " << grade << std::endl;
    }
    
    double get_grade() const { return grade; }
    
    bool operator<(const Student& other) const {
        return grade < other.grade;
    }
};

int main() {
    std::cout << "=== STL std::vector ===\n\n";
    
    // Tuščias vector
    std::vector<Student> students;
    std::cout << "Pradinis size: " << students.size() 
              << ", capacity: " << students.capacity() << "\n\n";
    
    // Pridėjimas su emplace_back (C++11)
    std::cout << "--- emplace_back ---\n";
    students.emplace_back("Jonas", 20, 8.5);
    students.emplace_back("Petras", 21, 9.0);
    students.emplace_back("Marija", 19, 8.8);
    
    std::cout << "\nPo pridėjimo - size: " << students.size() 
              << ", capacity: " << students.capacity() << "\n";
    
    // Pridėjimas su push_back
    std::cout << "\n--- push_back ---\n";
    Student temp("Tomas", 22, 7.5);
    students.push_back(temp);  // Copy
    students.push_back(Student("Ona", 20, 9.2));  // Move
    
    std::cout << "\n--- Visi studentai ---\n";
    for (size_t i = 0; i < students.size(); i++) {
        std::cout << (i + 1) << ". ";
        students[i].print();
    }
    
    // Rūšiavimas
    std::cout << "\n--- Rūšiavimas ---\n";
    std::sort(students.begin(), students.end());
    
    for (const auto& student : students) {
        student.print();
    }
    
    // Įterpimas
    std::cout << "\n--- Insert operacija ---\n";
    auto it = students.begin() + 1;
    students.insert(it, Student("Inserted", 23, 8.7));
    
    std::cout << "Po insert:\n";
    for (size_t i = 0; i < students.size(); i++) {
        std::cout << i << ". ";
        students[i].print();
    }
    
    // Šalinimas
    std::cout << "\n--- Erase operacija ---\n";
    students.erase(students.begin() + 2);
    
    std::cout << "Po erase (size = " << students.size() << "):\n";
    for (const auto& student : students) {
        student.print();
    }
    
    // Capacity stebėjimas
    std::cout << "\n--- Capacity stebėjimas ---\n";
    std::cout << "Prieš reserve: capacity = " << students.capacity() << "\n";
    students.reserve(20);
    std::cout << "Po reserve(20): capacity = " << students.capacity() << "\n";
    
    std::cout << "\n--- Destruktoriai ---\n";
    return 0;
}