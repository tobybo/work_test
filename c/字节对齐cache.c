#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 1000000

struct student {
    char name[10];
    int age;
    char gender;
};

int main() {
    struct student *students = malloc(sizeof(struct student) * ARRAY_SIZE);
    int i;

    // 随机生成学生数据
    srand(time(NULL));
    for (i = 0; i < ARRAY_SIZE; i++) {
        students[i].age = rand() % 100;
        students[i].gender = rand() % 2 ? 'M' : 'F';
    }

    // 计算不对齐时的访问时间
    clock_t start = clock();
    long long sum = 0;
    for (i = 0; i < ARRAY_SIZE; i++) {
        sum += students[i].age;
    }
    clock_t end = clock();
    printf("sum: %lld, time: %ld\n", sum, end - start);

    // 计算对齐时的访问时间
    start = clock();
    sum = 0;
    for (i = 0; i < ARRAY_SIZE; i++) {
        sum += ((int *)(&students[i]))[1];
    }
    end = clock();
    printf("sum: %lld, time: %ld\n", sum, end - start);

    free(students);
    return 0;
}
