# STL std::vector - Paprasta Demonstracija

## 📦 Kas čia yra?

Paprasta, suprantama `std::vector` demonstracija **be jokių sudėtingų konceptų**:
- ❌ **Be** Rule of Five
- ❌ **Be** move semantics
- ❌ **Be** custom copy constructors
- ✅ **Tik** gražus, automatinis C++ konteineris!

## 🎯 Tikslas

Parodyti, kad `std::vector` yra:
1. **Paprastas** naudoti (kaip Python list)
2. **Saugus** (automatinis atminties valdymas)
3. **Galingas** (STL algoritmai veikia iš karto)

**Nereikia baimintis!** C++ su STL yra draugiškas! 🤗

---

## 🚀 Kompiliavimas ir Paleidimas

### Linux / Git Bash / WSL:
```bash
g++ demo_07_simple.cpp -o app -std=c++11 -Wall
./app
```

### Windows (MinGW):
```bash
g++ demo_07_simple.cpp -o app.exe -std=c++11 -Wall
app.exe
```

### Windows UTF-8 emoji palaikymui:
```bash
chcp 65001
g++ demo_07_simple.cpp -o app.exe -std=c++11 -Wall
app.exe
```

---

## 📚 Kas Demonstruojama?

### 1. **Kūrimas ir Pridėjimas** 📝
```cpp
std::vector<Student> students;

// push_back - prideda pabaigoje
students.push_back(Student("Jonas", 20, 8.5));

// emplace_back - efektyvesnis (C++11)
students.emplace_back("Petras", 21, 9.0);
```

### 2. **Prieiga prie Elementų** 🔍
```cpp
students[0].print();           // Pirmas
students.back().print();       // Paskutinis
students.at(1).print();        // Su bounds checking
```

### 3. **Iteravimas** 🔄
```cpp
// Range-based for (C++11) - REKOMENDUOJAMA
for (const auto& student : students) {
    student.print();
}

// Tradicinis būdas
for (size_t i = 0; i < students.size(); i++) {
    students[i].print();
}
```

### 4. **Rūšiavimas** 📊
```cpp
// Su operator<
std::sort(students.begin(), students.end());

// Su lambda (custom comparator)
std::sort(students.begin(), students.end(), 
          [](const Student& a, const Student& b) {
              return a.get_grade() > b.get_grade();
          });
```

### 5. **Įterpimas ir Šalinimas** ✂️
```cpp
// Insert į konkretią poziciją
students.insert(students.begin() + 1, newStudent);

// Erase konkretų elementą
students.erase(students.begin() + 2);
```

### 6. **Paieška** 🔎
```cpp
auto found = std::find_if(students.begin(), students.end(),
                          [](const Student& s) {
                              return s.get_grade() > 9.0;
                          });

if (found != students.end()) {
    found->print();
}
```

### 7. **Capacity Valdymas** 💾
```cpp
students.reserve(20);        // Išskiria atmintį iš anksto
students.shrink_to_fit();    // Sumažina capacity iki size
students.clear();            // Išvalo turinį (capacity lieka)
```

---

## 🎓 Svarbūs Konceptai

### Size vs Capacity

```
┌────────────────────────────────────────┐
│ [0] [1] [2] [3] [4] [ ] [ ] [ ]        │
│ ─────────────────── ───────────        │
│       size=5         capacity=8        │
└────────────────────────────────────────┘
```

- **size** = kiek elementų realiai yra
- **capacity** = kiek vietos užrezervuota
- Kai `size == capacity`, pridedant naują:
  - Vector perkelia visus į naują didesnę vietą
  - Paprastai **dvigubina** capacity

### Iteratoriai

```cpp
students.begin()  → [Jonas, Petras, Marija, ...]
                    ↑
                    
students.end()    → [Jonas, Petras, Marija, ...]
                                             ↑
                    (viena pozicija PO paskutinio!)
```

**SVARBU:** `end()` **nėra** paskutinis elementas!

### Lambda Funkcijos (C++11)

```cpp
[](args) { return result; }
 ↑  ↑          ↑
 │  │          └─ Function body
 │  └──────────── Parametrai
 └─────────────── Capture clause (kol kas tuščias)
```

---

## ⚡ Efektyvumo Patarimai

### ✅ GERAI:
```cpp
students.reserve(100);  // Jei žinai, kiek bus elementų
students.emplace_back("Jonas", 20, 8.5);  // Efektyviau nei push_back

for (const auto& s : students) {  // Pass by reference
    s.print();
}
```

### ❌ BLOGAI:
```cpp
for (int i = 0; i < 1000; i++) {
    students.push_back(...);  // Be reserve() - daug reallocation
}

for (auto s : students) {  // Kopijuoja kiekvieną objektą!
    s.print();
}

students[999];  // Jei size < 1000 → undefined behavior!
```

---

## 🐛 Dažniausios Klaidos

### 1. Out of Bounds
```cpp
std::vector<int> v = {1, 2, 3};
v[10] = 100;  // ❌ Undefined behavior!
v.at(10) = 100;  // ✅ Throws exception
```

### 2. Invalidated Iterator
```cpp
auto it = students.begin();
students.push_back(...);  // Gali perkelt į naują vietą!
*it;  // ❌ Iterator gali būti invalid!
```

### 3. end() nėra paskutinis elementas!
```cpp
auto last = students.end();
last->print();  // ❌ KLAIDA!

auto last = students.end() - 1;
last->print();  // ✅ Teisingai

students.back().print();  // ✅ Paprasčiau!
```

---

## 📖 Palyginimas su C Array

| Funkcija | C Array | std::vector |
|----------|---------|-------------|
| Dydis kompiliavimo metu | ✅ Taip | ❌ Ne (dinaminis) |
| Automatinis atminties valdymas | ❌ Ne | ✅ Taip |
| Bounds checking | ❌ Ne | ✅ at() |
| Dydžio keitimas | ❌ Ne | ✅ push_back, resize |
| STL algoritmai | ⚠️ Su pointers | ✅ Tiesiogiai |
| Efektyvumas | ✅ Greitas | ✅ Beveik toks pat |

---

## 🎯 Užduotys Studentams

### Lengva:
1. Pridėkite metodą `set_grade(double g)` į Student klasę
2. Sukurkite vector su 10 studentų ir išrūšiuokite pagal vardą
3. Parašykite funkciją, kuri suskaičiuoja vidurkį

### Vidutinė:
4. Ištrinkite visus studentus su pažymiu < 5.0
   - Naudokite `std::remove_if()` ir `erase()`
5. Sukurkite funkciją, kuri suranda studentą pagal vardą
6. Parašykite funkciją, kuri grąžina top 3 studentus

### Sudėtingesnė:
7. Sukurkite 2D vector (vector of vectors)
   - Kiekviena "grupė" turi studentų vector
8. Parašykite funkciją, kuri filtruoja studentus pagal pažymį
   - Grąžina naują vector
9. Implementuokite `print_histogram()` - parodo pažymių pasiskirstymą

---

## 💡 Ko NEREIKIA Šiame Etape

❌ **Rule of Five** - per sudėtinga, paliksime vėlesniam etapui  
❌ **Move semantics** - C++ pats tvarkosi  
❌ **Custom copy constructors** - nereikia!  
❌ **Smart pointers** - dar ne šioje temoje  

**Tiesiog džiaukitės automatiniu atminties valdymu!** 🎉

---

## 🔗 Tolimesnis Mokymasis

### Sekantys Žingsniai:
1. ✅ **vector** - išmokome! 
2. 📝 **list** - doubly linked list
3. 🗺️ **map** - associative container
4. 📚 **set** - unique elements
5. ⚡ **algorithms** - daugiau STL galimybių

### Kai Bus Pasirengę (Vėliau):
- Move semantics ir rvalue references
- Rule of Five
- Perfect forwarding
- Custom allocators

---

## 📞 Pagalba

Jei kyla klausimų:
- Perskaitykite komentarus faile `demo_07_simple.cpp`
- cppreference.com - `std::vector` dokumentacija
- Klauskite dėstytojo! 😊

---

**Autorius:** Viktoras Golubevas  
**Kursas:** Objektinis Programavimas su C++  
**Data:** 2026-02-12

**Atminkite:** `std::vector` yra jūsų draugas! 🤝
