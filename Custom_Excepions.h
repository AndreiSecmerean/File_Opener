using namespace std;

// Define a new exception class that
// inherits from std::exception
using namespace std;
class ValueAlreadyExists : public exception {
private:
    string message;
public:

    // Constructor accepting const char*
    ValueAlreadyExists(const char* msg) :
        message(msg) {
    }

    // Override what() method, marked
    // noexcept for modern C++
    const char* what() const noexcept {
        return message.c_str();
    }
}; 

class TagFileNotFound : public exception {
private:
    string message;
public:

    // Constructor accepting const char*
    TagFileNotFound(const char* msg) :
        message(msg) {
    }

    // Override what() method, marked
    // noexcept for modern C++
    const char* what() const noexcept {
        return message.c_str();
    }
};

class TagNotFound : public exception {
private:
    string message;
public:

    // Constructor accepting const char*
    TagNotFound(const char* msg) :
        message(msg) {
    }

    // Override what() method, marked
    // noexcept for modern C++
    const char* what() const noexcept {
        return message.c_str();
    }
};
