#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int ID;
    char name[20];
    float avg;
    int status;
} student;

typedef struct node {
    student data;
    struct node *next;
    struct node *prev;
} node;

student students[100];
int count = 0;
node *Head = NULL;

void addstudent() {
    if (count >= 100) {
        printf("Danh sach đay.\n");
        return;
    }
    student s;
    printf("Nhap ID: ");
    scanf("%d", &s.ID);
    getchar();

    printf("Nhap ten: ");
    fgets(s.name, 20, stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("Nhập AVG: ");
    scanf("%f", &s.avg);
    s.status = 1;

    students[count++] = s;
    printf("Them thanh cong.\n");
}

void showstudent() {
    if (count == 0) {
        printf("Danh sách rỗng.\n");
        return;
    }
    printf("======= DANH SACH SINH VIEN =======\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d | Tên: %s | AVG: %.2f | Trạng thái: %s\n",
               students[i].ID,
               students[i].name,
               students[i].avg,
               students[i].status ? "Hoat động" : "Khong hoat đong");
    }
}

void deletestudent() {
    int id;
    printf("Nhap ID can xoa: ");
    scanf("%d", &id);
    for (int i = 0; i < count; i++) {
        if (students[i].ID == id) {
            for (int j = i; j < count - 1; j++) {
                students[j] = students[j + 1];
            }
            count--;
            printf("Xoa thanh cong.\n");
            return;
        }
    }
    printf("khong tim thay sinh vien.\n");
}

void updatestudent() {
    int id;
    printf("Nhap ID can cap nhat: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < count; i++) {
        if (students[i].ID == id) {
            printf("Nhap ten moi: ");
            fgets(students[i].name, 20, stdin);
            students[i].name[strcspn(students[i].name, "\n")] = '\0';

            printf("Nhập AVG mới: ");
            scanf("%f", &students[i].avg);
            printf("Cap nhat thanh cong.\n");
            return;
        }
    }
    printf("Khong tìm thay sinh vien.\n");
}

void apptoinactivelist(student s) {
    node *newnode = (node *)malloc(sizeof(node));
    if (!newnode) {
        printf("Không cấp phát được bộ nhớ.\n");
        return;
    }
    newnode->data = s;
    newnode->next = Head;
    newnode->prev = NULL;
    if (Head != NULL)
        Head->prev = newnode;
    Head = newnode;
}

void changestudent() {
    int id;
    printf("Nhập ID muốn thay đổi trạng thái: ");
    scanf("%d", &id);
    for (int i = 0; i < count; i++) {
        if (students[i].ID == id) {
            if (students[i].status == 1) {
                students[i].status = 0;
                apptoinactivelist(students[i]);
                printf("da chuyen trang thai khong hoat dong.\n");
            } else {
                students[i].status = 1;
                printf("da chuyen trang thai  hoat dong.\n");
            }
            return;
        }
    }
    printf("Khong tìm thấy sinh viên.\n");
}

void merge(student arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    student *L = (student *)malloc(n1 * sizeof(student));
    student *R = (student *)malloc(n2 * sizeof(student));

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].avg <= R[j].avg)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergesort(student arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergesort(arr, l, m);
        mergesort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void sortstudent() {
    if (count == 0) {
        printf("Danh sách rỗng.\n");
        return;
    }
    mergesort(students, 0, count - 1);
    printf("Sắp xếp theo AVG tăng dần.\n");
}

void seachstudent() {
    if (count == 0) {
        printf("Danh sách rỗng.\n");
        return;
    }
    int target;
    printf("Nhập ID cần tìm: ");
    scanf("%d", &target);

    int left = 0, right = count - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (students[mid].ID == target) {
            printf("Tim thay sinh vien: ID: %d | Ten: %s | AVG: %.2f\n",
                   students[mid].ID,
                   students[mid].name,
                   students[mid].avg);
            return;
        } else if (students[mid].ID < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    printf("Khong tim thay sinh vien có ID = %d\n", target);
}

void showstudenthead() {
    node *current = Head;
    if (!current) {
        printf("Danh sách sinh viên không hoạt động rỗng.\n");
        return;
    }
    printf("======= SINH VIEN KHONG HOAT DONG =======\n");
    while (current != NULL) {
        student s = current->data;
        printf("ID: %d | Tên: %s | AVG: %.2f\n", s.ID, s.name, s.avg);
        current = current->next;
    }
}

int main(void) {
    int choice;
    do {
        printf("\n=========STUDENT MANAGER ========\n");
        printf("1. Them sinh vien\n");
        printf("2. Hien thi danh sach sinh vien\n");
        printf("3. Xoa sinh vien\n");
        printf("4. Cap nhat thong tin sinh vien\n");
        printf("5. Thay doi trang thai sinh vien\n");
        printf("6. Sap xep sinh vien\n");
        printf("7. Tim kiem sinh vien\n");
        printf("8. Thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addstudent();
                break;
            case 2:
                showstudent();
                break;
            case 3:
                deletestudent();
                break;
            case 4:
                updatestudent();
                break;
            case 5:
                changestudent();
                break;
            case 6:
                sortstudent();
                break;
            case 7:
                seachstudent();
                break;

            case 8:
                printf("Ket thuc chuong trinh\n");
                break;
            default:
                printf("lua chon khong hop le.\n");
        }
    } while (choice != 8);

    return 0;
}
