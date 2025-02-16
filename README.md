"# LibraryManagementSystemC" 

Library Management System

Overview
This is a simple Library Management System written in C. It allows users to add books, display available books, search for books, register users, borrow books, and return borrowed books. The system uses text files to store data persistently.

Features
- Add new books to the library
- Display all available books
- Search for a book by its ID
- Register new users
- Borrow a book if available
- Return a borrowed book
- Persistent storage using text files

Files Used
- `books.txt` - Stores book records
- `users.txt` - Stores user records
- `borrow.txt` - Stores records of borrowed books

How to Compile and Run
#Compilation:
```sh
gcc library_management.c -o library_management
```
#Execution:
```sh
./library_management
```

Usage
Upon running the program, you will be presented with a menu:
1. Add Book
2. Display Books
3. Search Book
4. Register User
5. Borrow Book
6. Return Book
7. Exit

Adding a Book
- Enter a unique book ID, title, and author.
- The book will be saved in `books.txt`.

Displaying Books
- Shows a list of all books with their availability status.

Searching for a Book
- Enter a book ID to check if it exists and whether it is available.

Registering a User
- Enter a unique user ID and name.
- The user will be saved in `users.txt`.

Borrowing a Book
- Enter your user ID and the book ID you want to borrow.
- If the book is available, it will be marked as borrowed.

Returning a Book
- Enter your user ID and the book ID you wish to return.
- The book will be marked as available again.

Requirements
- GCC Compiler
- Basic understanding of C programming

Notes
- Ensure that `books.txt`, `users.txt`, and `borrow.txt` exist before running the program, or create them manually.
- The system handles basic input validation to prevent errors.

Contributing
Feel free to fork the repository and improve the system by adding features like:
- User authentication
- Book categories
- Due dates and fine calculation
