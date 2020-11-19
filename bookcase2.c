#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define MAX 9
#define MAXIMUM 99999

enum bool {false, true};
typedef enum bool bool;

struct bookcase {
    char board[MAX][MAX];
    int parent;
    int number;
    int height;
    int width;
};

typedef struct bookcase Bookcase;

/* Function to make book move*/
void make_move(Bookcase *child, int start, int end); 

/*Function to get parent*/
void get_parent(Bookcase *child, Bookcase *parent); 

/*Function to check if a move is valid*/
bool valid_move(char array[MAX][MAX] ,int start, int end);

/* Function to assign structure an array number*/
void fill_number(Bookcase cases[MAXIMUM]);

/* Function to map parent bookcase onto child bookcase*/
void copy_bookcase(Bookcase *child, Bookcase *parent); 

/* Testing function to fill parent bookcase*/
void test_fill_case(Bookcase *bkcs);

/* Function to check whether calloc has freed up space*/
void *ncalloc(int n, size_t size);

/*Function to remove a book from a shelf*/
bool remove_book(char array[MAX][MAX], int row, char book);

/*Function to add a book to a shelf*/
bool add_book(char array[MAX][MAX], int row, char book);

/*Function to find right most book of a row*/
char find_book(char array[MAX][MAX], int row);

/* Function to test if bookcase is happy*/
bool is_happy(char array[MAX][MAX]);

/*Function to check whether first book of each row is different*/
bool books_in_rows(char array[MAX][MAX]);

/* Function to determine if a row is happy*/
bool is_row_happy(char array[MAX][MAX], int row); 

/* Function to check whether letter is valid*/
bool is_valid_letter(char a);

/* Function used to clean testing array*/
void test_clean_shelf(char array[MAX][MAX]);

/*Function to check whether there is space in the row*/
bool is_space(char array[MAX][MAX], int row);

/*Function to check whether a row is empty*/
bool is_row_empty(char array[MAX][MAX], int row, int width);

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

    Bookcase *cases;


    /*Test is_row_empty funtion*/
    for (i = 0; i < MAX; i++) {
        assert(is_row_empty(test_case, i, MAX));
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

    /*Test books_in_rows function*/
    assert(books_in_rows(test_case));
    test_case[0][0] = 'Y';
    test_case[1][0] = 'R';
    test_case[2][0] = 'G';
    test_case[3][0] = 'B';
    test_case[4][0] = 'C';
    assert(books_in_rows(test_case));
    test_case[4][0] = 'Y';
    assert(!books_in_rows(test_case));
    test_clean_shelf(test_case);
    

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

    for (i = 0; i < MAX; i++) {
        test_case[8][i] = 'Y';
        test_case[2][i] = 'Y';
    }
    assert(!is_happy(test_case));
    

    /*Test find_book function*/
    test_case[0][1] = 'Y';
    assert(find_book(test_case, 0) == 'Y');
    test_case[0][2] = 'C';
    assert(find_book(test_case, 0) == 'C');
    test_case[0][3] = 'Y';
    assert(find_book(test_case, 0) != 'C');
    assert(find_book(test_case, 0) == 'Y');

    for (i = 0; i < MAX; i++) {
        test_case[0][i] = 'B';
    }
    assert(find_book(test_case, 0) == 'B');
    test_case[0][8] = 'Y';
    assert(find_book(test_case, 0) == 'Y');
    for (i = 0; i < MAX; i++) {
        test_case[0][i] = '.';
    }
    assert(find_book(test_case, 0) == '.');

    /*Test add book function*/
    add_book(test_case, 7, 'M');
    assert(test_strings(test_case, 7, "M........"));
    add_book(test_case, 7, 'C');
    assert(test_strings(test_case, 7, "MC......."));  

    /*Test whether fails to add to full book shelf*/
    for (i = 0; i< MAX; i++) {
        test_case[7][i] = 'C';
    }
    add_book(test_case, 7, 'M');
    assert(!add_book(test_case, 7, 'M'));
    assert(test_strings(test_case, 7, "CCCCCCCCC"));
    test_clean_shelf(test_case);

    /* Test remove_book function*/
    test_case[4][4] = 'M';
    remove_book(test_case, 4, 'M');
    assert(test_strings(test_case, 4, "........."));

    for (i = 0; i < MAX; i++) {
        test_case[3][i] = 'G';
    }
    remove_book(test_case, 3, 'G');
    assert(test_strings(test_case, 3, "GGGGGGGG."));

    test_case[3][2] = 'B';
    for (i = 0; i < MAX; i++) {
        remove_book(test_case, 3, 'G');
    }
    assert(test_strings(test_case, 3, "..B......"));
    test_clean_shelf(test_case);

    /* Test valid_move function*/
    assert(!valid_move(test_case, 0, 1));
    test_case[0][7] = 'C';
    assert(valid_move(test_case, 0, 1));
    test_case[1][7] = 'R';
    assert(valid_move(test_case, 0, 1));
    test_case[1][8] = 'R';
    assert(!valid_move(test_case, 0, 1));
    assert(!valid_move(test_case, 7, 7));
    test_clean_shelf(test_case);

    /* Calloc space for array of structures*/
    cases = ncalloc(MAXIMUM, sizeof(Bookcase));

    /*Test test_fill_case function*/
    test_fill_case(&cases[0]);
    assert(cases[0].board[3][5] == '.');
    assert(cases[0].board[8][8] == '.');
    assert(cases[0].board[0][0] == '.');

    /*Test copy_bookcase function*/
    copy_bookcase(&cases[1], &cases[0]);
    assert(cases[1].board[2][2] == '.');
    assert(cases[1].board[7][4] == '.');
    assert(cases[2].board[8][2] != '.');

    cases[0].board[6][0] = 'R';
    cases[0].board[6][1] = 'G';
    cases[0].board[4][7] = 'Y';
    copy_bookcase(&cases[1], &cases[0]);
    assert(cases[1].board[6][0] == 'R');
    assert(cases[1].board[6][1] == 'G');
    assert(cases[2].board[4][7] != 'Y');
    assert(cases[1].board[4][7] == 'Y');

    /* Test make_move function*/
    test_fill_case(&cases[0]);
    cases[0].board[0][1] = 'C';
    cases[0].board[0][2] = 'Y';
    make_move(&cases[0], 0, 1);
    assert(cases[0].board[1][0] == 'Y');
    assert(cases[0].board[0][2] == '.');
    make_move(&cases[0], 0, 1);
    assert(cases[0].board[1][1] == 'C');
    assert(cases[0].board[0][1] == '.');

    cases[0].board[5][8] = 'R';
    for (i = 0; i < MAX; i++) {
        cases[0].board[4][i] = 'Y';
    }
    make_move(&cases[0], 5, 4);
    assert(cases[0].board[5][8] == 'R');
    assert(cases[0].board[4][8] == 'Y');

    /*Test fill_number function*/
    fill_number(cases);
    assert(cases[0].number   ==   0);
    assert(cases[45].number  ==  45);
    assert(cases[967].number == 967);

    /* Test get_parent*/
    get_parent(&cases[34], &cases[45]);
    assert(cases[34].parent == 45);
    get_parent(&cases[98], &cases[103]);
    assert(cases[98].parent == 103);
    get_parent(&cases[7], &cases[967]);
    assert(cases[7].parent == 967);

    free(cases);
}

/*int make_children(Bookcase *parent, int endcase) {

    int height = parent->height;
    int y, x;

    for (y = 0; y < height; y++) {
        for (x = 0; x < height; x++) {

            if (valid_move(parent->board, y, x)) {
                copy_bookcase();
                get_parent();
                makemove();
            }
        }
    }
}*/

void make_move(Bookcase *child, int start, int end) {

    char book = find_book(child->board, start);

    if (add_book(child->board, end, book)) {
        remove_book(child->board, start, book);
    } 
}

void get_parent(Bookcase *child, Bookcase *parent) {

    child->parent = parent->number;

}

void fill_number(Bookcase cases[MAXIMUM]) {

    int i;

    for (i = 0; i < MAXIMUM; i++) {
        cases[i].number = i; 
    }
}

void copy_bookcase(Bookcase *child, Bookcase *parent) {

    int y, x;

    for (y = 0; y < MAX; y++) {
        for (x = 0; x < MAX; x++) {

            child->board[y][x] = parent->board[y][x];
        }
    }
}

void test_fill_case(Bookcase *bkcs) {

    int y, x;

    for (y = 0; y < MAX; y++) {
        for (x = 0; x < MAX; x++) {

            bkcs->board[y][x] = '.';
        }
    }    
}

void *ncalloc(int n, size_t size) {

    void* v = calloc(n, size);

    if (v == NULL) {
        fprintf(stderr, "Cannot calloc space\n");
    }

    return v;
}


bool valid_move(char array[MAX][MAX] ,int start, int end) {

    if (start == end) {
        return false;
    }

    if (is_row_empty(array, start)) {
        return false;
    }
    if (!is_space(array, end)){
        return false;
    }   

    return true;
}

bool remove_book(char array[MAX][MAX], int row, char book) {

    int i;

    for (i = MAX-1; i >= 0; i--) {
        if (array[row][i] == book) {
            
            array[row][i] = '.';
            return true;
        }
    }
    return false;
}

bool add_book(char array[MAX][MAX], int row, char book){

    int i;

    for (i = 0; i < MAX; i++) {
        if (array[row][i] == '.') {
            
            array[row][i] = book;
            return true;
        }
    }
    return false;
}

char find_book(char array[MAX][MAX], int row) {

    char book = '.'; 
    int i;

    for (i = 0; i < MAX; i++) {
        if (is_valid_letter(array[row][i])) {
            book = array[row][i];
        }
    } 
    return book;
}


bool is_happy(char array[MAX][MAX]) {

    int y = 0;

    while (y != MAX) {
        if (!is_row_happy(array, y)) {
            return false;
        }
        y++;
    }
    
    if (!books_in_rows(array)) {
        return false;
    }

    return true;
}

bool books_in_rows(char array[MAX][MAX]) {

    int x, y;
    
    for (y = 0; y < MAX; y++) {
        for (x = y+1; x < MAX; x++) {

            if (is_valid_letter(array[y][0]) && is_valid_letter(array[x][0])) {

                if (array[y][0] == array[x][0]) {
                    return false;
                }
            } 
        }
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

void test_clean_shelf(char array[MAX][MAX]){

    int y, x;

    for (y = 0; y < MAX; y++) {
        for (x = 0; x < MAX; x++) {

            array[y][x] = '.';
        }
    }
}

bool is_space(char array[MAX][MAX], int row) {

    if (row >= MAX || row < 0) {
        fprintf(stderr, "Row invalid, please pick another\n");
        exit(EXIT_FAILURE);
    }

    if (array[row][MAX-1] == '.') {
            return true;
    }
    return false;
}


bool is_row_empty(char array[MAX][MAX], int row, int width) {

    int x;

    if (row >= width || row < 0) {
        fprintf(stderr, "Row invalid, please pick another\n");
        exit(EXIT_FAILURE);
    }

    for (x = 0; x < width; x++) {
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

