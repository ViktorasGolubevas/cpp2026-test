# Etapas 02: Decomposing to UNITS
## Nuo monolito iki fizinio padalijimo

!!! tip "Šio etapo tikslas"
    Išmokti **fiziškai** atskirti programą į kompiliavimo vienetus, suprasti `#include` mechanizmą ir **patirti** tipines kompiliavimo/linkavimo klaidas kaip mokymosi įrankį. Studentai patiria "per nagus", kodėl reikia header failų.

---

## Problema, kurią sprendžiame

Etape 01 turėjome **monolitinį failą** - visa logika vienoje vietoje. Tai veikė ir net turėjo privalumų: galėjome rašyti `main()` funkcijų **prieš** stack funkcijas, nes kompiliatorius matė viską iš karto. Bet kai projektas auga, monolitas tampa nepriežiūrimu.

**Dėstytojas paprašo:** "Atskirkit stack logiką į atskirą failą, kad galėtumėte naudoti keliuose projektuose!"

**Studentų kelionė:** Trys bandymai, trys skirtingos klaidos, viena pamoka.

---

## Struktūra

```
02_Decomposing_to_UNITS/
├── 01_NC/              # Not Compiling - implicit declarations
│   ├── stack.c         
│   └── user.c          
├── 02_NL/              # Not Linking - multiple definition
│   ├── stack.c         
│   └── user.c          
└── 03_OK_Wrong/        # Veikia, bet antipattern
    ├── stack.c
    └── user.c
```

---

## Žingsnis 1: Naivus atskyrimas (01_NC)

Studentas tiesiog "supjaudo" monolitą į du failus ir bando kompiliuoti **atskirai**, kaip dėstytojas prašė.

=== "stack.c"

    ```c title="stack.c"
    --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/01_NC/stack.c"
    ```

=== "user.c"

    ```c title="user.c"
    --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/01_NC/user.c"
    ```

=== "Bandymas kompiliuoti"

    ```bash
    gcc -c stack.c    # ✅ Veikia
    gcc -c user.c     # ❓ Kas nutiks?
    ```

### Kas nutinka?

Priklausomai nuo kompiliatoriaus:

=== "GCC (Warning)"

    ```bash
    $ gcc -c user.c
    user.c: In function 'main':
    user.c:6:5: warning: implicit declaration of function 'init'
    user.c:7:37: warning: implicit declaration of function 'push'
    user.c:8:13: warning: implicit declaration of function 'isEmpty'
    user.c:8:32: warning: implicit declaration of function 'pop'
    ```
    
    ⚠️ **Kompiliuojasi su įspėjimais** - GCC "atleidžia" studentui

=== "Clang (Error)"

    ```bash
    $ clang -c user.c
    user.c:6:5: error: call to undeclared function 'init'; 
    ISO C99 and later do not support implicit function declarations
    user.c:7:37: error: call to undeclared function 'push'
    user.c:8:13: error: call to undeclared function 'isEmpty'
    user.c:8:32: error: call to undeclared function 'pop'
    4 errors generated.
    ```
    
    ❌ **Kompiliavimas nepavyksta!**

??? danger "Diagnozė: Monolito vs modulių skirtumas"
    
    **Monolite (01 etapas):**
    ```c
    // Viskas viename faile - kompiliatorius mato VISKĄ
    int main(void) {
        push('a');  // ✅ Kompiliatorius žino, kad push() bus žemiau
    }
    
    void push(char c) { ... }  // Apibrėžimas žemiau
    ```
    
    **Moduliuose (dabar):**
    ```c
    // user.c - kompiliatorius mato TIK ŠĮ failą!
    int main(void) {
        push('a');  // ❌ Kas tas push? Niekur nedeklaruotas!
    }
    // stack.c yra KITAME faile - kompiliatorius nemato!
    ```
    
    **Pamoka:** Kiekvienas `.c` failas kompiliuojamas **atskirai**. Funkcijos turi būti **deklaruotos** prieš naudojimą (arba apibrėžtos aukščiau faile).

??? info "Kodėl GCC leidžia, o Clang - ne?"
    
    **C89/C90 standartas:** Leido **implicit function declarations** - jei funkcija nedeklaruota, kompiliatorius priskirdavo default signatūrą `int func()`.
    
    **C99+ standartas:** Nebeleidžia implicit declarations - būtina aiški deklaracija.
    
    - **GCC:** Dėl backward compatibility default režimas toleruoja (warning)
    - **Clang:** Griežtai laikosi modernaus standarto (error)
    
    **Išvada:** Visada rašykite prototipus! Naudokite `gcc -std=c11 -Werror` arba testuokite su Clang.

---

## Žingsnis 2: "Logiška" idėja - #include "stack.c" (02_NL)

Studentas pamąsto: "Aha! Monolite viskas veikė, nes buvo kartu. Tai tiesiog **sujungsiu** failus su `#include`!"

**Ir vis tiek kompiliuoja atskirai**, kaip dėstytojas mokė:

=== "stack.c"

    ```c title="stack.c (nepakeistas)"
    --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/02_NL/stack.c"
    ```

=== "user.c"

    ```c title="user.c (su #include)"
    --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/02_NL/user.c"
    ```
    
    💡 Studentas mąsto: "Dabar `user.c` žinos apie stack funkcijas!"

=== "Kompiliavimas"

    ```bash
    gcc -c stack.c -o stack.o   # ✅ Sukuria stack.o
    gcc -c user.c -o user.o     # ✅ Sukuria user.o (su stack.c viduje!)
    gcc stack.o user.o -o app   # ❓ Linkavimas...
    ```

### Kas nutinka?

**Linkavimo klaida (NL):**

```
/usr/bin/ld: user.o: in function `push':
user.c:(.text+0x0): multiple definition of `push'; 
stack.o:stack.c:(.text+0x0): first defined here

/usr/bin/ld: user.o: in function `pop':
user.c:(.text+0x10): multiple definition of `pop'; 
stack.o:stack.c:(.text+0x10): first defined here

... (ir t.t. visoms funkcijoms)
```

??? danger "Diagnozė: Dviguba kompiliacija"
    
    **Kas įvyko:**
    
    1. `gcc -c stack.c` → sukuria `stack.o` su push(), pop(), ...
    2. `gcc -c user.c` → preprocesoras **įklijuoja** stack.c turinį → sukuria `user.o` **IRGI** su push(), pop(), ...
    3. Linkavimas: **2 objektiniai failai**, abiejuose tos pačios funkcijos → **multiple definition**!
    
    **Vizualizacija:**
    ```
    stack.o:  push() pop() init() isEmpty()
    user.o:   push() pop() init() isEmpty() main()  ← Dubliavimasis!
              ^^^^^ ^^^^^ ^^^^^^ ^^^^^^^^^
    ```
    
    **Pamoka:** `#include "*.c"` **dubliuoja** kodą. Preprocesoras tiesiog **copy-paste** daro!

??? question "Kodėl monolite veikė?"
    
    Monolite buvo **vienas** kompiliavimo vienetas:
    ```bash
    gcc stack_monolith.c -o app  # Vienas .c → vienas .o → vienas binary
    ```
    
    Dabar yra **du** kompiliavimo vienetai, kurie linkuojami kartu:
    ```bash
    gcc -c stack.c    # Pirmas .o
    gcc -c user.c     # Antras .o (su stack.c viduje!)
    gcc *.o           # Abu jungiami → conflict!
    ```

=== "stack.c"

    ```c title="stack.c"
    --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/02_NL/stack.c"
    ```

=== "user.c"

    ```c title="user.c"
    --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/02_NL/user.c"
    ```

=== "Kompiliavimas"

    ```bash
    gcc -c stack.c -o stack.o
    gcc -c user.c -o user.o
    gcc stack.o user.o -o app
    ```

### Kas nutinka?

```
/usr/bin/ld: user.o:(.bss+0x0): multiple definition of `stack'; 
stack.o:(.bss+0x0): first defined here
/usr/bin/ld: user.o:(.bss+0x0): multiple definition of `top'; 
stack.o:(.bss+0x0): first defined here
```

**Linkavimo klaida (NL)!** Kodėl?

??? danger "Diagnozė: Funkcijų deklaracijos prototipai ≠ kintamųjų deklaracijos"
    
    **Funkcijoms:**
    ```c
    void push(char c);  // ✅ Deklaracija (prototipas)
    ```
    
    **Kintamiesiems globaliam apimties lygyje:**
    ```c
    char stack[STACK_SIZE];  // ❌ Apibrėžimas (definition)!
    int  top = 0;            // ❌ Apibrėžimas!
    ```
    
    **Problema:** Kintamieji **abiejuose** failuose tampa **apibrėžimais**, todėl linkeris mato **dubliavimąsi** (multiple definition).

---

## Žingsnis 3: Antipattern su #include (03_OK_Wrong)

Studentai dažnai bando "išspręsti" tiesiog įtraukdami `stack.c` į `user.c`:

---

## Žingsnis 3: "Žingsnis atgal" - tik user.c (03_OK_Wrong)

Studentas sumišęs: "Per daug sudėtinga... Gal užtenka kompiliuoti **tik** `user.c`?"

=== "stack.c"

    ```c title="stack.c (tas pats)"
    --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/03_OK_Wrong/stack.c"
    ```

=== "user.c"

    ```c title="user.c (su #include)"
    --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/03_OK_Wrong/user.c"
    ```

=== "Kompiliavimas"

    ```bash
    gcc user.c -o app  # ✅ VEIKIA!
    ./app
    12345
    54321
    ```

### Kodėl veikia?

Dabar `gcc user.c` sukuria **vieną** objektinį failą su viskuo:
- Preprocesoras įklijuoja `stack.c` turinį į `user.c`
- Kompiliuojamas **vienas** didelis failas
- Nėra linkavimo → nėra konfliktų!

??? example "Kas iš tikrųjų kompiliuojama"
    
    Preprocesoriaus išvestis (`gcc -E user.c`):
    ```c
    // ... stdio.h turinys ...
    
    // ↓ Čia įklijuotas stack.c
    #define STACK_SIZE 10
    char stack[STACK_SIZE];
    int top = 0;
    void init(void) { top = 0; }
    void push(char c) { ... }
    char pop(void) { ... }
    int isEmpty(void) { ... }
    
    // ↓ Originalus user.c
    int main(void) {
        init();
        // ...
    }
    ```
    
    Vienas failas → vienas .o → veikia!

### Kodėl tai BLOGAI (antipattern)?

**1. Nėra tikro padalijimo**

Grįžome prie monolito, tik per `#include` triuką.

**2. Negalima pakartotinio naudojimo**

Kas jei norime stack keliuose projektuose?

```c
// project1/user1.c
#include "stack.c"  // OK

// project2/user2.c  
#include "stack.c"  // OK

// project3/main.c su user1.c IR user2.c?
// user1.c: #include "stack.c"
// user2.c: #include "stack.c"
// → Multiple definition! 💥
```

**3. Kompiliavimo laikas**

Kas kartą modifikavus `user.c` perkompiliuojamas **ir** stack.c, nors jis nepasikeitė.

**4. Prieštarauja C filosofijai**

`#include` skirtas **deklaracijoms** (.h), ne **implementacijai** (.c)!

??? warning "Taisyklė"
    
    **NIEKADA** nerašykite:
    ```c
    #include "*.c"  // ❌ BLOGAI
    ```
    
    **Visada** rašykite:
    ```c
    #include "*.h"  // ✅ GERAI
    ```

---

## Kodėl reikalingi .h failai?

### Problema, kurią patyrėme

```
01_NC → Kompiliatorius nemato funkcijų (trūksta deklaracijų)
02_NL → #include "stack.c" dubliuoja viską (multiple definition)
03_OK_Wrong → Veikia, bet negalima pakartotinai naudoti
```

### Klausimas, kuris turėtų kilti

!!! question "Kaip pakartotinai naudoti stack keliuose projektuose?"
    
    Tarkime, turime 3 projektus, visi nori stack:
    
    ```
    project1/
    ├── user1.c     # Nori stack
    └── stack.c
    
    project2/
    ├── user2.c     # Nori stack  
    └── stack.c     # ← Kopija!
    
    project3/
    ├── main.c      # Nori stack
    ├── helper.c    # Ir čia nori!
    └── stack.c     # ← Dar viena kopija!
    ```
    
    **Problemos:**
    - Kopijuojame stack.c → prižiūrėjimo košmaras (bug fix reikia 3 vietose)
    - Arba `#include "stack.c"` → 02_NL klaida, jei keli failai linkuojami
    - Prototipus kopijuojame rankiniu būdu → pakeitė signatūrą? Taisyk visur!

### Sprendimas: Atskirkime "KĄ" nuo "KAIP"

**Esmė:** Reikia atskirti **interface** (ką galima daryti) nuo **implementation** (kaip tai padaryta).

??? example "Analogija: Restoranas"
    
    **Meniu (= .h failas):**
    - Parodo **ką** galima užsisakyti
    - Klientas (user.c) mato tik meniu
    - Lengvai kopijuojamas (daug kopijų nesukelia problemų)
    
    **Virtuvė (= .c failas):**
    - Žino **kaip** pagaminti patiekalus
    - Klientas nemato viryklės detalių
    - Viena virtuvė aptarnauja daug klientų
    
    **Blogai būtų:**
    - Kiekvienas klientas turi savo virtuvę (03_OK_Wrong su `#include "stack.c"`)
    - Klientas turi žinoti receptus (01_NC be deklaracijų)

### Prototipų dubliavimosi problema

**Be .h failo (dabar):**

```c
// user1.c
void push(char);  // ← Copy-paste
char pop(void);   // ← Copy-paste

// user2.c  
void push(char);  // ← Copy-paste
char pop(void);   // ← Copy-paste

// stack.c
void push(char c) { ... }  // Tikras apibrėžimas
char pop(void) { ... }
```

**Pakeitėte `push(char c)` → `push(int c)`?**  
Taisyti reikia **4 vietose**: stack.c + user1.c + user2.c + user3.c!

**Su .h failu (Etapas 03):**

```c
// stack.h (header)
void push(int);   // ← Viena vieta!
char pop(void);

// user1.c, user2.c, user3.c
#include "stack.h"  // Automatiškai gauna naujausią versiją

// stack.c
#include "stack.h"  // Ir implementacija naudoja tą patį
void push(int c) { ... }
```

**Pakeitėte signatūrą?** Taisote **1 vietą** (stack.h)!

### Nuo ko pradėti mokytis .h?

!!! tip "Header failas nėra baisus!"
    
    **Kas bus header faile?** Paprasčiausiai tai, ką jau rašėme:
    
    ```c
    // stack.h - tai tik prototipai!
    void push(char);
    char pop(void);
    int isEmpty(void);
    ```
    
    **Vienintelis skirtumas:** Dabar tai atskirame faile, kurį galima `#include` daug kartų.
    
    **Bonus:** Pridėsime "apsaugas" (`#ifndef`), kad nebūtų dubliavimo, jei failas įtraukiamas kelis kartus.

---

## Teisingas kelias → Etapas 03

Etape **03: Discovering C MODULE** išmoksime sukurti tikrą C modulį su header failu, ir pamirškite baimę - header failas yra paprasčiau nei atrodo!

---

## Mokymosi rezultatai

Po šio etapo studentai:

**Techniškai supranta:**
- Kompiliavimo vieneto (translation unit) koncepciją
- Skirtumą tarp monolito ir modulių (funkcijų eiliškumas)
- Kompiliatorių skirtumus (GCC vs Clang, implicit declarations)
- Linkavimo proceso esmę (kas yra multiple definition)
- Preprocesoriaus darbą (`#include` = copy-paste)

**"Per nagus" patyrė:**
- 01_NC → Implicit declarations (GCC toleruoja, Clang - ne)
- 02_NL → Dubliavimąsi (`#include "*.c"` + atskira kompiliacija)
- 03_OK_Wrong → Antipattern, kuris veikia (bet neišsprendžia problemos)

**Suvokia poreikį:**
- Header failų (.h) - ne iš teorijos, o iš praktikos
- Interface/Implementation atskyrimo
- Pakartotinio kodo naudojimo mechanizmų

**Pamokos:**
- Kompiliavimo klaidos = mokymosi įrankis
- `#include "*.c"` yra antipattern
- Vieno kompiliatoriaus nepakanka (testuokite su GCC ir Clang)
- Prototipų dubliavimas yra prižiūrėjimo košmaras

??? quote "Pedagoginis principas"
    
    **Studentai neturi bijoti header failų**, nes:
    
    1. Jau rašė prototipus (01_NC bandyme)
    2. Mato jų trūkumo problemą (02_NL dubliavimąsi)  
    3. Supranta pakartotinio naudojimo poreikį (03_OK_Wrong ribotumą)
    
    **Header failas yra tiesiog atsakymas į problemas, kurias patyrė.**
    
    Ne "nauja magija", o "protingas sprendimas".

---

## Kitas žingsnis

Etape **03: Discovering C MODULE** išmoksime sukurti **header** failą (`stack.h`), naudoti `extern` raktinius žodžius, header guards (`#ifndef`), tikrą C modulio struktūrą.

??? tip "README failai su detaliais paaiškinimais"
    
    - [01_NC README](https://github.com/ViktorasGolubevas/cpp2026-test/tree/main/code/evolution/stack-2026/02_Decomposing_to_UNITS/01_NC)
    - [02_NL README](https://github.com/ViktorasGolubevas/cpp2026-test/tree/main/code/evolution/stack-2026/02_Decomposing_to_UNITS/02_NL)
    - [03_OK_Wrong README](https://github.com/ViktorasGolubevas/cpp2026-test/tree/main/code/evolution/stack-2026/02_Decomposing_to_UNITS/03_OK_Wrong)
