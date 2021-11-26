/** @file Week12-8-SingletonDesignPattern
 *  @brief Singleton Design Pattern
    Singleton is a creational design pattern, which ensures that only one object of its kind exists
    and provides a single point of access to it for any other code.
    If you see the same value, then singleton was reused.
    If you see different values, then 2 singletons were created (not good!).
 *  @author Hooman Salamat
 *  @bug No known bugs.
 */

#include <string>
#include <chrono>
#include <thread>
#include <iostream>
using namespace std;

/**
 * The Singleton class defines the `GetInstance` method that serves as an
 * alternative to constructor and lets clients access the same instance of this
 * class over and over.
 */
class Singleton
{

    /**
     * The Singleton's constructor should always be private to prevent direct
     * construction calls with the `new` operator.
     */

protected:
    Singleton(const std::string value) : value_(value)
    {
    }

    static Singleton* singleton_;

    std::string value_;

public:

    /**
     * Singletons should not be cloneable.
     */
    Singleton(Singleton& other) = delete;
    /**
     * Singletons should not be assignable.
     */
    void operator=(const Singleton&) = delete;
    /**
     * This is the static method that controls the access to the singleton
     * instance. On the first run, it creates a singleton object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */

    static Singleton* GetInstance(const std::string& value);
    /**
     * Finally, any singleton should define some business logic, which can be
     * executed on its instance.
     */
    void SomeBusinessLogic()
    {
        cout << "create camera.." << endl;
    }

    std::string value() const {
        return value_;
    }
};

Singleton* Singleton::singleton_ = nullptr;;

/**
 * Static methods should be defined outside the class.
 */
Singleton* Singleton::GetInstance(const std::string& value)
{
    /**
     * This is a safer way to create an instance. instance = new Singleton is
     * dangeruous in case two instance threads wants to access at the same time
     */
    if (singleton_ == nullptr) {
        singleton_ = new Singleton(value);
    }
    return singleton_;
}

void ThreadEngineSubsystem1() {
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("EngineSubsystem1");
    std::cout << singleton->value() << "\n";
}

void ThreadEngineSubsystem2() {
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("EngineSubsystem2");
    std::cout << singleton->value() << "\n";
}


int main()
{
    Singleton* singleton = Singleton::GetInstance("SceneManager");
    std::cout << singleton->value() << "\n";
    singleton->SomeBusinessLogic();

    std::thread t1(ThreadEngineSubsystem1);
    std::thread t2(ThreadEngineSubsystem2);
    t1.join();
    t2.join();

    return 0;
}