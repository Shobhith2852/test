import unittest
from library import Book, Library
import os

class TestLibraryManagement(unittest.TestCase):

    def setUp(self):
        self.library = Library()
        self.book1 = Book("Title1", "Author1", "ISBN1", 2020, 15.99)
        self.book2 = Book("Title2", "Author2", "ISBN2", 2021, 10.99)
        self.book3 = Book("Another Title", "Author1", "ISBN3", 2019, 20.99)
        self.library.addBook(self.book1)
        self.library.addBook(self.book2)
        self.library.addBook(self.book3)

    def test_add_book(self):
        self.assertEqual(len(self.library.books), 3)
        new_book = Book("New Title", "New Author", "ISBN4", 2022, 5.99)
        self.library.addBook(new_book)
        self.assertEqual(len(self.library.books), 4)

    def test_remove_book(self):
        self.library.removeBook("ISBN2")
        self.assertEqual(len(self.library.books), 2)
        self.assertIsNone(self.library.displayBookByISBN("ISBN2"))

    def test_search_by_title(self):
        results = self.library.searchByTitle("Title")
        self.assertEqual(len(results), 2)
        self.assertIn(self.book1, results)
        self.assertIn(self.book2, results)

    def test_search_by_author(self):
        results = self.library.searchByAuthor("Author1")
        self.assertEqual(len(results), 2)
        self.assertIn(self.book1, results)
        self.assertIn(self.book3, results)

    def test_sort_by_price(self):
        self.library.sortByPrice()
        self.assertEqual(self.library.books[0], self.book2)
        self.assertEqual(self.library.books[2], self.book3)

    def test_sort_by_year(self):
        self.library.sortByYear()
        self.assertEqual(self.library.books[0], self.book3)
        self.assertEqual(self.library.books[2], self.book2)

    def test_display_book_by_isbn(self):
        book = self.library.displayBookByISBN("ISBN1")
        self.assertIsNotNone(book)
        self.assertEqual(book.title, "Title1")

    def test_update_book_details(self):
        self.library.updateBookDetails("ISBN1")
        updated_book = self.library.displayBookByISBN("ISBN1")
        self.assertIsNotNone(updated_book)
        self.assertEqual(updated_book.title, "Updated Title")

    def test_load_and_save_books(self):
        filename = "test_books.txt"
        # Create and write data to a file for testing
        with open(filename, "w") as file:
            file.write("Title1\nAuthor1\nISBN1\n2020\n15.99\n")
            file.write("Title2\nAuthor2\nISBN2\n2021\n10.99\n")
            file.write("Another Title\nAuthor1\nISBN3\n2019\n20.99\n")
        
        new_library = Library()
        new_library.loadBooksFromFile(filename)
        self.assertEqual(len(new_library.books), 3)
        os.remove(filename)

    def test_clear_books(self):
        self.library.clearBooks()
        self.assertEqual(len(self.library.books), 0)

    def test_display_total_books(self):
        self.assertEqual(len(self.library.books), 3)

if __name__ == "__main__":
    unittest.main()
