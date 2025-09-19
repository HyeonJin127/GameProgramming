# 2주차

### 목차

01. [커서의 위치 제어](#01)
02. [화면 지우기](#02)
03. [ASCII Code & Scan Code](#03)
04. [사각형 그리기](#04)
  - [정사각형의 표현](#041)
  - [길이가 n인 표준 정사각형](#042)
05. [메뉴 만들기](#05)
06. [범위 내의 난수 생성](#06)
    - [주사위 눈금 난수 생성](#061)
    - [1부터 45 난수 생성](#062)
    - [1부터 45 중복 없는 난수 생성](#063)
      - [정렬 이용](#0631)
07. [가변인수](#07)
  - [가변 인수를 사용하는 함수의 기본 구조](#071)

-----

<h3 id='01'>커서의 위치 제어</h3>

- 커서의 위치를 제어하려면 함수 `gotoxy` 를 사용
```C
void gotoxy(int x, int y) {
  COORD Pos = {x - 1, y - 1};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
```
- [CursorPosition.c](CursorPosition.c)

- [CursorPosition2.c](CursorPosition2.c)

---

<h3 id='02'>화면 지우기</h3>

- 콘솔 창의 내용 삭제
- Visual C++
  ```C
  #include <stdlib.h>
  system("cls");
  ```
  
- Turbo C/C++
  ```C
  #include <conio.h>
  clrscr();
  ```

- [clrScreen.c](crlScreen.c) 

- [clrScreen2.c](crlScreen2.c)

---

<h3 id='03'>ASCII Code & Scan Code</h3>

- 아스키 코드 : 컴퓨터 내부에서 문자를 처리 (또는 전송) 하기 위한 일종의 규칙으로, 'a'라는 문자에 대해서 미리 약속한 코드 값을 의미
- 스캔 코드 : 각각의 키(key)에 대한 코드 값을 의미

- 일반적으로 스캔 코드는 확장키 코드를 말함.
- 2바이트로써 상위 바이트는 스캔 코드이고 하위 바이트는 아스키 코드로 구성.
- 확장키 코드란 1 byte 에 해당하는 256개의 아스키코드로 나타낼 수 없는 키를 말하며 화살표 키를 포함한 Home, End, Page Up, Page Down 등이 있다.

|코드|상위 1 byte|하위 1 byte|
|:---:|---:|---:|
|아스키 코드|0|스캔코드|
|확장 코드|스캔코드|0|

- [asciiORscan.c](asciiORscan.c)
  
- [moveArrowKey.c](moveArrowKey.c)

---

<h3 id='04'>사각형 그리기</h3>

<h3 id='041'>정사각형의 표현</h3>

<h3 id='042'>길이가 n인 표준 정사각형</h3>

---

<h3 id='05'>메뉴 만들기</h3>

---

<h3 id='06'>범위 내의 난수 생성</h3>

<h3 id='061'>주사위 눈금 난수 생성</h3>

<h3 id='062'>1부터 45 난수 생성</h3>

<h3 id='063'>1부터 45 중복없는 난수 생성</h3>

<h3 id='0631'>정렬하는 경우</h3>

---

<h3 id='07'>가변인수</h3>

<h3 id='071'>가변 인수를 사용하는 함수의 기본 구조</h3>

---
