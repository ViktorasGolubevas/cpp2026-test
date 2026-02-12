# std::vector Užduotys Studentams

## 🎯 Lengvos Užduotys (Pradedantiesiems)

### Užduotis 1: Pridėjimas ir Spausdinimas
Sukurkite programą, kuri:
1. Sukuria tuščią `vector<int>`
2. Prideda 10 skaičių (nuo 1 iki 10)
3. Išspausdina visus skaičius

**Pavyzdys:**
```
Skaičiai: 1 2 3 4 5 6 7 8 9 10
```

---

### Užduotis 2: Suma ir Vidurkis
Sukurkite programą, kuri:
1. Sukuria `vector<double>` su 5 pažymiais
2. Suskaičiuoja sumą
3. Suskaičiuoja vidurkį

**Pavyzdys:**
```
Pažymiai: 8.5 9.0 7.5 8.8 9.2
Suma: 43.0
Vidurkis: 8.6
```

---

### Užduotis 3: Maksimumas ir Minimumas
Sukurkite programą, kuri:
1. Nuskaito 5 skaičius į vector
2. Suranda didžiausią skaičių
3. Suranda mažiausią skaičių

**Pavyzdys:**
```
Įveskite 5 skaičius: 3 8 1 9 5
Maksimumas: 9
Minimumas: 1
```

---

## 📊 Vidutinės Užduotys

### Užduotis 4: Studentų Klasė
Sukurkite `Student` klasę ir programą:

```cpp
class Student {
private:
    std::string name;
    double grade;
    
public:
    Student(std::string n, double g) : name(n), grade(g) {}
    
    // TODO: Pridėkite reikalingus metodus
};
```

Funkcionalumas:
1. Sukurti 5 studentus
2. Išrūšiuoti pagal pažymį
3. Atspausdinti visus studentus

**Pavyzdys:**
```
Studentai (rūšiuoti):
1. Tomas - 7.5
2. Jonas - 8.5
3. Marija - 8.8
4. Petras - 9.0
5. Ona - 9.2
```

---

### Užduotis 5: Filtravimas
Parašykite funkciją, kuri:
1. Priima `vector<int>` ir slenkstį
2. Grąžina naują vector tik su skaičiais > slenksčio

```cpp
std::vector<int> filter_greater(const std::vector<int>& vec, int threshold) {
    // TODO: Implementuoti
}
```

**Pavyzdys:**
```cpp
std::vector<int> nums = {3, 8, 1, 9, 5, 2, 7};
auto result = filter_greater(nums, 5);
// result = {8, 9, 7}
```

---

### Užduotis 6: Paieška
Parašykite programą su funkcijomis:

```cpp
// Ieško studento pagal vardą
int find_student(const std::vector<Student>& students, const std::string& name);

// Grąžina studentus su pažymiu >= threshold
std::vector<Student> get_top_students(const std::vector<Student>& students, double threshold);
```

---

## 🚀 Sudėtingesnės Užduotys

### Užduotis 7: 2D Vector (Matrix)
Sukurkite 2D vector (matrica):

```cpp
// 3x3 matrica
std::vector<std::vector<int>> matrix = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};
```

Funkcionalumas:
1. Atspausdinti matricą
2. Suskaičiuoti kiekvienos eilutės sumą
3. Suskaičiuoti kiekvieno stulpelio sumą

**Pavyzdys:**
```
Matrix:
1  2  3  | Suma: 6
4  5  6  | Suma: 15
7  8  9  | Suma: 24
──────────
12 15 18
```

---

### Užduotis 8: Histograma
Parašykite funkciją, kuri vaizduoja pažymių histogramą:

```cpp
void print_histogram(const std::vector<double>& grades) {
    // TODO: Implementuoti
}
```

**Pavyzdys:**
```
Pažymių Histograma:
7.0-7.9: **
8.0-8.9: ****
9.0-10.0: ***
```

---

### Užduotis 9: Grupių Sistema
Sukurkite programą su keletu klasių:

```cpp
class Student {
    std::string name;
    double grade;
    // ...
};

class Group {
    std::string groupName;
    std::vector<Student> students;
    
public:
    void add_student(const Student& s);
    double get_average() const;
    void print_students() const;
    // ...
};
```

Funkcionalumas:
1. Sukurti 3 grupes
2. Pridėti studentus į grupes
3. Atspausdinti kiekvienos grupės vidurkį
4. Rasti geriausią grupę

---

### Užduotis 10: Studentų Duomenų Bazė
Sukurkite mini duomenų bazę:

Funkcijos:
- `add_student()` - prideda studentą
- `remove_student(name)` - ištrina studentą pagal vardą
- `find_by_grade(min, max)` - randa studentus intervale
- `sort_by_name()` - rūšiuoja pagal vardą
- `sort_by_grade()` - rūšiuoja pagal pažymį
- `export_to_file(filename)` - išsaugo į failą
- `import_from_file(filename)` - nuskaito iš failo

---

## 🎨 Kūrybiškos Užduotys

### Užduotis 11: Žaidimas
Sukurkite paprastą žaidimą su vector:
- Tic-Tac-Toe (3x3 vector)
- Snake žaidimas (kūnas kaip vector)
- Card game (kortos kaip vector)

---

### Užduotis 12: Analizė
Nuskaitykite skaičius iš failo į vector ir:
1. Suskaičiuokite statistiką (vidurkis, mediana, moda)
2. Nubrėžkite histogramą
3. Raskite išskirtis (outliers)

---

## 💡 Patarimai

### Lengvoms Užduotims:
```cpp
// Iteravimas
for (const auto& item : vec) { ... }

// Pridėjimas
vec.push_back(item);
vec.emplace_back(args...);

// Dydis
vec.size()
```

### Vidutinėms Užduotims:
```cpp
// Rūšiavimas
std::sort(vec.begin(), vec.end());

// Lambda
[](const T& a, const T& b) { return a < b; }

// Paieška
std::find_if(vec.begin(), vec.end(), predicate);
```

### Sudėtingesnėms Užduotims:
```cpp
// Filtravimas
std::remove_if(vec.begin(), vec.end(), predicate);
vec.erase(..., vec.end());

// Transformavimas
std::transform(input.begin(), input.end(), output.begin(), func);

// 2D prieiga
matrix[row][col]
```

---

## 🎓 Vertinimo Kriterijai

### Lengvos (1-3):
- Kodas kompiliuojasi ✅
- Veikia su testavimo duomenimis ✅
- Komentarai ✅

### Vidutinės (4-6):
- Visi aukščiau minėti ✅
- Naudoja const reference ✅
- Naudoja range-based for ✅
- Geras error handling ✅

### Sudėtingesnės (7-10):
- Visi aukščiau minėti ✅
- Gerai organizuotas kodas ✅
- Atskiros funkcijos logiškiems blokams ✅
- Naudoja STL algoritmus ✅
- Efektyvus (reserve, emplace_back) ✅

---

## 📦 Pavyzdinė Struktūra

```
student_database/
├── main.cpp
├── Student.h
├── Student.cpp
├── Database.h
├── Database.cpp
├── utils.h
└── utils.cpp
```

---

## 🚀 Bonusas

**+10% prie pažymio:**
- Naudoja Google Test framework testams
- CI/CD su GitHub Actions
- CMake build sistema
- Doxygen dokumentacija

---

**Sėkmės!** 🎉

Jei kyla klausimų - klauskite dėstytojo arba bendramokslių!
