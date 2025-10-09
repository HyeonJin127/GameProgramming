// 재귀 호출로 각 자리 숫자 출력

#include <stdio.h>
#include <string.h>

void serial_number(n);
void reverse_number(n);

int main() {
    char number[20];
    int length, i;

    printf("숫자를 입력하고 Enter");
    scanf("%s", number);

    printf("높은 자리 숫자부터 출력");
    serial_number(number);

    printf("낮은 자리 숫자부터 출력");
    serial_number(number);

    printf("press any key to continue");
    getch();
    return 0;
}

void serial_number(n) {
    if (n > 0) {
        serial_number(n/10);
        printf("%ld\n", n%10);
    }
    else
        return;
}

void reverse_number(n) {
    printf("%ld\n", n/10);

    if (n > 0) {
        serial_number(n%10);
    }
    else
        return;
}