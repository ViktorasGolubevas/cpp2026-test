# Rule of Five - Vizualinė Diagrama

## 🎨 C++ Special Member Functions

```
┌─────────────────────────────────────────────────────────────┐
│                    RULE OF FIVE                             │
│                                                             │
│  Jei apibrėžiate BENT VIENĄ → apibrėžkite VISUS 5!        │
└─────────────────────────────────────────────────────────────┘
                               │
                ┌──────────────┼──────────────┐
                │              │              │
        ┌───────▼──────┐  ┌────▼────┐  ┌────▼──────┐
        │ CONSTRUCTORS │  │ ASSIGN  │  │ DESTRUCTOR│
        └──────┬───────┘  └────┬────┘  └─────┬─────┘
               │               │              │
        ┌──────┴──────┐   ┌────┴────┐       │
        │             │   │         │       │
    ┌───▼───┐    ┌───▼───▼─┐  ┌───▼────┐  ┌▼┐
    │ COPY  │    │  MOVE   │  │  COPY  │  │~│
    │ CTOR  │    │  CTOR   │  │ ASSIGN │  │T│
    └───────┘    └─────────┘  └────────┘  └─┘
                              ┌────────┐
                              │  MOVE  │
                              │ ASSIGN │
                              └────────┘
```

---

## 📊 Kompiliatoriaus Sprendimų Medis

```
Ar vartotojas apibrėžė BENT VIENĄ special member function?
│
├─ NE ─────────────────────────────────────────┐
│                                              │
│   Kompiliatorius automatiškai generuoja:    │
│   ✅ Default Constructor                     │
│   ✅ Copy Constructor                        │
│   ✅ Move Constructor                        │
│   ✅ Copy Assignment                         │
│   ✅ Move Assignment                         │
│   ✅ Destructor                              │
│                                              │
│   📊 Rezultatas: VISKAS VEIKIA!             │
└──────────────────────────────────────────────┘

└─ TAIP ────┬─ Apibrėžė tik DESTRUCTOR?
            │  │
            │  ├─ TAIP → Copy/Move constructors DEPRECATED
            │  │         Copy Assignment DEPRECATED
            │  │         Move operations NONE
            │  │         ⚠️ Veikia, bet nerekomenduojama
            │  │
            │  └─ NE ──┬─ Apibrėžė MOVE CONSTRUCTOR?
            │          │  │
            │          │  ├─ TAIP → ☠️ KATASTROFA!
            │          │  │         Copy Constructor DELETED
            │          │  │         Copy Assignment DELETED
            │          │  │         Move Assignment DELETED
            │          │  │         ❌ std::sort() NEVEIKIA
            │          │  │         ❌ vector::insert() NEVEIKIA
            │          │  │         ❌ vector::erase() NEVEIKIA
            │          │  │
            │          │  └─ NE ──┬─ Apibrėžė COPY CONSTRUCTOR?
            │          │          │  │
            │          │          │  ├─ TAIP → Move operations DELETED
            │          │          │  │         Copy Assignment DEPRECATED
            │          │          │  │         ⚠️ Veikia, bet suboptimal
            │          │          │  │
            │          │          │  └─ NE ──→ Apibrėžė Copy/Move Assignment?
            │          │                       → Panašiai kaip aukščiau
            │
            └──────────────────────────────────────────────────┐
                                                               │
                SPRENDIMAS: Rule of Five!                      │
                                                               │
                Apibrėžkite visus 5:                           │
                ✅ Copy Constructor                            │
                ✅ Move Constructor                            │
                ✅ Copy Assignment                             │
                ✅ Move Assignment                             │
                ✅ Destructor                                  │
                                                               │
                Arba naudokite = default / = delete            │
                ────────────────────────────────────────────────┘
```

---

## 🎯 Praktinis Workflow

```
┌─────────────────────────────────────────────────────────────┐
│ 1. PRADŽIA: Tuščia klasė                                    │
│                                                             │
│    class Student {                                          │
│        std::string name;                                    │
│    };                                                       │
│                                                             │
│    ✅ Viskas veikia automatiškai!                          │
└─────────────────────────────────────────────────────────────┘
                          │
                          ▼
┌─────────────────────────────────────────────────────────────┐
│ 2. PRIDĖJIMAS: Logging į konstruktorių                     │
│                                                             │
│    Student(Student&& other) noexcept {                      │
│        name = std::move(other.name);                        │
│        std::cout << "Move!\n";                              │
│    }                                                        │
│                                                             │
│    ❌ Dabar std::sort() NEVEIKIA!                          │
└─────────────────────────────────────────────────────────────┘
                          │
                          ▼
┌─────────────────────────────────────────────────────────────┐
│ 3. KOMPILIAVIMAS: Matote klaidas                           │
│                                                             │
│    error: use of deleted function                          │
│    'Student& Student::operator=(const Student&)'           │
│                                                             │
│    📍 Čia ir vyksta problema!                              │
└─────────────────────────────────────────────────────────────┘
                          │
                          ▼
┌─────────────────────────────────────────────────────────────┐
│ 4. SPRENDIMAS: Pridėti trūkstamus                          │
│                                                             │
│    Student(const Student&) = default;                       │
│    Student& operator=(const Student&) = default;            │
│    Student& operator=(Student&&) noexcept = default;        │
│                                                             │
│    ✅ Dabar viskas veikia!                                 │
└─────────────────────────────────────────────────────────────┘
```

---

## 🔍 STL Operacijų Reikalavimai

```
╔═══════════════════════════════════════════════════════════╗
║                  STL KONTEINERIAI                         ║
╚═══════════════════════════════════════════════════════════╝

std::vector<T>
│
├─ push_back(obj)          → 📋 Copy Constructor
├─ push_back(std::move())  → 🚚 Move Constructor
├─ emplace_back(...)       → 📚 Constructor (BEST!)
│
├─ std::sort()             → 🔄 Copy/Move Assignment + operator<
├─ insert(it, obj)         → 🔄 Copy/Move Assignment
├─ erase(it)               → 🔄 Move Assignment
│
├─ resize(n)               → 📚 Default Constructor + Copy
├─ clear()                 → 🗑️  Destructor
└─ ~vector()               → 🗑️  Destructor

std::sort()  ─────────────┐
std::copy()  ─────────────┤
std::swap()  ─────────────┼──→  REIKIA Assignment Operators!
std::move()  ─────────────┤
vector operations ────────┘

Jei Assignment DELETED → Visos šios operacijos NEVEIKIA! ❌
```

---

## 💥 Problemos Anatomija

```
╔═══════════════════════════════════════════════════════════╗
║         KODĖL std::sort() NEVEIKIA?                       ║
╚═══════════════════════════════════════════════════════════╝

1. Jūsų kodas:
   
   class Student {
       Student(Student&&) noexcept { ... }
       // ❌ Nėra operator=
   };

        │
        ▼
        
2. Kompiliatorius IŠTRINA:

   Student& operator=(const Student&) = delete;  ❌
   Student& operator=(Student&&) = delete;        ❌

        │
        ▼

3. std::sort() viduje:

   template<typename T>
   void sort(T* begin, T* end) {
       // ...
       T temp = std::move(*a);
       *a = std::move(*b);  // ← ČIA REIKIA operator= !
       *b = std::move(temp);
   }

        │
        ▼

4. Kompiliavimo klaida:

   error: use of deleted function
   'Student& Student::operator=(const Student&)'

        │
        ▼

5. Sprendimas:

   Pridėti:
   Student& operator=(const Student&) = default;
   Student& operator=(Student&&) noexcept = default;
```

---

## 🎓 Mokymosi Kelias

```
LEVEL 1: Pradedantis
┌────────────────────────┐
│ Naudoja std::string,   │
│ std::vector            │
│                        │
│ Nieko neapibrėžia      │
│ ✅ Viskas veikia       │
└────────────────────────┘

         │
         ▼

LEVEL 2: Intermediate
┌────────────────────────┐
│ Nori debug logging     │
│                        │
│ Apibrėžia move ctor    │
│ ❌ Viskas sugenda      │
│                        │
│ 💡 Išmoksta Rule of 5  │
└────────────────────────┘

         │
         ▼

LEVEL 3: Advanced
┌────────────────────────┐
│ Supranta, kada reikia: │
│                        │
│ • = default            │
│ • = delete             │
│ • pilna implementacija │
│                        │
│ ✅ Naudoja teisingai   │
└────────────────────────┘
```

---

## 🧩 Palyginimas: Prieš ir Po

```
❌ PRIEŠ (BROKEN)                 ✅ PO (FIXED)
═══════════════════════════════════════════════════════

class Student {                  class Student {
    std::string name;                std::string name;
                                     
public:                          public:
    Student(string n)                Student(string n)
        : name(n) {}                     : name(n) {}
                                     
    Student(Student&& other)         Student(Student&& other)
        : name(std::move(            noexcept
               other.name)) {}           : name(std::move(
                                                  other.name)) {}
                                     
    // ❌ TRŪKSTA!                  // ✅ PRIDĖTA!
                                     Student(const Student&) = default;
                                     Student& operator=(const Student&)
                                         = default;
                                     Student& operator=(Student&&)
                                         noexcept = default;
};                               };

───────────────────────────────────────────────────────

Rezultatas:                      Rezultatas:

❌ std::sort() neveikia          ✅ std::sort() veikia
❌ vector::insert() neveikia     ✅ vector::insert() veikia
❌ vector::erase() neveikia      ✅ vector::erase() veikia
❌ obj = other neveikia          ✅ obj = other veikia
```

---

## 📚 Checklistai

### ✅ Ar Mano Klasė Teisinga?

```
□ Jei neapibrėžiau NIEKO special member functions
  → Nieko papildomo nereikia ✅

□ Jei apibrėžiau DESTRUCTOR
  → Patikrinti, ar reikia copy/move (deprecated) ⚠️

□ Jei apibrėžiau COPY CONSTRUCTOR
  → Pridėti copy assignment (bent = default) ✅
  → Arba = delete, jei neleidi copy ✅

□ Jei apibrėžiau MOVE CONSTRUCTOR
  → BŪTINA pridėti:
      • Copy constructor (= default arba custom)
      • Copy assignment (= default arba custom)  
      • Move assignment (= default arba custom)
  → Pridėti noexcept prie move operacijų ✅

□ Jei apibrėžiau BET KURĮ ASSIGNMENT
  → Apibrėžti visus kitus special members ✅
```

### 🔧 Quick Fix Checklistai

```
Matau kompiliavimo klaidą → Tikrinti:

□ error: use of deleted function
  → Pridėti = default operators

□ no matching function for call to 'swap'
  → Pridėti = default operators

□ cannot bind rvalue reference
  → Pridėti noexcept prie move

□ STL algoritmai neveikia
  → Tikrinti ar turiu operator= ir operator<
```

---

**Sukūrė:** Viktoras Golubevas  
**Kursas:** OOP su C++  
**Data:** 2026-02-12

**Atminkite diagrama:**
```
    🖐️
   /│\
  / │ \
 1  2  3  4  5
 │  │  │  │  │
 ~  ©  ©  →  →
    C  M  C  M
```

Vienas → Visi penki!
