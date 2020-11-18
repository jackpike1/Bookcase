#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define MAX 9

enum bool {false, true};
typedef enum bool bool;

struct bookcase {
    char board[MAX][MAX];
    int parent;
};

typedef struct bookcase Bookcase;

/* Function to test if bookcase is happy*/
bool is_happy(char array[MAX][MAX]);

/* Function to determine if a row is happy*/
bool is_row_happy(char array[MAX][MAX], int row); 

/* Function to check whether letter is valid*/
bool is_valid_letter(char a);

/*Function to check whether there is space in the row*/
bool is_space(char array[MAX][MAX], int row);

/*Function to check whether a row is empty*/
bool is_row_empty(char array[MAX][MAX], int row);

/* Function used for testing*/
bool test_strings(char array[MAX][MAX], int row, char str[10]);

void test(void);

int main(void) {

    test();

    return 0;
}

void test(void) {

    char test_case[MAX][MAX] = {{'.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                {'.', '.', '.', '.', '.', '.', '.', '.', '.'}};
    char test_case2[MAX][MAX];
    int i;


    /*Test is_row_empty funtion*/
    for (i = 0; i < MAX; i++) {
        assert(is_row_empty(test_case, i));
        assert(test_strings(test_case, i, "........."));
    }

    test_case[5][1] = 'R';
    test_case[0][1] = 'Y';
    test_case[8][3] = 'R';
    assert(!is_row_empty(test_case, 5));
    assert(!is_row_empty(test_case, 0));
    assert(!is_row_empty(test_case, 8));
    assert(is_row_empty(test_case, 6));
    test_case[5][1] = '.';
    test_case[0][1] = '.';
    test_case[8][3] = '.';
    assert(is_row_empty(test_case, 5));
    assert(is_row_empty(test_case, 0));
    assert(is_row_empty(test_case, 8));

    assert(!is_row_empty(test_case2, 8));
    assert(!is_row_empty(test_case2, 3));

    /*Test is_space function*/
    for (i = 0; i < MAX; i++) {
        assert(is_space(test_case, i));
    }

    test_case[0][8] = 'R';
    test_case[1][8] = 'R';
    test_case[5][5] = 'R';
    test_case[8][8] = '$';
    assert(!is_space(test_case, 0));
    assert(!is_space(test_case, 1));
    assert(is_space(test_case, 5));
    assert(!is_space(test_case, 8));
    test_case[0][8] = '.';
    test_case[1][8] = '.';
    test_case[5][5] = '.';
    test_case[8][8] = '.';
    assert(is_space(test_case, 0));
    assert(is_space(test_case, 1));
    assert(is_space(test_case, 5));
    assert(is_space(test_case, 8));
    
    assert(!is_space(test_case2, 8));
    assert(!is_space(test_case2, 3));

    /* Test is_valid_letter function*/
    assert(is_valid_letter('B'));
    assert(is_valid_letter('K'));
    assert(is_valid_letter('C'));
    assert(is_valid_letter('W'));
    
    assert(!is_valid_letter('.'));

    /*Test is_row_happy function*/
    for (i = 0; i < MAX; i++) {
        assert(is_row_happy(test_case, i));
    }
    
    test_case[0][0] = 'R';
    test_case[0][1] = 'R';
    test_case[0][2] = 'R';
    assert(is_row_happy(test_case, 0));
    test_case[0][1] = 'Y';
    assert(!is_row_happy(test_case, 0));
    test_case[0][1] = '.';
    assert(is_row_happy(test_case, 0));
    test_case[0][0] = '.';
    assert(is_row_happy(test_case, 0));
    test_case[0][2] = '.';
    assert(is_row_happy(test_case, 0));

    /*Test if is_happy function*/
    assert(is_happy(test_case));
    test_case[8][8] = 'Y';
    test_case[8][7] = 'Y';
    assert(is_happy(test_case));
    test_case[8][6] = 'B';
    assert(!is_happy(test_case));

    for (i = 0; i < MAX; i++) {
        test_case[3][i] = 'C';
    }

    assert(!is_happy(test_case));

    test_case[8][6] = '.';
    assert(is_happy(test_case));
    
    for (i = 0; i < MAX; i++) {
        test_case[3][i] = '.';
    }
    assert(is_happy(test_case));

}

bool is_happy(char array[MAX][MAX]) {

    int y = 0;

    while (y != MAX) {
        if (!is_row_happy(array, y)) {
            return false;
        }
        y++;
    }

    return true;
}

bool is_row_happy(char array[MAX][MAX], int row) {

    int i, j;

    for (i = 0; i < MAX; i++) {
        for (j = i+1; j < MAX; j++) {

            if (is_valid_letter(array[row][i]) && is_valid_letter(array[row][j])) { 

                if (array[row][i] != array[row][j]) {
                return false;
                }
            }
        }
    }
    return true;
}

bool is_valid_letter(char a) {

    switch (a) {
        case 'K':
        case 'R':
        case 'G':
        case 'Y':
        case 'B':
        case 'M':
        case 'C':
        case 'W':
            return true;
        case '.':
            return false;
        default :
            fprintf(stderr, "Invalid bookcase definition within bookcase\n");
            exit(EXIT_FAILURE);
    }
}

bool is_space(char array[MAX][MAX], int row) {

    if (row >= 9 || row < 0) {
        fprintf(stderr, "Row invalid, please pick another\n");
        exit(EXIT_FAILURE);
    }

    if (array[row][MAX-1] == '.') {
            return true;
    }
    return false;
}


bool is_row_empty(char array[MAX][MAX], int row) {

    int x;

    if (row >= 9 || row < 0) {
        fprintf(stderr, "Row invalid, please pick another\n");
        exit(EXIT_FAILURE);
    }

    for (x = 0; x < MAX; x++) {
        if (array[row][x] != '.') {
            return false;
        }
    }
    
    return true;
}

bool test_strings(char array[MAX][MAX], int row, char str[10]) {

    int i;
    char str2[10];
    
    /* Fill string with row from array*/
    for (i = 0; i < MAX; i++) {
        str2[i] = array[row][i];
    }
    str2[MAX] = '\0';

    if (strcmp(str2, str) == 0) {
        return true;
    }    

    return false;
}

