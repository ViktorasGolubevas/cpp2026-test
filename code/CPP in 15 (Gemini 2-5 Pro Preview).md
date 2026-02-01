Puikus planas! Parengti visą 15 paskaitų kursą iš šios medžiagos yra didelis, bet labai vertingas darbas. Jūsų pateikti klausimai yra itin geri, nes apima platų spektrą temų – nuo pačių pagrindų iki subtilių C++ kalbos niuansų (pvz., virtualus paveldėjimas, išimčių saugumo garantijos, pasenusių STL dalių).

Žemiau pateikiu Jums pilną kurso struktūrą ir turinį Markdown formatu, kaip ir pageidavote. Struktūra sukurta atsižvelgiant į tai, kad studentai ateina po procedūrinio programavimo C kalba kurso. Pradedama nuo pačių pagrindų (kas yra klasė) ir palaipsniui pereinama prie sudėtingesnių objektinio programavimo ir C++ ypatybių.

Kiekvienoje paskaitoje, kur tai tinkama, yra integruoti Jūsų pateikti klausimai. Jie suformatuoti taip:

---
#### Klausimas # (Failo Nr.)

**Problematika/Kontekstas:** Mano sugeneruotas klausimo esmės aprašymas.

**Klausimas:**
> Klausimo tekstas.

**Atsakymų variantai ir analizė:**
*   **`[Atsakymo variantas]`**: Teisingas/Klaidingas.
    *   *Vertinimas:* Kodėl atsakymas yra teisingas arba klaidingas.

---

Šis formatas leis studentams ne tik pasitikrinti žinias, bet ir suprasti, *kodėl* vienas ar kitas atsakymas yra teisingas, o tai yra svarbiausia mokymosi proceso dalis.

---

# Objektinio programavimo C++ kalba kursas (15 paskaitų)

## Dalyko apžvalga

Šis kursas skirtas supažindinti pirmo kurso informatikos studentus, baigusius „Procedūrinio programavimo su C“ dalyką, su objektinio programavimo (OP) paradigma ir jos realizacija C++ kalba. Kurso metu bus gilinamasi į keturis pagrindinius OP principus: abstrakciją, enkapsuliaciją, paveldėjimą ir polimorfizmą. Taip pat bus nagrinėjamos svarbios C++ kalbos ypatybės: klasių gyvavimo ciklas, atminties valdymas, operatorių perkrovimas, išimčių valdymas, šablonai (templates) ir standartinė šablonų biblioteka (STL).

---

## Kurso struktūra ir turinys

### **1 Paskaita: Įvadas į objektinį programavimą ir C++**

*   **1.1. Procedūrinio ir objektinio programavimo palyginimas.**
    *   Problemos, kylančios dideliuose procedūriniuose projektuose.
    *   OP privalumai: modularumas, pakartotinis panaudojimas, lengvesnė priežiūra.
*   **1.2. Keturios objektinio programavimo kolonos.**
    *   **Abstrakcija:** Esminių savybių išskyrimas, sudėtingumo slėpimas.
    *   **Enkapsuliacija:** Duomenų ir su jais susijusių operacijų apjungimas, prieigos ribojimas.
    *   **Paveldėjimas:** Naujų klasių kūrimas egzistuojančių pagrindu ("is-a" ryšys).
    *   **Polimorfizmas:** Galimybė tam pačiam kreipiniui sukelti skirtingą elgesį.
*   **1.3. Nuo C iki C++.**
    *   C++ kaip C praplėtimas.
    *   Nauji raktažodžiai ir pagrindiniai standartinės bibliotekos elementai (`iostream`, `string`, `std` vardų erdvė).

---
#### Klausimas #1 (1.txt)

**Problematika/Kontekstas:** Šis klausimas apjungia kelias pagrindines OP koncepcijas ir patikrina jų bendrą supratimą bei terminologiją.

**Klausimas:**
> Objektiniame programavime, [[1]] yra svarbi koncepcija, reiškianti siekį paprastinti, slepiant sudėtingumą nuo vartotojo. Kuomet klasės yra kažkaip susijusios, t.y. kuomet yra [[2]] tarp klasių, yra svarbu mažinti priklausomybės tarp klasių laipsnį. [[1]] leidžia lengviau valdyti kodą, nes klientas tampa priklausomas tik nuo to, kas jam būtina. Yra daug šios koncepcijos taikymo pavyzdžių. Vienas yra [[3]] - tai leidžia pasiekti jog [[8]] paslepiamas/paslepiama klasės viduje, o išorei pateikiama/pateikiamas stabilus/stabili [[7]], kurią/kurį ir naudoja klientas. Kitas yra [[7]], kuomet klasių hierarchijoms sukurti naudojamas/naudojama [[6]], o tada rašomi metodų kreipiniai nežinant kuri hierarchijoje esančio metodo kopija bus kviečiama, sprendimą priimant vykdymo metu priklausomai nuo naudojamo egzemplioriaus.

**Teisingas užpildymas:**
> Objektiniame programavime, **Abstrakcija** [[1]] yra svarbi koncepcija, reiškianti siekį paprastinti, slepiant sudėtingumą nuo vartotojo. Kuomet klasės yra kažkaip susijusios, t.y. kuomet yra **Asociacija** [[2]] tarp klasių, yra svarbu mažinti priklausomybės tarp klasių laipsnį. **Abstrakcija** [[1]] leidžia lengviau valdyti kodą, nes klientas tampa priklausomas tik nuo to, kas jam būtina. Yra daug šios koncepcijos taikymo pavyzdžių. Vienas yra **Enkapsuliacija** [[3]] - tai leidžia pasiekti jog **Realizacija** [[8]] paslepiamas/paslepiama klasės viduje, o išorei pateikiama/pateikiamas stabilus/stabili **Interfeisas** [[7]], kurią/kurį ir naudoja klientas. Kitas yra **Interfeisas** [[7]], kuomet klasių hierarchijoms sukurti naudojamas/naudojama **Paveldėjimas** [[6]], o tada rašomi metodų kreipiniai nežinant kuri hierarchijoje esančio metodo kopija bus kviečiama, sprendimą priimant vykdymo metu priklausomai nuo naudojamo egzemplioriaus.

---
#### Klausimas #100 (100.txt)

**Problematika/Kontekstas:** Atpažįstami C++ raktažodžiai, keičiantys programos vykdymo eigą (angl. control flow statements). Dalis jų studentams jau turėtų būti žinomi iš C kurso.

**Klausimas:**
> Kurie iš žemiau nurodytų žodžių yra C++ kalbos raktažodžiai, skirti valdymo perdavimui?

**Atsakymų variantai ir analizė:**
*   **`goto`**: Teisingas. Be sąlygų perduoda valdymą į žymę (label).
*   **`return`**: Teisingas. Užbaigia funkcijos vykdymą.
*   **`break`**: Teisingas. Nutraukia ciklo arba `switch` sakinio vykdymą.
*   **`continue`**: Teisingas. Praleidžia likusią ciklo iteracijos dalį.
*   **`then`**: Klaidingas. Nėra C++ raktažodis (naudojamas Pascal).
*   **`jmp`**: Klaidingas. Asamblerio instrukcija.
*   **`end`**: Klaidingas. Nėra C++ raktažodis.
*   **`exit`**: Klaidingas. Tai standartinės bibliotekos funkcija, o ne raktažodis.

---
### **2 Paskaita: Klasės ir Objektai. Organizaciniai elementai.**

*   **2.1. Klasės apibrėžimas.**
    *   `class` ir `struct` raktažodžiai, jų skirtumai.
    *   Duomenų nariai (laukai) ir metodai.
*   **2.2. Objekto sukūrimas.**
    *   Deklaravimas steko (stack) ir dinaminėje (heap) atmintyje.
    *   Prieiga prie narių per `.` ir `->` operatorius. `this` rodyklė.
*   **2.3. Statiniai nariai (Static members).**
    *   Statiniai laukai: bendri visai klasei, o ne individualiam objektui.
    *   Statiniai metodai: nepriklauso nuo objekto, neturi `this` rodyklės.
*   **2.4. Organizaciniai elementai.**
    *   Vardų erdvės (`namespace`).
    *   Įdėtinės klasės (`nested class`).
    *   UML klasių diagramos pagrindai.

---
#### Klausimas #3 (3.txt)

**Problematika/Kontekstas:** Patikrinamos pačios pagrindinės sąvokos: klasė, objektas, laukas, metodas, ir jų tarpusavio ryšys bei informacijos slėpimo principas.

**Klausimas:**
> Objektiniame programavime kodas yra skaidomas į [[1]], tokiu būdu skirstant ir atskiriant atsakomybes. [[5]] yra išvestiniai duomenų tipai ir jų pagrindu kuriami [[8]], kurie yra tam tikrų [[9]] egzemplioriai. [[12]] viduje [[6]] saugo jų būseną ir nusako jų savybes. Bendru atveju, [[6]] neturėtų būti naudojami tiesiogiai - vietoje to naudotini [[7]]. Naudojant [[3]] vietoje [[10]] kad dirbti su [[16]] už jų [[9]] ribų, galima įgyvendinti informacijos slėpimo principą, ir gauti kodą, kuris yra atsparesnis įvairiems pokyčiams.

**Teisingas užpildymas:**
> ... skaidomas į **Klases** [[1]], ... **Klasės** [[5]] yra ... kuriami **Objektai** [[8]], ... **Klasių** [[9]] egzemplioriai. **Objektų** [[12]] viduje **Laukai** [[6]] saugo jų būseną ... naudotini **Metodai** [[7]]. Naudojant **Metodus** [[3]] vietoje **Laukų** [[10]] kad dirbti su **Laukais** [[16]] už jų **Klasių** [[9]] ribų...

---
#### Klausimas #125 (125.txt)

**Problematika/Kontekstas:** Tikrinami statinio metodo kvietimo būdai iš išorės (pvz., `main`).

**Klausimas:**
> Sukūrus klasės Class objektą object, main funkcijoje galima kreiptis į prieinamą statinį Class metodą method, šiais būdais:

**Atsakymų variantai ir analizė:**
*   **`Class::method(...)`**: Teisingas. Tai standartinis ir rekomenduojamas būdas kviesti statinį metodą.
*   **`object.method(...)`**: Teisingas. Nors nerekomenduojama, C++ leidžia kviesti statinį metodą per klasės objektą.

---
#### Klausimas #110 (110.txt)

**Problematika/Kontekstas:** Tikrinamos įdėtinių klasių (nested classes) savybės C++ kalboje.

**Klausimas:**
> Teisingi šie teiginiai:

**Atsakymų variantai ir analizė:**
*   **`Vidinė (nested) klasė yra išorinės klasės vardų erdvėje`**: Teisingas. Tai yra pagrindinė įdėtinės klasės savybė. Kreipinys į ją iš išorės vyksta per `Išorinė::Vidinė`.
*   **`Vidinė (nested) klasė turi prieigą prie išorinės klasės slaptų (private) elementų`**: Klaidingas. Skirtingai nei kai kuriose kitose kalbose (pvz., Java), C++ įdėtinė klasė neturi specialių prieigos teisių.
*   **`Išorinė klasė turi prieigą prie vidinės (nested) klasės slaptų (private) elementų`**: Klaidingas. Galioja ta pati taisyklė.

---
#### Klausimas #130 (130.txt)

**Problematika/Kontekstas:** Tikrinamas standartinės UML klasės diagramos struktūros išmanymas.

**Klausimas:**
> UML klasių diagramoje (o ir klasės apraše) elementai pateiktini šia tvarka:

**Atsakymų variantai ir analizė:**
*   **`Klasės pavadinimas, klasės laukai, klasės metodai`**: Teisingas. Tai standartinė UML klasės notacija: viršuje – pavadinimas, per vidurį – atributai (laukai), apačioje – operacijos (metodai).

---
### **3 Paskaita: Objektų gyvavimo ciklas. Konstruktoriai ir Destruktoriai**

*   **3.1. Konstruktoriai.**
    *   Paskirtis: objekto inicializavimas.
    *   Numatytasis (default) konstruktorius.
    *   Parametrizuoti konstruktoriai.
    *   Konstruktorių perkrovimas.
    *   Inicializavimo sąrašas (Initializer List) ir jo svarba (`const` laukams, nuorodoms).
*   **3.2. Destruktorius.**
    *   Paskirtis: resursų atlaisvinimas.
    *   RAII (Resource Acquisition Is Initialization) principas.
    *   Kada kviečiamas destruktorius.
*   **3.3. Objektų kūrimas ir naikinimas praktikoje.**
    *   Skirtumai tarp `new`/`delete` ir `malloc`/`free`.
    *   Objektų masyvai ir jų gyvavimo ciklas.

---
#### Klausimas #5 (5.txt)

**Problematika/Kontekstas:** Patikrinamas objekto gyvavimo ciklo specialiųjų metodų (konstruktoriaus, destruktoriaus, geterių/seterių) supratimas.

**Klausimas:**
> Kiekvienas objektas turi savo gyvavimo ciklą, kurį pradeda [[3]]. Kol objektas gyvuoja, jo būsenos pakeitimui gali būti naudojamas [[4]], o būsenos skaitymui - [[2]], su sąlyga, kad jie yra klasėje. [[3]] užtikrina, kad objektas gyvavimą pradeda su korektiška būsena...

**Teisingas užpildymas:**
> ...pradeda **Konstruktorius** [[3]]. ...pakeitimui gali būti naudojamas **Setter'is** [[4]], o būsenos skaitymui - **Getter'is** [[2]]... **Destruktorius** [[1]] turi atlaisvinti visus resursus...

---
#### Klausimas #95 (95.txt)

**Problematika/Kontekstas:** Analizuojamas teisingas dinaminio objekto gyvavimo ciklas naudojant `new` ir `delete`.

**Klausimas:**
> { Object *ptr = new Object(); delete ptr; }<br>Esant aukščiau nurodytiems kodo sakiniams, teisingi šie teiginiai:

**Atsakymų variantai ir analizė:**
*   **`Vieta objektui išskiriama dinaminėje atmintyje (heap)`**: Teisingas. `new` išskiria atmintį iš dinaminės atminties.
*   **`Iškviečiamas klasės Object konstruktorius`**: Teisingas. `new` po atminties išskyrimo kviečia konstruktorių.
*   **`Iškviečiamas klasės Object destruktorius`**: Teisingas. `delete` prieš atlaisvinant atmintį kviečia destruktorių.
*   **`Atlaisvinama Object užimama vieta atmintyje`**: Teisingas. `delete` atlaisvina atmintį.

---
#### Klausimas #96 (96.txt)

**Problematika/Kontekstas:** Analizuojamas dinaminio objekto sukūrimas be atlaisvinimo, kas sukelia atminties nutekėjimą.

**Klausimas:**
> { Object *ptr = new Object(); }<br>Esant aukščiau nurodytiems kodo sakiniams, teisingi šie teiginiai:

**Atsakymų variantai ir analizė:**
*   **`Vieta objektui išskiriama dinaminėje atmintyje (heap)`**: Teisingas.
*   **`Iškviečiamas klasės Object konstruktorius`**: Teisingas.
*   **`Iškviečiamas klasės Object destruktorius`**: Klaidingas. Kadangi `delete` nėra iškviestas, destruktorius taip pat neiškviečiamas.
*   **`Atlaisvinama Object užimama vieta atmintyje`**: Klaidingas. Įvyksta atminties nutekėjimas (memory leak).

---
### **4 Paskaita: Enkapsuliacija ir `const` korektiškumas**

*   **4.1. Prieigos specifikatoriai.**
    *   `public`: viešas interfeisas.
    *   `private`: vidinė realizacija.
    *   `protected`: prieinamumas išvestinėms klasėms.
*   **4.2. Duomenų slėpimas.**
    *   Geteriai ir seteriai. Privalumai lyginant su viešais laukais.
*   **4.3. `friend` mechanizmas.**
    *   Draugiškos funkcijos ir klasės. Kada naudoti ir kodėl vengti.
*   **4.4. `const` korektiškumas.**
    *   `const` objektai ir `const` nuorodos/rodyklės.
    *   `const` metodai: pažadas nekeisti objekto būsenos.

---
#### Klausimas #2 (2.txt)

**Problematika/Kontekstas:** Tikrinamos žinios apie prieigos valdymą ir enkapsuliaciją objektiniame programavime.

**Klausimas:**
> Kad vartotojas galėtų pasiekti klasės narius už klasės ribų, jų matomumas turi būti [[3]]. Bendru atveju, laukų matomumas turėtų būti [[4]]. Tai reiškia, kad vartotojas turi dirbti su [[1]] netiesiogiai, per [[7]][[6]]...

**Teisingas užpildymas:**
> ...matomumas turi būti **Viešas** [[3]]. ...laukų matomumas turėtų būti **Slaptas** [[4]]. ...dirbti su **Laukais** [[1]] netiesiogiai, per **Viešus** [[7]] **Metodus** [[6]]...

---
#### Klausimas #62 (62.txt)

**Problematika/Kontekstas:** Tikrinamas `friend` mechanizmo C++ kalboje supratimas.

**Klausimas:**
> Klasė X paskelbia, kad tai pačiai hierarchijai nepriklausančią klasę Y laikys draugu. Šis paskelbimas pakeičia (!) ir (tik) jam esant lemia, kad:

**Atsakymų variantai ir analizė:**
*   **`Klasės Y viešame metode galima kreiptis į klasės X slaptą metodą`**: Teisingas. Tai tikslus `friend` deklaracijos (`X` paskelbė `Y` draugu) poveikis. `Y` gauna prieigą prie `X` `private` ir `protected` narių.
*   **`Klasės X viešame metode galima kreiptis į klasės Y slaptą (private) metodą`**: Klaidingas. Draugystė nėra abipusė. `X` negauna jokių specialių teisių prie `Y` narių.

---
#### Klausimas #45 (45.txt)

**Problematika/Kontekstas:** Tikrinamos `const` metodų taisyklės.

**Klausimas:**
> Teisingi šie teiginiai:

**Atsakymų variantai ir analizė:**
*   **`Iš nekonstantinio metodo galima kreiptis į konstantinį metodą.`**: Teisingas. Nekonstantinis metodas gali daryti viską, ką gali konstantinis, ir dar daugiau.
*   **`Iš konstantinio metodo galima kreiptis į nekonstantinį metodą.`**: Klaidingas. Tai pažeistų `const` garantiją, nes nekonstantinis metodas gali keisti objekto būseną.
*   **`Nekonstantiniame metode galima skaityti objekto būseną.`**: Teisingas. Gali tiek skaityti, tiek keisti.
*   **`Konstantiniame metode galima keisti objekto būseną.`**: Klaidingas. Tai yra `const` metodo apibrėžimo pažeidimas.

---
### **5 Paskaita: Rodyklės ir Nuorodos (References) C++ kontekste**

*   **5.1. Rodyklių (`pointer`) atkartojimas.**
    *   Adreso operatorius `&` ir išrodyklinimo operatorius `*`.
    *   `nullptr` (C++11). Rodyklių aritmetika.
*   **5.2. Nuorodos (`reference`).**
    *   Skirtumai nuo rodyklių: negali būti `null`, privalo būti inicializuotos, negali būti pernukreiptos.
    *   Sintaksinis "cukrus".
*   **5.3. Parametrų perdavimas funkcijai.**
    *   Perdavimas pagal reikšmę (pass-by-value).
    *   Perdavimas pagal rodyklę (pass-by-pointer).
    *   Perdavimas pagal nuorodą (pass-by-reference).
    *   Perdavimas pagal `const` nuorodą – efektyvus ir saugus būdas.

---
#### Klausimas #120 (120.txt)

**Problematika/Kontekstas:** Tikrinamos pagrindinės C++ nuorodų (references) savybės ir apribojimai.

**Klausimas:**
> Sinonimai (angl. reference) negali:

**Atsakymų variantai ir analizė:**
*   **`Būti lygus NULL.`**: Teisingas. Nuorodos visada turi rodyti į egzistuojantį objektą.
*   **`Būti neinicializuoti.`**: Teisingas. Nuoroda privalo būti susieta su objektu jos sukūrimo metu.
*   **`Būti nukreipti kitur.`**: Teisingas. Priskyrimas nuorodai pakeičia ne pačią nuorodą, o objektą, į kurį ji rodo.
*   **`Būti konstantiniai.`**: Klaidingas. Galima turėti nuorodą į konstantą (`const T&`).

---
#### Klausimas #124 (124.txt)

**Problematika/Kontekstas:** Lyginamas nuorodų ir rodyklių naudojimas.

**Klausimas:**
> Sinonimų (angl. reference) naudojimas vietoje rodyklių (angl. pointer), kaip taisyklė, veda prie:

**Atsakymų variantai ir analizė:**
*   **`Trumpesnės kodo sintaksės.`**: Teisingas. Naudojamas `.` vietoj `->`, nereikia nuolatinio išrodyklinimo.
*   **`Mažesnių šansų suklysti.`**: Teisingas. Nuorodos yra saugesnės, nes negali būti `nullptr` ir negali būti netyčia "perkeltos" į kitą objektą.
*   **`Efektyvesnio kompiuterio resursų naudojimo.`**: Klaidingas. Našumas yra praktiškai identiškas.

---
### **6 Paskaita: Kopijavimo valdymas (Copy Control)**

*   **6.1. Problema: paviršutinė vs. gili kopija.**
    *   Kada kompiliatoriaus sugeneruotos operacijos yra nepakankamos (kai klasė valdo resursus, pvz., dinaminę atmintį).
*   **6.2. Trijų taisyklė (The Rule of Three).**
    *   Kopijavimo konstruktorius (`Copy Constructor`).
    *   Kopijavimo priskyrimo operatorius (`Copy-Assignment Operator`).
    *   Destruktorius.
*   **6.3. Penkių taisyklė (The Rule of Five) (C++11).**
    *   Perkėlimo konstruktorius (`Move Constructor`).
    *   Perkėlimo priskyrimo operatorius (`Move-Assignment Operator`).
    *   `std::move` ir `r-value` nuorodos.
*   **6.4. Kopijavimo uždraudimas.**

---
#### Klausimas #23 (23.txt)

**Problematika/Kontekstas:** Analizuojamas C++ kodo fragmentas, siekiant atskirti kopijavimo inicializaciją (kviečiamas kopijavimo konstruktorius) nuo priskyrimo.

**Klausimas:**
> Duotas kodo fragmentas, kuriame X - anksčiau apibrėžta klasė.<p>X x1, x2 = x1;<br><br>Teisingi šie teiginiai:

**Atsakymų variantai ir analizė:**
*   **`Kodo fragmente kviečiamas standartinis (angl. default) X konstruktorius`**: Teisingas. Objektui `x1` sukurti.
*   **`Kodo fragmente kviečiamas X kopijos konstruktorius`**: Teisingas. Objektui `x2` sukurti ir inicializuoti iš `x1`.
*   **`Kodo fragmente kviečiamas X priskyrimo operatorius`**: Klaidingas. Priskyrimo operatorius būtų kviečiamas, jei `x2` jau būtų sukurtas anksčiau, pvz., `X x1, x2; x2 = x1;`.

---
#### Klausimas #27 (27.txt)

**Problematika/Kontekstas:** Analizuojama klasė, valdanti dinaminę atmintį per `char* ptr`. Tai yra klasikinis Trijų/Penkių taisyklės atvejis.

**Klausimas:**
> Klasė MyString komponuoja savo viduje dinaminį simbolių masyvą (char* ptr) ... Teisingi šie teiginiai:

**Atsakymų variantai ir analizė:**
*   **`Klasei MyString būtina apibrėžti priskyrimo operatorių.`**: Teisingas. Norint atlikti gilųjį kopijavimą, o ne tiesiog nukopijuoti rodyklės adresą, reikia pačiam apibrėžti kopijavimo priskyrimo operatorių (ir kopijavimo konstruktorių, ir destruktorių).
*   **`Klasė MyString pagal nutylėjimą kopijuojasi korektiškai.`**: Klaidingas. Paviršutinis kopijavimas sukels problemas (du objektai rodys į tą pačią atmintį).
*   **`Klasėje MyString gali nebūti destruktoriaus.`**: Klaidingas. Būtinas destruktorius, kuris atlaisvintų dinamiškai išskirtą atmintį.

---
### **7 Paskaita: Operatoriai ir Konversijos**

*   **7.1. Operatorių perkrovimo (overloading) pagrindai.**
    *   Kodėl tai naudinga: sintaksinis patogumas.
    *   Bendrosios taisyklės: negalima keisti operatoriaus arumo, prioritetų, asociatyvumo.
    *   Operatoriai, kurių negalima perkrauti (`.`, `::`, `?:`, `sizeof`).
*   **7.2. Perkrovimas kaip narys-metodas vs. kaip ne narys-funkcija.**
    *   Aritmetiniai, palyginimo, srauto (`<<`, `>>`) operatoriai.
*   **7.3. Tipo konversijos.**
    *   Konversijos konstruktoriai. `explicit` raktažodis.
    *   Konversijos operatoriai.

---
#### Klausimas #7 (7.txt)

**Problematika/Kontekstas:** Tikrinamos pagrindinės sąvokos, susijusios su operatoriais: operacija, operandas, prioritetas, asociatyvumas.

**Klausimas:**
> Programa gali vykdyti įvairius/įvairias [[1]], kurias atlieka [[6]], kurias/kuriuos galima laikyti funkcijomis, kurios dažniausiai priima (vieną arba du) parametrus, vadinamus [[8]]...

**Teisingas užpildymas:**
> ...vykdyti **Operacijas** [[1]], kurias atlieka **Operatoriai** [[6]], ... vadinamus **Operandais** [[8]]. Operatoriams galioja **Prioritetai** [[11]], ... nusakoma pagal **Asociatyvumo** [[12]] taisykles.

---
### **8 Paskaita: Paveldėjimas**

*   **8.1. "is-a" ryšys.**
    *   Bazinės ir išvestinės klasės (tėvas ir vaikas).
    *   Sintaksė, prieigos specifikatoriai paveldėjime (`public`, `protected`, `private`).
*   **8.2. Konstruktoriai ir destruktoriai hierarchijoje.**
    *   Konstravimo ir naikinimo tvarka.
    *   Bazinės klasės konstruktoriaus kvietimas iš išvestinės klasės.
*   **8.3. Metodų paslėpimas (Hiding).**
    *   Kas nutinka, kai išvestinėje klasėje apibrėžiamas metodas tuo pačiu vardu kaip bazinėje.

---
#### Klausimas #77 (77.txt)

**Problematika/Kontekstas:** Tikrinama, kas yra paveldima C++ kalboje.

**Klausimas:**
> Iš tėvinės klasės vaiko klasė paveldi:

**Atsakymų variantai ir analizė:**
*   **`Laukus`, `Metodus`, `Operatorius`**: Teisingi.
*   **`Konstruktorius`, `Destruktorius`, `Draugus`**: Klaidingi. Šie elementai nėra paveldimi tiesiogine prasme.

---
#### Klausimas #81 (81.txt)

**Problematika/Kontekstas:** Analizuojama klasių hierarchija ir terminologija.

**Klausimas:**
> Duotas kodo fragmentas:<br><br>class X { }; class Y : public X { }; class Z : public X, public Y { };<p>Remiantis (tik) fragmentu, teisingais galima laikyti tokius teiginius:

**Atsakymų variantai ir analizė:**
*   **`Klasė Y paveldi klasę X.`**: Teisingas.
*   **`Klasė Y yra išvestinė klasė.`**: Teisingas (iš X).
*   **`Klasė Y yra tėvinė klasė.`**: Teisingas (klasei Z).
*   **`Klasė Y yra vaiko klasė.`**: Teisingas (klasės X atžvilgiu).

---
### **9 Paskaita: Dinaminis polimorfizmas**

*   **9.1. Statinis vs. Dinaminis susiejimas.**
*   **9.2. `virtual` funkcijos.**
    *   Kaip `virtual` įgalina dinaminį susiejimą.
    *   Virtualių funkcijų lentelė (`vtable`) (konceptualus paaiškinimas).
*   **9.3. Metodų perrašymas (Overriding).**
    *   `override` specifikatorius (C++11).
*   **9.4. Polimorfizmas praktikoje.**
    *   Bazinės klasės rodyklės/nuorodos, rodančios į išvestinės klasės objektus.
    *   Objekto "supjaustymas" (Object Slicing) ir kaip jo išvengti.

---
#### Klausimas #112 (112.txt)

**Problematika/Kontekstas:** Tikrinami pagrindiniai potipų polimorfizmo (dinaminio polimorfizmo) komponentai C++ kalboje.

**Klausimas:**
> Kad potipų (angl. subtype) polimorfizmas galėtų įvykti, būtini šie techniniai elementai:

**Atsakymų variantai ir analizė:**
*   **`Paveldėjimas`**: Teisingas.
*   **`Metodų perrašymas (angl. overriding)`**: Teisingas.
*   **`Dinaminis susiejimas (angl. dynamic binding)`**: Teisingas.
*   **`Metodų perkrovimas (angl. overloading)`**: Klaidingas. Tai statinis polimorfizmas.

---
#### Klausimas #8 (8.txt)

**Problematika/Kontekstas:** Šis klausimas apjungia paveldėjimo, polimorfizmo ir Liskovo pakeitimo principo sąvokas.

**Klausimas:**
> [[2]] tipo rodyklė gali būti nukreiptą į [[1]] objektą, bet ne atvirkščiai. [[8]] klasės viduje yra įmanoma tiesiogiai kreiptis į [[7]] klasės metodus, bet ne atvirkščiai. ... Šito pasekoje įgalinamas [[6]], kuomet viena kodo eilutė gali veikti skirtingai...

**Teisingas užpildymas:**
> **Superklasės** [[2]] tipo rodyklė gali būti nukreiptą į **Subklasės** [[1]] objektą... **Vaiko klasės** [[8]] viduje... kreiptis į **Tėvo klasės** [[7]] metodus... įgalinamas **Polimorfizmas** [[6]]...

---
### **10 Paskaita: Išplėstinis paveldėjimas ir RTTI**

*   **10.1. Abstračiosios bazinės klasės (Abstract Base Classes).**
    *   Grynosios virtualios funkcijos (`= 0`).
    *   Abstračios klasės kaip interfeisai.
*   **10.2. Daugialypis paveldėjimas (Multiple Inheritance).**
    *   Privalumai ir problemos.
    *   "Deimanto" problema (The Diamond Problem).
*   **10.3. Virtualus paveldėjimas (Virtual Inheritance).**
    *   `virtual` raktažodis paveldėjime. Kaip jis sprendžia "deimanto" problemą.
*   **10.4. RTTI (Run-Time Type Information).**
    *   `dynamic_cast` operatorius saugiam tipo keitimui žemyn.
    *   `typeid` operatorius.

---
#### Klausimas #10 (10.txt)

**Problematika/Kontekstas:** Pateikta C++ klasių hierarchija su daugialypiu paveldėjimu. Reikia nustatyti, kurios klasės yra abstrakčios.

**Klausimas:**
> Klasėje A metodas <i>int f(int)</i> abstraktus. Duotas kodo fragmentas... Teisingi šie teiginiai:

**Atsakymų variantai ir analizė:**
*   **`Klasė A abstrakti.`**: Teisingas. Turi abstraktų metodą.
*   **`Klasė B abstrakti.`**: Teisingas. Paveldi, bet nerealizuoja abstraktaus metodo.
*   **`Klasė C abstrakti.`**: Teisingas. Metodas `void f()` neperrašo `int f(int)`.
*   **`Klasė D abstrakti.`**: Klaidingas. `D` perrašo metodą, todėl yra konkreti.
*   **`Klasė E abstrakti.`**: Teisingas. Paveldi iš abstrakčios klasės `C`.

---
#### Klausimas #118 (118.txt)

**Problematika/Kontekstas:** Tikrinamas saugus rodyklės tipo keitimas žemyn hierarchija (downcasting).

**Klausimas:**
> Kaip turint bazinės klasės A rodyklę įsitikinti, kad ji rodo į objektą, kuris tenkina išvestinės klasės B kontraktą?

**Atsakymų variantai ir analizė:**
*   **`Reikia patikrinti su dynamic_cast operatoriumi`**: Teisingas. `dynamic_cast<B*>(a_ptr)` grąžins `nullptr`, jei konvertuoti negalima, arba galiojančią rodyklę, jei galima.
*   **`Reikia patikrinti su static_cast operatoriumi`**: Klaidingas. `static_cast` atlieka konversiją be patikrinimo vykdymo metu ir gali sukelti neapibrėžtą elgesį.

---
#### Klausimas #141 (141.txt)

**Problematika/Kontekstas:** Skaičiuojami subobjektai "deimanto" hierarchijoje be virtualaus paveldėjimo.

**Klausimas:**
> struct A { }; struct B : public A { }; struct C : public A, public B { ... }; Kiek A tipo subobjektų sukuriama, kuriant C klasės objektą?

**Teisingas atsakymas:** 5.
**Analizė:**
*   1 iš `public A`
*   1 iš `public B` (kuris turi `A` subobjektą)
*   1 iš nario `A b`
*   1 iš nario `A c`
*   1 iš nario `B d` (kuris turi `A` subobjektą)

---
### **11 Paskaita: Išimčių valdymas (Exception Handling)**

*   **11.1. Klaidų apdorojimo būdai.**
    *   Grąžinamos reikšmės vs. Išimtys.
*   **11.2. `try`, `catch`, `throw` mechanizmas.**
    *   `try-catch` blokų struktūra.
    *   Išimčių gaudymas pagal tipą (reikšmę, nuorodą, rodyklę).
    *   `catch(...)` – visų išimčių gaudyklė.
    *   Išimčių permetimas (`re-throw`).
*   **11.3. Standartinės išimčių klasės.**
    *   `std::exception` hierarchija (`std::logic_error`, `std::runtime_error` ir jų išvestinės).

---
#### Klausimas #4 (4.txt)

**Problematika/Kontekstas:** Patikrinamos pagrindinės išimčių valdymo sąvokos ir terminai.

**Klausimas:**
> Programavimo kalbos naudoja išimčių (angl. exception) valdymą... Signalui apie klaidą sukurti, kodas gali [[4]] išimtį, kuri siunčiama iki kol randamas kodo blokas, kuris gali ją [[3]]. Virš [[5]]-bloko visada yra [[7]]-blokas...

**Teisingas užpildymas:**
> ...kodas gali **Mesti** [[4]] išimtį... gali ją **Pagauti** [[3]]. Virš **Catch** [[5]]-bloko visada yra **Try** [[7]]-blokas...

---
#### Klausimas #67 (67.txt)

**Problematika/Kontekstas:** Tikrinama `catch` blokų tvarkos svarba gaudant išimtis iš paveldėjimo hierarchijos.

**Klausimas:**
> try { ... } catch (A &a) { ... } catch (B &b){ ... }<p>Jei B yra A klasės vaikas ... kokio tipo išimtį reikėtų sukelti ... kad ją pagautų ne pirmas, o antras catch blokas?

**Atsakymų variantai ir analizė:**
*   **`Netinka nei vienas (kitas) atsakymas.`**: Teisingas. Dėl neteisingos `catch` blokų tvarkos (bazinė klasė pirma), antrasis `catch(B& b)` blokas yra nepasiekiamas. Bet kokia `B` ar jos vaiko išimtis bus pagauta pirmojo `catch(A& a)`.

---
### **12 Paskaita: Išimčių saugumas ir Išmaniosios rodyklės**

*   **12.1. Steko atvyniojimas (Stack Unwinding).**
    *   Kaip destruktoriai kviečiami išimties metu.
*   **12.2. Išimčių saugumo garantijos.**
    *   Bazinė (Basic Guarantee).
    *   Stipri (Strong Guarantee).
    *   Nemetimo (Nothrow Guarantee).
*   **12.3. RAII ir išmaniosios rodyklės (Smart Pointers).**
    *   `std::unique_ptr`: unikali nuosavybė.
    *   `std::shared_ptr`: dalinama nuosavybė, skaičiuojamos nuorodos.
    *   `std::weak_ptr`: ciklinių priklausomybių sprendimas.

---
#### Klausimas #73 (73.txt)

**Problematika/Kontekstas:** Analizuojama išimčių saugumo garantija konstruktoriuje, kai keli metodai gali mesti išimtis.

**Klausimas:**
> X::X(int x, int y){ setX(x); setY(y); } ... setX, tiek setY - ...stiprią (strong) garantiją...gali mesti išimtis... Tokia konstruktoriaus realizacija suteikia:

**Atsakymų variantai ir analizė:**
*   **`Silpną (weak) garantiją`**: Teisingas. Jei `setX(x)` pavyksta, o `setY(y)` meta išimtį, objektas lieka su pakeista `x` dalimi, bet nepakeista `y` dalimi. Būsena lieka validi, bet nebuvo atstatyta į pradinę, todėl tai nėra stipri garantija.
*   **`Stiprią (strong) garantiją`**: Klaidingas. Būsena nebuvo atstatyta.

---
### **13 Paskaita: Šablonai (Templates)**

*   **13.1. Kodo dubliavimo problema.**
*   **13.2. Funkcijų šablonai (Function Templates).**
    *   Sintaksė. Tipo išvedimas.
*   **13.3. Klasių šablonai (Class Templates).**
    *   Sintaksė. Šabloninių klasių naudojimas.
    *   Nariai-metodai šabloninėse klasėse.
*   **13.4. Šablonų specializacija.**

---
### **14 Paskaita: STL: Konteineriai ir Iteratoriai**

*   **14.1. STL apžvalga: Konteineriai, Iteratoriai, Algoritmai.**
*   **14.2. Sekų konteineriai (Sequence Containers).**
    *   `std::vector`: dinaminis masyvas. Privalumai ir trūkumai.
    *   `std::list`: dvipusis sąrašas. Privalumai ir trūkumai.
    *   `std::deque`: dvipusė eilė.
*   **14.3. Asociatyvūs konteineriai (Associative Containers).**
    *   `std::set`, `std::map`. Rikiuota tvarka.
    *   `std::unordered_set`, `std::unordered_map`. Maišos lentelės.
*   **14.4. Iteratoriai.**
    *   Iteratoriai kaip rodyklių apibendrinimas.
    *   Iteratorių kategorijos (`Input`, `Output`, `Forward`, `Bidirectional`, `Random Access`).

---
#### Klausimas #49 (49.txt)

**Problematika/Kontekstas:** Lyginamos C++ STL konteinerių `std::set` ir `std::list` operacijų asimptotinės sudėtingumai.

**Klausimas:**
> Aibė (set), lyginant su sąrašu (list), vidutiniu (!) atveju:

**Atsakymų variantai ir analizė:**
*   **`Leidžia sparčiau ieškoti pagal elemento reikšmę`**: Teisingas. `set` (O(log n)) vs `list` (O(n)).
*   **`Leidžia sparčiau ištrinti reikšmę`**: Teisingas. `set` (O(log n)) vs `list` (O(n)).
*   **`Leidžia sparčiau įterpti reikšmę`**: Teisingas. `set` (O(log n)) vs `list` (O(n) norint išlaikyti tvarką).

---
#### Klausimas #86 (86.txt)

**Problematika/Kontekstas:** Analizuojami iteratorių tipai pagal galimybes. Reikalavimai: 1) skaityti, 2) judėti pirmyn.

**Klausimas:**
> Siekiant nuosekliai peržiūrėti konteinerį, skaitant jame esančius duomenis nuo pradžios iki galo, galima turėti:

**Atsakymų variantai ir analizė:**
*   **`Įvedimo (input) iteratorių`**: Teisingas. Atitinka minimalius reikalavimus.
*   **`Vienpusį (forward) iteratorių`**: Teisingas.
*   **`Dvipusį (bidirectional) iteratorių`**: Teisingas.
*   **`Tiesioginės prieigos (random access) iteratorių`**: Teisingas. Visi šie tipai gali atlikti užduotį.

---
### **15 Paskaita: STL: Algoritmai ir Lambda išraiškos**

*   **15.1. STL algoritmai.**
    *   Principas: atskirti duomenis nuo operacijų.
    *   Dažniausiai naudojami algoritmai: `std::sort`, `std::find`, `std::find_if`, `std::for_each`, `std::copy`, `std::remove`.
*   **15.2. Funkcijų objektai (Functors).**
    *   Klasės su perkrautu `operator()`.
*   **15.3. Lambda išraiškos (Lambda Expressions) (C++11).**
    *   Anoniminės funkcijos.
    *   Sintaksė: gaudymo blokas (`[]`), parametrai (`()`), kūnas (`{}`).
    *   Modernus būdas perduoti logiką algoritmams.

---
#### Klausimas #16 (16.txt)

**Problematika/Kontekstas:** Analizuojamas `count_if` kvietimas su pasenusiu rišikliu `bind2nd`. Tai gera proga paaiškinti, kaip tą pačią užduotį atlikti su modernia lambda išraiška.

**Klausimas:**
> Žemiau esantis kodo fragmentas:<br><br>count_if(start, end, bind2nd(greater<int>(), 10));

**Atsakymų variantai ir analizė:**
*   **`Skaičiuoja kiek intervale yra reikšmių, didesnių už 10`**: Teisingas. `bind2nd` fiksuoja `greater` funkcijos antrąjį argumentą reikšme 10. Taigi, tikrinama sąlyga `x > 10`.
    *   *Papildomas komentaras dėstytojui:* Paaiškinti studentams, kad nors toks kodas veikia, jis yra pasenęs. Modernus ir skaitomesnis atitikmuo būtų:
        ```cpp
        count_if(start, end, [](int x){ return x > 10; });
        ```

---
#### Klausimas #19 (19.txt)

**Problematika/Kontekstas:** Analizuojamas `remove` kvietimas su pre-inkremento ir post-inkremento operatoriais.

**Klausimas:**
> Žemiau esantis kodo fragmentas:<br><br>remove(++start, end, value++);

**Atsakymų variantai ir analizė:**
*   **`Pašalina visus value iš intervalo, išskyrus pirmą elementą`**: Teisingas. `++start` reiškia, kad intervalas prasidės nuo antrojo elemento. `value++` reiškia, kad lyginimui bus naudojama originali `value` reikšmė.

---

Ši struktūra apima visas Jūsų pateiktų klausimų temas ir jas išdėsto logine seka, tinkama pradedantiesiems OP programuotojams.