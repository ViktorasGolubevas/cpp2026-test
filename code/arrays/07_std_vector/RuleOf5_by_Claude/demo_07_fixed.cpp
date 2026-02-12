// demo_07.cpp - STL std::vector
// Demonstracija: Dinaminis masyvas, RAII, STL algoritmai, Rule of Five

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
    // ============================================================================
    // CONSTRUCTORS
    // ============================================================================
    
    // Default konstruktorius
    Student() : name("Unknown"), age(0), grade(0.0) {
        std::cout << "📚 Default konstruktorius: " << name << std::endl;
    }
    
    // Parametrinis konstruktorius
    Student(const std::string& n, int a, double g) 
        : name(n), age(a), grade(g) {
        std::cout << "📚 Parametrinis konstruktorius: " << name << std::endl;
    }
    
    // ============================================================================
    // RULE OF FIVE - KRITINĖ TAISYKLĖ!
    // ============================================================================
    // Kai apibrėžiate BENT VIENĄ iš šių funkcijų:
    //   - Destructor
    //   - Copy constructor
    //   - Move constructor
    //   - Copy assignment operator
    //   - Move assignment operator
    // 
    // Paprastai turėtumėte apibrėžti VISUS PENKIS (arba ištrinti/default)
    // ============================================================================
    
    // Copy konstruktorius
    Student(const Student& other) 
        : name(other.name), age(other.age), grade(other.grade) {
        std::cout << "📋 Copy konstruktorius: " << name << std::endl;
    }
    
    // Move konstruktorius
    Student(Student&& other) noexcept
        : name(std::move(other.name)), age(other.age), grade(other.grade) {
        std::cout << "🚚 Move konstruktorius: " << name << std::endl;
    }
    
    // Copy assignment operator
    // SVARBU: Būtinas STL algoritmams (sort, insert, erase)!
    Student& operator=(const Student& other) {
        if (this != &other) {  // Apsisauga nuo self-assignment
            name = other.name;
            age = other.age;
            grade = other.grade;
            std::cout << "📋 Copy assignment: " << name << std::endl;
        }
        return *this;
    }
    
    // Move assignment operator
    // SVARBU: Būtinas efektyviam STL veikimui!
    Student& operator=(Student&& other) noexcept {
        if (this != &other) {  // Apsisauga nuo self-assignment
            name = std::move(other.name);
            age = other.age;
            grade = other.grade;
            std::cout << "🚚 Move assignment: " << name << std::endl;
        }
        return *this;
    }
    
    // Destruktorius
    ~Student() {
        std::cout << "🗑️ Destruktorius: " << name << std::endl;
    }
    
    // ============================================================================
    // MEMBER FUNCTIONS
    // ============================================================================
    
    void print() const {
        std::cout << "Student: " << name << ", Age: " << age 
                  << ", Grade: " << grade << std::endl;
    }
    
    double get_grade() const { return grade; }
    
    // Būtinas std::sort() algoritmui
    bool operator<(const Student& other) const {
        return grade < other.grade;
    }
};

int main() {
    std::cout << "=== STL std::vector - Rule of Five demonstracija ===\n\n";
    
    // ========================================================================
    // 1. KŪRIMAS IR PRIDĖJIMAS
    // ========================================================================
    
    std::vector<Student> students;
    std::cout << "Pradinis size: " << students.size() 
              << ", capacity: " << students.capacity() << "\n\n";
    
    // emplace_back - konstruoja objektą IN-PLACE (nereikia copy/move)
    std::cout << "--- emplace_back (efektyviausia) ---\n";
    students.emplace_back("Jonas", 20, 8.5);
    students.emplace_back("Petras", 21, 9.0);
    students.emplace_back("Marija", 19, 8.8);
    
    std::cout << "\nPo pridėjimo - size: " << students.size() 
              << ", capacity: " << students.capacity() << "\n";
    
    // push_back - reikalauja copy arba move operacijos
    std::cout << "\n--- push_back ---\n";
    Student temp("Tomas", 22, 7.5);
    students.push_back(temp);  // Copy (temp egzistuoja toliau)
    students.push_back(Student("Ona", 20, 9.2));  // Move (laikinas objektas)
    
    // ========================================================================
    // 2. ITERAVIMAS
    // ========================================================================
    
    std::cout << "\n--- Visi studentai ---\n";
    for (size_t i = 0; i < students.size(); i++) {
        std::cout << (i + 1) << ". ";
        students[i].print();
    }
    
    // ========================================================================
    // 3. RŪŠIAVIMAS (reikalauja copy/move assignment!)
    // ========================================================================
    
    std::cout << "\n--- Rūšiavimas pagal pažymį ---\n";
    // std::sort TURI TURĖTI:
    //   - operator< arba custom comparator
    //   - copy/move assignment operators
    std::sort(students.begin(), students.end());
    
    std::cout << "Po rūšiavimo:\n";
    for (const auto& student : students) {
        student.print();
    }
    
    // ========================================================================
    // 4. ĮTERPIMAS (reikalauja copy/move assignment!)
    // ========================================================================
    
    std::cout << "\n--- Insert operacija ---\n";
    auto it = students.begin() + 1;
    // insert TURI TURĖTI copy/move assignment (perkelia elementus)
    students.insert(it, Student("Inserted", 23, 8.7));
    
    std::cout << "Po insert:\n";
    for (size_t i = 0; i < students.size(); i++) {
        std::cout << i << ". ";
        students[i].print();
    }
    
    // ========================================================================
    // 5. ŠALINIMAS (reikalauja move assignment!)
    // ========================================================================
    
    std::cout << "\n--- Erase operacija ---\n";
    // erase TURI TURĖTI move assignment (perkelia elementus kairėn)
    students.erase(students.begin() + 2);
    
    std::cout << "Po erase (size = " << students.size() << "):\n";
    for (const auto& student : students) {
        student.print();
    }
    
    // ========================================================================
    // 6. CAPACITY STEBĖJIMAS
    // ========================================================================
    
    std::cout << "\n--- Capacity stebėjimas ---\n";
    std::cout << "Prieš reserve: capacity = " << students.capacity() << "\n";
    students.reserve(20);  // Išskiria atmintį 20 elementų (nereikia perkopijuoti)
    std::cout << "Po reserve(20): capacity = " << students.capacity() << "\n";
    std::cout << "Size lieka tas pats: " << students.size() << "\n";
    
    // ========================================================================
    // 7. DESTRUKTORIAI
    // ========================================================================
    
    std::cout << "\n--- Destruktoriai (išeinant iš scope) ---\n";
    return 0;
}

// ============================================================================
// IŠVADOS STUDENTAMS:
// ============================================================================
//
// 1. RULE OF FIVE būtina, kai turite custom copy/move semantics:
//    - Apibrėžėte bent vieną → apibrėžkite visus arba naudokite = default
//    - Kompiliatorius IŠTRINA copy assignment, jei turite move constructor!
//
// 2. STL konteineriai REIKALAUJA:
//    ✅ Copy/Move constructors  → emplace_back, push_back, resize
//    ✅ Copy/Move assignment    → sort, insert, erase, assignment
//    ✅ Destructor              → clear, vector destrukcija
//
// 3. Kodėl kompiliavimo klaidos buvo tokios sudėtingos?
//    - STL naudoja template metaprogramming
//    - Klaidos atsiranda template instantiation metu
//    - Viena trūkstama funkcija → cascade of errors
//
// 4. Kaip išvengti problemų?
//    - Jei nereikia custom behavior → naudokite = default
//    - Jei reikia logging → implementuokite visus 5
//    - Jei nenorite kopijų → = delete ir naudokite std::move()
//
// 5. Efektyvumo patarimai:
//    - emplace_back() > push_back() - mažiau kopijų/move
//    - reserve() prieš pridėjimą - išvengia reallocation
//    - Pass by const reference - išvengia kopijų
//
// ============================================================================
