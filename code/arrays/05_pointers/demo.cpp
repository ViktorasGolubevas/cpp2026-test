// demo_05.cpp - Rodyklių semantika ir polimorfizmas
// Demonstracija: Object slicing, rodyklių masyvas

#include <iostream>
#include <string>

class Student {
protected:
    std::string name;
    int age;
    
public:
    Student(const std::string& n, int a) : name(n), age(a) {
        std::cout << "📚 Student konstruktorius: " << name << std::endl;
    }
    
    virtual ~Student() {
        std::cout << "🗑️ Student destruktorius: " << name << std::endl;
    }
    
    virtual void print() const {
        std::cout << "Student: " << name << ", Age: " << age << std::endl;
    }
    
    virtual std::string get_type() const { return "Student"; }
};

class GraduateStudent : public Student {
private:
    std::string thesis_topic;
    
public:
    GraduateStudent(const std::string& n, int a, const std::string& topic) 
        : Student(n, a), thesis_topic(topic) {
        std::cout << "🎓 GraduateStudent konstruktorius: " << name << std::endl;
    }
    
    ~GraduateStudent() override {
        std::cout << "🗑️ GraduateStudent destruktorius: " << name << std::endl;
    }
    
    void print() const override {
        std::cout << "Graduate Student: " << name << ", Age: " << age 
                  << ", Thesis: " << thesis_topic << std::endl;
    }
    
    std::string get_type() const override { return "GraduateStudent"; }
};

int main() {
    std::cout << "=== Rodyklių semantika ir polimorfizmas ===\n\n";
    
    // 💥 PROBLEMA: Objektų masyvas su polimorfizmu
    std::cout << "--- 1. Objektų masyvas (object slicing!) ---\n";
    Student mixed_array[3] = {
        Student("Jonas", 20),
        GraduateStudent("Petras", 25, "AI Research"),  // 💥 Object slicing!
        Student("Marija", 19)
    };
    
    std::cout << "\n--- Tikrinimas (neteisingas polimorfizmas) ---\n";
    for (int i = 0; i < 3; i++) {
        std::cout << "Tipas: " << mixed_array[i].get_type() << " - ";
        mixed_array[i].print();
    }
    std::cout << "\n❌ Petras turėjo būti GraduateStudent, bet slicing!\n";
    
    // ✅ SPRENDIMAS: Rodyklių masyvas
    std::cout << "\n--- 2. Rodyklių masyvas (teisingas polimorfizmas) ---\n";
    Student* polymorphic_array[3];
    polymorphic_array[0] = new Student("Jonas", 20);
    polymorphic_array[1] = new GraduateStudent("Petras", 25, "AI Research");
    polymorphic_array[2] = new Student("Marija", 19);
    
    std::cout << "\n--- Tikrinimas (teisingas polimorfizmas) ---\n";
    for (int i = 0; i < 3; i++) {
        std::cout << "Tipas: " << polymorphic_array[i]->get_type() << " - ";
        polymorphic_array[i]->print();
    }
    std::cout << "\n✅ Petras teisingai rodomas kaip GraduateStudent!\n";
    
    // Išvalymas
    std::cout << "\n--- Manual cleanup ---\n";
    for (int i = 0; i < 3; i++) {
        delete polymorphic_array[i];
    }
    
    std::cout << "\n--- Objektų masyvo destruktoriai ---\n";
    return 0;
}