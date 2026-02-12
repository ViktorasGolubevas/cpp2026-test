// demo_07.cpp - STL std::vector (paprastas variantas)
// Demonstracija: Dinaminis masyvas, automatinis atminties valdymas, STL algoritmai

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
    // Konstruktorius
    Student(const std::string& n, int a, double g) 
        : name(n), age(a), grade(g) {
        std::cout << "📚 Sukurtas: " << name << std::endl;
    }
    
    // Spausdinimas
    void print() const {
        std::cout << "Student: " << name 
                  << ", Amžius: " << age 
                  << ", Pažymys: " << grade << std::endl;
    }
    
    // Getteris
    double get_grade() const { 
        return grade; 
    }
    
    std::string get_name() const {
        return name;
    }
    
    // Palyginimas (reikalingas std::sort)
    bool operator<(const Student& other) const {
        return grade < other.grade;
    }
};

int main() {
    std::cout << "=== STL std::vector demonstracija ===\n\n";
    
    // ========================================================================
    // 1. KŪRIMAS - tuščias vector
    // ========================================================================
    
    std::vector<Student> students;
    std::cout << "Pradinis dydis: " << students.size() << "\n";
    std::cout << "Pradinis capacity: " << students.capacity() << "\n\n";
    
    // ========================================================================
    // 2. PRIDĖJIMAS - push_back ir emplace_back
    // ========================================================================
    
    std::cout << "--- Pridedame studentus (push_back) ---\n";
    
    // push_back - reikia sukurti objektą prieš tai
    Student s1("Jonas", 20, 8.5);
    students.push_back(s1);
    
    // Arba sukuriame ir iš karto įdedame
    students.push_back(Student("Petras", 21, 9.0));
    students.push_back(Student("Marija", 19, 8.8));
    
    std::cout << "\nPo push_back:\n";
    std::cout << "  size = " << students.size() << "\n";
    std::cout << "  capacity = " << students.capacity() << "\n\n";
    
    // emplace_back - efektyvesnis, konstruoja objektą vietoje
    std::cout << "--- Pridedame studentus (emplace_back) ---\n";
    students.emplace_back("Tomas", 22, 7.5);
    students.emplace_back("Ona", 20, 9.2);
    
    std::cout << "\nPo emplace_back:\n";
    std::cout << "  size = " << students.size() << "\n";
    std::cout << "  capacity = " << students.capacity() << "\n\n";
    
    // ========================================================================
    // 3. PRIEIGA - operatorius [] ir at()
    // ========================================================================
    
    std::cout << "--- Prieiga prie elementų ---\n";
    std::cout << "Pirmas studentas (students[0]): ";
    students[0].print();
    
    std::cout << "\nPaskutinis studentas (students.back()): ";
    students.back().print();
    
    std::cout << "\n";
    
    // ========================================================================
    // 4. ITERAVIMAS - range-based for loop
    // ========================================================================
    
    std::cout << "--- Visi studentai (range-based for) ---\n";
    for (const auto& student : students) {
        student.print();
    }
    std::cout << "\n";
    
    // ========================================================================
    // 5. ITERAVIMAS - tradicinis būdas su indeksais
    // ========================================================================
    
    std::cout << "--- Visi studentai (su indeksais) ---\n";
    for (size_t i = 0; i < students.size(); i++) {
        std::cout << i + 1 << ". ";
        students[i].print();
    }
    std::cout << "\n";
    
    // ========================================================================
    // 6. RŪŠIAVIMAS - std::sort()
    // ========================================================================
    
    std::cout << "--- Rūšiavimas pagal pažymį (mažėjimo tvarka) ---\n";
    std::sort(students.begin(), students.end());
    
    for (const auto& student : students) {
        std::cout << "  Pažymys: " << student.get_grade() 
                  << " - " << student.get_name() << "\n";
    }
    std::cout << "\n";
    
    // ========================================================================
    // 7. RŪŠIAVIMAS - custom comparator (didėjimo tvarka)
    // ========================================================================
    
    std::cout << "--- Rūšiavimas pagal pažymį (didėjimo tvarka) ---\n";
    std::sort(students.begin(), students.end(), 
              [](const Student& a, const Student& b) {
                  return a.get_grade() > b.get_grade();
              });
    
    for (const auto& student : students) {
        std::cout << "  Pažymys: " << student.get_grade() 
                  << " - " << student.get_name() << "\n";
    }
    std::cout << "\n";
    
    // ========================================================================
    // 8. ĮTERPIMAS - insert()
    // ========================================================================
    
    std::cout << "--- Įterpiame studentą į antrą poziciją ---\n";
    auto it = students.begin() + 1;  // Pozicija [1]
    students.insert(it, Student("Lukas", 23, 8.7));
    
    std::cout << "Po insert:\n";
    for (size_t i = 0; i < students.size(); i++) {
        std::cout << "  [" << i << "] " << students[i].get_name() << "\n";
    }
    std::cout << "\n";
    
    // ========================================================================
    // 9. ŠALINIMAS - erase()
    // ========================================================================
    
    std::cout << "--- Šaliname trečią studentą ---\n";
    students.erase(students.begin() + 2);
    
    std::cout << "Po erase (size = " << students.size() << "):\n";
    for (size_t i = 0; i < students.size(); i++) {
        std::cout << "  [" << i << "] " << students[i].get_name() << "\n";
    }
    std::cout << "\n";
    
    // ========================================================================
    // 10. PAIEŠKA - std::find_if()
    // ========================================================================
    
    std::cout << "--- Ieškome studento su pažymiu > 9.0 ---\n";
    auto found = std::find_if(students.begin(), students.end(),
                              [](const Student& s) {
                                  return s.get_grade() > 9.0;
                              });
    
    if (found != students.end()) {
        std::cout << "Rastas: ";
        found->print();
    } else {
        std::cout << "Nerastas!\n";
    }
    std::cout << "\n";
    
    // ========================================================================
    // 11. CAPACITY VALDYMAS
    // ========================================================================
    
    std::cout << "--- Capacity valdymas ---\n";
    std::cout << "Dabartinis size: " << students.size() << "\n";
    std::cout << "Dabartinis capacity: " << students.capacity() << "\n\n";
    
    // reserve() - išskiria atmintį iš anksto (išvengiame perkėlimų)
    students.reserve(20);
    std::cout << "Po reserve(20):\n";
    std::cout << "  size: " << students.size() << " (nepasikeitė)\n";
    std::cout << "  capacity: " << students.capacity() << " (padidėjo)\n\n";
    
    // shrink_to_fit() - sumažina capacity iki size
    students.shrink_to_fit();
    std::cout << "Po shrink_to_fit():\n";
    std::cout << "  size: " << students.size() << "\n";
    std::cout << "  capacity: " << students.capacity() << "\n\n";
    
    // ========================================================================
    // 12. IŠVALYMAS
    // ========================================================================
    
    std::cout << "--- Išvalome vector ---\n";
    students.clear();
    std::cout << "Po clear():\n";
    std::cout << "  size: " << students.size() << "\n";
    std::cout << "  capacity: " << students.capacity() 
              << " (capacity lieka!)\n\n";
    
    // ========================================================================
    // 13. PRADINIS DYDIS
    // ========================================================================
    
    std::cout << "--- Kuriame vector su pradiniu dydžiu ---\n";
    std::vector<int> numbers(5, 100);  // 5 elementai, visi = 100
    
    std::cout << "numbers = { ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "}\n";
    
    return 0;
}

// ============================================================================
// PASTABOS STUDENTAMS:
// ============================================================================
//
// 1. AUTOMATINIS ATMINTIES VALDYMAS:
//    - vector PATS valdo atmintį (new/delete nevartojamas!)
//    - Išeinant iš scope, atmintis automatiškai atlaisvinama
//    - Nereikia RAII patternų - jau įdiegta!
//
// 2. PUSH_BACK vs EMPLACE_BACK:
//    - push_back(obj) - reikia sukurto objekto
//    - emplace_back(args...) - konstruoja objektą vietoje (efektyviau)
//
// 3. SIZE vs CAPACITY:
//    - size = kiek elementų realiai yra
//    - capacity = kiek elementų galima įdėti be naujo alokavimo
//    - Kai size == capacity, pridedant naują elementą capacity dvigubėja!
//
// 4. ITERATORIAI:
//    - begin() - pirmas elementas
//    - end() - VIENA POZICIJA PO paskutinio (ne pats paskutinis!)
//    - Iteratoriai gali sugesti po insert/erase/push_back (jei reallocate)
//
// 5. STL ALGORITMAI:
//    - std::sort() - rūšiavimas (reikia operator< arba custom comparator)
//    - std::find_if() - paieška su lambda funkcija
//    - Visi algoritmai veikia su iteratoriais, ne indeksais!
//
// 6. LAMBDA FUNKCIJOS (C++11):
//    - [](args) { body } - anoniminis funkcijos objektas
//    - Naudojamas kaip callback std::sort, std::find_if ir kt.
//
// 7. EFEKTYVUMAS:
//    - reserve() prieš daug pridėjimų - išvengia perkėlimų
//    - emplace_back > push_back - konstruoja vietoje
//    - Pass by const reference - išvengia kopijų
//
// 8. DAŽNIAUSIOS KLAIDOS:
//    - students[i] nespaudžia bounds (gali crash)
//    - students.at(i) tikrina bounds (meta exception jei out of range)
//    - Naudoti invalidated iterator po erase/insert
//
// ============================================================================
