#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <fstream>

// Node structure for a singly linked list
template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node(const T& data) : data(data), next(nullptr) {}
};

// Book class representing a book in the catalog
class Book {
    std::string title;
    std::string author;
    std::string condition;
    bool available;

public:
    Book(const std::string& title, const std::string& author, const std::string& condition = "New")
        : title(title), author(author), condition(condition), available(true) {}

    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    std::string getCondition() const { return condition; }
    bool checkAvailability() const { return available; }
    void setAvailability(bool status) { available = status; }

    std::string toString() const {
        return "Title: " + title + ", Author: " + author + ", Condition: " + condition + ", Available: " + (available ? "Yes" : "No");
    }
};

// User class representing a library user
class User {
    std::string firstName;
    std::string lastName;
    std::string phone;
    std::string address;
    int userID;

public:
    User(const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& address, int userID)
        : firstName(firstName), lastName(lastName), phone(phone), address(address), userID(userID) {}

    int getUserID() const { return userID; }
    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }

    std::string toString() const {
        return "ID: " + std::to_string(userID) + ", Name: " + firstName + " " + lastName + ", Phone: " + phone + ", Address: " + address;
    }
};

// Loan class representing a loan record
class Loan {
    User* user;
    Book* book;
    std::string dueDate;
    bool isReturned;

public:
    Loan(User* user, Book* book, const std::string& dueDate)
        : user(user), book(book), dueDate(dueDate), isReturned(false) {}

    User* getUser() const { return user; }
    Book* getBook() const { return book; }
    std::string getDueDate() const { return dueDate; }
    bool getIsReturned() const { return isReturned; }
    void setReturnStatus(bool status) { isReturned = status; }
};

// Catalog class managing a collection of books
class Catalog {
    Node<Book>* head;

public:
    Catalog() : head(nullptr) {}

    void addBook(const Book& book) {
        Node<Book>* newNode = new Node<Book>(book);
        newNode->next = head;
        head = newNode;
    }

    Book* findBook(const std::string& title) {
        Node<Book>* current = head;
        while (current) {
            if (current->data.getTitle() == title) {
                return &current->data;
            }
            current = current->next;
        }
        return nullptr;
    }

    void displayAllBooks() const {
        Node<Book>* current = head;
        std::cout << "Library Catalog:" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        while (current) {
            std::cout << current->data.toString() << std::endl;
            current = current->next;
        }
    }

    ~Catalog() {
        Node<Book>* current = head;
        while (current) {
            Node<Book>* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
};

// UserManager class managing a collection of users
class UserManager {
    Node<User>* head;

public:
    UserManager() : head(nullptr) {}

    void addUser(const User& user) {
        Node<User>* newNode = new Node<User>(user);
        newNode->next = head;
        head = newNode;
    }

    User* findUser(int userID) {
        Node<User>* current = head;
        while (current) {
            if (current->data.getUserID() == userID) {
                return &current->data;
            }
            current = current->next;
        }
        return nullptr;
    }

    void displayAllUsers() const {
        Node<User>* current = head;
        std::cout << "Library Users:" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        while (current) {
            std::cout << current->data.toString() << std::endl;
            current = current->next;
        }
    }

    ~UserManager() {
        Node<User>* current = head;
        while (current) {
            Node<User>* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
};

// LoanManager class managing a collection of loans
class LoanManager {
    Node<Loan>* head;

public:
    LoanManager() : head(nullptr) {}

    void issueLoan(Loan* loan) {
        Node<Loan>* newNode = new Node<Loan>(*loan);
        newNode->next = head;
        head = newNode;
        loan->getBook()->setAvailability(false);
    }

    void returnBook(Loan* loan, const std::string& returnDate) {
        loan->setReturnStatus(true);
        loan->getBook()->setAvailability(true);
    }

    void displayAllLoans() const {
        Node<Loan>* current = head;
        std::cout << "Library Loans:" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        while (current) {
            std::cout << "User: " << current->data.getUser()->getFirstName() << " " << current->data.getUser()->getLastName()
                      << ", Book: " << current->data.getBook()->getTitle()
                      << ", Due Date: " << current->data.getDueDate()
                      << ", Returned: " << (current->data.getIsReturned() ? "Yes" : "No") << std::endl;
            current = current->next;
        }
    }

    ~LoanManager() {
        Node<Loan>* current = head;
        while (current) {
            Node<Loan>* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
};

// LibraryManagementSystem class managing the overall library system
class LibraryManagementSystem {
    Catalog catalog;
    UserManager userManager;
    LoanManager loanManager;

public:
    void addBookToCatalog(const std::string& title, const std::string& author, const std::string& condition = "New") {
        Book book(title, author, condition);
        catalog.addBook(book);
    }

    void addUser(const std::string& firstName, const std::string& lastName, const std::string& phone, const std::string& address, int userID) {
        User user(firstName, lastName, phone, address, userID);
        userManager.addUser(user);
    }

    void issueLoan(int userID, const std::string& bookTitle, const std::string& dueDate) {
        User* user = userManager.findUser(userID);
        Book* book = catalog.findBook(bookTitle);
        if (user && book && book->checkAvailability()) {
            Loan loan(user, book, dueDate);
            loanManager.issueLoan(&loan);
        } else {
            std::cerr << "User or book not found or book not available." << std::endl;
        }
    }

    void returnBook(int userID, const std::string& bookTitle, const std::string& returnDate) {
        // Logic to return the book (similar to issuing loan)
        std::cerr << "Functionality not yet implemented." << std::endl;
    }

    void displayAllBooks() const {
        catalog.displayAllBooks();
    }

    void displayAllUsers() const {
        userManager.displayAllUsers();
    }

    void displayAllLoans() const {
        loanManager.displayAllLoans();
    }
};

int main() {
    LibraryManagementSystem lms;

    int choice;
    do {
        std::cout << "\nLibrary Management System Menu:" << std::endl;
        std::cout << "1. Add Book to Catalog" << std::endl;
        std::cout << "2. Add User" << std::endl;
        std::cout << "3. Issue Loan" << std::endl;
        std::cout << "4. Return Book" << std::endl;
        std::cout << "5. Display All Books" << std::endl;
        std::cout << "6. Display All Users" << std::endl;
        std::cout << "7. Display All Loans" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string title, author, condition;
                std::cout << "Enter book title: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                std::cout << "Enter book author: ";
                std::getline(std::cin, author);
                std::cout << "Enter book condition: ";
                std::getline(std::cin, condition);
                lms.addBookToCatalog(title, author, condition);
                break;
            }
            case 2: {
                std::string firstName, lastName, phone, address;
                int userID;
                std::cout << "Enter first name: ";
                std::cin.ignore();
                std::getline(std::cin, firstName);
                std::cout << "Enter last name: ";
                std::getline(std::cin, lastName);
                std::cout << "Enter phone: ";
                std::getline(std::cin, phone);
                std::cout << "Enter address: ";
                std::getline(std::cin, address);
                std::cout << "Enter user ID: ";
                std::cin >> userID;
                lms.addUser(firstName, lastName, phone, address, userID);
                break;
            }
            case 3: {
                int userID;
                std::string bookTitle, dueDate;
                std::cout << "Enter user ID: ";
                std::cin >> userID;
                std::cin.ignore();
                std::cout << "Enter book title: ";
                std::getline(std::cin, bookTitle);
                std::cout << "Enter due date: ";
                std::getline(std::cin, dueDate);
                lms.issueLoan(userID, bookTitle, dueDate);
                break;
            }
            case 4: {
                int userID;
                std::string bookTitle, returnDate;
                std::cout << "Enter user ID: ";
                std::cin >> userID;
                std::cin.ignore();
                std::cout << "Enter book title: ";
                std::getline(std::cin, bookTitle);
                std::cout << "Enter return date: ";
                std::getline(std::cin, returnDate);
                lms.returnBook(userID, bookTitle, returnDate);
                break;
            }
            case 5:
                lms.displayAllBooks();
                break;
            case 6:
                lms.displayAllUsers();
                break;
            case 7:
                lms.displayAllLoans();
                break;
            case 0:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice!" << std::endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
