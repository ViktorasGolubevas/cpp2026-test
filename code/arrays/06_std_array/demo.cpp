// demo_06.cpp - STL std::array
// Demonstracija: Saugus masyvas, STL algoritmai

#include <iostream>
#include <string>
#include <array>
#include <algorithm>

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
        std::cout << "🗑️ Destruktorius: " << name << std::endl;
    }
    
    void print() const {
        std::cout << "Student: " << name << ", Age: " << age 
                  << ", Grade: " << grade << std::endl;
    }
    
    double get_grade() const { return grade; }
    const std::string& get_name() const { return name; }
    
    bool operator<(const Student& other) const {
        return grade < other.grade;
    }
};

int main() {
    std::cout << "=== STL std::array ===\n\n";
    
    // ✅ std::array su inicializacijos sąrašu
    std::array<Student, 4> students = {{
        Student("Jonas", 20, 8.5),
        Student("Petras", 21, 9.0),
        Student("Marija", 19, 8.8),
        Student("Tomas", 22, 7.5)
    }};
    
    std::cout << "--- Pradinis masyvas ---\n";
    for (size_t i = 0; i < students.size(); i++) {
        std::cout << (i + 1) << ". ";
        students[i].print();
    }
    
    // STL algoritmai
    std::cout << "\n--- Rūšiavimas pagal pažymį ---\n";
    std::sort(students.begin(), students.end());
    
    for (size_t i = 0; i < students.size(); i++) {
        std::cout << (i + 1) << ". ";
        students[i].print();
    }
    
    // Paieška
    std::cout << "\n--- Paieška (pažymys > 8.7) ---\n";
    auto it = std::find_if(students.begin(), students.end(), 
        [](const Student& s) { return s.get_grade() > 8.7; });
    
    if (it != students.end()) {
        std::cout << "Rastas: ";
        it->print();
    }
    
    // Saugus prieigos metodas
    std::cout << "\n--- Saugi prieiga su at() ---\n";
    try {
        std::cout << "students.at(2): ";
        students.at(2).print();
        
        std::cout << "students.at(10): ";
        students.at(10).print();  // ❌ Mestų exception
    } catch (const std::out_of_range& e) {
        std::cout << "❌ Klaida: " << e.what() << std::endl;
    }
    
    // Array informacija
    std::cout << "\n--- Array informacija ---\n";
    std::cout << "Size: " << students.size() << std::endl;
    std::cout << "Empty: " << (students.empty() ? "Taip" : "Ne") << std::endl;
    std::cout << "Front: "; students.front().print();
    std::cout << "Back: "; students.back().print();
    
    std::cout << "\n--- Destruktoriai ---\n";
    return 0;
}