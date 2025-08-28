#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id[10];
    char title[50];
    char author[50];
    float price;
    char category[30];
} Book;

Book *books = NULL;
int bookCount = 0;

void addBook();
void displayBooks();
void insertBookAtPosition();
void deleteBookById();
void updateBookById();
void sortBooksByPrice();
void searchBookByTitle();

int main() {
    int choice;
    do {
        printf("\nMENU:\n");
        printf("1. Nhap so luong va thong tin sach\n");
        printf("2. Hien thi thong tin sach\n");
        printf("3. Them sach vao vi tri\n");
        printf("4. Xoa sach them ma sach\n");
        printf("5. Cap nhat thong tin theo ma sach\n");
        printf("6. Sap xep theo gia (tang/giam)\n");
        printf("7. Tim kiem theo ten\n");
        printf("8. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: insertBookAtPosition(); break;
            case 4: deleteBookById(); break;
            case 5: updateBookById(); break;
            case 6: sortBooksByPrice(); break;
            case 7: searchBookByTitle(); break;
            case 8: printf("Thoat chuong trinh"); break;
            default: printf("Lua chon khong phu hop\n"); break;
        }
    } while (choice != 8);

    free(books);
    return 0;
}

void addBook() {
    books = realloc(books, (bookCount + 1) * sizeof(Book));
    
    printf("Nhap ma sach: "); scanf("%s", books[bookCount].id);
    printf("Nhap ten sach: "); scanf(" %[^\n]", books[bookCount].title);
    printf("Nhap tac gia: "); scanf(" %[^\n]", books[bookCount].author);
    printf("Nhap gia tien: "); scanf("%f", &books[bookCount].price);
    printf("Nhap the loai: "); scanf(" %[^\n]", books[bookCount].category);
    
    bookCount++;
}

void displayBooks() {
    if (bookCount == 0) {
        printf("Danh sach sach trong\n");
        return;
    }
    for (int i = 0; i < bookCount; i++) {
        printf("Ma sach: %s, Ten sach: %s, Tac gia: %s, Gia: %.2f, The loai: %s\n",
               books[i].id, books[i].title, books[i].author, books[i].price, books[i].category);
    }
}

void insertBookAtPosition() {
    int position;
    printf("Nhap vi tri can them sach (0-%d): ", bookCount);
    scanf("%d", &position);

    if (position < 0 || position > bookCount) {
        printf("Vi tri ko phu hop\n");
        return;
    }

    books = realloc(books, (bookCount + 1) * sizeof(Book));

    for (int i = bookCount; i > position; i--) {
        books[i] = books[i - 1];
    }

    printf("Nhap ma sach: "); scanf("%s", books[position].id);
    printf("Nhap ten sach: "); scanf(" %[^\n]", books[position].title);
    printf("Nhap tac gia: "); scanf(" %[^\n]", books[position].author);
    printf("Nhap gia tien: "); scanf("%f", &books[position].price);
    printf("Nhap the loai: "); scanf(" %[^\n]", books[position].category);
    
    bookCount++;
}

void deleteBookById() {
    char id[10];
    printf("Nhap ma sach can xoa: ");
    scanf("%s", id);
    
    int index = -1;
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].id, id) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Khong tim thay sach\n");
        return;
    }

    for (int i = index; i < bookCount - 1; i++) {
        books[i] = books[i + 1];
    }
    
    books = realloc(books, (bookCount - 1) * sizeof(Book));
    bookCount--;
    printf("Sach da xoa\n");
}

void updateBookById() {
    char id[10];
    printf("Nhap ma sach can cap nhat: ");
    scanf("%s", id);

    int index = -1;
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].id, id) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Ko tim thay\n");
        return;
    }

    printf("Nhap ten moi: "); scanf(" %[^\n]", books[index].title);
    printf("Nhap tac gia moi: "); scanf(" %[^\n]", books[index].author);
    printf("Nhap gia moi: "); scanf("%f", &books[index].price);
    printf("Nhap the loai moi: "); scanf(" %[^\n]", books[index].category);
    
    printf("Cap nhat thanh cong\n");
}

void sortBooksByPrice() {
    int ascending;
    printf("Sap xep theo gia tang hoac giam (1 la tang, 0 la giam) ");
    scanf("%d", &ascending);

    for (int i = 0; i < bookCount - 1; i++) {
        for (int j = i + 1; j < bookCount; j++) {
            if ((ascending && books[i].price > books[j].price) ||
                (!ascending && books[i].price < books[j].price)) {
                Book temp = books[i];
                books[i] = books[j];
                books[j] = temp;
            }
        }
    }
    printf("Da sap xep\n");
}

void searchBookByTitle() {
    char title[50];
    printf("Nhap ten sach can tim: ");
    scanf(" %[^\n]", title);

    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strstr(books[i].title, title) != NULL) {
            printf("Ma sach: %s, Ten sach: %s, Tac gia: %s, Gia: %.2f, The loai: %s\n",
                   books[i].id, books[i].title, books[i].author, books[i].price, books[i].category);
            found = 1;
        }
    }

    if (!found) {
        printf("Khong tim thay sach\n");
    }
}
