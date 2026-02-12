# Rule of Five - Variantų Palyginimas

## 📊 Kada Kompiliatorius Generuoja / Ištrina Special Member Functions

| Situacija | Default Ctor | Copy Ctor | Move Ctor | Copy Assign | Move Assign | Destructor |
|-----------|:------------:|:---------:|:---------:|:-----------:|:-----------:|:----------:|
| **Nieko neapibrėžta** | ✅ Gen | ✅ Gen | ✅ Gen | ✅ Gen | ✅ Gen | ✅ Gen |
| **Tik Destructor** | ✅ Gen | ⚠️ Dep | ❌ None | ⚠️ Dep | ❌ None | ✋ User |
| **Tik Copy Ctor** | ❌ None | ✋ User | ❌ None | ⚠️ Dep | ❌ None | ✅ Gen |
| **Tik Move Ctor** | ❌ None | ❌ Del | ✋ User | ❌ Del | ❌ Del | ✅ Gen |
| **Tik Copy Assign** | ✅ Gen | ⚠️ Dep | ❌ None | ✋ User | ❌ None | ✅ Gen |
| **Tik Move Assign** | ✅ Gen | ❌ Del | ❌ Del | ❌ Del | ✋ User | ✅ Gen |

**Legenda:**
- ✅ **Gen** = Kompiliatorius generuoja automatiškai
- ✋ **User** = Vartotojas apibrėžė
- ❌ **None** = Negeneruojamas
- ❌ **Del** = Ištrinta (deleted)
- ⚠️ **Dep** = Deprecated (generuojamas, bet nerekomenduojama)

---

## 🎯 Praktiniai Scenarijai

### Scenarijus 1: Pradedantis (be jokių apibrėžimų)

```cpp
class Simple {
    std::string name;
    int value;
public:
    Simple(std::string n, int v) : name(n), value(v) {}
};
```

| Operacija | Veikia? | Rezultatas |
|-----------|:-------:|-----------|
| `Simple a = b;` | ✅ | Kompiliatorius generuoja copy ctor |
| `Simple a = std::move(b);` | ✅ | Kompiliatorius generuoja move ctor |
| `a = b;` | ✅ | Kompiliatorius generuoja copy assign |
| `a = std::move(b);` | ✅ | Kompiliatorius generuoja move assign |
| `std::sort(vec)` | ✅ | Veikia visos operacijos |

**Išvada:** Jei neturite custom resource management → nieko nereikia apibrėžti!

---

### Scenarijus 2: Tik Move Constructor (SUGADINTA!)

```cpp
class Broken {
    std::string name;
public:
    Broken(std::string n) : name(n) {}
    
    // ❌ Apibrėžėte tik move constructor
    Broken(Broken&& other) noexcept 
        : name(std::move(other.name)) {}
};
```

| Operacija | Veikia? | Rezultatas |
|-----------|:-------:|-----------|
| `Broken a = b;` | ❌ | Copy ctor = DELETED |
| `Broken a = std::move(b);` | ✅ | Move ctor veikia |
| `a = b;` | ❌ | Copy assign = DELETED |
| `a = std::move(b);` | ❌ | Move assign = DELETED |
| `std::sort(vec)` | ❌ | COMPILATION ERROR |

**Išvada:** Negalite apibrėžti tik move constructor!

---

### Scenarijus 3: = default (TAISYTA)

```cpp
class Fixed {
    std::string name;
public:
    Fixed(std::string n) : name(n) {}
    
    Fixed(Fixed&&) noexcept = default;
    
    // ✅ Pridėti trūkstamus
    Fixed(const Fixed&) = default;
    Fixed& operator=(const Fixed&) = default;
    Fixed& operator=(Fixed&&) noexcept = default;
    ~Fixed() = default;
};
```

| Operacija | Veikia? | Rezultatas |
|-----------|:-------:|-----------|
| `Fixed a = b;` | ✅ | Default copy ctor |
| `Fixed a = std::move(b);` | ✅ | Default move ctor |
| `a = b;` | ✅ | Default copy assign |
| `a = std::move(b);` | ✅ | Default move assign |
| `std::sort(vec)` | ✅ | Viskas veikia |

**Išvada:** `= default` yra paprasčiausias sprendimas!

---

### Scenarijus 4: Custom Resource (Raw Pointer)

```cpp
class Resource {
    int* data;
    size_t size;
public:
    Resource(size_t s) : size(s), data(new int[s]) {}
    
    // ✅ Būtina pilna implementacija!
    ~Resource() {
        delete[] data;
    }
    
    Resource(const Resource& other) 
        : size(other.size), data(new int[other.size]) {
        std::copy(other.data, other.data + size, data);
    }
    
    Resource(Resource&& other) noexcept
        : size(other.size), data(other.data) {
        other.data = nullptr;
        other.size = 0;
    }
    
    Resource& operator=(const Resource& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            std::copy(other.data, other.data + size, data);
        }
        return *this;
    }
    
    Resource& operator=(Resource&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }
};
```

**Išvada:** Jei valdote raw resources → būtina pilna Rule of Five implementacija!

---

### Scenarijus 5: No Copy (move-only)

```cpp
class MoveOnly {
    std::unique_ptr<int> ptr;
public:
    MoveOnly(int val) : ptr(std::make_unique<int>(val)) {}
    
    // ❌ Uždrausti copy
    MoveOnly(const MoveOnly&) = delete;
    MoveOnly& operator=(const MoveOnly&) = delete;
    
    // ✅ Leisti move
    MoveOnly(MoveOnly&&) noexcept = default;
    MoveOnly& operator=(MoveOnly&&) noexcept = default;
};
```

| Operacija | Veikia? | Rezultatas |
|-----------|:-------:|-----------|
| `MoveOnly a = b;` | ❌ | Copy = deleted |
| `MoveOnly a = std::move(b);` | ✅ | Move veikia |
| `a = b;` | ❌ | Copy assign = deleted |
| `a = std::move(b);` | ✅ | Move assign veikia |
| `vec.push_back(obj)` | ❌ | Reikia std::move |
| `vec.push_back(std::move(obj))` | ✅ | Veikia |

**Išvada:** Tinka objektams, kurie negali būti kopijavami (pvz., mutex, unique_ptr)

---

## 📈 Efektyvumas

### Copy vs Move Palyginimas

```cpp
class Data {
    std::vector<int> vec;  // Tarkime 1,000,000 elementų
public:
    // Copy - BRANGU
    Data(const Data& other) : vec(other.vec) {
        // Kopijuoja 1,000,000 int → ~4MB
        // Laiko sudėtingumas: O(n)
    }
    
    // Move - PIGU
    Data(Data&& other) noexcept : vec(std::move(other.vec)) {
        // Perkelia tik 3 pointer/size fields → ~24 bytes
        // Laiko sudėtingumas: O(1)
    }
};
```

### Testavimo Rezultatai (1M elementų vector)

| Operacija | Copy Laikas | Move Laikas | Santykis |
|-----------|-------------:|------------:|---------:|
| Constructor | 15 ms | 0.001 ms | 15,000x |
| Assignment | 15 ms | 0.001 ms | 15,000x |
| `std::sort()` | 250 ms | 3 ms | 83x |
| `vec.insert()` | 20 ms | 0.5 ms | 40x |

**Išvada:** Move semantics duoda **didžiulį** efektyvumo laimėjimą!

---

## 🎓 Kada Naudoti Ką?

| Jūsų Situacija | Rekomenduojamas Sprendimas |
|----------------|---------------------------|
| Tik `std::string`, `std::vector`, etc. | Nieko neapibrėžti (Rule of Zero) |
| Reikia debug logging | Pilna implementacija su `std::cout` |
| Raw pointers, `new`/`delete` | Pilna implementacija (arba geriau RAII) |
| `std::unique_ptr` nariai | `= default` visur |
| Norite move-only | Copy `= delete`, Move `= default` |
| Thread-unsafe objektai | Copy/Move `= delete` |
| Singleton pattern | Visi `= delete` |

---

## ⚡ Quick Decision Tree

```
Ar turite custom resource management?
│
├─ NE → Nieko neapibrėžkite (Rule of Zero)
│
└─ TAIP → Ar naudojate RAII (unique_ptr, vector)?
    │
    ├─ TAIP → = default visur
    │
    └─ NE (raw pointers) → Pilna Rule of Five implementacija
```

---

## 🔧 STL Konteineriai - Minimalūs Reikalavimai

### `std::vector<T>` reikalauja:

| Operacija | Reikalavimas | Ar būtina? |
|-----------|--------------|:----------:|
| `vector<T> v;` | Default ctor | ❌ Ne |
| `v.push_back(obj)` | Copy ctor | ✅ Taip |
| `v.push_back(std::move(obj))` | Move ctor | ⚠️ Fallback į copy |
| `v.resize(n)` | Default ctor + Copy ctor | ✅ Taip |
| `std::sort(v)` | Copy/Move assign + operator< | ✅ Taip |
| `v.insert(it, obj)` | Copy/Move assign | ✅ Taip |
| `v.erase(it)` | Move assign | ⚠️ Fallback į copy |

### `std::map<K, V>` reikalauja:

| Operacija | Reikalavimas |
|-----------|--------------|
| Kaip key | Copy ctor + operator< (arba hash) |
| Kaip value | Copy ctor + Copy assign |

### `std::unique_ptr<T>` duoda:

- ✅ Move ctor / assign
- ❌ Copy ctor / assign (deleted)

---

## 📝 Santrauka: 3 Taisyklės

### **Rule of Zero**
Jei nereikia custom resource management → neapibrėžkite nieko!

### **Rule of Five**
Jei apibrėžiate bent vieną → apibrėžkite visus 5!

### **Rule of Default**
Jei galite naudoti `= default` → naudokite!

---

**Sukūrė:** Viktoras Golubev  
**Kursas:** OOP su C++  
**Data:** 2026-02-12
