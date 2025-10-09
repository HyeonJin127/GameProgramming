// 숫자를 입력받아 낮은 자리부터 순서대로 출력

#include <stdio.h>
#include <string.h>

int main() {
    char number[20];
    int length, i;

    printf("금액을 입력하고 Enter");
    scanf("%s", number);
    
    length = strlen(number);

    for (i = length; i >= 0; i--) {
        printf("%c\n", number[i]);
    }

    return 0;
}