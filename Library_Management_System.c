#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOOKS_FILE "books.txt"
#define USERS_FILE "users.txt"
#define BORROW_FILE "borrow.txt"

struct Book {
    int id;
    char title[100];
    char author[100];
    int available;
};

struct User {
    int id;
    char name[100];
};

void addBook();
void displayBooks();
void searchBook();
void registerUser();
int userExists(int userId);
void borrowBook();
void returnBook();

int main() {
    int choice;
    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Search Book\n");
        printf("4. Register User\n");
        printf("5. Borrow Book\n");
        printf("6. Return Book\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while(getchar()!='\n'); // flush input
            continue;
        }
        while(getchar()!='\n'); // clear newline

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: registerUser(); break;
            case 5: borrowBook(); break;
            case 6: returnBook(); break;
            case 7: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

void addBook() {
    struct Book b;
    printf("Enter Book ID: ");
    if (scanf("%d", &b.id) != 1) {
        printf("Invalid input for Book ID!\n");
        while(getchar()!='\n');
        return;
    }
    while(getchar()!='\n'); // flush newline

    // Check if the book already exists
    FILE *file = fopen(BOOKS_FILE, "r");
    if (file != NULL) {
        struct Book temp;
        while (fscanf(file, "%d|%99[^|]|%99[^|]|%d\n", &temp.id, temp.title, temp.author, &temp.available) == 4) {
            if (temp.id == b.id) {
                printf("A book with this ID already exists.\n");
                fclose(file);
                return;
            }
        }
        fclose(file);
    }
    
    printf("Enter Book Title: ");
    fgets(b.title, sizeof(b.title), stdin);
    b.title[strcspn(b.title, "\n")] = '\0';  // remove newline

    printf("Enter Author: ");
    fgets(b.author, sizeof(b.author), stdin);
    b.author[strcspn(b.author, "\n")] = '\0';  // remove newline

    b.available = 1;

    file = fopen(BOOKS_FILE, "a");
    if (!file) {
        perror("Error opening books file");
        return;
    }
    fprintf(file, "%d|%s|%s|%d\n", b.id, b.title, b.author, b.available);
    fclose(file);
    printf("Book added successfully!\n");
}

void displayBooks() {
    FILE *file = fopen(BOOKS_FILE, "r");
    if (!file) {
        printf("No books available!\n");
        return;
    }
    struct Book b;
    printf("\nBook List:\n");
    printf("ID | Title | Author | Available\n");
    while (fscanf(file, "%d|%99[^|]|%99[^|]|%d\n", &b.id, b.title, b.author, &b.available) == 4) {
        printf("%d | %s | %s | %s\n", b.id, b.title, b.author, b.available ? "Yes" : "No");
    }
    fclose(file);
}

void searchBook() {
    int id, found = 0;
    printf("Enter Book ID to search: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        while(getchar()!='\n');
        return;
    }
    while(getchar()!='\n');

    FILE *file = fopen(BOOKS_FILE, "r");
    if (!file) {
        printf("No books available!\n");
        return;
    }
    struct Book b;
    while (fscanf(file, "%d|%99[^|]|%99[^|]|%d\n", &b.id, b.title, b.author, &b.available) == 4) {
        if (b.id == id) {
            printf("Found: %s by %s (%s)\n", b.title, b.author, b.available ? "Available" : "Borrowed");
            found = 1;
            break;
        }
    }
    fclose(file);
    if (!found)
        printf("Book not found!\n");
}

void registerUser() {
    struct User u;
    printf("Enter User ID: ");
    if (scanf("%d", &u.id) != 1) {
        printf("Invalid input for User ID!\n");
        while(getchar()!='\n');
        return;
    }
    while(getchar()!='\n'); // flush newline

    // Check if user already exists
    FILE *file = fopen(USERS_FILE, "r");
    if (file != NULL) {
        struct User temp;
        while (fscanf(file, "%d|%99[^\n]\n", &temp.id, temp.name) == 2) {
            if (temp.id == u.id) {
                printf("A user with this ID already exists.\n");
                fclose(file);
                return;
            }
        }
        fclose(file);
    }

    printf("Enter User Name: ");
    fgets(u.name, sizeof(u.name), stdin);
    u.name[strcspn(u.name, "\n")] = '\0';

    file = fopen(USERS_FILE, "a");
    if (!file) {
        perror("Error opening users file");
        return;
    }
    fprintf(file, "%d|%s\n", u.id, u.name);
    fclose(file);
    printf("User registered successfully!\n");
}

int userExists(int userId) {
    FILE *file = fopen(USERS_FILE, "r");
    if (!file) {
        return 0;
    }
    struct User u;
    while (fscanf(file, "%d|%99[^\n]\n", &u.id, u.name) == 2) {
        if (u.id == userId) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void borrowBook() {
    int userId, bookId;
    printf("Enter your User ID: ");
    if (scanf("%d", &userId) != 1) {
        printf("Invalid input for User ID!\n");
        while(getchar()!='\n');
        return;
    }
    while(getchar()!='\n');
    if (!userExists(userId)) {
        printf("User not registered. Please register first.\n");
        return;
    }
    printf("Enter Book ID to borrow: ");
    if (scanf("%d", &bookId) != 1) {
        printf("Invalid input for Book ID!\n");
        while(getchar()!='\n');
        return;
    }
    while(getchar()!='\n');

    FILE *file = fopen(BOOKS_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!file || !temp) {
        perror("Error opening book file(s)");
        if (file) fclose(file);
        if (temp) fclose(temp);
        return;
    }

    int found = 0;
    struct Book b;
    while (fscanf(file, "%d|%99[^|]|%99[^|]|%d\n", &b.id, b.title, b.author, &b.available) == 4) {
        if (b.id == bookId) {
            if (b.available) {
                b.available = 0;
                found = 1;
                printf("Book borrowed successfully!\n");
                // Record the borrowing in BORROW_FILE
                FILE *borrowFile = fopen(BORROW_FILE, "a");
                if (borrowFile) {
                    fprintf(borrowFile, "%d|%d\n", userId, bookId);
                    fclose(borrowFile);
                }
            } else {
                printf("Book is currently not available!\n");
            }
        }
        fprintf(temp, "%d|%s|%s|%d\n", b.id, b.title, b.author, b.available);
    }
    fclose(file);
    fclose(temp);
    remove(BOOKS_FILE);
    rename("temp.txt", BOOKS_FILE);
    if (!found) {
        printf("Book not found or already borrowed!\n");
    }
}

void returnBook() {
    int userId, bookId;
    printf("Enter your User ID: ");
    if (scanf("%d", &userId) != 1) {
        printf("Invalid input for User ID!\n");
        while(getchar()!='\n');
        return;
    }
    while(getchar()!='\n');
    if (!userExists(userId)) {
        printf("User not registered.\n");
        return;
    }
    printf("Enter Book ID to return: ");
    if (scanf("%d", &bookId) != 1) {
        printf("Invalid input for Book ID!\n");
        while(getchar()!='\n');
        return;
    }
    while(getchar()!='\n');

    // Check if a borrowing record exists for this user and book
    FILE *borrowFile = fopen(BORROW_FILE, "r");
    if (!borrowFile) {
        printf("No borrowing records found.\n");
        return;
    }
    int recordFound = 0;
    char line[100];
    FILE *tempBorrow = fopen("temp_borrow.txt", "w");
    if (!tempBorrow) {
        perror("Error opening temporary borrow file");
        fclose(borrowFile);
        return;
    }
    while (fgets(line, sizeof(line), borrowFile)) {
        int uid, bid;
        if (sscanf(line, "%d|%d", &uid, &bid) == 2) {
            if (uid == userId && bid == bookId) {
                recordFound = 1;
                continue; // Skip this record to remove it
            }
        }
        fputs(line, tempBorrow);
    }
    fclose(borrowFile);
    fclose(tempBorrow);
    remove(BORROW_FILE);
    rename("temp_borrow.txt", BORROW_FILE);

    if (!recordFound) {
        printf("No borrowing record found for User ID %d and Book ID %d.\n", userId, bookId);
        return;
    }

    // Update the book's availability in BOOKS_FILE
    FILE *file = fopen(BOOKS_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!file || !temp) {
        perror("Error opening book file(s) for return operation");
        if (file) fclose(file);
        if (temp) fclose(temp);
        return;
    }
    struct Book b;
    int updated = 0;
    while (fscanf(file, "%d|%99[^|]|%99[^|]|%d\n", &b.id, b.title, b.author, &b.available) == 4) {
        if (b.id == bookId) {
            b.available = 1;
            updated = 1;
        }
        fprintf(temp, "%d|%s|%s|%d\n", b.id, b.title, b.author, b.available);
    }
    fclose(file);
    fclose(temp);
    remove(BOOKS_FILE);
    rename("temp.txt", BOOKS_FILE);

    if (updated) {
        printf("Book returned successfully!\n");
    } else {
        printf("Book record not found!\n");
    }
}

