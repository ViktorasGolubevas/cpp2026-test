Puiku! Jūsų požiūris – **gili, evoliucinė, koncepcinė kelionė nuo C iki C++** – yra ne tik pedagogiškai stipri, bet ir labai motyvuojanti studentams. Toks požiūris padeda suprasti **ne tik kaip**, bet ir **kodėl** OOP yra toks, koks jis yra.

Jūsų idėja suskirstyti C dalį į **8 etapus**, o 077 versiją laikyti „finišu“ – visiškai pagrįsta. Štai siūlomas **patobulintas struktūrizavimas**, kuris:

* išlaiko jūsų originalią logiką,
* aiškiai atskiria kiekvieno etapo **mokomąją vertę**,
* paruošia pagrindą C++ perėjimui,
* leidžia lengvai kurti **studentų užduotis**.

---

## 🧱 **C kalbos ADT evoliucija: 8 etapai (su mokomaisiais tikslais)**

|Etapas|Kodas|Pavadinimas|Pagrindinė idėja / mokoma koncepcija|Kritinė klaida / problema|Mokomasis tikslas|
|-|-|-|-|-|-|
|**1**|`01\_n\_usestack.c`|**Monolitas**|Viskas viename faile – globalūs kintamieji + funkcijos|Nelankštumas, nesidalinama|Suprasti, kad kodas gali veikti, bet tai nėra skalė|
|**2**|`02\_\*.c`|**Fizinis padalijimas be headerio**|`#include "modulis.c"`|Implicit function declaration, blogas stilius|Parodyti, kad fizinis padalijimas ≠ moduliavimas|
|**3**|`03\_nx/ny\_\*.c`|**Neteisingas moduliavimas**|Deklaracijos vs apibrėžimai|Multiple definition / undefined reference|Išmokti skirti `.h` (deklaracijos) ir `.c` (apibrėžimai)|
|**4**|`03\_stack.c/h`|**Tinkamas modulis, bet vieši duomenys**|Interfeisas per header’į|Duomenys prieinami iš išorės|Suprasti, kad **moduliavimas ≠ saugumas**|
|**5**|`04\_stack.c/h`|**Informacijos slėpimas per `static`**|Internal linkage|Tik **vienas** stekas sistemoje|Pamatyti ribas: slėpimas → bet ne daugelio egzempliorių|
|**6**|`05\_n\_usestack.c`|**ADT kaip tipas (`struct`)**|Vartotojo tipas su rodyklėmis|Vis dar viename faile|Perėjimas nuo globalaus → objektinio mąstymo|
|**7**|`06\_stack.c/h`|**Modulinis ADT su tipu**|Struktūra + funkcijos modulyje|Struktūros vidiniai laukai vieši|Galima „atakuoti“ – trūksta **abstrakcijos lygio**|
|**8**|`07\_stack.c/h`|**Opaque pointer (slėpimas per forward declaration)**|`struct Stack;` header’yje, pilnas apibrėžimas `.c`|Nėra tiesioginės prieigos prie laukų|**Pilnas informacijos slėpimas** – ADT baigtas C kontekste|
|**9** *(finišas)*|`077\_stack.c/h`|**ADT su resursų valdymu**|`create()` / `destroy()`|—|Paruošta RAII, konstruktoriams/destruktoriams|

> 💡 \*\*Pastaba\*\*: galite 8 ir 9 etapus sujungti, jei norite išlaikyti 8 etapus. Tada 8-as būtų „ADT su slėpimu + resursų valdymu“.

---

## 📝 **Studentų užduotis (C dalis)**

### **Užduotis 1: Evoliucijos analizė**

> \*\*Aprašymas\*\*:  
> Analizuokite pateiktus failus (nuo 01 iki 077). Kiekvienam etapui:
> - Paaiškinkite, kas buvo \*\*pagerinta\*\* arba \*\*išmokta\*\*.
> - Nurodykite, kodėl ankstesnis sprendimas buvo \*\*nepakankamas\*\*.
> - Pateikite trumpą \*\*kodu komentuotą palyginimą\*\* tarp dviejų gretimų etapų.

> \*\*Reikalavimas\*\*:  
> Pateikite ataskaitą su lentelėmis, klaidų analize ir savo refleksija – „Kodėl C++ reikalingas?“

---

### **Užduotis 2: Savarankiškas ADT kūrimas**

> \*\*Aprašymas\*\*:  
> Sukurkite \*\*dviejų tipų ADT\*\* (pvz., \*Queue\* ir \*Deque\*) C kalba, naudodami \*\*8-o etapo principus\*\*:
> - Opaque pointer (`struct Queue;`)
> - Atskiras `.h` ir `.c`
> - `create()` / `destroy()`
> - Visos operacijos per rodyklę
> - Testinis `main()` su „atakos“ bandymu (kuris turi \*\*nepavykti\*\*)

> \*\*Bonus\*\*:  
> Pabandykite sukurti \*\*dviejų stekų sistemą\*\* – patikrinkite, ar jos nepersidengia (t.y., ar `static` nebūtų pakankamas).

---

## 🔁 **Perėjimas į C++: 8+ etapai**

Dabar, kai C dalis baigta, C++ dalį galima struktūruoti **tiesiogiai kaip „atgalinę migraciją“** – kiekvienas C++ etapas **pašalina C apribojimus**:

|Etapas|C++ idėja|C analogas|Ką išsprendžia|
|-|-|-|-|
|**1**|`class Stack { public: ... }`|`06\_stack.h`|Funkcijos priklauso tipui|
|**2**|`private` laukai|`07\_stack.h`|Automatinis info hiding|
|**3**|Konstruktorius / destruktorius|`create()` / `destroy()`|RAII – resursai valdomi automatiškai|
|**4**|Rule of 3 (kopijavimo konstruktorius, operator=, destruktorius)|–|Gyliai kopijuojami duomenys|
|**5**|Rule of 5 (+ move)|–|Efektyvus perkėlimas|
|**6**|`std::array<char, SIZE>`|`char stack\[SIZE]`|Saugesnis, STL suderinamumas|
|**7**|`std::vector<char>`|–|Dinaminis dydis, realus naudojimas|
|**8**|`std::unique\_ptr<Stack>` / `shared\_ptr`|–|Automatinis atminties valdymas|
|**9**|`std::stack<char>`|–|„Rule of 0“ – nereikia rašyti nieko|

> 💡 \*\*Filosofinė mintis\*\*:  
> C++ leidžia \*\*pasiekti tą patį, ką pasiekėte C 8 etape\*\*, bet \*\*su mažiau kodo ir didesne sauga\*\*. Tai – esmė.

---

## 📚 Rekomenduojamas pavadinimas projektui

> \*\*„From C to C++: The Evolution of Abstraction and Encapsulation in Stack ADT“\*\*

Arba lietuviškai:

> \*\*„Nuo C iki C++: abstrakcijos ir inkapsuliacijos evoliucija steko ADT pavyzdžiu“\*\*

---

Jei norite, galiu:

* Sugeneruoti **PDF šabloną** su lentele ir užduotimis,
* Parašyti **pirmo C++ etapo kodą** (klasė su `private` laukais),
* Sukurti **testinius scenarijus** „atakoms“ (kad studentai pamatytų, kada slėpimas veikia, o kada – ne).

Sakykite, kur norėtumėte eiti toliau!

