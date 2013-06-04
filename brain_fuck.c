#include<stdio.h>
#include<string.h>

#define MAX_MEM_SIZE 30000

int evalInstruction(char*, int, char**);
char* strrnchr(char*, int, char);


int main(void) {
    /* Hello World ! */
    char instructions[] = "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.";
    /* char instructions[] = "++[>+[>++[>]]]"; */
    int i, instructions_size = strlen(instructions);
    char mem[MAX_MEM_SIZE] = {0}, *dataPtr = mem;

    evalInstruction(instructions, instructions_size, &dataPtr);

    return 0;
}


/* 指定したサイズ直前の指定文字を見つける */
char* strrnchr(char* str, int size, char ch){
    int i;
    char* detectPos = NULL;

    for (i = 0; i < size; ++i) {
        if (str[i] == ch) {
            detectPos = str + i;
        }
    }

    return detectPos;
}


int evalInstruction(char* instructions, int instructions_size, char** dataPtr){
    int i, betweenParenSize = 0;

    for (i = 0; i < instructions_size; ++i) {
        switch (instructions[i]) {
            case '>':
                ++(*dataPtr);
                break;
            case '<':
                --(*dataPtr);
                break;
            case '+':
                ++(**dataPtr);
                break;
            case '-':
                --(**dataPtr);
                break;
            case '.':
                putchar(**dataPtr);
                break;
            case ',':
                **dataPtr = getchar();
                break;
            case '[':
                // 対になる']'までのサイズ
                betweenParenSize = strrnchr(instructions, instructions_size, ']') - (instructions + i);

                // 0でないのでループ
                if (**dataPtr != 0) {
                    /* '[]'の内部を抜き出して再帰評価させる */
                    while (0 != evalInstruction(instructions + i + 1, betweenParenSize - 1, dataPtr)){}
                }

                // '[]'内の処理をしたのでずらす
                i += betweenParenSize;

                break;
        }
    }

    // ']' の判別用
    return **dataPtr;
}
