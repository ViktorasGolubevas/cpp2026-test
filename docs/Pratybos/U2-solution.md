# U2: Sprendimas - OOP Pagrindai. Klasės ir Objektai

**Dėstytojui:** Šis failas skirtas jums - pilnas sprendimas su kodu, paaiškinimais ir "virtuve".

---

## 📁 Galutinė failų struktūra

```
U2/
├── 01/
│   ├── student_struct.cpp
│   └── student_class.cpp
├── 02/
│   ├── Student.h
│   ├── Student.cpp
│   ├── main.cpp
│   └── Makefile
├── 03/
│   ├── Student.h
│   ├── Student.cpp
│   ├── main.cpp
│   └── Makefile
├── 04/
│   ├── Student.h
│   ├── Student.cpp
│   ├── main.cpp
│   └── Makefile
├── 05/
│   ├── Student.h
│   ├── Student.cpp
│   ├── main.cpp
│   └── Makefile
└── 06-bonus/
    ├── Student.h
    ├── Student.cpp
    ├── main.cpp
    └── Makefile
```

---

## 1️⃣ **1 žingsnis: Struct → Class transformacija**

### **student_struct.cpp (C struktūros versija):**

```cpp
#include <iostream>
#include <cstring>
using namespace std;

struct Student {
    char vardas[50];
    int amzius;
    double pazymys;
};

int main() {
    Student s1;
    strcpy(s1.vardas, "Jonas");
    s1.amzius = 20;
    s1.pazymys = 8.5;
    
    cout << "Studentas: " << s1.vardas 
         << ", Amžius: " << s1.amzius 
         << ", Pažymys: " << s1.pazymys << endl;
    
    return 0;
}
```

### **Kompiliavimas:**
```bash
g++ student_struct.cpp -o struct_versija
./struct_versija
```

### **Išvestis:**
```
Studentas: Jonas, Amžius: 20, Pažymys: 8.5
```

---

### **student_class.cpp (C++ klasės versija su public):**

```cpp
#include <iostream>
#include <cstring>
using namespace std;

class Student {
public:  // Visi nariai public (kaip struct)
    char vardas[50];
    int amzius;
    double pazymys;
};

int main() {
    Student s1;
    strcpy(s1.vardas, "Petras");
    s1.amzius = 21;
    s1.pazymys = 9.0;
    
    cout << "Studentas: " << s1.vardas 
         << ", Amžius: " << s1.amzius 
         << ", Pažymys: " << s1.pazymys << endl;
    
    return 0;
}
```

### **Kompiliavimas:**
```bash
g++ student_class.cpp -o class_versija
./class_versija
```

### **Išvestis:**
```
Studentas: Petras, Amžius: 21, Pažymys: 9
```

### **Pedagoginės pastabos:**
- ✅ Abu failai **veikia vienodai** - skirtumas tik `struct` vs `class` keyword
- ✅ `struct` - nariai **public** pagal nutylėjimą
- ✅ `class` su `public:` - taip pat visi nariai **public**
- 💡 Kitas žingsnis: `class` su `private` - tikroji enkapsulacija
- ⚠️ Dažna klaida: Pamiršti `;` po `}` klasės deklaracijoje

---

## 2️⃣ **2 žingsnis: Konstruktoriai**

### **Student.h:**

```cpp
#ifndef STUDENT_H
#define STUDENT_H

class Student {
private:
    char vardas[50];
    int amzius;
    double pazymys;
    
public:
    // Konstruktoriai
    Student();  // Default
    Student(const char* v, int a, double p);  // Parametrinis
    
    // Metodai (kol kas tik prototypai)
};

#endif
```

### **Student.cpp:**

```cpp
#include "Student.h"
#include <iostream>
#include <cstring>

// Default konstruktorius
Student::Student() {
    strcpy(vardas, "Nezinomas");
    amzius = 0;
    pazymys = 0.0;
    std::cout << "[TEST] Student sukurtas (default): " << vardas << std::endl;
}

// Parametrinis konstruktorius
Student::Student(const char* v, int a, double p) {
    strcpy(vardas, v);
    amzius = a;
    pazymys = p;
    std::cout << "[TEST] Student sukurtas: " << vardas << std::endl;
}
```

### **main.cpp:**

```cpp
#include <iostream>
#include "Student.h"
using namespace std;

int main() {
    Student s1;  // Default konstruktorius
    Student s2("Jonas", 20, 8.5);  // Parametrinis
    Student s3("Petras", 21, 9.0);
    
    return 0;
}
```

### **Makefile:**

```makefile
CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJS = main.o Student.o
TARGET = programa

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

main.o: main.cpp Student.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Student.o: Student.cpp Student.h
	$(CXX) $(CXXFLAGS) -c Student.cpp

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
```

### **Kompiliavimas:**
```bash
make
./programa
```

### **Išvestis:**
```
[TEST] Student sukurtas (default): Nezinomas
[TEST] Student sukurtas: Jonas
[TEST] Student sukurtas: Petras
```

### **Pedagoginės pastabos:**
- ✅ Konstruktorius **automatiškai** kviečiamas sukuriant objektą
- ✅ Default konstruktorius - **be parametrų**
- ✅ Parametrinis konstruktorius - **su parametrais**
- ✅ `strcpy()` - C-style string kopijavimas (reikia `<cstring>`)
- 💡 **Initialization list** (paminėti kaip alternatyvą 4 žingsnyje)
- ⚠️ Dažna klaida: Užmiršti `strcpy()`, tiesiog `vardas = v` (ne veiks!)
- ⚠️ Dažna klaida: Pamiršti header guard'us `Student.h` faile

---

## 3️⃣ **3 žingsnis: Metodai (getters, setters, pagalbiniai)**

### **Student.h:**

```cpp
#ifndef STUDENT_H
#define STUDENT_H

class Student {
private:
    char vardas[50];
    int amzius;
    double pazymys;
    
public:
    // Konstruktoriai
    Student();
    Student(const char* v, int a, double p);
    
    // Getters (const metodai!)
    const char* gautiVarda() const;
    int gautiAmziu() const;
    double gautiPazymi() const;
    
    // Setters
    void nustatytiVarda(const char* v);
    void nustatytiAmziu(int a);
    void nustatytiPazymi(double p);
    
    // Pagalbiniai metodai
    bool arPilnametis() const;
    void spausdinti() const;
};

#endif
```

### **Student.cpp:**

```cpp
#include "Student.h"
#include <iostream>
#include <cstring>

// Konstruktoriai (tie patys kaip žingsnis 2)
Student::Student() {
    strcpy(vardas, "Nezinomas");
    amzius = 0;
    pazymys = 0.0;
}

Student::Student(const char* v, int a, double p) {
    strcpy(vardas, v);
    amzius = a;
    pazymys = p;
}

// Getters
const char* Student::gautiVarda() const {
    return vardas;
}

int Student::gautiAmziu() const {
    return amzius;
}

double Student::gautiPazymi() const {
    return pazymys;
}

// Setters (su patvirtinimu)
void Student::nustatytiVarda(const char* v) {
    strcpy(vardas, v);
}

void Student::nustatytiAmziu(int a) {
    if (a > 0 && a < 120) {  // Patikrinimas
        amzius = a;
    }
}

void Student::nustatytiPazymi(double p) {
    if (p >= 0.0 && p <= 10.0) {  // Patikrinimas
        pazymys = p;
    }
}

// Pagalbiniai metodai
bool Student::arPilnametis() const {
    return amzius >= 18;
}

void Student::spausdinti() const {
    std::cout << "Studentas: " << vardas 
              << ", Amžius: " << amzius 
              << ", Pažymys: " << pazymys;
    
    if (arPilnametis()) {
        std::cout << " (pilnametis)";
    }
    std::cout << std::endl;
}
```

### **main.cpp:**

```cpp
#include <iostream>
#include "Student.h"
using namespace std;

int main() {
    Student s1("Jonas", 20, 8.5);
    s1.spausdinti();
    
    s1.nustatytiPazymi(9.0);
    cout << "Naujas pažymys: " << s1.gautiPazymi() << endl;
    
    Student s2("Petras", 16, 7.5);
    s2.spausdinti();
    
    return 0;
}
```

### **Išvestis:**
```
Studentas: Jonas, Amžius: 20, Pažymys: 8.5 (pilnametis)
Naujas pažymys: 9
Studentas: Petras, Amžius: 16, Pažymys: 7.5
```

### **Pedagoginės pastabos:**
- ✅ `const` metodai - **nekeičia** objekto būsenos (getters, pagalbiniai)
- ✅ Getters - **tik skaito**, setters - **modifikuoja**
- ✅ Patikrinimas setter'iuose - **validacija**
- 💡 Enkapsulacija - privatūs duomenys, public metodai
- ⚠️ Dažna klaida: Pamiršti `const` getter'iams (kompiliatorius skundžiasi)
- ⚠️ Dažna klaida: `strcpy(vardas, v)` setter'yje, o ne `vardas = v`

---

## 4️⃣ **4 žingsnis: Static counter + destruktorius**

### **Student.h:**

```cpp
#ifndef STUDENT_H
#define STUDENT_H

class Student {
private:
    char vardas[50];
    int amzius;
    double pazymys;
    
    static int sukurtaStudentu;  // Statinis skaitiklis
    
public:
    // Konstruktoriai
    Student();
    Student(const char* v, int a, double p);
    ~Student();  // Destruktorius
    
    // Getters
    const char* gautiVarda() const;
    int gautiAmziu() const;
    double gautiPazymi() const;
    
    // Setters
    void nustatytiVarda(const char* v);
    void nustatytiAmziu(int a);
    void nustatytiPazymi(double p);
    
    // Pagalbiniai
    bool arPilnametis() const;
    void spausdinti() const;
    
    // Static getter
    static int gautiSukurtaStudentu();
};

#endif
```

### **Student.cpp:**

```cpp
#include "Student.h"
#include <iostream>
#include <cstring>

// Statinio nario inicializacija (už klasės ribų!)
int Student::sukurtaStudentu = 0;

// Default konstruktorius
Student::Student() {
    strcpy(vardas, "Nezinomas");
    amzius = 0;
    pazymys = 0.0;
    sukurtaStudentu++;
    std::cout << "[TEST] Student sukurtas (default): " << vardas 
              << ". Viso studentų: " << sukurtaStudentu << std::endl;
}

// Parametrinis konstruktorius
Student::Student(const char* v, int a, double p) {
    strcpy(vardas, v);
    amzius = a;
    pazymys = p;
    sukurtaStudentu++;
    std::cout << "[TEST] Student sukurtas: " << vardas 
              << ". Viso studentų: " << sukurtaStudentu << std::endl;
}

// Destruktorius
Student::~Student() {
    sukurtaStudentu--;
    std::cout << "[TEST] Student sunaikintas: " << vardas 
              << ". Liko studentų: " << sukurtaStudentu << std::endl;
}

// Getters, setters, pagalbiniai (tie patys kaip žingsnis 3)
// ...

// Static getter
int Student::gautiSukurtaStudentu() {
    return sukurtaStudentu;
}
```

### **main.cpp:**

```cpp
#include <iostream>
#include "Student.h"
using namespace std;

int main() {
    cout << "Studentų: " << Student::gautiSukurtaStudentu() << endl;  // 0
    
    {
        Student s1("Jonas", 20, 8.5);
        Student s2("Petras", 21, 9.0);
        cout << "Studentų: " << Student::gautiSukurtaStudentu() << endl;  // 2
    }  // s1 ir s2 sunaikinami čia
    
    cout << "Studentų: " << Student::gautiSukurtaStudentu() << endl;  // 0
    
    return 0;
}
```

### **Išvestis:**
```
Studentų: 0
[TEST] Student sukurtas: Jonas. Viso studentų: 1
[TEST] Student sukurtas: Petras. Viso studentų: 2
Studentų: 2
[TEST] Student sunaikintas: Petras. Liko studentų: 1
[TEST] Student sunaikintas: Jonas. Liko studentų: 0
Studentų: 0
```

### **Pedagoginės pastabos:**
- ✅ **Static** narys - **bendras visiems objektams** (ne kiekvienas turi savo)
- ✅ Inicializacija **už klasės ribų**: `int Student::sukurtaStudentu = 0;`
- ✅ Destruktorius - **automatiškai** kviečiamas išeinant iš scope
- ✅ Static getter - galima kviesti **be objekto**: `Student::gautiSukurtaStudentu()`
- 💡 **Initialization list alternatyva** (paminėti studentams):
  ```cpp
  Student::Student(const char* v, int a, double p) 
      : amzius(a), pazymys(p)  // Initialization list
  {
      strcpy(vardas, v);  // char[] reikia body'je
      sukurtaStudentu++;
  }
  ```
- ⚠️ Dažna klaida: Pamiršti inicializuoti static narį už klasės (`int Student::sukurtaStudentu = 0;`)
- ⚠️ Dažna klaida: Bandyti inicializuoti static narį konstruktoriuje (`sukurtaStudentu = 0` - blogai!)

---

## 5️⃣ **5 žingsnis: Pažymių masyvas**

### **Student.h:**

```cpp
#ifndef STUDENT_H
#define STUDENT_H

class Student {
private:
    char vardas[50];
    int amzius;
    
    // Pažymių masyvas
    static const int MAX_PAZYMIU = 20;
    double pazymiai[MAX_PAZYMIU];
    int pazymiuKiekis;
    
    static int sukurtaStudentu;
    
public:
    // Konstruktoriai (be pažymio parametro!)
    Student();
    Student(const char* v, int a);
    ~Student();
    
    // Getters
    const char* gautiVarda() const;
    int gautiAmziu() const;
    
    // Setters
    void nustatytiVarda(const char* v);
    void nustatytiAmziu(int a);
    
    // Pažymių metodai
    void pridetiPazymi(double p);
    double skaiciuotiVidurki() const;
    void spausdintiPazymius() const;
    
    // Pagalbiniai
    bool arPilnametis() const;
    void spausdinti() const;
    
    // Static
    static int gautiSukurtaStudentu();
};

#endif
```

### **Student.cpp:**

```cpp
#include "Student.h"
#include <iostream>
#include <cstring>

int Student::sukurtaStudentu = 0;

// Default konstruktorius
Student::Student() {
    strcpy(vardas, "Nezinomas");
    amzius = 0;
    pazymiuKiekis = 0;  // Pradžioje 0 pažymių
    sukurtaStudentu++;
    std::cout << "[TEST] Student sukurtas (default): " << vardas 
              << ". Viso studentų: " << sukurtaStudentu << std::endl;
}

// Parametrinis konstruktorius (be pažymio!)
Student::Student(const char* v, int a) {
    strcpy(vardas, v);
    amzius = a;
    pazymiuKiekis = 0;
    sukurtaStudentu++;
    std::cout << "[TEST] Student sukurtas: " << vardas 
              << ". Viso studentų: " << sukurtaStudentu << std::endl;
}

// Destruktorius
Student::~Student() {
    sukurtaStudentu--;
    std::cout << "[TEST] Student sunaikintas: " << vardas 
              << ". Liko studentų: " << sukurtaStudentu << std::endl;
}

// Getters, setters (tie patys)
// ...

// Pažymių metodai
void Student::pridetiPazymi(double p) {
    if (pazymiuKiekis < MAX_PAZYMIU && p >= 0.0 && p <= 10.0) {
        pazymiai[pazymiuKiekis] = p;
        pazymiuKiekis++;
    } else {
        std::cout << "[KLAIDA] Negalima pridėti pažymio!" << std::endl;
    }
}

double Student::skaiciuotiVidurki() const {
    if (pazymiuKiekis == 0) {
        return 0.0;
    }
    
    double suma = 0.0;
    for (int i = 0; i < pazymiuKiekis; i++) {
        suma += pazymiai[i];
    }
    
    return suma / pazymiuKiekis;
}

void Student::spausdintiPazymius() const {
    std::cout << "Pažymiai (" << pazymiuKiekis << "): ";
    for (int i = 0; i < pazymiuKiekis; i++) {
        std::cout << pazymiai[i];
        if (i < pazymiuKiekis - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

void Student::spausdinti() const {
    std::cout << "Studentas: " << vardas 
              << ", Amžius: " << amzius << std::endl;
    spausdintiPazymius();
    std::cout << "Vidurkis: " << skaiciuotiVidurki() << std::endl;
}

int Student::gautiSukurtaStudentu() {
    return sukurtaStudentu;
}
```

### **main.cpp:**

```cpp
#include <iostream>
#include "Student.h"
using namespace std;

int main() {
    Student s1("Jonas", 20);
    
    s1.pridetiPazymi(8.5);
    s1.pridetiPazymi(9.0);
    s1.pridetiPazymi(7.5);
    s1.pridetiPazymi(8.0);
    
    s1.spausdinti();
    
    return 0;
}
```

### **Išvestis:**
```
[TEST] Student sukurtas: Jonas. Viso studentų: 1
Studentas: Jonas, Amžius: 20
Pažymiai (4): 8.5, 9, 7.5, 8
Vidurkis: 8.25
[TEST] Student sunaikintas: Jonas. Liko studentų: 0
```

### **Pedagoginės pastabos:**
- ✅ Masyvas `double pazymiai[MAX_PAZYMIU]` + `int pazymiuKiekis` - kaip U1
- ✅ Patikrinimas: `pazymiuKiekis < MAX_PAZYMIU` (ribos)
- ✅ Vidurkio skaičiavimas - suma / kiekis
- 💡 Kitas žingsnis - vector (dinaminis, be limitų)
- ⚠️ Dažna klaida: Pamiršti `pazymiuKiekis = 0` konstruktoriuje
- ⚠️ Dažna klaida: `pazymiai[pazymiuKiekis++] = p` vietoj dviejų eilučių
- ⚠️ Dažna klaida: Off-by-one kablelių spausdinime (`i < pazymiuKiekis - 1`)

---

## 6️⃣ **BONUS žingsnis: Masyvas → vector**

### **Student.h:**

```cpp
#ifndef STUDENT_H
#define STUDENT_H

#include <vector>  // SVARBU!

class Student {
private:
    char vardas[50];
    int amzius;
    
    // Vector vietoj masyvo
    std::vector<double> pazymiai;
    
    static int sukurtaStudentu;
    
public:
    // Konstruktoriai
    Student();
    Student(const char* v, int a);
    ~Student();
    
    // Getters, setters
    const char* gautiVarda() const;
    int gautiAmziu() const;
    void nustatytiVarda(const char* v);
    void nustatytiAmziu(int a);
    
    // Pažymių metodai
    void pridetiPazymi(double p);
    double skaiciuotiVidurki() const;
    void spausdintiPazymius() const;
    
    // Pagalbiniai
    bool arPilnametis() const;
    void spausdinti() const;
    
    // Static
    static int gautiSukurtaStudentu();
};

#endif
```

### **Student.cpp:**

```cpp
#include "Student.h"
#include <iostream>
#include <cstring>

int Student::sukurtaStudentu = 0;

// Konstruktoriai (pazymiai jau tuščias vector)
Student::Student() {
    strcpy(vardas, "Nezinomas");
    amzius = 0;
    // pazymiai - default konstruktorius (tuščias vector)
    sukurtaStudentu++;
}

Student::Student(const char* v, int a) {
    strcpy(vardas, v);
    amzius = a;
    // pazymiai - default konstruktorius (tuščias vector)
    sukurtaStudentu++;
}

// Pažymių metodai (atnaujinti su vector)
void Student::pridetiPazymi(double p) {
    if (p >= 0.0 && p <= 10.0) {
        pazymiai.push_back(p);  // Vietoj pazymiai[pazymiuKiekis++]
    } else {
        std::cout << "[KLAIDA] Netinkamas pažymys!" << std::endl;
    }
}

double Student::skaiciuotiVidurki() const {
    if (pazymiai.empty()) {  // Vietoj pazymiuKiekis == 0
        return 0.0;
    }
    
    double suma = 0.0;
    for (double p : pazymiai) {  // Range-based for loop!
        suma += p;
    }
    
    return suma / pazymiai.size();  // Vietoj pazymiuKiekis
}

void Student::spausdintiPazymius() const {
    std::cout << "Pažymiai (" << pazymiai.size() << "): ";
    for (size_t i = 0; i < pazymiai.size(); i++) {
        std::cout << pazymiai[i];
        if (i < pazymiai.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

// Kiti metodai tie patys kaip žingsnis 5
// ...
```

### **main.cpp (tas pats kaip žingsnis 5):**

```cpp
#include <iostream>
#include "Student.h"
using namespace std;

int main() {
    Student s1("Jonas", 20);
    
    // Pridedame daugiau nei 20 pažymių - veiks!
    for (int i = 0; i < 25; i++) {
        s1.pridetiPazymi(7.0 + i * 0.1);
    }
    
    s1.spausdinti();
    
    return 0;
}
```

### **Pedagoginės pastabos:**
- ✅ Vector **dinamiškai plečiasi** - ne limitų!
- ✅ `.push_back(p)` - vietoj `pazymiai[pazymiuKiekis++] = p`
- ✅ `.size()` - vietoj `pazymiuKiekis`
- ✅ `.empty()` - vietoj `pazymiuKiekis == 0`
- ✅ Range-based for loop: `for (double p : pazymiai)` - moderniškas C++
- 💡 Vector **automatiškai** valdo atmintį (RAII)
- ⚠️ Dažna klaida: `pazymiai.size()` grąžina `size_t` (unsigned) - galimi warning'ai

---

## 📦 **README.md pavyzdys**

```markdown
# U2: OOP Pagrindai. Klasės ir Objektai

**Būsena**: ✅ Atlikta  
**Pateikta**: 2026-03-01

---

## 📁 Žingsniai

| Žingsnis | Direktorija | Aprašymas |
|----------|-------------|-----------|
| 1 | `01/` | Struct → Class transformacija |
| 2 | `02/` | Konstruktoriai (default + parametrinis) |
| 3 | `03/` | Metodai (getters, setters, pagalbiniai) |
| 4 | `04/` | Static counter + destruktorius |
| 5 | `05/` | Pažymių masyvas |
| 6 | `06-bonus/` | BONUS: array → vector |

---

## 🧪 Testavimas

**Testas 1 (konstruktoriai)**:

    [TEST] Student sukurtas: Jonas. Viso studentų: 1
    ✅ VEIKIA

**Testas 2 (pažymių vidurkis)**:

    Pažymiai (4): 8.5, 9, 7.5, 8
    Vidurkis: 8.25
    ✅ VEIKIA

---

## 💭 Pagrindinės įžvalgos

1. Class vs Struct - private vs public
2. Konstruktoriai inicializuoja objektą
3. Static nariai - bendri visiems objektams
4. Destruktorius - automatiškas cleanup
5. Masyvas → vector (lankstesnis!)
```

---

## 🎓 **Pedagoginės gairės dėstytojui**

### **Tikėtinos studentų klaidos:**

| Klaida | Dažnumas | Sprendimas |
|--------|----------|------------|
| Pamiršo `;` po klasės deklaracijos | ⭐⭐⭐⭐⭐ | Kompiliavimo klaida - parodyti |
| `vardas = v` vietoj `strcpy(vardas, v)` | ⭐⭐⭐⭐ | Paaiškinti C-style strings |
| Pamiršo `const` getter'iams | ⭐⭐⭐⭐ | Kompiliatorius skundžiasi |
| Pamiršo inicializuoti static narį už klasės | ⭐⭐⭐⭐ | Linking error |
| Bandė inicializuoti static narį konstruktoriuje | ⭐⭐⭐ | Logic error - skaitiklis neteisingas |
| Pamiršo header guard'us | ⭐⭐⭐ | Multiple definition error |
| `pazymiuKiekis` ne inicializuotas | ⭐⭐⭐ | Undefined behavior |
| Off-by-one kablelių spausdinime | ⭐⭐ | Estetinė problema |

### **Galimi praplėtimai stipriesiems:**

1. **Initialization list naudojimas**
   - Pademonstruoti efektyvumą (ne copy)
   
2. **Overload'inti operator<<**
   - `cout << s1` vietoj `s1.spausdinti()`
   
3. **Copy constructor**
   - Nors čia dar nereikia (žingsnis 5 vector jau turi default'ą)
   
4. **Const correctness**
   - Visur kur galima `const`

5. **std::string vietoj char[]**
   - Modernesnis C++

---

## 💡 **Diskusijos taškai paskaitoje**

1. **Struct vs Class**
   - Tik keyword'o skirtumas
   - Praktikoje: `struct` - duomenims, `class` - objektams su logika
   
2. **Enkapsulacija**
   - Kodėl `private` + getters/setters?
   - Validacija, kontrolė, flexibility
   
3. **Static nariai**
   - Kada naudoti? (counter'iai, config, shared state)
   - Kodėl inicializuoti už klasės?
   
4. **Destruktorius**
   - Kada kviečiamas? (scope)
   - Vėliau: dynamic memory cleanup
   
5. **Masyvas vs Vector**
   - Trade-off'ai (performance vs flexibility)
   - RAII principas (vector valdo atmintį)

---

**Sėkmės dėstant!** 🎓
