# Objektų masyvų evoliucija - Kodų pavyzdžiai

## Kompiliavimas

### Linux/Mac
```bash
g++ -std=c++17 01_c_arrays/student.cpp -o 01_c_arrays
g++ -std=c++17 02_init_list/student.cpp -o 02_init_list
# ... ir t.t.
```

### Windows (MinGW)
```bash
g++ -std=c++17 01_c_arrays\student.cpp -o 01_c_arrays.exe
```

### Visi iš karto
```bash
for i in {01..08}; do
    dir=$(ls -d ${i}_* 2>/dev/null | head -1)
    [ -d "$dir" ] && g++ -std=c++17 $dir/*.cpp -o $dir/demo
done
```

## Paleidimas
```bash
./01_c_arrays/demo
./02_init_list/demo
# ... ir t.t.
```

## Etapų aprašymai

1. **01_c_arrays** - C masyvai, default konstruktorius
2. **02_init_list** - Inicializacijos sąrašas
3. **03_dynamic** - new/delete
4. **04_rule_of_three** - Deep copy
5. **05_pointers** - Polimorfizmas
6. **06_std_array** - STL array
7. **07_std_vector** - STL vector
8. **08_smart_ptr** - unique_ptr/shared_ptr