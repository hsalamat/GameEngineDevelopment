/**
/** @file Week12-9-ObserverDesignPattern
 *  @brief  Observer Design Pattern
 *
 * Intent: Lets you define a subscription mechanism to notify multiple objects
 * about any events that happen to the object they're listening(observing).
 *
 * Note that there's a lot of different terms with similar meaning associated
 * with this pattern. Just remember that the Subject is also called the
 * Publisher and the Observer is often called the Subscriber and vice versa.
 * Also the verbs "observe", "listen" or "track" usually mean the same thing.
 */

#include <iostream>
#include <list>
#include <string>

class IListener {
public:
    virtual ~IListener() {};
    virtual void Update(const std::string& message_from_subject) = 0;
};

class ISubject {
public:
    virtual ~ISubject() {};
    virtual void Attach(IListener* listener) = 0;
    virtual void Detach(IListener* listener) = 0;
    virtual void Notify() = 0;
};

/**
 * The Subject owns some important state and notifies listeners when the state changes.
 */

class Subject : public ISubject {
public:
    virtual ~Subject() {
        std::cout << "Goodbye, I was the Subject.\n";
    }

    /**
     * The subscription management methods.
     */
    void Attach(IListener* listener) override {
        list_listener_.push_back(listener);
    }
    void Detach(IListener* listener) override {
        list_listener_.remove(listener);
    }
    void Notify() override {
        std::list<IListener*>::iterator iterator = list_listener_.begin();
        HowManyListener();
        while (iterator != list_listener_.end()) {
            (*iterator)->Update(message_);
            ++iterator;
        }
    }

    void CreateMessage(std::string message = "Empty") {
        this->message_ = message;
        Notify();
    }
    void HowManyListener() {
        std::cout << "There are " << list_listener_.size() << " listeners in the list.\n";
    }

    /**
     * Usually, the subscription logic is only a fraction of what a Subject can
     * really do. Subjects commonly hold some important business logic, that
     * triggers a notification method whenever something important is about to
     * happen (or after it).
     */
    void SomeBusinessLogic() {
        this->message_ = "change message message";
        Notify();
        std::cout << "I'm about to do some thing important\n";
    }

private:
    std::list<IListener*> list_listener_;
    std::string message_;
};

class Listener : public IListener {
public:
    Listener(Subject& subject) : subject_(subject) {
        this->subject_.Attach(this);
        std::cout << "Hi, I'm the Listener \"" << ++Listener::static_number_ << "\".\n";
        this->number_ = Listener::static_number_;
    }
    virtual ~Listener() {
        std::cout << "Goodbye, I was the Listener \"" << this->number_ << "\".\n";
    }

    void Update(const std::string& message_from_subject) override {
        message_from_subject_ = message_from_subject;
        PrintInfo();
    }
    void RemoveMeFromTheList() {
        subject_.Detach(this);
        std::cout << "Listener \"" << number_ << "\" removed from the list.\n";
    }
    void PrintInfo() {
        std::cout << "Listener \"" << this->number_ << "\": a new message is available --> " << this->message_from_subject_ << "\n";
    }

private:
    std::string message_from_subject_;
    Subject& subject_;
    static int static_number_;
    int number_;
};

int Listener::static_number_ = 0;

void ClientCode() {
    Subject* subject = new Subject;
    Listener* listener1 = new Listener(*subject);
    Listener* listener2 = new Listener(*subject);
    Listener* listener3 = new Listener(*subject);
    Listener* listener4;
    Listener* listener5;

    subject->CreateMessage("Sinad has moved! :D");
    listener3->RemoveMeFromTheList();

    subject->CreateMessage("Ninja has moved! :p");
    listener4 = new Listener(*subject);

    listener2->RemoveMeFromTheList();
    listener5 = new Listener(*subject);

    subject->CreateMessage("Ogre is dancing! ;)");
    listener5->RemoveMeFromTheList();

    listener4->RemoveMeFromTheList();
    listener1->RemoveMeFromTheList();

    delete listener5;
    delete listener4;
    delete listener3;
    delete listener2;
    delete listener1;
    delete subject;
}

int main() {
    ClientCode();
    return 0;
}
