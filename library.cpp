#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits> // For std::numeric_limits
#include <ctime> // For fine calculation

using namespace std;

// Class definition for Book
class Book {
public:
    string title;
    string author;
    string isbn;
    int year;
    double price;
    bool isAvailable;
    string genre;

    // Constructor
    Book(string t, string a, string i, int y, double p, string g)
        : title(t), author(a), isbn(i), year(y), price(p), isAvailable(true), genre(g) {}

    // Display Book information
    void display() const {
        cout << left << setw(20) << title
             << setw(20) << author
             << setw(15) << isbn
             << setw(10) << year
             << setw(10) << price
             << setw(10) << (isAvailable ? "Available" : "Not Available")
             << setw(10) << genre << endl;
    }

    // Save book data to a file
    void saveToFile(ofstream &file) const {
        file << title << "\n" << author << "\n" << isbn << "\n" << year << "\n" << price << "\n"
             << isAvailable << "\n" << genre << "\n";
    }

    // Load book data from file
    static Book loadFromFile(ifstream &file) {
        string t, a, i, g;
        int y;
        double p;
        bool available;

        getline(file, t);
        getline(file, a);
        getline(file, i);
        file >> y >> p >> available;
        file.ignore(); // To consume the newline character
        getline(file, g);

        return Book(t, a, i, y, p, g);
    }
};

// Class to handle the library system
class Library {
private:
    vector<Book> books;

public:
    // Add a new book to the library
    void addBook(const Book &book) {
        books.push_back(book);
    }

    // Remove a book by ISBN
    void removeBook(const string &isbn) {
        auto it = find_if(books.begin(), books.end(), [&](const Book &book) {
            return book.isbn == isbn;
        });

        if (it != books.end()) {
            books.erase(it);
            cout << "Book removed successfully!" << endl;
        } else {
            cout << "Book not found!" << endl;
        }
    }

    // Search books by title
    vector<Book> searchByTitle(const string &title) const {
        vector<Book> result;
        for (const auto &book : books) {
            if (book.title.find(title) != string::npos) {
                result.push_back(book);
            }
        }
        return result;
    }

    // Search books by author
    vector<Book> searchByAuthor(const string &author) const {
        vector<Book> result;
        for (const auto &book : books) {
            if (book.author.find(author) != string::npos) {
                result.push_back(book);
            }
        }
        return result;
    }

    // Search books by genre
    vector<Book> searchByGenre(const string &genre) const {
        vector<Book> result;
        for (const auto &book : books) {
            if (book.genre.find(genre) != string::npos) {
                result.push_back(book);
            }
        }
        return result;
    }

    // Sort books by price (ascending)
    void sortByPrice() {
        sort(books.begin(), books.end(), [](const Book &a, const Book &b) {
            return a.price < b.price;
        });
    }

    // Sort books by year (ascending)
    void sortByYear() {
        sort(books.begin(), books.end(), [](const Book &a, const Book &b) {
            return a.year < b.year;
        });
    }

    // Sort books by title (ascending)
    void sortByTitle() {
        sort(books.begin(), books.end(), [](const Book &a, const Book &b) {
            return a.title < b.title;
        });
    }

    // Sort books by author (ascending)
    void sortByAuthor() {
        sort(books.begin(), books.end(), [](const Book &a, const Book &b) {
            return a.author < b.author;
        });
    }

    // Display all books
    void displayAllBooks() const {
        cout << left << setw(20) << "Title"
             << setw(20) << "Author"
             << setw(15) << "ISBN"
             << setw(10) << "Year"
             << setw(10) << "Price"
             << setw(10) << "Availability"
             << setw(10) << "Genre" << endl;

        for (const auto &book : books) {
            book.display();
        }
    }

    // Load books from a file
    void loadBooksFromFile(const string &filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file for reading!" << endl;
            return;
        }

        while (!file.eof()) {
            books.push_back(Book::loadFromFile(file));
        }
        file.close();
    }

    // Save books to a file
    void saveBooksToFile(const string &filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file for writing!" << endl;
            return;
        }

        for (const auto &book : books) {
            book.saveToFile(file);
        }
        file.close();
    }
};

// Class to handle users
class User {
public:
    string name;
    vector<Book*> borrowedBooks;
    static const int maxBorrowLimit = 5;

    // Constructor
    User(string n) : name(n) {}

    // Borrow a book
    bool borrowBook(Book &book) {
        if (borrowedBooks.size() < maxBorrowLimit && book.isAvailable) {
            borrowedBooks.push_back(&book);
            book.isAvailable = false;
            cout << name << " borrowed the book: " << book.title << endl;
            return true;
        }
        cout << "Cannot borrow more books or book is unavailable." << endl;
        return false;
    }

    // Return a book
    void returnBook(Book &book) {
        auto it = find(borrowedBooks.begin(), borrowedBooks.end(), &book);
        if (it != borrowedBooks.end()) {
            borrowedBooks.erase(it);
            book.isAvailable = true;
            cout << name << " returned the book: " << book.title << endl;
        }
    }

    // List all borrowed books
    void listBorrowedBooks() const {
        cout << name << "'s Borrowed Books:" << endl;
        for (const auto &book : borrowedBooks) {
            cout << book->title << endl;
        }
    }
};

// Display the main menu options
void displayMenu() {
    cout << "\nLibrary Management System\n";
    cout << "1. Add a new book\n";
    cout << "2. Remove a book\n";
    cout << "3. Search books by title\n";
    cout << "4. Search books by author\n";
    cout << "5. Search books by genre\n";
    cout << "6. Display all books\n";
    cout << "7. Sort books by price\n";
    cout << "8. Sort books by year\n";
    cout << "9. Sort books by title\n";
    cout << "10. Sort books by author\n";
    cout << "11. Load books from file\n";
    cout << "12. Save books to file\n";
    cout << "13. Borrow a book\n";
    cout << "14. Return a book\n";
    cout << "15. Exit\n";
    cout << "Enter your choice: ";
}

// Main function for library management
int main() {
    Library library;
    User user1("Alice");
    int choice;

    // Preload some books for testing
    library.addBook(Book("The Great Gatsby", "F. Scott Fitzgerald", "9780743273565", 1925, 10.99, "Classic"));
    library.addBook(Book("1984", "George Orwell", "9780451524935", 1949, 8.99, "Dystopian"));

    while (true) {
        displayMenu();
        cin >> choice;

        if (choice == 1) {
            string title, author, isbn, genre;
            int year;
            double price;
            cout << "Enter book title: ";
            cin.ignore(); // To ignore the leftover newline
            getline(cin, title);
            cout << "Enter book author: ";
            getline(cin, author);
            cout << "Enter book ISBN: ";
            getline(cin, isbn);
            cout << "Enter book year: ";
            cin >> year;
            cout << "Enter book price: ";
            cin >> price;
            cout << "Enter book genre: ";
            cin.ignore(); // To ignore the leftover newline
            getline(cin, genre);
            library.addBook(Book(title, author, isbn, year, price, genre));
            cout << "Book added successfully!" << endl;

        } else if (choice == 2) {
            string isbn;
            cout << "Enter ISBN of the book to remove: ";
            cin.ignore();
            getline(cin, isbn);
            library.removeBook(isbn);

        } else if (choice == 3) {
            string title;
            cout << "Enter title to search for: ";
            getline(cin, title);
            auto foundBooks = library.searchByTitle(title);
            if (foundBooks.empty()) {
                cout << "No books found with that title." << endl;
            } else {
                for (const auto &book : foundBooks) {
                    book.display();
                }
            }

        } else if (choice == 4) {
            string author;
            cout << "Enter author to search for: ";
            getline(cin, author);
            auto foundBooks = library.searchByAuthor(author);
            if (foundBooks.empty()) {
                cout << "No books found by that author." << endl;
            } else {
                for (const auto &book : foundBooks) {
                    book.display();
                }
            }

        } else if (choice == 5) {
            string genre;
            cout << "Enter genre to search for: ";
            getline(cin, genre);
            auto foundBooks = library.searchByGenre(genre);
            if (foundBooks.empty()) {
                cout << "No books found in that genre." << endl;
            } else {
                for (const auto &book : foundBooks) {
                    book.display();
                }
            }

        } else if (choice == 6) {
            library.displayAllBooks();
        } else if (choice == 7) {
            library.sortByPrice();
            cout << "Books sorted by price." << endl;
        } else if (choice == 8) {
            library.sortByYear();
            cout << "Books sorted by year." << endl;
        } else if (choice == 9) {
            library.sortByTitle();
            cout << "Books sorted by title." << endl;
        } else if (choice == 10) {
            library.sortByAuthor();
            cout << "Books sorted by author." << endl;
        } else if (choice == 11) {
            string filename;
            cout << "Enter filename to load from: ";
            getline(cin, filename);
            library.loadBooksFromFile(filename);
        } else if (choice == 12) {
            string filename;
            cout << "Enter filename to save to: ";
            getline(cin, filename);
            library.saveBooksToFile(filename);
        } else if (choice == 13) {
            string isbn;
            cout << "Enter ISBN of the book to borrow: ";
            getline(cin, isbn);
            auto foundBooks = library.searchByTitle(isbn);
            if (!foundBooks.empty()) {
                user1.borrowBook(foundBooks[0]);
            }
        } else if (choice == 14) {
            string isbn;
            cout << "Enter ISBN of the book to return: ";
            getline(cin, isbn);
            auto foundBooks = library.searchByTitle(isbn);
            if (!foundBooks.empty()) {
                user1.returnBook(foundBooks[0]);
            }
        } else if (choice == 15) {
            cout << "Exiting the program." << endl;
            break;
        }
    }

    return 0;
}
