#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <sstream>  // For stringstream manipulation

using namespace std;

// Class definition for Book
class Book {
public:
    string title;
    string author;
    string isbn;
    int year;
    double price;

    // Constructor
    Book(string t, string a, string i, int y, double p)
        : title(t), author(a), isbn(i), year(y), price(p) {}

    // Display Book information
    void display() const {
        cout << left << setw(20) << title
             << setw(20) << author
             << setw(15) << isbn
             << setw(10) << year
             << setw(10) << price << endl;
    }

    // Save book data to a file
    void saveToFile(ofstream &file) const {
        file << title << "\n" << author << "\n" << isbn << "\n" << year << "\n" << price << "\n";
    }

    // Load book data from file
    static Book loadFromFile(ifstream &file) {
        string t, a, i;
        int y;
        double p;

        getline(file, t);
        getline(file, a);
        getline(file, i);
        file >> y >> p;
        file.ignore(); // To consume the newline character

        return Book(t, a, i, y, p);
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

    // Display all books
    void displayAllBooks() const {
        cout << left << setw(20) << "Title"
             << setw(20) << "Author"
             << setw(15) << "ISBN"
             << setw(10) << "Year"
             << setw(10) << "Price" << endl;

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

    // Display total number of books in the library
    void displayTotalBooks() const {
        cout << "Total books in the library: " << books.size() << endl;
    }

    // Clear all books from the library
    void clearBooks() {
        books.clear();
        cout << "All books have been removed from the library!" << endl;
    }

Book displayBookByISBN(const string &isbn) const {
    auto it = find_if(books.begin(), books.end(), [&](const Book &book) {
        return book.isbn == isbn;
    });

    if (it != books.end()) {
        it->display();  // Still print the book details
        return *it;     // Return the found book
    } else {
        cout << "Book not found!" << endl;
        return Book();  // Return a default Book object if not found
    }
}


    // Update book details
    void updateBookDetails(const string &isbn) {
        auto it = find_if(books.begin(), books.end(), [&](const Book &book) {
            return book.isbn == isbn;
        });

        if (it != books.end()) {
            string newTitle, newAuthor;
            int newYear;
            double newPrice;

            cout << "Enter new title (current: " << it->title << "): ";
            cin.ignore(); // To clear leftover newline
            getline(cin, newTitle);

            cout << "Enter new author (current: " << it->author << "): ";
            getline(cin, newAuthor);

            cout << "Enter new year (current: " << it->year << "): ";
            cin >> newYear;

            cout << "Enter new price (current: " << it->price << "): ";
            cin >> newPrice;

            it->title = newTitle;
            it->author = newAuthor;
            it->year = newYear;
            it->price = newPrice;

            cout << "Book details updated successfully!" << endl;
        } else {
            cout << "Book not found!" << endl;
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
    cout << "5. Display all books\n";
    cout << "6. Sort books by price\n";
    cout << "7. Sort books by year\n";
    cout << "8. Load books from file\n";
    cout << "9. Save books to file\n";
    cout << "10. Display total books\n";
    cout << "11. Clear all books\n";
    cout << "12. Display book by ISBN\n";
    cout << "13. Update book details\n";
    cout << "14. Exit\n";
    cout << "Enter your choice: ";
}

// Function to get valid integer input
int getValidIntegerInput() {
    int choice;
    while (true) {
        cin >> choice;

        if (cin.fail()) { // Check if the input is invalid
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid characters
            cout << "Invalid input. Please enter a number between 1 and 14.\n";
        } else if (choice < 1 || choice > 14) {
            cout << "Invalid choice. Please enter a number between 1 and 14.\n";
        } else {
            break; // Valid input, break out of the loop
        }
    }
    return choice;
}

// Main function for library management
int main() {
    Library library;
    int choice;

    while (true) {
        displayMenu();
        choice = getValidIntegerInput(); // Get valid choice input

        if (choice == 1) {
            // Add a new book
            string title, author, isbn;
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
            cin.ignore();

            library.addBook(Book(title, author, isbn, year, price));
            cout << "Book added successfully!" << endl;

        } else if (choice == 2) {
            // Remove a book by ISBN
            string isbn;
            cout << "Enter ISBN of the book to remove: ";
            cin.ignore(); // To ignore the leftover newline
            getline(cin, isbn);

            library.removeBook(isbn);

        } else if (choice == 3) {
            // Search books by title
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
            // Search books by author
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
            // Display all books
            library.displayAllBooks();

        } else if (choice == 6) {
            // Sort books by price
            library.sortByPrice();
            cout << "Books sorted by price." << endl;

        } else if (choice == 7) {
            // Sort books by year
            library.sortByYear();
            cout << "Books sorted by year." << endl;

        } else if (choice == 8) {
            // Load books from a file
            string filename;
            cout << "Enter filename to load from: ";
            getline(cin, filename);

            library.loadBooksFromFile(filename);
            cout << "Books loaded from file." << endl;

        } else if (choice == 9) {
            // Save books to a file
            string filename;
            cout << "Enter filename to save to: ";
            getline(cin, filename);

            library.saveBooksToFile(filename);
            cout << "Books saved to file." << endl;

        } else if (choice == 10) {
            // Display total number of books
            library.displayTotalBooks();

        } else if (choice == 11) {
            // Clear all books
            library.clearBooks();

        } else if (choice == 12) {
            // Display book by ISBN
            string isbn;
            cout << "Enter ISBN to display: ";
            cin.ignore(); // To ignore the leftover newline
            getline(cin, isbn);

            library.displayBookByISBN(isbn);

        } else if (choice == 13) {
            // Update book details
            string isbn;
            cout << "Enter ISBN of the book to update: ";
            cin.ignore(); // To ignore the leftover newline
            getline(cin, isbn);

            library.updateBookDetails(isbn);

        } else if (choice == 14) {
            // Exit the program
            cout << "Exiting program..." << endl;
            break;
        }
    }

    return 0;
}
