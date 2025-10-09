// 텍스트 모드 테트리스 게임

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

int game_board[BOARD_HEIGHT][BOARD_WIDTH];

int score = 0;
int level = 1;

// 테트로미노 도형 정의
int shapes[7][4][4] = {
    
    // 0: I 모양 (파란색)
    {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    // 1: O 모양 (노란색)
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    },

    // 2: T 모양 (보라색)
    {
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0}
    },

    // 3: J 모양 (어두운 파랑)
    {
        {0, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0}
    },

    // 4: L 모양 (주황색)
    {
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0}
    },

    // 5: S 모양 (녹색)
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}
    },

    // 6: Z 모양 (빨간색)
    {
        {0, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    }
};

// 현재 블록 상태 구조체 정의
typedef struct {
    int x;
    int y;
    int shape_index;
    int shape[4][4];
} Piece;

Piece current_piece;
Piece next_piece;

void initialize_board();
void draw_board();
void merge_piece();
bool check_collision(int new_x, int new_y, int new_shape[4][4]);
void create_new_piece();
void draw_next_piece();
bool move_piece(int dx, int dy);
void rotate_piece();
void handle_input();
int clear_lines();

// main 함수
int main() {

    srand(time(NULL)); // 난수 생성기 초기화 (블록 모양을 무작위로 선택)
    
    initialize_board();

    // 새로운 블록 생성
    create_new_piece(); // next_piece 생성
    create_new_piece(); // next_piece를 current_piece 로 옮기고, 새로운 next_piece 생성

    int fall_timer = 0; // 한 칸 내려가기까지 타이머
    const int FALL_SPEED = 10; // 한 칸 내려가기까지 시간

    while (1) {
        handle_input();

        if (++fall_timer >= FALL_SPEED) {

            if (!move_piece(0, 1)) {
                merge_piece();

                clear_lines();

                create_new_piece();
                // printf("\n\n블록이 고정되었습니다. (현재는 게임 종료)\n");
                // return 0;
            }

            fall_timer = 0;
        }

        // 게임 판 출력
        draw_board();    
        Sleep(50);
    }

    return 0;
}

// board 초기화 함수
void initialize_board() {
    int x, y;
    for (y = 0; y < BOARD_HEIGHT; y++) {
        for (x = 0; x < BOARD_WIDTH; x++) {
            game_board[y][x] = 0; // 모든 칸을 0(빈 공간)으로 초기화
        }
    }
}

// board 출력 함수
void draw_board() {
    int i, x, y, px, py;

    // 깔끔한 출력을 위한 콘솔 화면 지우기
    system("cls");

    printf("\n"); // 화면을 구분하기 위한 줄바꿈

    draw_next_piece();

    // 1. 위쪽 경계 출력
    printf("┌");
    for (i = 0; i < BOARD_WIDTH; i++) {
        printf("─┬");
    }
    printf("\n");

    // 2. 게임 판 내용 출력
    for (y = 0; y < BOARD_HEIGHT; y++) {
        printf("│"); // 왼쪽 경계
        for (x = 0; x < BOARD_WIDTH; x++) {

            // 2-1. 현재 블록이 이 위치에 있는지 확인
            int is_current_piece = 0;
            // 현재 블록의 4x4 영역을 순회
            for (py = 0; py < 4; py++) {
                for (px = 0; px < 4; px++) {
                    // 블록을 구성하는 칸이면서, 게임 판 좌표와 일치하는지 확인
                    if (current_piece.shape[py][px] == 1 &&
                        (current_piece.y + py) == y &&
                        (current_piece.x + px) == x) {
                            is_current_piece = 1;
                            break; // 블록을 찾았으니 내부 루프 종료
                    }
                }
                if (is_current_piece) break; // 외부 루프 종료
            }

            // 2-2. 출력 결정
            if (is_current_piece) {
                printf("@"); // 현재 떨어지는 블록은 '@'로 표시
            } else if (game_board[y][x] != 0) {
                printf("#"); // 이미 고정된 블록은 '#' 로 표시
            } else {
                printf(" "); // 빈 공간
            }

            // 칸 구분자 출력
            printf("│");
        }
        printf("\n"); // 오른쪽 경계

        if (y < BOARD_HEIGHT - 1) {
            printf("├");
            for (i = 0; i < BOARD_WIDTH; i++) {
                printf("─┤"); // ?? 중간 가로선에 교차점(+) 추가
            }
            printf("\n");
        }
    }

    // 3. 아래쪽 경계 출력
    printf("└");
    for (i = 0; i < BOARD_WIDTH; i++) {
        printf("─┴");
    }
    printf("\n");

}

// 현재 블록을 메인 게임 판에 병합(고정)합니다.
void merge_piece() {
    int x, y;
    // 현재 블록의 4x4 배열을 순회합니다.
    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            
            // 1. 현재 4x4 칸이 실제로 블록의 일부라면 (값이 1)
            if (current_piece.shape[y][x] == 1) {
                
                // 2. 게임 판에서의 실제 좌표 계산
                int board_x = current_piece.x + x;
                int board_y = current_piece.y + y;

                // 3. 계산된 좌표에 블록의 종류를 기록 (고정)
                // - game_board[y][x] = 0 (빈 공간)
                // - game_board[y][x] = 1, 2, 3... (고정된 블록)
                
                // ?? 주의: 게임 판 경계를 벗어나는 칸은 무시
                if (board_y >= 0 && board_y < BOARD_HEIGHT && 
                    board_x >= 0 && board_x < BOARD_WIDTH) 
                {
                    // 블록 종류를 기록합니다. (shapes_index + 1을 사용해 1~7 사이의 값 사용)
                    game_board[board_y][board_x] = current_piece.shape_index + 1;
                }
            }
        }
    }
}

// 충돌 감지 함수
bool check_collision(int new_x, int new_y, int new_shape[4][4]) {
    int x, y;

    // 4x4 블록의 모든 구성 요소를 순회합니다.
    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            
            // 1. 현재 4x4 블록의 이 셀이 실제로 블록의 일부인지 확인
            if (new_shape[y][x] == 1) {
                
                // 2. 게임 판에서의 실제 좌표 계산
                int board_x = new_x + x;
                int board_y = new_y + y;

                // --- 3. 경계 충돌 검사 (벽 또는 바닥) ---

                // a) 좌우 벽 충돌 검사
                if (board_x < 0 || board_x >= BOARD_WIDTH || board_y >= BOARD_HEIGHT) {
                    return true; // 충돌 발생
                }
                
                // b) 바닥 충돌 검사
                // (윗부분은 블록이 생성되는 공간이므로 보통 0 미만은 체크하지 않습니다.)
                if (board_y >= BOARD_HEIGHT && game_board[board_y][board_x] != 0) {
                    return true; // 충돌 발생
                }

                // --- 4. 고정된 블록과의 충돌 검사 ---
                
                // c) 게임 판 내부에 있고 (0 <= board_y < BOARD_HEIGHT) 
                //    이미 고정된 다른 블록이 있는지 확인 (game_board[y][x] != 0)
                
                if (board_y >= 0 && game_board[board_y][board_x] != 0) {
                    return true; // 충돌 발생
                }
            }
        }
    }
    
    // 위의 모든 검사를 통과했다면 충돌 없음
    return false;
}

// 새로운 블록 생성 함수
// 새로운 블록을 생성하고 교체하는 함수
void create_new_piece() {
    int i, j;
    
    // 1. 현재 next_piece를 current_piece로 교체합니다.
    // ----------------------------------------------------
    
    // (a) next_piece의 모양과 종류를 current_piece로 복사
    current_piece.shape_index = next_piece.shape_index;
    memcpy(current_piece.shape, next_piece.shape, sizeof(next_piece.shape));
    
    // (b) current_piece의 위치를 게임 판 상단 중앙으로 설정
    current_piece.x = (BOARD_WIDTH / 2) - 2;
    current_piece.y = 0; // 맨 위에서 시작

    // 2. 새로운 next_piece를 생성합니다.
    // ----------------------------------------------------
    
    // (a) 무작위로 모양 선택
    int new_index = rand() % 7;
    next_piece.shape_index = new_index;

    // (b) next_piece의 위치는 0으로 초기화 (출력 전용)
    next_piece.x = 0; 
    next_piece.y = 0;
    
    // (c) ? 새로운 next_piece의 모양을 배열에 복사합니다. (누락된 부분)
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            next_piece.shape[i][j] = shapes[new_index][i][j];
        }
    }
    
    // 3. 게임 오버 감지
    // ----------------------------------------------------
    if (check_collision(current_piece.x, current_piece.y, current_piece.shape)) {
        printf("\n\n*************************\n");
        printf("       G A M E   O V E R       \n");
        printf("*************************\n");
        exit(0); 
    }
}

void draw_next_piece() {
	int x, y;
    printf("\nNEXT PIECE:\n");
    // next_piece의 4x4 배열을 출력
    for (y = 0; y < 4; y++) {
        printf("    ");
        for (x = 0; x < 4; x++) {
            if (next_piece.shape[y][x] == 1) {
                printf("@");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

// 블록 이동 함수 (좌우/하)
// 블록을 주어진 방향(dx, dy)으로 이동시키려고 시도합니다.
// 성공하면 true, 실패(충돌)하면 false를 반환합니다.
bool move_piece(int dx, int dy) {
    int new_x = current_piece.x + dx;
    int new_y = current_piece.y + dy;

    // 새로운 위치에서 충돌 검사
    if (!check_collision(new_x, new_y, current_piece.shape)) {
        // 충돌이 없으면 위치 업데이트
        current_piece.x = new_x;
        current_piece.y = new_y;
        return true; // 이동 성공
    }
    return false; // 이동 실패 (충돌)
}

// 블록 회전 함수
void rotate_piece() {
    int x, y;

    // 1. 회전된 모양을 임시로 저장할 4x4 배열 (충돌 검사용)
    int temp_shape[4][4];

    // 2. 현재 블록 모양을 시계 방향으로 90도 변환하여 temp_shape에 저장
    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            // 변환된 데이터: current_piece.shape[y][x]
            // 새로운 위치: temp_shape[x][3 - y]
            
            temp_shape[x][3 - y] = current_piece.shape[y][x]; 
        }
    }
    
    // 3. 임시 모양으로 충돌 검사
    // 회전 후 새로운 위치(x, y)에서도 벽이나 다른 블록과 겹치는지 확인합니다.
    if (!check_collision(current_piece.x, current_piece.y, temp_shape)) {
        // 충돌이 없으면 회전 확정: 현재 블록의 모양(current_piece.shape)을 
        //                           임시 배열(temp_shape)의 데이터로 업데이트합니다.
        for (y = 0; y < 4; y++) {
            for (x = 0; x < 4; x++) {
                current_piece.shape[y][x] = temp_shape[y][x];
            }
        }
    }
    // 충돌이 있으면 회전하지 않고 함수를 종료합니다.
}

// 키보드 입력 및 게임 루프 기본 구조
void handle_input() {
    if (_kbhit()) {
        char key = _getch();

        switch (key) {
            case 'a': // 왼쪽(-1, 0) 이동
            case 'A':
            case 75:
                move_piece(-1, 0); // 왼쪽 이동 로직 호출
                break;
            case 'd': // 오른쪽(1, 0) 이동
            case 'D':
            case 77:
                move_piece(1, 0); // 오른쪽 이동 로직 호출
                break;
            case 's': // 아래쪽(0, +1) 이동 / 소프트 드롭 (바로 아래로 한 칸)
            case 'S':
            case 80:
                move_piece(0, 1); // 아래 이동 로직 호출
                break;
            case 'w': // 회전
            case 'W':
            case 72:
                rotate_piece(); // 회전 로직 호출
                break;
            case 'q': // 게임 종료
            case 'Q':
                exit(0);
        }
    }
}

// 꽉 찬 줄을 찾아 제거하고 점수를 업데이트하는 함수
int clear_lines() {
	int x, y, k;
    int lines_cleared = 0; // 제거된 줄 수를 카운트
    
    // 게임 판을 아래쪽(BOARD_HEIGHT - 1)부터 위쪽(0)으로 순회합니다.
    for (y = BOARD_HEIGHT - 1; y >= 0; y--) {
        int is_line_full = 1; // 현재 줄이 꽉 찼는지(1) 아닌지(0)를 나타내는 플래그

        // 현재 행(y)의 모든 열을 검사합니다.
        for (x = 0; x < BOARD_WIDTH; x++) {
            // 빈 공간(0)이 하나라도 있다면, 이 줄은 꽉 찬 줄이 아닙니다.
            if (game_board[y][x] == 0) {
                is_line_full = 0;
                break;
            }
        }

        // 1. 줄이 꽉 찼을 경우
        if (is_line_full) {
            lines_cleared++;
            
            // 2. 현재 줄(y)을 제거하고, 그 위의 모든 줄을 한 칸씩 아래로 내립니다.
            // y-1 행부터 0 행까지 위로 순회합니다.
            for (k = y; k > 0; k--) {
                // k 행을 k-1 행의 내용으로 덮어씁니다.
                for (x = 0; x < BOARD_WIDTH; x++) {
                    game_board[k][x] = game_board[k - 1][x];
                }
            }

            // 가장 위쪽 행(0행)을 비웁니다.
            for (x = 0; x < BOARD_WIDTH; x++) {
                game_board[0][x] = 0;
            }

            // 3. 줄이 제거되었으므로, 같은 높이(y)를 다시 검사해야 합니다.
            //    (새로운 행이 이 위치로 내려왔기 때문)
            y++; 
        }
    }

    // 4. 점수 계산 (간단한 버전)
    if (lines_cleared > 0) {
        printf("\n\n? %d줄이 제거되었습니다! ?\n", lines_cleared);
        // 여기에 실제로 점수를 더하는 로직을 추가해야 합니다.
    }
    
    return lines_cleared;
}
