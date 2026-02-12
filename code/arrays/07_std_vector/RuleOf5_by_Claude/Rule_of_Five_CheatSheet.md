# Rule of Five - Cheat Sheet

## 🎯 Pagrindinė Taisyklė

**Jei apibrėžiate BENT VIENĄ iš šių funkcijų, turėtumėte apibrėžti VISUS PENKIS:**

1. **Destructor** (`~ClassName()`)
2. **Copy Constructor** (`ClassName(const ClassName&)`)
3. **Move Constructor** (`ClassName(ClassName&&)`)
4. **Copy Assignment** (`operator=(const ClassName&)`)
5. **Move Assignment** (`operator=(ClassName&&)`)

---

## 📋 Sintaksė

```cpp
class MyClass {
public:
    // 1. Destructor
    ~MyClass() { /* cleanup */ }
    
    // 2. Copy Constructor
    MyClass(const MyClass& other) 
        : member(other.member) { }
    
    // 3. Move Constructor
    MyClass(MyClass&& other) noexcept
        : member(std::move(other.member)) { }
    
    // 4. Copy Assignment
    MyClass& operator=(const MyClass& other) {
        if (this != &other) {
            member = other.member;
        }
        return *this;
    }
    
    // 5. Move Assignment
    MyClass& operator=(MyClass&& other) noexcept {
        if (this != &other) {
            member = std::move(other.member);
        }
        return *this;
    }

private:
    std::string member;
};
```

---

## 🚀 Naudojant `= default`

**Paprasčiausias sprendimas, jei nereikia custom logic:**

```cpp
class MyClass {
public:
    ~MyClass() = default;
    MyClass(const MyClass&) = default;
    MyClass(MyClass&&) noexcept = default;
    MyClass& operator=(const MyClass&) = default;
    MyClass& operator=(MyClass&&) noexcept = default;
};
```

---

## 🚫 Naudojant `= delete`

**Jei norite uždrausti copy/move:**

```cpp
class NoCopy {
public:
    NoCopy() = default;
    
    // Uždrausti copy
    NoCopy(const NoCopy&) = delete;
    NoCopy& operator=(const NoCopy&) = delete;
    
    // Leisti move
    NoCopy(NoCopy&&) noexcept = default;
    NoCopy& operator=(NoCopy&&) noexcept = default;
};
```

---

## ⚠️ Kodėl tai svarbu?

### Problema

```cpp
class Student {
    std::string name;
public:
    Student(const std::string& n) : name(n) {}
    
    // ❌ Apibrėžėte tik move constructor
    Student(Student&& other) noexcept 
        : name(std::move(other.name)) {}
    
    // ❌ TRŪKSTA: Copy/Move assignment operators
};

// ❌ NEKOMPILIUOSIS:
std::vector<Student> students;
students.emplace_back("Jonas");
students.emplace_back("Petras");
std::sort(students.begin(), students.end());  // ERROR!
```

### Sprendimas

```cpp
class Student {
    std::string name;
public:
    Student(const std::string& n) : name(n) {}
    Student(Student&& other) noexcept 
        : name(std::move(other.name)) {}
    
    // ✅ Pridėti trūkstamus operators
    Student& operator=(const Student&) = default;
    Student& operator=(Student&&) noexcept = default;
};

// ✅ Dabar veikia!
```

---

## 📊 Kada kas vyksta?

| Operacija | Reikalingas Operator |
|-----------|---------------------|
| `MyClass a = b;` | Copy Constructor |
| `MyClass a = std::move(b);` | Move Constructor |
| `a = b;` | Copy Assignment |
| `a = std::move(b);` | Move Assignment |
| `vector.push_back(obj)` | Copy Constructor |
| `vector.push_back(std::move(obj))` | Move Constructor |
| `std::sort(vec.begin(), vec.end())` | **Copy/Move Assignment** |
| `vec.insert(it, obj)` | **Copy/Move Assignment** |
| `vec.erase(it)` | **Move Assignment** |

---

## 🎓 STL Reikalavimai

### `std::vector` operacijos reikalauja:

✅ **Default Constructor** → `resize(n)`  
✅ **Copy Constructor** → `push_back(obj)`, `insert()`  
✅ **Move Constructor** → `push_back(std::move(obj))`  
✅ **Copy Assignment** → `std::sort()`, `std::copy()`  
✅ **Move Assignment** → `std::sort()`, `erase()`, `insert()`  
✅ **Destructor** → `clear()`, vector destrukcija  

---

## 🔍 Kodėl Kompiliatorius Ištrina?

### C++11 Taisyklės:

1. **Jei apibrėžiate move constructor arba move assignment:**
   - Kompiliatorius **IŠTRINA** copy assignment operator
   - Kompiliatorius **IŠTRINA** copy constructor (nerekomenduojama)

2. **Jei apibrėžiate destructor:**
   - Copy/move constructors vis dar generuojami (deprecated)
   - Bet geriausia praktika - apibrėžti visus

---

## 💡 Geriausios Praktikos

### 1️⃣ **Jei galite - naudokite `= default`**

```cpp
MyClass(const MyClass&) = default;
MyClass& operator=(const MyClass&) = default;
```

### 2️⃣ **Jei reikia logging - implementuokite pilnai**

```cpp
MyClass(const MyClass& other) : data(other.data) {
    std::cout << "Copy constructor called\n";
}
```

### 3️⃣ **Pridėkite `noexcept` prie move operacijų**

```cpp
MyClass(MyClass&&) noexcept = default;
MyClass& operator=(MyClass&&) noexcept = default;
```

Kodėl? `std::vector` gali naudoti move tik jei garantuoja `noexcept`.

### 4️⃣ **Self-assignment apsauga**

```cpp
MyClass& operator=(const MyClass& other) {
    if (this != &other) {  // ✅ Būtina!
        // ... assignment logic
    }
    return *this;
}
```

---

## 🐛 Dažniausios Klaidos

### ❌ Pamiršta `noexcept`

```cpp
MyClass(MyClass&& other)  // ❌ Trūksta noexcept
```

### ❌ Pamiršta `return *this`

```cpp
MyClass& operator=(const MyClass& other) {
    member = other.member;
    // ❌ Trūksta: return *this;
}
```

### ❌ Neapsaugota nuo self-assignment

```cpp
MyClass& operator=(const MyClass& other) {
    delete[] data;
    data = new int[other.size];  // ❌ Jei this == &other?
    // ...
}
```

---

## 📚 Kada Naudoti Ką?

| Situacija | Sprendimas |
|-----------|-----------|
| Standartiniai duomenų nariai (`std::string`, `std::vector`) | `= default` |
| Reikia logging / debugging | Pilna implementacija |
| Nereikia copy semantics | `= delete` copy, `= default` move |
| Resource management (raw pointers) | Pilna implementacija + RAII |
| Norite optimize move | Custom move implementation |

---

## 🎯 Trumpai

```cpp
// Minimalus teisingas pavyzdys:
class MyClass {
public:
    ~MyClass() = default;
    MyClass(const MyClass&) = default;
    MyClass(MyClass&&) noexcept = default;
    MyClass& operator=(const MyClass&) = default;
    MyClass& operator=(MyClass&&) noexcept = default;
};
```

**Įsiminti:** Vienas → Visi penki! 🖐️

---

## 📖 Papildoma Literatūra

- Scott Meyers - "Effective Modern C++" (Item 17)
- Howard Hinnant - "A Brief Introduction to Rvalue References"
- cppreference.com - "The rule of three/five/zero"

---

**Sukūrė:** Viktoras Golubev  
**Data:** 2026-02-12  
**Kursas:** OOP su C++
