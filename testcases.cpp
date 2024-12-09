#include <iostream>
#include <fstream>
#include <string>
#include <gtest/gtest.h>
#include "library_system.cpp"  // Include the header for your library management code

// Helper function to create a temporary file with book data
void createTempFileForBooks(const std::string& filename) {
    std::ofstream file(filename);
    file << "The C++ Programming\n";
    file << "Bjarne Stroustrup\n";
    file << "12345\n";
    file << "2020\n";
    file << "29.99\n";
    file << "Effective Modern C++\n";
    file << "Scott Meyers\n";
    file << "67890\n";
    file << "2017\n";
    file << "35.99\n";
    file.close();
}

// Helper function to check if a file is empty (after operations)
bool isFileEmpty(const std::string& filename) {
    std::ifstream file(filename);
    return file.peek() == std::ifstream::traits_type::eof();
}

// Test for saving and loading books with real file I/O
TEST(LibraryTest, RealFileIO) {
    Library library;
    std::string filename = "test_books.txt";

    // Create a temporary file with book data
    createTempFileForBooks(filename);

    // Load books from the file
    library.loadBooksFromFile(filename);

    // Ensure books are loaded correctly
    auto books = library.searchByTitle("C++");
    ASSERT_EQ(books.size(), 1);
    ASSERT_EQ(books[0].title, "The C++ Programming");
    ASSERT_EQ(books[0].author, "Bjarne Stroustrup");
    ASSERT_EQ(books[0].isbn, "12345");
    ASSERT_EQ(books[0].year, 2020);
    ASSERT_EQ(books[0].price, 29.99);

    // Add another book to the library
    Book newBook("Clean Code", "Robert C. Martin", "11223", 2008, 42.50);
    library.addBook(newBook);

    // Save books to the file
    library.saveBooksToFile(filename);

    // Check if file is not empty
    ASSERT_FALSE(isFileEmpty(filename));

    // Now load the books again from the file
    Library library2;
    library2.loadBooksFromFile(filename);

    // Ensure books are loaded correctly
    auto loadedBooks = library2.searchByTitle("Clean Code");
    ASSERT_EQ(loadedBooks.size(), 1);
    ASSERT_EQ(loadedBooks[0].title, "Clean Code");
    ASSERT_EQ(loadedBooks[0].author, "Robert C. Martin");

    // Clean up the file after testing
    std::remove(filename.c_str());
}

// Edge case: Ensure file is cleared correctly when loading an empty file
TEST(LibraryTest, LoadFromEmptyFile) {
    Library library;
    std::string filename = "empty_books.txt";
    
    // Create an empty file
    std::ofstream file(filename);
    file.close();

    // Load books from the empty file
    library.loadBooksFromFile(filename);

    // Ensure no books are loaded
    auto books = library.searchByTitle("Non-Existing Title");
    ASSERT_TRUE(books.empty());

    // Clean up the file after testing
    std::remove(filename.c_str());
}

// Edge case: Try loading from a non-existent file
TEST(LibraryTest, LoadFromNonExistentFile) {
    Library library;
    std::string filename = "non_existent_file.txt";

    // Try loading from a file that doesn't exist
    library.loadBooksFromFile(filename);

    // Ensure the library remains empty
    auto books = library.searchByTitle("Non-Existing Title");
    ASSERT_TRUE(books.empty());
}

// Edge case: Test saving to a file that can't be written to (e.g., read-only file)
TEST(LibraryTest, SaveToReadOnlyFile) {
    Library library;
    std::string filename = "read_only_books.txt";

    // Create a file and set it to read-only (this might need OS-specific handling)
    std::ofstream file(filename);
    file << "Read Only Book\n";
    file.close();
    
    // Set the file to read-only (UNIX/Linux example)
    chmod(filename.c_str(), 0444); // Read-only permissions

    // Try saving to the read-only file
    ASSERT_THROW(library.saveBooksToFile(filename), std::ios_base::failure);

    // Clean up the file after testing (restore write permissions)
    chmod(filename.c_str(), 0666); // Write permissions
    std::remove(filename.c_str());
}

// Test for adding a new book
TEST(LibraryTest, AddBook) {
    Library library;
    Book b1("C++ Programming", "Bjarne Stroustrup", "12345", 2020, 29.99);
    
    library.addBook(b1);
    
    auto books = library.searchByTitle("C++ Programming");
    ASSERT_EQ(books.size(), 1);
    ASSERT_EQ(books[0].title, "C++ Programming");
}

// Test for removing a book by ISBN
TEST(LibraryTest, RemoveBookByISBN) {
    Library library;
    Book b1("C++ Programming", "Bjarne Stroustrup", "12345", 2020, 29.99);
    library.addBook(b1);
    
    library.removeBook("12345");
    
    auto books = library.searchByTitle("C++ Programming");
    ASSERT_EQ(books.size(), 0);
}

// Test for searching books by title
TEST(LibraryTest, SearchBooksByTitle) {
    Library library;
    Book b1("C++ Programming", "Bjarne Stroustrup", "12345", 2020, 29.99);
    Book b2("Effective Modern C++", "Scott Meyers", "67890", 2017, 35.99);
    library.addBook(b1);
    library.addBook(b2);
    
    auto books = library.searchByTitle("C++");
    ASSERT_EQ(books.size(), 2);
}

// Test for searching books by author
TEST(LibraryTest, SearchBooksByAuthor) {
    Library library;
    Book b1("C++ Programming", "Bjarne Stroustrup", "12345", 2020, 29.99);
    Book b2("Effective Modern C++", "Scott Meyers", "67890", 2017, 35.99);
    library.addBook(b1);
    library.addBook(b2);
    
    auto books = library.searchByAuthor("Scott Meyers");
    ASSERT_EQ(books.size(), 1);
    ASSERT_EQ(books[0].author, "Scott Meyers");
}

// Test for sorting books by price
TEST(LibraryTest, SortBooksByPrice) {
    Library library;
    Book b1("C++ Programming", "Bjarne Stroustrup", "12345", 2020, 29.99);
    Book b2("Effective Modern C++", "Scott Meyers", "67890", 2017, 35.99);
    library.addBook(b1);
    library.addBook(b2);

    library.sortByPrice();

    auto books = library.searchByTitle("C++");
    ASSERT_EQ(books[0].price, 29.99);
    ASSERT_EQ(books[1].price, 35.99);
}

// Test for sorting books by year
TEST(LibraryTest, SortBooksByYear) {
    Library library;
    Book b1("C++ Programming", "Bjarne Stroustrup", "12345", 2020, 29.99);
    Book b2("Effective Modern C++", "Scott Meyers", "67890", 2017, 35.99);
    library.addBook(b1);
    library.addBook(b2);

    library.sortByYear();

    auto books = library.searchByTitle("C++");
    ASSERT_EQ(books[0].year, 2017);
    ASSERT_EQ(books[1].year, 2020);
}

// Test for displaying all books
TEST(LibraryTest, DisplayAllBooks) {
    Library library;
    Book b1("C++ Programming", "Bjarne Stroustrup", "12345", 2020, 29.99);
    Book b2("Effective Modern C++", "Scott Meyers", "67890", 2017, 35.99);
    library.addBook(b1);
    library.addBook(b2);

    // We can't assert directly for display, but we can verify the count
    auto books = library.searchByTitle("C++");
    ASSERT_EQ(books.size(), 2);
}

// Test for displaying total books
TEST(LibraryTest, DisplayTotalBooks) {
    Library library;
    Book b1("C++ Programming", "Bjarne Stroustrup", "12345", 2020, 29.99);
    Book b2("Effective Modern C++", "Scott Meyers", "67890", 2017, 35.99);
    library.addBook(b1);
    library.addBook(b2);

    int totalBooks = library.totalBooks();
    ASSERT_EQ(totalBooks, 2);
}

// Test for clearing all books
TEST(LibraryTest, ClearAllBooks) {
    Library library;
    Book b1("C++ Programming", "Bjarne Stroustrup", "12345", 2020, 29.99);
    library.addBook(b1);
    
    library.clearBooks();
    
    auto books = library.searchByTitle("C++ Programming");
    ASSERT_TRUE(books.empty());
}

// Test for displaying book by ISBN
TEST(LibraryTest, DisplayBookByISBN) {
    Library library;
    Book b1("C++ Programming", "Bjarne Stroustrup", "12345", 2020, 29.99);
    library.addBook(b1);
    
    auto book = library.displayBookByISBN("12345");
    ASSERT_EQ(book.isbn, "12345");
    ASSERT_EQ(book.title, "C++ Programming");
}

// Test for updating book details
TEST(LibraryTest, UpdateBookDetails) {
    Library library;
    Book b1("C++ Programming", "Bjarne Stroustrup", "12345", 2020, 29.99);
    library.addBook(b1);

    Book updatedBook("C++ Programming Updated", "Bjarne Stroustrup", "12345", 2023, 39.99);
    library.updateBookDetails(updatedBook);

    auto books = library.searchByISBN("12345");
    ASSERT_EQ(books.size(), 1);
    ASSERT_EQ(books[0].title, "C++ Programming Updated");
    ASSERT_EQ(books[0].year, 2023);
    ASSERT_EQ(books[0].price, 39.99);
}

// Main function to run all tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
