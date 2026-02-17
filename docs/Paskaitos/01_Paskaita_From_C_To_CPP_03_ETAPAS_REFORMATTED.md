# Stack ADT Evoliucija C kalboje
## 9 Etapų Kelionė: Nuo Monolito iki Pilno ADT

!!! abstract "Šios kelionės tikslas"
    Susipažinti su **Abstraktaus duomenų tipo** (toliau - **ADT**) "Stekas", (angl. _Abstract Data Type_ _**Stack**_) evoliucija **C kalboje**: nuo paprasčiausio monolito iki pilnai realizuoto ADT su jo egzemoliorių gyvavimo ciklo (_lifecycle_) valdymu.

    Kiekvienas etapas (paprastai) sprendžia ankstesnio problemą, mokydamasis iš bandymų ir klaidų, gilindamas teorinies žinias ir praktikius įgūdžius. 
    >**Kompiliavimo ir linkavimo klaidos ir perspėjimai yra mokymosi įrankis!**

---

## 1️⃣Etapas: "Stekas-Programa" 
> `01_Running_PROGRAM`
 
!!! note "Kontekstas"
    "Monolitinė" programa - viskas viename faile.

---

### 1 sprendimas: "Naivus"
> `01_Running_PROGRAM/01_OK_Naive/`

Pradedame nuo paprasčiausio sprendimo - **vienas failas: ir visa logika, ir visa "fizika" kartu**.

=== "usestack.c"

    ??? "📄 01_Running_PROGRAM/01_OK_naive/usestack.c"

        ```c linenums="1" hl_lines="6-7"
        --8<-- "code/evolution/stack-2026/01_Running_PROGRAM/01_OK_naive/usestack.c"
        ```

=== "🔨 = ⚙️➔🔗➔🚀"

    ```bash
    $gcc usestack.c -o app
    ./app
    ```
    arba (win)
    ```bash
    >gcc usestack.c -o app
    app
    ```

=== "⌨️➔🖥️"

    ```
    123
    321
    ```

---

#### ✅ Veikia! Bet...

??? success "Privalumai"
    - **Funkcijų eiliškumas nesvarbus:** `main()` gali būti viršuje
    - **Kompiliatorius mato viską:** Vienas kompiliavimo vienetas
    - **Paprastas build:** Viena komanda
    - **Greitas prototipavimas:** Įdarbinimo pokalbio "quick solution"

??? danger "Problemos, pavojai..."
    - **Globalūs kintamieji:** `stack[]` ir `top` matomi visur
    - **Tik vienas stekas:** Negalima turėti kelių
    - **Pakartotinis naudojimas:** Kaip kitas projektas naudotų?
    - **Prižiūrėjimas:** 1000+ eilučių viename faile

---

## 2️⃣Etapas: "Stekas-Failas" 

> [`02_Decomposing_to_UNITS`](https://github.com/ViktorasGolubevas/cpp2026-test/tree/main/code/evolution/stack-2026/02_Decomposing_to_UNITS/)

!!! note "Kontekstas"
    Lyg ir logiškas fizinis padalijimas į failus: paslauga (`stack.c`) + vartotojas (`user.c`).

---

### 1 sprendimas: Kodo padalijimas

> `02_Decomposing_to_UNITS/01_NC/`

!!! quote "sumanymas/ketinimas"
    Tiesiog padalinau kodą į du failus ir kompiliuoju atskirai, kaip manęs ir reikalauja.

=== "stack.c"

    ??? "📄 02_Decomposing_to_UNITS/01_NC/stack.c"

        ```c linenums="1" 
        --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/01_NC/stack.c"
        ```

=== "user.c"

    ??? "📄 02_Decomposing_to_UNITS/01_NC/user.c"

        ```c linenums="1"
        --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/01_NC/user.c"
        ```

=== "⚙️gcc → ⚠️warning"

    ```bash
    gcc -c stack.c # ✅
    gcc -c user.c  # ⚠️
    user.c: In function 'main':
    user.c:6:5: warning: implicit declaration of function 'init' [-Wimplicit-function-declaration]
        6 |     init();
        |     ^~~~
    user.c:7:37: warning: implicit declaration of function 'push' [-Wimplicit-function-declaration]
        7 |     while ('\n' != (c = getchar())) push(c);
        |                                     ^~~~
    user.c:8:13: warning: implicit declaration of function 'isEmpty' [-Wimplicit-function-declaration]
        8 |     while (!isEmpty()) putchar(pop());
        |             ^~~~~~~
    user.c:8:32: warning: implicit declaration of function 'pop'; did you mean 'popen'? [-Wimplicit-function-declaration]
        8 |     while (!isEmpty()) putchar(pop());
        |                                ^~~
        |                                popen
    ```
    
=== "⚙️clang → ❌error"

    ```bash
    clang -c stack.c # ✅
    clang -c user.c  # ❌
    user.c:6:5: error: call to undeclared function 'init'; ISO C99 and later do not support implicit function declarations
        [-Wimplicit-function-declaration]
        6 |     init();
        |     ^
    user.c:7:37: error: call to undeclared function 'push'; ISO C99 and later do not support implicit function declarations
        [-Wimplicit-function-declaration]
        7 |     while ('\n' != (c = getchar())) push(c);
        |                                     ^
    user.c:8:13: error: call to undeclared function 'isEmpty'; ISO C99 and later do not support implicit function
        declarations [-Wimplicit-function-declaration]
        8 |     while (!isEmpty()) putchar(pop());
        |             ^
    user.c:8:32: error: call to undeclared function 'pop'; ISO C99 and later do not support implicit function declarations
        [-Wimplicit-function-declaration]
        8 |     while (!isEmpty()) putchar(pop());
        |                                ^
    4 errors generated.
    ```
---

#### ❌ Nesikompiliuoja

??? bug "Kompiliavimo klaida!"
    Kreipiamės į **neaprašytą** funkciją - kompiliatorius "nežino" kas tai per vardas, ką ar kokį veiksmą jis "atstovauja".

??? info "Monolitas vs atskiri failai"
    **Monolite:** kompiliatorius mato visą failą: jeigu kreipiamės vardu (į kintamąjį ar kviečiame funkciją), jų **apibrėžimai** (_*definition*_) yra jame.

    **Failuose:** kiekvienas `.c` yra atskiras kompiliavimo vienetas: vardų apibrėžtų kitame faile nemato - reikia (bent) jų **aprašų**/**deklaracijų** (_*declaration*_).

---

### 2 sprendimas: `.c` failo `#include`

> `02_Decomposing_to_UNITS/02_NL/`

!!! quote "sumanymas/ketinimas"
    Jei nemato vardų, o yra `#include`, tai jį ir panaudosiu - tada matys (kitur veikia pvz. `import`).

=== "user.c"

    ???+ "📄 02_Decomposing_to_UNITS/02_NL/user.c"

        ```c linenums="1"  hl_lines="2"
        --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/02_NL/user.c"
        ```

=== "stack.c"

    ???+ "📄 02_Decomposing_to_UNITS/02_NL/stack.c"

        ```c linenums="1"
        --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/02_NL/stack.c"
        ```

=== "⚙️gcc → 🔗gcc → ❌error"

    ```bash
    gcc -c stack.c -o stack.o  # ✅
    gcc -c user.c -o user.o    # ✅
    gcc stack.o user.o -o app  # ❌
    ```
    ```
    C:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: user.o:user.c:(.text+0x0): multiple definition of `init'; stack.o:stack.c:(.text+0x0): first defined here
    C:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: user.o:user.c:(.text+0x11): multiple definition of `isEmpty'; stack.o:stack.c:(.text+0x11): first defined here
    C:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: user.o:user.c:(.text+0x25): multiple definition of `isFull'; stack.o:stack.c:(.text+0x25): first defined here
    C:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: user.o:user.c:(.text+0x3a): multiple definition of `push'; stack.o:stack.c:(.text+0x3a): first defined here
    C:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: user.o:user.c:(.text+0x76): multiple definition of `pop'; stack.o:stack.c:(.text+0x76): first defined here
    C:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: user.o:user.c:(.bss+0x0): multiple definition of `stack'; stack.o:stack.c:(.bss+0x0): first defined here
    C:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: user.o:user.c:(.bss+0x8): multiple definition of `top'; stack.o:stack.c:(.bss+0x8): first defined here
    collect2.exe: error: ld returned 1 exit status
    ```
    ❌ multiple definition of ...

=== "⚙️clang → 🔗clang → ❌error"

    ```bash
    clang -c stack.c -o stack.o  # ✅
    clang -c user.c -o user.o    # ✅
    clang stack.o user.o -o app  # ❌
    ```
    ```
    C:/mingw64/bin/ld: user.o:user.c:(.text+0x0): multiple definition of `init'; stack.o:stack.c:(.text+0x0): first defined here
    C:/mingw64/bin/ld: user.o:user.c:(.text+0x11): multiple definition of `isEmpty'; stack.o:stack.c:(.text+0x11): first defined here
    C:/mingw64/bin/ld: user.o:user.c:(.text+0x25): multiple definition of `isFull'; stack.o:stack.c:(.text+0x25): first defined here
    C:/mingw64/bin/ld: user.o:user.c:(.text+0x3a): multiple definition of `push'; stack.o:stack.c:(.text+0x3a): first defined here
    C:/mingw64/bin/ld: user.o:user.c:(.text+0x76): multiple definition of `pop'; stack.o:stack.c:(.text+0x76): first defined here
    C:/mingw64/bin/ld: user.o:user.c:(.bss+0x0): multiple definition of `stack'; stack.o:stack.c:(.bss+0x0): first defined here
    C:/mingw64/bin/ld: user.o:user.c:(.bss+0x8): multiple definition of `top'; stack.o:stack.c:(.bss+0x8): first defined here
    clang: error: linker command failed with exit code 1 (use -v to see invocation)
    ```
    ❌ multiple definition of ...

---

#### ❌ Nesilinkina

??? bug "Linkinimo klaida!"
    `#include "stack.c"` įterpia turinį → visi `stack.c` **apibrėžimai** (kintamieji ir funkcijos) po kompiliavimo yra abiejuose `.o` failuose.

    Kad pagaminti vykdantijį failą (programą) linkeris turi sulinkinti `.o` failuoses esančius kreipinius į vardus su jų **apibrėžimais**/realizacijomis (vieninteliais!), bet jų po du per abu. Ką daryti? Linkeris lyg ir galėtų pasirinkti, bet... pagal kokį kriterijų? Jis šį sprendimą griežtai deleguoja autoriui,informuodamas apie "daugybinio apibrėžimo" klaidą.

---

### 3 sprendimas: `.c` failo `#include` be "galvos skausmo"

> `02_Decomposing_to_UNITS/03_OK_Wrong/`

!!! quote "sumanymas/ketinimas"
    Jei nesilinkina dėl pasikartojančių apibrėžimų, tai paliksiu `#include "stack.c"` ir nebelinkinsiu su juo.

=== "stack.c"

    ??? "📄 02_Decomposing_to_UNITS/03_OK_Wrong/stack.c"
    
        ```c linenums="1"
        --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/03_OK_Wrong/stack.c"
        ```

=== "user.c"

    ???+ "📄 02_Decomposing_to_UNITS/03_OK_Wrong/user.c"
    
        ```c linenums="1" hl_lines="2"
        --8<-- "code/evolution/stack-2026/02_Decomposing_to_UNITS/03_OK_Wrong/user.c"
        ```

=== "🔨"

    ```bash
    gcc user.c -o app
    app  # ✅ VEIKIA!
    ```

=== "⌨️➔🖥️"

    ```
    123
    321
    ```

---

#### ✅ Veikia! Bet...

??? warning "Kodėl BLOGAI (antipattern)?"
    - Grįžome prie monolito ir jo ribotumo/netinkamumo
    - Negalimas pakartotinis naudojimas...
    - `#include` skirtas `.h`, ne `.c`

---

---

### 💡 Pamokos

!!! tip "Veikiantis Kodas ≠ Geras Kodas"

---

## 3️⃣Etapas: "Stekas-Modulis"

> [`03_Discovering_C_MODULE`](https://github.com/ViktorasGolubevas/cpp2026-test/tree/main/code/evolution/stack-2026/03_Discovering_C_MODULE/)

!!! note "Kontekstas"
    Tikras C modulis su header failu.

**Modulis** = Interfeisas + Realizacija = Antraštė (antraštės failas) + Kodas (išeities failas)

**Modulis** = `.h` + `.c`

**4 sprendimai** (prasideda nuo 02_NL).

---

### 1 sprendimas: į `.h` be `extern`

> `03_Discovering_C_MODULE/02_NL/`

!!! quote "sumanymas/ketinimas"
    Sukursiu tikrą C modulį: `.h` su deklaracijomis, `.c` su apibrėžimais. Tiesiog perkelsiu funkcijų prototipus ir kintamųjų deklaracijas į header failą.

=== "stack.h" 

    ???+ "📄 03_Discovering_C_MODULE/02_NL/stack.h"
    
        ```c linenums="1" hl_lines="6-7"
        --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/02_NL/stack.h"
        ```

=== "stack.c"

    ??? "📄 03_Discovering_C_MODULE/02_NL/stack.c"
    
        ```c linenums="1" hl_lines="2"
        --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/02_NL/stack.c"
        ```

=== "user.c"

    ??? "📄 03_Discovering_C_MODULE/02_NL/user.c"
    
        ```c linenums="1" hl_lines="2"
        --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/02_NL/user.c"
        ```

=== "🔨 = ⚙️➔🔗➔❌"

    === "⚙️gcc ➔ 🔗gcc ➔ ❌error"
    
        ```bash
        gcc -c stack.c -o stack.o  # ✅
        gcc -c user.c -o user.o    # ✅
        gcc stack.o user.o -o app  # ❌
        ```
        ```
        C:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: user.o:user.c:(.bss+0x0): multiple definition of `stack'; stack.o:stack.c:(.bss+0x0): first defined here
        C:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: user.o:user.c:(.bss+0x64): multiple definition of `top'; stack.o:stack.c:(.bss+0x64): first defined here
        collect2.exe: error: ld returned 1 exit status
        ```
        ❌ multiple definition of ...
    
    === "⚙️clang ➔ 🔗clang ➔ ❌error"
    
        ```bash
        clang -c stack.c -o stack.o  # ✅
        clang -c user.c -o user.o    # ✅
        clang stack.o user.o -o app  # ❌
        ```
        ```
        C:/mingw64/bin/ld: user.o:user.c:(.bss+0x0): multiple definition of `top'; stack.o:stack.c:(.bss+0x0): first defined here
        C:/mingw64/bin/ld: user.o:user.c:(.bss+0x10): multiple definition of `stack'; stack.o:stack.c:(.bss+0x10): first defined here
        clang: error: linker command failed with exit code 1 (use -v to see invocation)
        ```
        ❌ multiple definition of ...

---

#### ❌ Nesilinkina

??? bug "Linkinimo klaida!"
    Kintamieji apibrėžti header'yje → abu failai sukuria kopijas. Tas pats kaip buvo, bet tik kintamiesiems. Reikia "aprašo formos" kintamiesiems. Pasitelkiam `extern`.

---

### 2 sprendimas: į `.h` su `extern`

> `03_Discovering_C_MODULE/03_NL/`

!!! quote "sumanymas/ketinimas"
    Išmokau, kad header'yje reikia `extern` kintamiesiems! Pridėsiu `extern` prie `stack[]` ir `top` deklaracijų.

=== "stack.h"

    ???+ "📄 03_Discovering_C_MODULE/03_NL/stack.h"
    
        ```c linenums="1" hl_lines="6-7"
        --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/03_NL/stack.h"
        ```

=== "stack.c"

    ??? "📄 03_Discovering_C_MODULE/03_NL/stack.c"
    
        ```c linenums="1" hl_lines="2"
        --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/03_NL/stack.c"
        ```

=== "user.c"

    ??? "📄 03_Discovering_C_MODULE/03_NL/user.c"
    
        ```c linenums="1" hl_lines="2"
        --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/03_NL/user.c"
        ```

=== "🔨 = ⚙️➔🔗➔❌"

    === "⚙️gcc ➔ 🔗gcc ➔ ❌error"
    
        ```bash
        gcc -c stack.c -o stack.o  # ✅
        gcc -c user.c -o user.o    # ✅
        gcc stack.o user.o -o app  # ❌
        ```
        ```
        C:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: stack.o:stack.c:(.bss+0x0): multiple definition of `stack'; user.o:user.c:(.bss+0x0): first defined here
        C:/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: stack.o:stack.c:(.bss+0x64): multiple definition of `top'; user.o:user.c:(.bss+0x64): first defined here
        collect2.exe: error: ld returned 1 exit status
        ```
        ❌ multiple definition of ...
    
    === "⚙️clang ➔ 🔗clang ➔ ❌error"
    
        ```bash
        clang -c stack.c -o stack.o  # ✅
        clang -c user.c -o user.o    # ✅
        clang stack.o user.o -o app  # ❌
        ```
        ```
        C:/mingw64/bin/ld: user.o:user.c:(.bss+0x0): multiple definition of `stack'; stack.o:stack.c:(.bss+0x0): first defined here
        C:/mingw64/bin/ld: user.o:user.c:(.bss+0x64): multiple definition of `top'; stack.o:stack.c:(.bss+0x64): first defined here
        clang: error: linker command failed with exit code 1 (use -v to see invocation)
        ```
        ❌ multiple definition of ...

---

#### ❌ Nesilinkina

??? bug "Dar viena NL klaida!"
    `extern` header'yje gerai, bet `stack.c` TAIP PAT turi kintamųjų apibrėžimus! Dabar abu `.c` failai sukuria apibrėžimus. Header'yje turi būti TIK `extern` deklaracijos, o apibrėžimas – TIKTAI viename `.c` faile.

---

### 3 sprendimas: Teisingas modulis

> `03_Discovering_C_MODULE/04_OK/`

!!! quote "sumanymas/ketinimas"
    Supratau! Header'yje – `extern` deklaracijos, o apibrėžimas tik `stack.c` faile (be `extern`). User.c tik naudoja, bet neapibrėžia.

=== "stack.h"

    ???+ "📄 03_Discovering_C_MODULE/04_OK/stack.h"
    
        ```c linenums="1" hl_lines="6-7"
        --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/04_OK/stack.h"
        ```

=== "stack.c"

    ??? "📄 03_Discovering_C_MODULE/04_OK/stack.c"
    
        ```c linenums="1" hl_lines="2 5-6"
        --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/04_OK/stack.c"
        ```

=== "user.c"

    ??? "📄 03_Discovering_C_MODULE/04_OK/user.c"
    
        ```c linenums="1" hl_lines="2"
        --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/04_OK/user.c"
        ```

=== "🔨 = ⚙️➔🔗➔🚀"

    ```bash
    gcc -c stack.c -o stack.o  # ✅
    gcc -c user.c -o user.o    # ✅
    gcc stack.o user.o -o app  # ✅
    ./app
    ```
    arba (win)
    ```bash
    gcc -c stack.c -o stack.o
    gcc -c user.c -o user.o
    gcc stack.o user.o -o app
    app
    ```

=== "⌨️➔🖥️"

    ```
    123
    321
    ```

---

#### ✅ Veikia! Bet...

??? success "Dabar teisingai!"
    - `extern` deklaracijos header'yje
    - Apibrėžimai stack.c
    - Tikras C modulis

??? danger "Problemos, pavojai..."
    - **Globalūs kintamieji viešai prieinami:** Kas nors gali rašyti `extern int top;` savo kode ir manipuliuoti!
    - **Nėra apsaugos:** Bet kas gali sugadinti `top` ar `stack[]`

---

### 4 sprendimas: Ataka pavyksta

> `03_Discovering_C_MODULE/05_OK_Attack/`

!!! quote "sumanymas/ketinimas"
    Pademonstruoju, kad net ir "teisingas" modulis su `extern` nėra saugus – "attacker" gali pridėti `extern int top;` ir keisti steko būseną.

=== "stack.h"

    ??? "📄 03_Discovering_C_MODULE/05_OK_Attack/stack.h"
    
        ```c linenums="1" hl_lines="6-7"
        --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/05_OK_Attack/stack.h"
        ```

=== "stack.c"

    ??? "📄 03_Discovering_C_MODULE/05_OK_Attack/stack.c"
    
        ```c linenums="1" hl_lines="2 5-6"
        --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/05_OK_Attack/stack.c"
        ```

=== "user_attack.c"

    ???+ "📄 03_Discovering_C_MODULE/05_OK_Attack/user_attack.c"
    
        ```c linenums="1" hl_lines="3-4 10"
        --8<-- "code/evolution/stack-2026/03_Discovering_C_MODULE/05_OK_Attack/user_attack.c"
        ```

=== "🔨 = ⚙️➔🔗➔🚀"

    ```bash
    gcc -c stack.c -o stack.o
    gcc -c user_attack.c -o user_attack.o
    gcc stack.o user_attack.o -o app
    ./app  # ✅ bet rezultatas BLOGAS!
    ```
    arba (win)
    ```bash
    gcc -c stack.c -o stack.o
    gcc -c user_attack.c -o user_attack.o
    gcc stack.o user_attack.o -o app
    app
    ```

=== "⌨️➔🖥️"

    ```
    HACKED: -1
    321
    ```

---

#### ✅ Veikia, bet BLOGAI!

??? danger "Globalūs kintamieji viešai prieinami"
    ```c
    extern int top;
    top = -1;  // ← Galima manipuliuoti!
    ```
    Vartotojas gali tiesiogiai pasiekti ir sugadinti vidinę steко būseną!
    
    **Sprendimas → Etapas 04:** `static` linkage

---

### 💡 Pamokos

!!! tip "C Modulio Anatomija"
    - **Header (`.h`)**: `extern` deklaracijos globalių kintamųjų + funkcijų prototipai
    - **Source (`.c`)**: Kintamųjų apibrėžimai (be `extern`) + funkcijų realizacijos
    - **Problem**: Globalūs kintamieji su `extern` yra prieinami bet kam!

---
## Etapas 04: Protecting IMPLEMENTATION
### Information hiding su `static`

### Žingsnis 1: Ataka su static (01_NL_Attack)

=== "stack.h"

    ```c title="04_Protecting_IMPLEMENTATION/01_NL_Attack/stack.h"
    --8<-- "code/evolution/stack-2026/04_Protecting_IMPLEMENTATION/01_NL_Attack/stack.h"
    ```

??? danger "Problema: `extern` vis dar header'yje"
    Jei header'yje `extern`, bet `.c` faile `static` → konfliktas

---

### Žingsnis 2: Tikras information hiding (02_OK)

=== "stack.h"

    ```c title="04_Protecting_IMPLEMENTATION/02_OK/stack.h"
    --8<-- "code/evolution/stack-2026/04_Protecting_IMPLEMENTATION/02_OK/stack.h"
    ```

=== "stack.c"

    ```c title="04_Protecting_IMPLEMENTATION/02_OK/stack.c"
    --8<-- "code/evolution/stack-2026/04_Protecting_IMPLEMENTATION/02_OK/stack.c"
    ```

??? success "`static` linkage veikia!"
    ```c
    static char stack[STACK_SIZE];
    static int top = 0;
    ```
    Ataka dabar neveiks! Bet... tik vienas stekas.

---

## Etapas 05: Defining USER TYPE
### Struct monolite - "greitas entry point"

**Koncepcija:** Grįžtame į monolitą, bet su **struct** - tarsi įdarbinimo pokalbio "quick solution".

### Žingsnis 1: static struktūroje (01_NC)

=== "usestack.c"

    ```c title="05_Defining_USER_TYPE/01_NC/usestack.c"
    --8<-- "code/evolution/stack-2026/05_Defining_USER_TYPE/01_NC/usestack.c"
    ```

??? danger "Kompiliavimo klaida"
    ```c
    struct Stack {
        static char stack[SIZE];  // ❌ Neleidžiama!
    };
    ```
    C draudžia storage-class specifiers struktūroje

---

### Žingsnis 2: Pass-by-value (02_RT)

=== "usestack.c"

    ```c title="05_Defining_USER_TYPE/02_RT/usestack.c"
    --8<-- "code/evolution/stack-2026/05_Defining_USER_TYPE/02_RT/usestack.c"
    ```

??? danger "Runtime problema"
    ```c
    void init(struct Stack st) {  // Kopija!
        st.top = 0;  // Keičia kopiją, ne originalą
    }
    ```

---

### Žingsnis 3: Pass-by-pointer (03_OK)

=== "usestack.c"

    ```c title="05_Defining_USER_TYPE/03_OK/usestack.c"
    --8<-- "code/evolution/stack-2026/05_Defining_USER_TYPE/03_OK/usestack.c"
    ```

??? success "Dabar veikia!"
    ```c
    void init(struct Stack *pst) {
        pst->top = 0;  // Keičia originalą
    }
    
    struct Stack st1, st2;  // Du stekai!
    ```

---

## Etapas 06: ENCAPSULATING UDT in Module
### Struct + modulis = apjungimas idėjų

**Koncepcija:** Dabar **struct modulyje** - apjungiame 05 (struct) + 03 (modulis).

### Žingsnis 1: Modulinis UDT (01_OK)

=== "stack.h"

    ```c title="06_ENCAPSULATING_UDT_in_Module/01_OK/stack.h"
    --8<-- "code/evolution/stack-2026/06_ENCAPSULATING_UDT_in_Module/01_OK/stack.h"
    ```

=== "stack.c"

    ```c title="06_ENCAPSULATING_UDT_in_Module/01_OK/stack.c"
    --8<-- "code/evolution/stack-2026/06_ENCAPSULATING_UDT_in_Module/01_OK/stack.c"
    ```

=== "user.c"

    ```c title="06_ENCAPSULATING_UDT_in_Module/01_OK/user.c"
    --8<-- "code/evolution/stack-2026/06_ENCAPSULATING_UDT_in_Module/01_OK/user.c"
    ```

---

### Žingsnis 2: Ataka pavyksta (02_OK_Attack)

=== "user_attack.c"

    ```c title="06_ENCAPSULATING_UDT_in_Module/02_OK_Attack/user_attack.c"
    --8<-- "code/evolution/stack-2026/06_ENCAPSULATING_UDT_in_Module/02_OK_Attack/user_attack.c"
    ```

??? danger "Struktūros nariai vieši"
    ```c
    struct Stack st;
    st.top = 999;  // ← Galima!
    ```
    **Encapsulation ≠ Information hiding**

---

## Etapas 07: HIDING UDT Information
### Opaque pointer - forward declaration

### Žingsnis 1: Incomplete type (01_NC)

=== "stack.h"

    ```c title="07_HIDING_UDT_Information/01_NC/stack.h"
    --8<-- "code/evolution/stack-2026/07_HIDING_UDT_Information/01_NC/stack.h"
    ```

??? danger "Kompiliavimo klaida"
    ```c
    struct Stack st;  // ❌ Incomplete type
    ```
    Kompiliatorius nežino sizeof(Stack)

---

### Žingsnis 2: Bandymas su malloc (02_NC)

=== "stack.h"

    ```c title="07_HIDING_UDT_Information/02_NC/stack.h"
    --8<-- "code/evolution/stack-2026/07_HIDING_UDT_Information/02_NC/stack.h"
    ```

??? danger "Linkavimo klaida"
    Greičiausiai problema su funkcijų deklaracijomis

---

### Žingsnis 3: Neininicializuotos rodyklės (03_RT)

=== "stack.h"

    ```c title="07_HIDING_UDT_Information/03_RT/stack.h"
    --8<-- "code/evolution/stack-2026/07_HIDING_UDT_Information/03_RT/stack.h"
    ```

=== "user.c"

    ```c title="07_HIDING_UDT_Information/03_RT/user.c"
    --8<-- "code/evolution/stack-2026/07_HIDING_UDT_Information/03_RT/user.c"
    ```

??? danger "Segmentation fault"
    ```c
    struct Stack *pst1, *pst2;  // Neininicializuotos!
    init(pst1);  // 💥 Crash
    ```
    **Sprendimas → Etapas 08:** Factory pattern

---

## Etapas 08: Acquiring RESOURCES
### Factory pattern - create() / destroy()

=== "stack.h"

    ```c title="08_Acquiring_RESOURCES/02_OK/stack.h"
    --8<-- "code/evolution/stack-2026/08_Acquiring_RESOURCES/02_OK/stack.h"
    ```

=== "stack.c"

    ```c title="08_Acquiring_RESOURCES/02_OK/stack.c"
    --8<-- "code/evolution/stack-2026/08_Acquiring_RESOURCES/02_OK/stack.c"
    ```

=== "user.c"

    ```c title="08_Acquiring_RESOURCES/02_OK/user.c"
    --8<-- "code/evolution/stack-2026/08_Acquiring_RESOURCES/02_OK/user.c"
    ```

??? success "Factory pattern veikia!"
    ```c
    struct Stack *pst1 = create();
    // ... naudojimas ...
    destroy(pst1);
    ```

---

## Etapas 09: Completing LIFECYCLE
### Pilnas lifecycle valdymas

=== "stack.h"

    ```c title="09_Completing_LIFECYCLE/01_OK/stack.h"
    --8<-- "code/evolution/stack-2026/09_Completing_LIFECYCLE/01_OK/stack.h"
    ```

=== "stack.c"

    ```c title="09_Completing_LIFECYCLE/01_OK/stack.c"
    --8<-- "code/evolution/stack-2026/09_Completing_LIFECYCLE/01_OK/stack.c"
    ```

=== "user.c"

    ```c title="09_Completing_LIFECYCLE/01_OK/user.c"
    --8<-- "code/evolution/stack-2026/09_Completing_LIFECYCLE/01_OK/user.c"
    ```

??? success "Pilnas C ADT!"
    - ✅ Information hiding (opaque pointer)
    - ✅ Lifecycle management (create/destroy)
    - ✅ Multiple instances
    - ✅ Factory pattern

---

## Evoliucijos santrauka

### 9 etapų kelias

| Nr | Etapas | Failai | Žingsnių | Info Hiding? | Lifecycle? | Esmė |
|----|--------|--------|----------|--------------|------------|------|
| **01** | Running_PROGRAM | `usestack.c` | 1 | ❌ | ❌ | Monolitas |
| **02** | Decomposing_to_UNITS | `stack.c, user.c` | 3 | ❌ | ❌ | NL klaidos |
| **03** | Discovering_C_MODULE | `stack.h/c, user.c` | 4 | ❌ | ❌ | Modulis |
| **04** | Protecting_IMPLEMENTATION | `stack.h/c, user.c` | 2 | ✅ (1 stekas) | ❌ | `static` |
| **05** | Defining_USER_TYPE | `usestack.c` | 3 | ❌ | ❌ | Struct monolite |
| **06** | ENCAPSULATING_UDT | `stack.h/c, user.c` | 2 | ❌ | ❌ | Struct + modulis |
| **07** | HIDING_UDT_Information | `stack.h/c, user.c` | 3 | ✅ | ❌ | Opaque pointer |
| **08** | Acquiring_RESOURCES | `stack.h/c, user.c` | 1 | ✅ | ✅ (manual) | Factory |
| **09** | Completing_LIFECYCLE | `stack.h/c, user.c` | 1 | ✅ | ✅ | Pilnas ADT |

---

## Šuolis į C++

### C ADT (Etapas 09):
```c
struct Stack *s = create();
push(s, 'a');
destroy(s);
```

### C++ Class:
```cpp
Stack s;               // Konstruktorius
s.push('a');          // Metodas
// Destruktorius automatiškai
```

**Kitas žingsnis:** C++ Stack evoliucija! 🚀
