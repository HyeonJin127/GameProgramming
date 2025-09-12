#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int menu_display(void);
int sub_menu_display01(void);
int sub_menu_display02(void);
void sub_main01(void);
void sub_main02(void);

void chicken_sandwich(void);
void cheese_burger(void);
void tomato_spaghetti(void);
void cream_spaghetti(void);
void press_any_key(void);

int main(void) {
    int c;
    while((c = menu_display()) != 3) {
        switch(c) {
            case 1: sub_main01(); break;
            case 2: sub_main02(); break;
            default: break;
        }
    }

    return 0;
}

int menu_display(void) {
    int select;
    system("cls");
    printf("Make dish\n\n");
    printf("1. Hamburger\n");
    printf("2. Spaghetti\n");
    printf("3. Close Program\n");
    printf("Enter number of menu");
    
    select = getch() - 48;
    return select;
}

void sub_main01(void) {
    int c;
    while((c = sub_menu_display01()) != 3) {
        switch(c) {
            case 1: chicken_sandwich(); break;
            case 2: cheese_burger(); break;
            default: break;
        }
    }
}

int sub_menu_display01(void) {
    int select;
    system("cls");
    printf("Make dish\n\n");
    printf("1. Chicken Sandwich\n");
    printf("2. Cheese Burger\n");
    printf("3. Go to Main menu\n");
    printf("Enter number of menu");
    
    select = getch() - 48;
    return select;
}

void chicken_sandwich(void) {
    system("cls");
    printf("How to make Chicken Sandwich");
    printf("~~");
    press_any_key();
}

void cheese_burger(void) {
    system("cls");
    printf("How to make Cheese Burger");
    printf("~~");
    press_any_key();
}

void sub_main02(void) {
    int c;
    while((c = sub_menu_display02()) != 3) {
        switch(c) {
            case 1: tomato_spaghetti(); break;
            case 2: cream_spaghetti(); break;
            default: break;
        }
    }
}

int sub_menu_display02(void) {
    int select;
    system("cls");
    printf("Make dish\n\n");
    printf("1. Tomato Spaghetti\n");
    printf("2. Cream Spaghetti\n");
    printf("3. Go to Main menu\n");
    printf("Enter number of menu");
    
    select = getch() - 48;
    return select;
}

void tomato_spaghetti(void) {
    system("cls");
    printf("How to make Tomato Spaghetti");
    printf("~~");
    press_any_key();
}

void cream_spaghetti(void) {
    system("cls");
    printf("How to make Cream Spaghetti");
    printf("~~");
    press_any_key();
}

void press_any_key(void) {
    printf("\n\n");
    printf("Press any key to Previos menu");
    getch();
}