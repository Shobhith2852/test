import os
from typing import List, Optional

# Class definition for Book
class Book:
    def __init__(self, title="", author="", isbn="", year=0, price=0.0):
        self.title = title
        self.author = author
        self.isbn = isbn
        self.year = year
        self.price = price

    def display(self):
        print("{:<20}{:<20}{:<15}{:<10}{:<10.2f}".format(self.title, self.author, self.isbn, self.year, self.price))

   # def save_to_file(self, file):
    #    file.write("{}\n{}\n{}\n{}\n{}\n".format(self.title, self.author, self.isbn, self.year, self.price))

    #@staticmethod
    #def load_from_file(file):
     #   title = file.readline().strip()
      #  author = file.readline().strip()
       # isbn = file.readline().strip()
        #year = int(file.readline().strip())
        #price = float(file.readline().strip())
        #return Book(title, author, isbn, year, price)

# Class to handle the library system
class Library:
    def __init__(self):
        self.books = []  # List of Book objects


    def add_book(self, book: Book):
        self.books.append(book)

    def remove_book(self, isbn: str):
        book = next((b for b in self.books if b.isbn == isbn), None)
        if book:
            self.books.remove(book)
            print("Book removed successfully!")
        else:
            print("Book not found!")

    def search_by_title(self, title: str) -> List[Book]:
        return [book for book in self.books if title.lower() in book.title.lower()]

    def search_by_author(self, author: str) -> List[Book]:
        return [book for book in self.books if author.lower() in book.author.lower()]

    def sort_by_price(self):
        self.books.sort(key=lambda book: book.price)

    def sort_by_year(self):
        self.books.sort(key=lambda book: book.year)

    def display_all_books(self):
        print(f"{'Title':<20}{'Author':<20}{'ISBN':<15}{'Year':<10}{'Price':<10}")
        for book in self.books:
            book.display()

    '''def load_books_from_file(self, filename: str):
        if not os.path.exists(filename):
            print("File not found!")
            return
    
        with open(filename, 'r') as file:
            while True:
                try:
                    book = Book.load_from_file(file)
                    if book:
                        self.books.append(book)
                except ValueError:
                    break  # Break out of the loop if there is an issue with file format (end of file or invalid data)


    def save_books_to_file(self, filename: str):
        with open(filename, 'w') as file:
            for book in self.books:
                book.save_to_file(file)'''

    def display_total_books(self):
        print(f"Total books in the library: {len(self.books)}")

    def clear_books(self):
        self.books.clear()
        print("All books have been removed from the library!")

    def display_book_by_isbn(self, isbn: str) -> Optional[Book]:
        book = next((b for b in self.books if b.isbn == isbn), None)
        if book:
            book.display()
            return book
        else:
            print("Book not found!")
            return None
    
    def update_book_details(self, isbn: str, new_book: Optional[Book] = None):
        book = next((b for b in self.books if b.isbn == isbn), None)
        if book:
            if new_book:
                # Update book with new_book details
                book.title = new_book.title
                book.author = new_book.author
                book.year = new_book.year
                book.price = new_book.price
            else:
                # Otherwise, prompt for user input
                book.title = input(f"Enter new title (current: {book.title}): ") or book.title
                book.author = input(f"Enter new author (current: {book.author}): ") or book.author
                book.year = int(input(f"Enter new year (current: {book.year}): ") or book.year)
                book.price = float(input(f"Enter new price (current: {book.price}): ") or book.price)
            print("Book details updated successfully!")
        else:
            print("Book not found!")


# Display the main menu options
def display_menu():
    print("\nLibrary Management System")
    print("1. Add a new book")
    print("2. Remove a book")
    print("3. Search books by title")
    print("4. Search books by author")
    print("5. Display all books")
    print("6. Sort books by price")
    print("7. Sort books by year")
    print("8. Load books from file")
    print("9. Save books to file")
    print("10. Display total books")
    print("11. Clear all books")
    print("12. Display book by ISBN")
    print("13. Update book details")
    print("14. Exit")
    print("Enter your choice: ", end="")

# Main function for library management
def main():
    library = Library()

    while True:
        display_menu()
        try:
            choice = int(input())
        except ValueError:
            print("Invalid input. Please enter a number between 1 and 14.")
            continue

        if choice == 1:
            title = input("Enter book title: ")
            author = input("Enter book author: ")
            isbn = input("Enter book ISBN: ")
            year = int(input("Enter book year: "))
            price = float(input("Enter book price: "))
            library.add_book(Book(title, author, isbn, year, price))
            print("Book added successfully!")

        elif choice == 2:
            isbn = input("Enter ISBN of the book to remove: ")
            library.remove_book(isbn)

        elif choice == 3:
            title = input("Enter title to search for: ")
            books = library.search_by_title(title)
            if books:
                for book in books:
                    book.display()
            else:
                print("No books found with that title.")

        elif choice == 4:
            author = input("Enter author to search for: ")
            books = library.search_by_author(author)
            if books:
                for book in books:
                    book.display()
            else:
                print("No books found by that author.")

        elif choice == 5:
            library.display_all_books()

        elif choice == 6:
            library.sort_by_price()
            print("Books sorted by price.")

        elif choice == 7:
            library.sort_by_year()
            print("Books sorted by year.")

        '''elif choice == 8:
            filename = input("Enter filename to load from: ")
            library.load_books_from_file(filename)
            print("Books loaded from file.")

        elif choice == 9:
            filename = input("Enter filename to save to: ")
            library.save_books_to_file(filename)
            print("Books saved to file.")'''

        elif choice == 10:
            library.display_total_books()

        elif choice == 11:
            library.clear_books()

        elif choice == 12:
            isbn = input("Enter ISBN to display: ")
            library.display_book_by_isbn(isbn)

        elif choice == 13:
            isbn = input("Enter ISBN of the book to update: ")
            library.update_book_details(isbn)

        elif choice == 14:
            print("Exiting program...")
            break

        else:
            print("Invalid choice. Please enter a number between 1 and 14.")

if __name__ == "__main__":
    main()
