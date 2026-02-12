# 🎓 BONUS: Advanced - Rule of Five

## ⚠️ Perspėjimas

Ši medžiaga yra **pažengusiems studentams** ir **neegzamininė**!

**Neprivaloma!** Tai papildoma medžiaga tiems, kurie nori:
- Suprasti, kaip veikia C++ viduje
- Pasiruošti darbo pokalbiams
- Optimizuoti performance-critical kodą
- Tapti C++ ekspertu

## 📚 Kas Čia Yra?

Pilna **Rule of Five** medžiaga, kuri paaiškina:
- Kodėl kartais reikia apibrėžti 5 special member functions
- Kas atsitinka, kai apibrėžiate tik vieną
- Kaip išvengti kompiliavimo klaidų
- Copy vs Move semantics

## 📁 Failai

1. **demo_07_fixed.cpp** - Veikiantis pavyzdys su pilnu Rule of Five
2. **demo_07_pedagogy.cpp** - Pedagoginis su broken/fixed versijomis
3. **Rule_of_Five_CheatSheet.md** - Greitas reference
4. **Rule_of_Five_Comparison.md** - Scenarijai ir palyginimas
5. **Rule_of_Five_Compilation_Scenarios.md** - Kada kompiliuojasi
6. **Rule_of_Five_Visual_Diagrams.md** - ASCII diagrams

## 🎯 Kam Tai Reikia?

### Problemos Scenarijus:

```cpp
class Student {
    std::string name;
public:
    Student(std::string n) : name(n) {}
    
    // Norite logging į move constructor
    Student(Student&& other) noexcept 
        : name(std::move(other.name)) {
        std::cout << "Move!\n";
    }
    
    // ❌ BUM! Kompiliatorius IŠTRINA copy/move assignment!
};

std::vector<Student> students;
students.emplace_back("Jonas");
students.emplace_back("Petras");
std::sort(students.begin(), students.end());  // ❌ NEVEIKIA!
```

### Sprendimas:

```cpp
// Pridėti:
Student(const Student&) = default;
Student& operator=(const Student&) = default;
Student& operator=(Student&&) noexcept = default;
```

## 🚫 Kada NEREIKIA Rule of Five?

**90% atvejų NEREIKIA!**

Jei klasė naudoja tik:
- `std::string`
- `std::vector`
- `std::unique_ptr`
- Kitus RAII objektus

→ **Kompiliatorius viską sutvarko automatiškai!**

## 🎓 Mokymosi Kelias

1. **Pirmiausia:** Perskaitykite `Rule_of_Five_CheatSheet.md`
2. **Tada:** Paleiskite `demo_07_pedagogy.cpp`
3. **Gilintis:** Skaitykite `Rule_of_Five_Comparison.md`
4. **Praktika:** Bandykite modifikuoti kodą

## 💡 Kada Tai Bus Aktualu?

- **Darbo pokalbis** - dažnai klausiama apie Rule of Five
- **Performance tuning** - move semantics kritiškas
- **Legacy code** - prižiūrint seną kodą
- **Library development** - rašant bendras bibliotekas

## ⚠️ Perspėjimas Dėstytojui

Šios temos **nerekomenduojama** dėstyti pirmame kurse:
- Per daug konceptų vienu metu
- Gąsdina studentus
- Užima daug laiko
- Nėra praktinė reikšmė pradžiai

**Geriau:**
- Parodykite, kad `std::vector` tiesiog veikia
- Džiaukitės automatiniu atminties valdymu
- Rule of Five paliktite vėliau (3-4 kursui arba darbo rinkoje)

## 🔗 Susijusi Medžiaga

Po šios temos natūraliai seka:
- Perfect forwarding
- Template metaprogramming
- Custom allocators
- Move-only types (unique_ptr, mutex)

## 📖 Literatūra

- Scott Meyers - "Effective Modern C++" (Item 17)
- Howard Hinnant - "A Brief Introduction to Rvalue References"
- cppreference.com - "The rule of three/five/zero"

---

**Sukūrė:** Viktoras Golubevas  
**Tikslas:** Bonus medžiaga pažengusiems  
**Statusas:** Neegzamininė, papildoma

**Atminkite:** Jei nesuprantate - nieko baisaus! 90% C++ programuotojų dirba nežinodami šių detalių. 😊
