// demo_07_pedagogy.cpp - Rule of Five mokymui
// Šis failas demonstruoja KODĖL Rule of Five yra svarbi

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// ============================================================================
// VERSION 1: BROKEN - Tik move constructor, nėra assignment operators
// ============================================================================
// NEPASILEISTI ŠIO KODO! Jis nekompiliuosis!
// ============================================================================

#if 0  // Išjungta - nekompiliuosis

class StudentBroken {
private:
    std::string name;
    int age;
    double grade;
    
public:
    StudentBroken(const std::string& n, int a, double g) 
        : name(n), age(a), grade(g) {}
    
    StudentBroken(const StudentBroken& other) 
        : name(other.name), age(other.age), grade(other.grade) {}
    
    // ❌ PROBLEMA: Apibrėžtas move constructor
    StudentBroken(StudentBroken&& other) noexcept
        : name(std::move(other.name)), age(other.age), grade(other.grade) {}
    
    // ❌ TRŪKSTA: Copy assignment operator (DELETED by compiler!)
    // ❌ TRŪKSTA: Move assignment operator (DELETED by compiler!)
    
    ~StudentBroken() {}
    
    bool operator<(const StudentBroken& other) const {
        return grade < other.grade;
    }
};

void test_broken() {
    std::vector<StudentBroken> students;
    students.emplace_back("Jonas", 20, 8.5);
    students.emplace_back("Petras", 21, 9.0);
    
    // ❌ KLAIDA: std::sort reikalauja copy/move assignment
    std::sort(students.begin(), students.end());
    // Kompiliatorius sako:
    // "use of deleted function 'Student& Student::operator=(const Student&)'"
}

#endif

// ============================================================================
// VERSION 2: MINIMAL FIX - Naudojame = default
// ============================================================================
// Tai paprasčiausias sprendimas, jei nereikia custom behavior
// ============================================================================

class StudentMinimal {
private:
    std::string name;
    int age;
    double grade;
    
public:
    // Constructors
    StudentMinimal(const std::string& n, int a, double g) 
        : name(n), age(a), grade(g) {
        std::cout << "📚 Constructor: " << name << std::endl;
    }
    
    // Rule of Five su = default
    StudentMinimal(const StudentMinimal&) = default;
    StudentMinimal(StudentMinimal&&) noexcept = default;
    StudentMinimal& operator=(const StudentMinimal&) = default;  // ✅ FIX
    StudentMinimal& operator=(StudentMinimal&&) noexcept = default;  // ✅ FIX
    ~StudentMinimal() = default;
    
    // Utility
    void print() const {
        std::cout << "  " << name << ", " << age << ", " << grade << std::endl;
    }
    
    bool operator<(const StudentMinimal& other) const {
        return grade < other.grade;
    }
};

// ============================================================================
// VERSION 3: FULL IMPLEMENTATION - Su logging demonstracijai
// ============================================================================

class StudentFull {
private:
    std::string name;
    int age;
    double grade;
    
public:
    // Constructors
    StudentFull(const std::string& n, int a, double g) 
        : name(n), age(a), grade(g) {
        std::cout << "📚 Constructor: " << name << std::endl;
    }
    
    // Rule of Five - pilna implementacija
    StudentFull(const StudentFull& other) 
        : name(other.name), age(other.age), grade(other.grade) {
        std::cout << "📋 Copy constructor: " << name << std::endl;
    }
    
    StudentFull(StudentFull&& other) noexcept
        : name(std::move(other.name)), age(other.age), grade(other.grade) {
        std::cout << "🚚 Move constructor: " << name << std::endl;
    }
    
    StudentFull& operator=(const StudentFull& other) {
        std::cout << "📋 Copy assignment: " << name << " ← " << other.name << std::endl;
        if (this != &other) {
            name = other.name;
            age = other.age;
            grade = other.grade;
        }
        return *this;
    }
    
    StudentFull& operator=(StudentFull&& other) noexcept {
        std::cout << "🚚 Move assignment: " << name << " ← " << other.name << std::endl;
        if (this != &other) {
            name = std::move(other.name);
            age = other.age;
            grade = other.grade;
        }
        return *this;
    }
    
    ~StudentFull() {
        std::cout << "🗑️  Destructor: " << name << std::endl;
    }
    
    // Utility
    void print() const {
        std::cout << "  " << name << ", " << age << ", " << grade << std::endl;
    }
    
    bool operator<(const StudentFull& other) const {
        return grade < other.grade;
    }
};

// ============================================================================
// TESTAI
// ============================================================================

void test_minimal() {
    std::cout << "\n═══════════════════════════════════════════════════════\n";
    std::cout << "TEST 1: StudentMinimal (= default)\n";
    std::cout << "═══════════════════════════════════════════════════════\n";
    
    std::vector<StudentMinimal> students;
    students.emplace_back("Jonas", 20, 8.5);
    students.emplace_back("Petras", 21, 9.0);
    students.emplace_back("Marija", 19, 8.8);
    
    std::cout << "\nPrieš sort:\n";
    for (const auto& s : students) s.print();
    
    std::cout << "\n>>> std::sort() vykdomas...\n";
    std::sort(students.begin(), students.end());
    
    std::cout << "\nPo sort:\n";
    for (const auto& s : students) s.print();
}

void test_full() {
    std::cout << "\n═══════════════════════════════════════════════════════\n";
    std::cout << "TEST 2: StudentFull (su logging)\n";
    std::cout << "═══════════════════════════════════════════════════════\n";
    
    std::vector<StudentFull> students;
    
    std::cout << "\n--- emplace_back ---\n";
    students.emplace_back("Jonas", 20, 7.5);
    students.emplace_back("Petras", 21, 9.0);
    students.emplace_back("Marija", 19, 8.8);
    
    std::cout << "\n--- push_back (copy) ---\n";
    StudentFull temp("Tomas", 22, 8.0);
    students.push_back(temp);
    
    std::cout << "\n--- push_back (move) ---\n";
    students.push_back(StudentFull("Ona", 20, 9.2));
    
    std::cout << "\n--- std::sort() ---\n";
    std::sort(students.begin(), students.end());
    
    std::cout << "\nPo sort:\n";
    for (const auto& s : students) s.print();
    
    std::cout << "\n--- insert() ---\n";
    students.insert(students.begin() + 2, StudentFull("Inserted", 23, 8.5));
    
    std::cout << "\n--- erase() ---\n";
    students.erase(students.begin() + 1);
    
    std::cout << "\n--- Destruktoriai (scope exit) ---\n";
}

void demonstrate_problem() {
    std::cout << "\n═══════════════════════════════════════════════════════\n";
    std::cout << "DEMONSTRACIJA: Kodėl reikia assignment operators?\n";
    std::cout << "═══════════════════════════════════════════════════════\n";
    
    std::cout << "\nSTL operacijos, kurioms reikia assignment:\n";
    std::cout << "  1. std::sort()       - perkelia elementus rūšiuojant\n";
    std::cout << "  2. vector::insert()  - perkelia elementus sukurdamas vietą\n";
    std::cout << "  3. vector::erase()   - perkelia elementus užpildydamas tuštumą\n";
    std::cout << "  4. std::copy()       - kopijuoja į kitą konteinerį\n";
    std::cout << "  5. vector resize()   - gali reikėti perkopijuoti duomenis\n";
    
    std::cout << "\nKai apibrėžiate MOVE CONSTRUCTOR:\n";
    std::cout << "  ❌ Kompiliatorius IŠTRINA copy assignment operator\n";
    std::cout << "  ❌ Kompiliatorius IŠTRINA move assignment operator\n";
    std::cout << "  ✅ Turite apibrėžti juos patys!\n";
    
    std::cout << "\nSprendimai:\n";
    std::cout << "  1. Naudoti = default (jei nereikia custom logic)\n";
    std::cout << "  2. Implementuoti visus Rule of Five\n";
    std::cout << "  3. = delete (jei neleidžiate copy/move)\n";
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    std::cout << "╔═══════════════════════════════════════════════════════╗\n";
    std::cout << "║       RULE OF FIVE - Pedagoginė demonstracija        ║\n";
    std::cout << "╚═══════════════════════════════════════════════════════╝\n";
    
    demonstrate_problem();
    
    test_minimal();
    
    test_full();
    
    std::cout << "\n╔═══════════════════════════════════════════════════════╗\n";
    std::cout << "║                      IŠVADOS                          ║\n";
    std::cout << "╚═══════════════════════════════════════════════════════╝\n";
    std::cout << "\n";
    std::cout << "1. RULE OF FIVE: Apibrėžus vieną → apibrėžk visus 5\n";
    std::cout << "   - Destructor\n";
    std::cout << "   - Copy constructor\n";
    std::cout << "   - Move constructor\n";
    std::cout << "   - Copy assignment operator\n";
    std::cout << "   - Move assignment operator\n";
    std::cout << "\n";
    std::cout << "2. Jei nereikia custom logic → naudok = default\n";
    std::cout << "\n";
    std::cout << "3. STL algoritmai REIKALAUJA assignment operators!\n";
    std::cout << "\n";
    std::cout << "4. Kompiliavimo klaidos bus sudėtingos (templates!)\n";
    std::cout << "   bet priežastis paprasta - trūksta operators\n";
    std::cout << "\n";
    
    return 0;
}

// ============================================================================
// UŽDUOTYS STUDENTAMS:
// ============================================================================
//
// 1. Bandykite paleisti VERSION 1 (išjunkite #if 0)
//    - Pasižiūrėkite į kompiliavimo klaidas
//    - Suprasite, kodėl jos tokios sudėtingos
//
// 2. Palyginkite StudentMinimal ir StudentFull
//    - Kada naudotumėte = default?
//    - Kada reikia pilnos implementacijos?
//
// 3. Pridėkite debug output į StudentMinimal
//    - Pakeiskite = default į full implementation
//    - Stebėkite, kada vyksta copy vs move
//
// 4. Eksperimentuokite su std::vector capacity
//    - Kas atsitinka, kai capacity pasiekiamas?
//    - Kiek copy/move operacijų vyksta?
//    - Kaip reserve() pakeičia elgesį?
//
// 5. Pabandykite = delete
//    - Kas atsitinka, jei: operator=(const Student&) = delete;
//    - Kurios operacijos dar veikia?
//
// ============================================================================
