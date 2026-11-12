#include <stdio.h>
#include <string.h>

#define EMP_FILE "employee.bin"
#define EMP_COUNT 3
#define EMP_MAX 10

typedef struct employee {
    int id;
    char name[12];
    int age;
    float salary;
} employee_t;

void emp_info(employee_t emp) {
    printf("employee id = %d\n", emp.id);
    printf("employee name = %s\n", emp.name);
    printf("employee age = %d\n", emp.age);
    printf("employee salary = %f\n\n", emp.salary);
}

int emp_average_age(employee_t emp[], int n) {
    int sum = 0;

    if (n <= 0) {
        return 0;
    }
    for (int i = 0; i < n; i++) {
        sum += emp[i].age;
    }
    return sum / n;
}

void emp_writefile(employee_t emp[], int n) {
    FILE *fp = fopen(EMP_FILE, "wb+");

    if (fp == NULL) {
        printf("Cannot open %s for writing\n", EMP_FILE);
        return;
    }
    for (int i = 0; i < n; i++) {
        fwrite(&emp[i], sizeof(employee_t), 1, fp);
    }
    fclose(fp);
}

int emp_readfile(employee_t emp[], int n) {
    FILE *fp = fopen(EMP_FILE, "rb");
    int i = 0;

    if (fp == NULL) {
        printf("Cannot open %s for reading\n", EMP_FILE);
        return 0;
    }
    while (i < n && fread(&emp[i], sizeof(employee_t), 1, fp) == 1) {
        printf("[%d] %d %s\n", i, emp[i].id, emp[i].name);
        i++;
    }
    fclose(fp);
    return i;
}

int main() {
    employee_t emp[EMP_COUNT];
    employee_t read_emp[EMP_MAX];
    int count;

    emp[0].id = 1;
    emp[0].age = 20;
    emp[0].salary = 30000.0;
    strcpy(emp[0].name, "IU");

    emp[1].id = 2;
    emp[1].age = 26;
    emp[1].salary = 36000.0;
    strcpy(emp[1].name, "taylor");

    emp[2].id = 3;
    emp[2].age = 31;
    emp[2].salary = 90000.0;
    strcpy(emp[2].name, "swift");

    printf("Average age: %d\n\n", emp_average_age(emp, EMP_COUNT));

    emp_writefile(emp, EMP_COUNT);
    count = emp_readfile(read_emp, EMP_MAX);

    for (int i = 0; i < count; i++) {
        emp_info(read_emp[i]);
    }
    return 0;
}
