// demo_08.cpp - Smart pointers su polimorfizmu
// Demonstracija: unique_ptr, shared_ptr, automatinis cleanup

#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Student {
protected:
    std::string name;
    int age;
    double grade;
    
public:
    Student(const std::string& n, int a, double g) 
        : name(n), age(a), grade(g) {
        std::cout << "📚 Student konstruktorius: " << name << std::endl;
    }
    
    virtual ~Student() {
        std::cout << "🗑️ Student destruktorius: " << name << std::endl;
    }
    
    virtual void print() const {
        std::cout << "Student: " << name << ", Age: " << age 
                  << ", Grade: " << grade << std::endl;
    }
    
    virtual std::string get_type() const { return "Student"; }
};

class GraduateStudent : public Student {
private:
    std::string thesis_topic;
    
public:
    GraduateStudent(const std::string& n, int a, double g, const std::string& topic) 
        : Student(n, a, g), thesis_topic(topic) {
        std::cout << "🎓 GraduateStudent konstruktorius: " << name << std::endl;
    }
    
    ~GraduateStudent() override {
        std::cout << "🗑️ GraduateStudent destruktorius: " << name << std::endl;
    }
    
    void print() const override {
        std::cout << "Graduate: " << name << ", Age: " << age 
                  << ", Grade: " << grade << ", Thesis: " << thesis_topic << std::endl;
    }
    
    std::string get_type() const override { return "GraduateStudent"; }
};

void demonstrate_unique_ptr() {
    std::cout << "\n=== unique_ptr demonstracija ===\n";
    
    // Vector su unique_ptr - polimorfizmas
    std::vector<std::unique_ptr<Student>> students;
    
    students.push_back(std::make_unique<Student>("Jonas", 20, 8.5));
    students.push_back(std::make_unique<GraduateStudent>("Petras", 25, 9.0, "AI"));
    students.push_back(std::make_unique<Student>("Marija", 19, 8.8));
    students.push_back(std::make_unique<GraduateStudent>("Tomas", 26, 9.2, "ML"));
    
    std::cout << "\n--- Visi studentai (teisingas polimorfizmas) ---\n";
    for (const auto& student : students) {
        std::cout << "Type: " << student->get_type() << " - ";
        student->print();
    }
    
    std::cout << "\n--- Automatinis cleanup ---\n";
}

void demonstrate_shared_ptr() {
    std::cout << "\n=== shared_ptr demonstracija ===\n";
    
    auto student1 = std::make_shared<Student>("Shared1", 20, 8.0);
    auto student2 = std::make_shared<GraduateStudent>("Shared2", 25, 9.0, "Data Science");
    
    std::cout << "\nstudent1 use_count: " << student1.use_count() << "\n";
    std::cout << "student2 use_count: " << student2.use_count() << "\n";
    
    {
        std::vector<std::shared_ptr<Student>> group1;
        std::vector<std::shared_ptr<Student>> group2;
        
        group1.push_back(student1);
        group1.push_back(student2);
        
        group2.push_back(student1);  // Tas pats objektas!
        
        std::cout << "\nPo pridėjimo į vector'ius:\n";
        std::cout << "student1 use_count: " << student1.use_count() << "\n";
        std::cout << "student2 use_count: " << student2.use_count() << "\n";
        
        std::cout << "\n--- Vector'iai sunaikinami ---\n";
    }
    
    std::cout << "\nPo vector'ių sunaikinimo:\n";
    std::cout << "student1 use_count: " << student1.use_count() << "\n";
}

class StudentManager {
private:
    std::vector<std::unique_ptr<Student>> students;
    
public:
    StudentManager() {
        std::cout << "🏗️ StudentManager konstruktorius\n";
    }
    
    ~StudentManager() {
        std::cout << "🗑️ StudentManager destruktorius\n";
    }
    
    template<typename StudentType, typename... Args>
    void emplace_student(Args&&... args) {
        students.push_back(std::make_unique<StudentType>(std::forward<Args>(args)...));
    }
    
    void print_all() const {
        std::cout << "\n--- StudentManager (" << students.size() << " studentų) ---\n";
        for (const auto& student : students) {
            std::cout << "Type: " << student->get_type() << " - ";
            student->print();
        }
    }
    
    size_t size() const { return students.size(); }
};

int main() {
    std::cout << "=== Smart pointers su polimorfizmu ===\n";
    
    demonstrate_unique_ptr();
    demonstrate_shared_ptr();
    
    // StudentManager testas
    std::cout << "\n=== StudentManager su smart pointers ===\n";
    StudentManager manager;
    
    manager.emplace_student<Student>("A", 20, 8.0);
    manager.emplace_student<GraduateStudent>("B", 25, 9.0, "Robotics");
    manager.emplace_student<Student>("C", 21, 7.5);
    manager.emplace_student<GraduateStudent>("D", 26, 8.8, "CV");
    
    manager.print_all();
    
    std::cout << "\n=== Destruktoriai ===\n";
    return 0;
}