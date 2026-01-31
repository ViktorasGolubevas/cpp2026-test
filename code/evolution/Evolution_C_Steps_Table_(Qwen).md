Puiku! Jūsų pateikta evoliucinė seka – tai labai aiškus ir pedagogiškai vertingas C kalbos ADT (Abstract Data Type) kūrimo demonstravimas, kuris puikiai paruošia kelią OOP konceptams C++. Štai jūsų lentelės **apibendrinta ir struktūruota versija**, kuri galėtų būti naudojama kaip mokomoji medžiaga ar net projekto dokumentacija:

---

### 📚 **C kalbos steko ADT evoliucija: nuo naivaus sprendimo iki paslėptos realizacijos**

|Nr.|Komanda / Failai|Neformalus pavadinimas|Pagrindinė koncepcija / terminas|Taikoma technika|Rezultatas / Pastabos|Klaidos / Problemos|
|-|-|-|-|-|-|-|
|1|`gcc 01\_n\_usestack.c`|**Stekas – viename faile**|Monolitas|Visa logika viename faile|Veikia, bet nelankstus|Nėra moduliavimo|
|2|`gcc 02\_n\_stack.c 02\_nx\_user.c`|**Stekas – failas (daugiafailinis)**|Fizinis padalijimas|`.c` failas įtraukiamas per `#include`|**Nesikompiliuoja**|Implicit function declaration|
|3|`gcc 02\_n\_user.c`|**Pseudo-projektas**|Modulinis požiūris be headerio|`#include "02\_n\_stack.c"`|Veikia, bet blogas stilius|Netinkamas moduliavimas|
|4|`gcc 03\_nx\_stack.c 03\_nx\_user.c`|**Neteisingas modulis**|Deklaracijos vs apibrėžimai|Headeris su apibrėžimais|**Linkerio klaida**|Multiple definition of `stack`, `top`|
|5|`gcc 03\_ny\_stack.c 03\_ny\_user.c`|**Trūksta apibrėžimų**|`extern` deklaracijos be apibrėžimų|Headeris su `extern`, bet nėra `.c` apibrėžimų|**Linkerio klaida**|Undefined reference to `stack`, `top`|
|6|`gcc 03\_stack.c 03\_user.c`|**Tinkamas modulis**|Interfeisas + realizacija|Headeris tik deklaracijoms|Veikia gerai|Bet duomenys vieši → **nėra informacijos slėpimo**|
|7|`gcc 03\_z\_user.c`|**"Ataka" į viešus duomenis**|Duomenų saugumas|Tiesioginis prieiga prie `stack\[]`|**Pavyko**|Parodo, kad ADT neapsaugotas|
|8|`gcc 04\_stack.c 04\_user.c`|**Paslėpta realizacija**|Internal linkage (`static`)|`static` globalūs kintamieji|Veikia, bet **tik vienas stekas**|Nėra daugelio egzempliorių|
|9|`gcc 04\_zx\_user.c`|**Bandymas "atakuoti"**|Informacijos slėpimas|`extern` bandymas prieiti prie `static`|**Nepavyko**|Linkerio klaida – `undefined reference`|
|10|`gcc 05\_nx\_usestack.c`|**Neteisingas UDT**|Struktūros su `static` nariais|Bandyta `static` struktūroje|**Kompiliacijos klaida**|C neleidžia `static` struktūros narių|
|11|`gcc 05\_ny\_usestack.c`|**UDT su by-value perdavimu**|Netinkamas parametrų perdavimas|Perduodama kopija|**Veikia, bet blogai**|Pokyčiai neįsimena – **logikos klaida**|
|12|`gcc 05\_n\_usestack.c`|**Tinkamas UDT**|Struktūra + rodyklės|Funkcijos su `struct \*`|Veikia gerai|Bet vis dar viename faile|
|13|`gcc 06\_stack.c 06\_user.c`|**UDT modulyje**|Modulinis ADT|Skirstymas į `.h` ir `.c`|Veikia gerai|Bet duomenys vis dar vieši|
|14|`gcc 06\_z\_user.c`|**"Ataka" į UDT**|Vieša struktūra|Tiesioginis `st.stack\[i]` naudojimas|**Pavyko**|Trūksta informacijos slėpimo|
|15|`gcc 07\_n\_\*.c`|**Nepilnas slėpimas**|Forward declaration be pilno tipo|`struct Stack;` header'yje|**Kompiliacijos klaida**|Incomplete type|
|16|`gcc 07\_stack.c 07\_user.c`|**ADT su slėpimu**|Opaque pointer idėja|Tik pointeris, struktūra `.c` faile|Veikia gerai|**Informacija paslėpta**|
|17|`gcc 07\_zx\_user.c`|**Bandymas "atakuoti" opaque**|Slėpimo testas|Bandymas naudoti `pst->stack`|**Nepavyko**|Kompiliacijos klaida – incomplete type|
|18|`gcc 077\_stack.c 077\_user.c`|**ADT su resursų valdymu**|RAII analogas C|`create()` / `destroy()`|Veikia idealiai|Paruošta OOP perėjimui|

---

### 🔑 **Pagrindinės išmoktos pamokos (OOP C++ kontekste):**

1. **Abstrakcija** – atskirti *ką* objektas gali daryti nuo *kaip* tai daroma.
2. **Inkapsuliacija** – paslėpti vidinę būklę, leisti prieigą tik per sąsają.
3. **Moduliavimas** – skirstyti kodą į logiškai atskirtus vienetus (`.h` + `.c`).
4. **Opaque pointer (pimpl idėjos prototipas)** – `struct Stack;` header’yje, pilnas apibrėžimas `.c` faile → **informacijos slėpimas**.
5. **Resursų valdymas** – `create()`/`destroy()` → C analogas konstruktoriui/destruktoriui.

---

### 💡 Rekomendacija OOP C++ pereinant:

* Palyginkite `077\_\*.c` su C++ klasės realizacija:

```cpp
  class Stack {
      char stack\[SIZE];
      int top;
  public:
      void push(char c);
      char pop();
      bool isEmpty() const;
      // ...
  };
  ```

* Pabrėžkite, kad **C++ klasė = C struktūra + funkcijos + prieigos kontrolė (`private`/`public`)**.

Jei norite, galiu padėti sukurti **vizualią schemą**, **palyginimo lentelę C vs C++**, ar net **studentų užduotis** pagal šią evoliuciją.

