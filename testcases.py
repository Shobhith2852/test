import unittest
from library import Book, Library
import os

class TestLibraryManagement(unittest.TestCase):

    def setUp(self):
        self.library = Library()
        self.book1 = Book("Title1", "Author1", "ISBN1", 2020, 15.99)
        self.book2 = Book("Title2", "Author2", "ISBN2", 2021, 10.99)
        self.book3 = Book("Another Title", "Author1", "ISBN3", 2019, 20.99)
        self.library.add_book(self.book1)  # Corrected method name
        self.library.add_book(self.book2)  # Corrected method name
        self.library.add_book(self.book3)  # Corrected method name

    def test_add_book(self):
        self.assertEqual(len(self.library.books), 3)
        new_book = Book("New Title", "New Author", "ISBN4", 2022, 5.99)
        self.library.add_book(new_book)  # Corrected method name
        self.assertEqual(len(self.library.books), 4)

    def test_remove_book(self):
        self.library.remove_book("ISBN2")  # Corrected method name
        self.assertEqual(len(self.library.books), 2)
        self.assertIsNone(self.library.display_book_by_isbn("ISBN2"))  # Corrected method name

    def test_search_by_title(self):
        results = self.library.search_by_title("Title")  # Corrected method name
        self.assertEqual(len(results), 3)
        self.assertIn(self.book1, results)
        self.assertIn(self.book2, results)

    def test_search_by_author(self):
        results = self.library.search_by_author("Author1")  # Corrected method name
        self.assertEqual(len(results), 2)
        self.assertIn(self.book1, results)
        self.assertIn(self.book3, results)

    def test_sort_by_price(self):
        self.library.sort_by_price()  # Corrected method name
        self.assertEqual(self.library.books[0], self.book2)
        self.assertEqual(self.library.books[2], self.book3)

    def test_sort_by_year(self):
        self.library.sort_by_year()  # Corrected method name
        self.assertEqual(self.library.books[0], self.book3)
        self.assertEqual(self.library.books[2], self.book2)

    def test_display_book_by_isbn(self):
        book = self.library.display_book_by_isbn("ISBN1")  # Corrected method name
        self.assertIsNotNone(book)
        self.assertEqual(book.title, "Title1")

    def test_update_book_details(self):
        # Create a new Book object with updated details
        updated_book = Book("Updated Title", "Updated Author", "ISBN1", 2023, 25.99)
        
        # Call update_book_details and pass the updated_book
        self.library.update_book_details("ISBN1", updated_book)
        
        # Get the updated book and verify the changes
        updated_book_from_library = self.library.display_book_by_isbn("ISBN1")
        self.assertIsNotNone(updated_book_from_library)
        self.assertEqual(updated_book_from_library.title, "Updated Title")
        self.assertEqual(updated_book_from_library.author, "Updated Author")
        self.assertEqual(updated_book_from_library.year, 2023)
        self.assertEqual(updated_book_from_library.price, 25.99)


    def test_load_and_save_books(self):
        filename = "test_books.txt"
        # Create and write data to a file for testing
        with open(filename, "w") as file:
            file.write("Title10\nAuthor10\nISBN10\n2020\n15.99\n")
            file.write("Title20\nAuthor20\nISBN20\n2021\n10.99\n")
            file.write("Another Title1\nAuthor11\nISBN31\n2019\n20.99\n")
        
        new_library = Library()
        new_library.load_books_from_file(filename)  # Corrected method name
        self.assertEqual(len(new_library.books), 3)
        os.remove(filename)

    def test_clear_books(self):
        self.library.clear_books()  # Corrected method name
        self.assertEqual(len(self.library.books), 0)

    def test_display_total_books(self):
        self.assertEqual(len(self.library.books), 3)

if __name__ == "__main__":
    unittest.main()
