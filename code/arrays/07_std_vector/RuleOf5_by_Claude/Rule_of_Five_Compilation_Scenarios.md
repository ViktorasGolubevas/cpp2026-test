# Rule of Five - Kompiliavimo Scenarijai

## ✅❌ Kada Kodas Kompiliuojasi vs Nekompiliuojasi

### Scenarijus A: Nieko Neapibrėžta
```cpp
class Student {
    std::string name;
public:
    Student(std::string n) : name(n) {}
};
```
| Operacija | Rezultatas |
|-----------|-----------|
| Kompiliacija | ✅ TAIP |
| `std::vector<Student> v` | ✅ TAIP |
| `v.push_back(obj)` | ✅ TAIP (auto-generated copy) |
| `std::sort(v)` | ✅ TAIP (auto-generated assign) |

**Išvada:** Jei NIEKO neapibrėžiate → VISKAS VEIKIA!

---

### Scenarijus B: Tik Destructor
```cpp
class Student {
    std::string name;
public:
    Student(std::string n) : name(n) {}
    ~Student() { std::cout << "Bye\n"; }
};
```
| Operacija | Rezultatas |
|-----------|-----------|
| Kompiliacija | ✅ TAIP |
| `std::vector<Student> v` | ✅ TAIP |
| `v.push_back(obj)` | ⚠️ TAIP (deprecated) |
| `std::sort(v)` | ⚠️ TAIP (deprecated) |

**Išvada:** Deprecated, bet vis dar kompiliuojasi (C++11 legacy)

---

### Scenarijus C: Tik Copy Constructor
```cpp
class Student {
    std::string name;
public:
    Student(std::string n) : name(n) {}
    Student(const Student& other) : name(other.name) {}
};
```
| Operacija | Rezultatas |
|-----------|-----------|
| Kompiliacija | ✅ TAIP |
| `std::vector<Student> v` | ✅ TAIP |
| `v.push_back(obj)` | ✅ TAIP (uses copy ctor) |
| `std::sort(v)` | ⚠️ TAIP (deprecated assign) |
| Move operations | ❌ NE (deleted) |

**Išvada:** Copy veikia, move ištrinti

---

### Scenarijus D: TIK MOVE CONSTRUCTOR (PROBLEMA!) ❌
```cpp
class Student {
    std::string name;
public:
    Student(std::string n) : name(n) {}
    Student(Student&& other) noexcept : name(std::move(other.name)) {}
    // ❌ TRŪKSTA: Copy constructor DELETED
    // ❌ TRŪKSTA: Copy assignment DELETED
    // ❌ TRŪKSTA: Move assignment DELETED
};
```
| Operacija | Rezultatas |
|-----------|-----------|
| Kompiliacija | ✅ TAIP (pats failas) |
| `std::vector<Student> v` | ✅ TAIP |
| `v.emplace_back("Jonas")` | ✅ TAIP (constructs in-place) |
| `Student a = b;` | ❌ **COMPILATION ERROR** |
| `v.push_back(temp)` | ❌ **COMPILATION ERROR** |
| `std::sort(v.begin(), v.end())` | ❌ **COMPILATION ERROR** |
| `v.insert(it, obj)` | ❌ **COMPILATION ERROR** |
| `v.erase(it)` | ❌ **COMPILATION ERROR** |

**Klaidos pranešimas:**
```
error: use of deleted function 'Student& Student::operator=(const Student&)'
note: 'Student& Student::operator=(const Student&)' is implicitly 
      declared as deleted because 'Student' declares a move constructor
```

**Išvada:** ☠️ KATASTROFA! Beveik niekas neveikia su STL!

---

### Scenarijus E: Move Constructor + = default (TAISYTA) ✅
```cpp
class Student {
    std::string name;
public:
    Student(std::string n) : name(n) {}
    Student(Student&& other) noexcept : name(std::move(other.name)) {}
    
    // ✅ PRIDĖTA:
    Student(const Student&) = default;
    Student& operator=(const Student&) = default;
    Student& operator=(Student&&) noexcept = default;
};
```
| Operacija | Rezultatas |
|-----------|-----------|
| Kompiliacija | ✅ TAIP |
| `std::vector<Student> v` | ✅ TAIP |
| `Student a = b;` | ✅ TAIP |
| `v.push_back(temp)` | ✅ TAIP |
| `std::sort(v.begin(), v.end())` | ✅ TAIP |
| `v.insert(it, obj)` | ✅ TAIP |
| `v.erase(it)` | ✅ TAIP |

**Išvada:** ✨ VISKAS VEIKIA!

---

### Scenarijus F: Pilna Rule of Five ✅
```cpp
class Student {
    std::string name;
public:
    Student(std::string n) : name(n) {}
    ~Student() { std::cout << "~Student\n"; }
    
    Student(const Student& other) : name(other.name) {
        std::cout << "Copy ctor\n";
    }
    
    Student(Student&& other) noexcept : name(std::move(other.name)) {
        std::cout << "Move ctor\n";
    }
    
    Student& operator=(const Student& other) {
        if (this != &other) name = other.name;
        std::cout << "Copy assign\n";
        return *this;
    }
    
    Student& operator=(Student&& other) noexcept {
        if (this != &other) name = std::move(other.name);
        std::cout << "Move assign\n";
        return *this;
    }
};
```
| Operacija | Rezultatas |
|-----------|-----------|
| Kompiliacija | ✅ TAIP |
| Visos STL operacijos | ✅ TAIP |
| Debug logging | ✅ TAIP (mato, kas vyksta) |

**Išvada:** ✨ VISKAS VEIKIA + MATAI KAS VYKSTA!

---

## 📊 Santrauka: Ko Trūksta → Kas Neveikia

| Kas Apibrėžta | Copy Ctor | Move Ctor | Copy Assign | Move Assign | std::sort() |
|---------------|:---------:|:---------:|:-----------:|:-----------:|:-----------:|
| Nieko | ✅ Auto | ✅ Auto | ✅ Auto | ✅ Auto | ✅ Veikia |
| Tik Destructor | ⚠️ Dep | ❌ None | ⚠️ Dep | ❌ None | ⚠️ Veikia |
| Tik Copy Ctor | ✋ User | ❌ None | ⚠️ Dep | ❌ None | ⚠️ Veikia |
| **Tik Move Ctor** | ❌ **Del** | ✋ User | ❌ **Del** | ❌ **Del** | ❌ **NEVEIKIA** |
| Move + = default | ✅ Def | ✋ User | ✅ Def | ✅ Def | ✅ Veikia |
| Visi 5 | ✋ User | ✋ User | ✋ User | ✋ User | ✅ Veikia |

**Legenda:**
- ✅ Auto = Kompiliatorius generuoja automatiškai
- ✅ Def = `= default` naudojamas
- ✋ User = Vartotojas apibrėžė
- ❌ None = Negeneruojamas
- ❌ Del = **Deleted (PROBLEMA!)**
- ⚠️ Dep = Deprecated (veikia, bet nerekomenduojama)

---

## 🎯 Paprastas Checklistai

### Jei Matote Šią Klaidą:
```
error: use of deleted function 'T& T::operator=(const T&)'
```

**Sprendimas:** Pridėti copy/move assignment operators:
```cpp
T& operator=(const T&) = default;
T& operator=(T&&) noexcept = default;
```

---

### Jei Matote Šią Klaidą:
```
error: no matching function for call to 'swap(T&, T&)'
```

**Priežastis:** Move assignment deleted  
**Sprendimas:** Tas pats - pridėti assignment operators

---

## 🔧 Quick Fix Template

**Jei kodas nekompiliuojasi dėl Rule of Five:**

```cpp
class YourClass {
    // ... jūsų duomenys ...
    
public:
    // ... jūsų constructors ...
    
    // PRIDĖTI ŠIĄ BLOKĄ:
    YourClass(const YourClass&) = default;
    YourClass(YourClass&&) noexcept = default;
    YourClass& operator=(const YourClass&) = default;
    YourClass& operator=(YourClass&&) noexcept = default;
    ~YourClass() = default;
};
```

Šis šablonas išsprendžia 90% Rule of Five problemų! ✨

---

## 💡 Kaip Išvengti Problemų

### ❌ BLOGAI:
```cpp
class MyClass {
public:
    MyClass(MyClass&&) noexcept { ... }
    // Pamiršote kitus!
};
```

### ✅ GERAI - Variantas 1 (minimal):
```cpp
class MyClass {
public:
    MyClass(MyClass&&) noexcept { ... }
    MyClass(const MyClass&) = default;
    MyClass& operator=(const MyClass&) = default;
    MyClass& operator=(MyClass&&) noexcept = default;
};
```

### ✅ GERAI - Variantas 2 (su logging):
```cpp
class MyClass {
public:
    MyClass(const MyClass&) { std::cout << "Copy\n"; ... }
    MyClass(MyClass&&) noexcept { std::cout << "Move\n"; ... }
    MyClass& operator=(const MyClass&) { ... return *this; }
    MyClass& operator=(MyClass&&) noexcept { ... return *this; }
    ~MyClass() { std::cout << "~MyClass\n"; }
};
```

---

**Sukūrė:** Viktoras Golubevas  
**Data:** 2026-02-12  
**Kursas:** OOP su C++

**Atminkite:** Apibrėžėte vieną → apibrėžkite visus 5! 🖐️
