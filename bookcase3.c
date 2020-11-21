#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define MAX 9
#define MAXIMUM 9999999

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

void print_bookcase(Bookcase bkcs);

/*Function to find the number of bookcases that would be printed in solution*/
int find_parents(Bookcase array[MAXIMUM], int solution);

/* Function to generate children until a happy bookcase is found*/
int find_solution(Bookcase cases[MAXIMUM], int parent, int endpoint);

/* Function to find happy bookcase*/
int find_happy_bookcase(Bookcase array[MAXIMUM]);

/*Function to make children bookcases*/
int make_children(Bookcase array[MAXIMUM], Bookcase *parent, int endcase);

/* Function to make book move*/
void make_move(Bookcase *child, int start, int end, int width); 

/*Function to get parent*/
void get_info(Bookcase *child, Bookcase *parent); 

/*Function to check if a move is valid*/
bool valid_move(char array[MAX][MAX] ,int start, int end, int height, int width);

/* Function to assign structure an array number*/
void fill_number(Bookcase cases[MAXIMUM]);

/* Function to map parent bookcase onto child bookcase*/
void copy_bookcase(Bookcase *child, Bookcase *parent); 

/* Testing function to fill parent bookcase*/
void test_clean_case(Bookcase *bkcs);

/* Function to check whether calloc has freed up space*/
void *ncalloc(int n, size_t size);

/*Function to remove a book from a shelf*/
bool remove_book(char array[MAX][MAX], int row, char book, int width);

/*Function to add a book to a shelf*/
bool add_book(char array[MAX][MAX], int row, char book, int width);

/*Function to find right most book of a row*/
char find_book(char array[MAX][MAX], int row, int width);

/* Function to test if bookcase is happy*/
bool is_happy(char array[MAX][MAX], int height, int width);

/*Function to check whether first book of each row is different*/
bool books_in_rows(char array[MAX][MAX], int height);

/* Function to determine if a row is happy*/
bool is_row_happy(char array[MAX][MAX], int row, int width); 

/* Function to check whether letter is valid*/
bool is_valid_letter(char a);

/* Function used to clean testing array*/
void test_clean_shelf(char array[MAX][MAX]);

/*Function to check whether there is space in the row*/
bool is_space(char array[MAX][MAX], int row, int height, int width);

/* Function to check whether a shelf is empty*/
bool is_shelf_empty(char array[MAX][MAX], int height, int width);

/*Function to check whether a row is empty*/
bool is_row_empty(char array[MAX][MAX], int row, int height, int width);

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
    int solution, i;

    Bookcase *cases;


    /*Test is_row_empty funtion*/
    for (i = 0; i < MAX; i++) {
        assert(is_row_empty(test_case, i, MAX, MAX));
        assert(test_strings(test_case, i, "........."));
    }

    test_case[5][1] = 'R';
    test_case[0][1] = 'Y';
    test_case[8][3] = 'R';
    assert(!is_row_empty(test_case, 5, MAX, MAX));
    assert(!is_row_empty(test_case, 0, MAX, MAX));
    assert(!is_row_empty(test_case, 8, MAX, MAX));
    assert(is_row_empty(test_case, 6, MAX, MAX));
    test_case[5][1] = '.';
    test_case[0][1] = '.';
    test_case[8][3] = '.';
    assert(is_row_empty(test_case, 5, MAX, MAX));
    assert(is_row_empty(test_case, 0, MAX, MAX));
    assert(is_row_empty(test_case, 8, MAX, MAX));

    assert(!is_row_empty(test_case2, 8, MAX, MAX));
    assert(!is_row_empty(test_case2, 3, MAX, MAX));

    /*Test is_shelf_empty function*/
    assert(is_shelf_empty(test_case, MAX, MAX));
    test_case[0][1] = 'M';
    test_case[2][1] = 'Y';
    test_case[5][3] = 'C';
    assert(!is_shelf_empty(test_case, MAX, MAX));
    test_case[2][1] = '.';
    test_case[5][3] = '.';
    assert(!is_shelf_empty(test_case, MAX, MAX));
    test_case[0][1] = '.';
    assert(is_shelf_empty(test_case, MAX, MAX));

    /*Test is_space function*/
    for (i = 0; i < MAX; i++) {
        assert(is_space(test_case, i, MAX, MAX));
    }

    test_case[0][8] = 'R';
    test_case[1][8] = 'R';
    test_case[5][5] = 'R';
    test_case[8][8] = '$';
    assert(!is_space(test_case, 0, MAX, MAX));
    assert(!is_space(test_case, 1, MAX, MAX));
    assert(is_space(test_case, 5, MAX, MAX));
    assert(!is_space(test_case, 8, MAX, MAX));
    test_case[0][8] = '.';
    test_case[1][8] = '.';
    test_case[5][5] = '.';
    test_case[8][8] = '.';
    assert(is_space(test_case, 0, MAX, MAX));
    assert(is_space(test_case, 1, MAX, MAX));
    assert(is_space(test_case, 5, MAX, MAX));
    assert(is_space(test_case, 8, MAX, MAX));
    
    assert(!is_space(test_case2, 8, MAX, MAX));
    assert(!is_space(test_case2, 3, MAX, MAX));

    /* Test is_valid_letter function*/
    assert(is_valid_letter('B'));
    assert(is_valid_letter('K'));
    assert(is_valid_letter('C'));
    assert(is_valid_letter('W'));
    
    assert(!is_valid_letter('.'));

    /*Test is_row_happy function*/
    for (i = 0; i < MAX; i++) {
        assert(is_row_happy(test_case, i, MAX));
    }
    
    test_case[0][0] = 'R';
    test_case[0][1] = 'R';
    test_case[0][2] = 'R';
    assert(is_row_happy(test_case, 0, MAX));
    test_case[0][1] = 'Y';
    assert(!is_row_happy(test_case, 0, MAX));
    test_case[0][1] = '.';
    assert(is_row_happy(test_case, 0, MAX));
    test_case[0][0] = '.';
    assert(is_row_happy(test_case, 0, MAX));
    test_case[0][2] = '.';
    assert(is_row_happy(test_case, 0, MAX));
    test_case[4][1] = 'B';
    test_case[4][2] = 'R';
    assert(!is_row_happy(test_case, 4, MAX));

    /*Test books_in_rows function*/
    assert(books_in_rows(test_case, MAX));
    test_case[0][0] = 'Y';
    test_case[1][0] = 'R';
    test_case[2][0] = 'G';
    test_case[3][0] = 'B';
    test_case[4][0] = 'C';
    assert(books_in_rows(test_case, MAX));
    test_case[4][0] = 'Y';
    assert(!books_in_rows(test_case, MAX));
    test_clean_shelf(test_case);
    

    /*Test if is_happy function*/
    test_case[8][8] = 'Y';
    test_case[8][7] = 'Y';
    assert(is_happy(test_case, MAX, MAX));
    test_case[8][6] = 'B';
    assert(!is_happy(test_case, MAX, MAX));

    for (i = 0; i < MAX; i++) {
        test_case[3][i] = 'C';
    }

    assert(!is_happy(test_case, MAX, MAX));

    test_case[8][6] = '.';
    assert(is_happy(test_case, MAX, MAX));
    
    for (i = 0; i < MAX; i++) {
        test_case[3][i] = '.';
    }
    assert(is_happy(test_case, MAX, MAX));

    for (i = 0; i < MAX; i++) {
        test_case[8][i] = 'Y';
        test_case[2][i] = 'Y';
    }
    assert(!is_happy(test_case, MAX, MAX));
    

    /*Test find_book function*/
    test_case[0][1] = 'Y';
    assert(find_book(test_case, 0, MAX) == 'Y');
    test_case[0][2] = 'C';
    assert(find_book(test_case, 0, MAX) == 'C');
    test_case[0][3] = 'Y';
    assert(find_book(test_case, 0, MAX) != 'C');
    assert(find_book(test_case, 0, MAX) == 'Y');

    for (i = 0; i < MAX; i++) {
        test_case[0][i] = 'B';
    }
    assert(find_book(test_case, 0, MAX) == 'B');
    test_case[0][8] = 'Y';
    assert(find_book(test_case, 0, MAX) == 'Y');
    for (i = 0; i < MAX; i++) {
        test_case[0][i] = '.';
    }
    assert(find_book(test_case, 0, MAX) == '.');

    /*Test add book function*/
    add_book(test_case, 7, 'M', MAX);
    assert(test_strings(test_case, 7, "M........"));
    add_book(test_case, 7, 'C', MAX);
    assert(test_strings(test_case, 7, "MC......."));  

    /*Test whether fails to add to full book shelf*/
    for (i = 0; i< MAX; i++) {
        test_case[7][i] = 'C';
    }
    add_book(test_case, 7, 'M', MAX);
    assert(!add_book(test_case, 7, 'M', MAX));
    assert(test_strings(test_case, 7, "CCCCCCCCC"));
    test_clean_shelf(test_case);

    /* Test remove_book function*/
    test_case[4][4] = 'M';
    remove_book(test_case, 4, 'M', MAX);
    assert(test_strings(test_case, 4, "........."));

    for (i = 0; i < MAX; i++) {
        test_case[3][i] = 'G';
    }
    remove_book(test_case, 3, 'G', MAX);
    assert(test_strings(test_case, 3, "GGGGGGGG."));

    test_case[3][2] = 'B';
    for (i = 0; i < MAX; i++) {
        remove_book(test_case, 3, 'G', MAX);
    }
    assert(test_strings(test_case, 3, "..B......"));
    test_clean_shelf(test_case);

    /* Test valid_move function*/
    assert(!valid_move(test_case, 0, 1, MAX, MAX));
    test_case[0][7] = 'C';
    assert(valid_move(test_case, 0, 1, MAX, MAX));
    test_case[1][7] = 'R';
    assert(valid_move(test_case, 0, 1, MAX, MAX));
    test_case[1][8] = 'R';
    assert(!valid_move(test_case, 0, 1, MAX, MAX));
    assert(!valid_move(test_case, 7, 7, MAX, MAX));
    test_clean_shelf(test_case);

    /* Calloc space for array of structures*/
    cases = ncalloc(MAXIMUM, sizeof(Bookcase));

    /*Test test_clean_case function*/
    test_clean_case(&cases[0]);
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
    test_clean_case(&cases[0]);
    cases[0].board[0][1] = 'C';
    cases[0].board[0][2] = 'Y';
    make_move(&cases[0], 0, 1, MAX);
    assert(cases[0].board[1][0] == 'Y');
    assert(cases[0].board[0][2] == '.');
    make_move(&cases[0], 0, 1, MAX);
    assert(cases[0].board[1][1] == 'C');
    assert(cases[0].board[0][1] == '.');

    cases[0].board[5][8] = 'R';
    for (i = 0; i < MAX; i++) {
        cases[0].board[4][i] = 'Y';
    }
    make_move(&cases[0], 5, 4, MAX);
    assert(cases[0].board[5][8] == 'R');
    assert(cases[0].board[4][8] == 'Y');

    /*Test fill_number function*/
    fill_number(cases);
    assert(cases[0].number   ==   0);
    assert(cases[45].number  ==  45);
    assert(cases[967].number == 967);

    /* Test get_info*/
    cases[45].height = 6;
    cases[45].width = 6;
    get_info(&cases[34], &cases[45]);
    assert(cases[34].parent == 45);
    assert(cases[34].width  == 6);
    assert(cases[34].height == 6);

    cases[103].height = 7;
    cases[103].width  = 8;
    get_info(&cases[98], &cases[103]);
    assert(cases[98].parent == 103);
    assert(cases[98].width  == 8);
    assert(cases[98].height == 7);

    cases[967].height = 2;
    cases[967].width  = 2;
    get_info(&cases[7], &cases[967]);
    assert(cases[7].parent == 967);
    assert(cases[7].width  == 2);
    assert(cases[7].height == 2);

    /*Test make_children function. While row not empty or full, 
    children should be height x height-1*/
    test_clean_case(&cases[0]);
    cases[0].height = 2;
    cases[0].width = 3;
    assert(make_children(cases, &cases[0], 0) == 0);

    cases[0].board[0][0] = 'Y';
    cases[0].board[1][0] = 'R';
    assert(make_children(cases, &cases[0], 0) == 2);
    assert(cases[1].board[1][1] = 'Y');
    assert(cases[2].board[0][1] = 'R');
    assert(cases[1].height == 2);
    assert(cases[2].width == 3);

    test_clean_case(&cases[0]);
    cases[0].height = 6;
    cases[0].width = 7;
    cases[0].board[0][0] = 'K';
    cases[0].board[1][0] = 'R';
    cases[0].board[2][0] = 'C';
    cases[0].board[3][0] = 'B';
    cases[0].board[4][0] = 'G';
    cases[0].board[5][0] = 'M';
    assert(make_children(cases, &cases[0], 0) == 30);
    assert(cases[3].board[3][1]  == 'K');
    assert(cases[30].board[4][1] == 'M');
    assert(cases[24].board[2][0] == 'C');
    assert(cases[18].height == 6);
    assert(cases[22].width == 7);
    assert(cases[29].parent == 0);

    test_clean_case(&cases[0]);
    cases[0].height = 9;
    cases[0].width = 9; 
    cases[0].board[0][0] = 'Y';
    cases[0].board[1][0] = 'Y';
    cases[0].board[2][0] = 'Y';
    cases[0].board[3][0] = 'Y';
    cases[0].board[4][0] = 'Y';
    cases[0].board[5][0] = 'Y';
    cases[0].board[6][0] = 'Y';
    cases[0].board[7][0] = 'Y';
    cases[0].board[8][0] = 'Y';
    assert(make_children(cases, &cases[0], 0) == 72);
    assert(cases[59].height == 9);
    assert(cases[55].width  == 9);
    assert(cases[22].parent == 0);

    test_clean_case(&cases[0]);
    cases[0].height = 3;
    cases[0].width = 3; 
    cases[0].board[0][0] = 'Y';
    cases[0].board[0][1] = 'G';
    cases[0].board[0][2] = 'Y';
    cases[0].board[1][0] = 'M';
    cases[0].board[2][0] = 'Y';
    assert(make_children(cases, &cases[0], 0) == 4);
    assert(cases[3].height == 3);
    assert(cases[2].width  == 3);
    assert(cases[3].parent == 0);

    /*Test find_happy_bookcase function*/
    for (i = 0; i < 100; i++) {
        test_clean_case(&cases[i]);
    }
    cases[0].board[0][0] = 'Y';
    cases[0].board[1][0] = 'C';
    cases[0].board[2][0] = 'C';
    cases[0].board[2][1] = 'M';
    assert(find_happy_bookcase(cases) == -1);

    cases[0].height = 3;
    cases[0].width  = 3; 
    cases[0].board[0][0] = 'Y';
    cases[0].board[1][0] = 'G';
    cases[0].board[2][0] = 'Y';
    cases[0].board[2][1] = '.';
    make_children(cases, &cases[0], 0);
    assert(find_happy_bookcase(cases) == 2);
    
    test_clean_case(&cases[0]);
    cases[0].height = 8;
    cases[0].width  = 4; 
    cases[0].board[0][0] = 'B';
    cases[0].board[1][0] = '.';
    cases[0].board[2][0] = 'C';
    cases[0].board[3][0] = 'K';
    cases[0].board[4][0] = 'Y';
    cases[0].board[5][0] = 'W';
    cases[0].board[6][0] = 'K';
    cases[0].board[7][0] = 'G';
    make_children(cases, &cases[0], 0);
    assert(find_happy_bookcase(cases) == 20);

    test_clean_case(&cases[0]);
    cases[0].height = 5;
    cases[0].width  = 3; 
    cases[0].board[0][0] = 'B';
    cases[0].board[0][1] = 'B';
    cases[0].board[0][2] = 'K';
    cases[0].board[1][0] = 'Y';
    cases[0].board[2][0] = 'W';
    cases[0].board[3][0] = 'K';
    make_children(cases, &cases[0], 0);
    assert(find_happy_bookcase(cases) == 3);

    test_clean_case(&cases[0]);
    cases[0].height = 5;
    cases[0].width  = 3; 
    cases[0].board[0][0] = 'C';
    cases[0].board[1][0] = 'B';
    cases[0].board[2][0] = 'K';
    cases[0].board[3][0] = 'Y';
    cases[0].board[4][0] = 'W';
    cases[0].board[4][1] = 'W';
    assert(find_happy_bookcase(cases) == 0);

    /* Test find_solutions function*/
    for (i = 0; i < 100; i++) {
        test_clean_case(&cases[i]);
    }
    cases[0].height = 3;
    cases[0].width  = 3; 
    cases[0].board[0][0] = 'Y';
    cases[0].board[1][0] = 'G';
    cases[0].board[2][0] = 'Y';
    cases[0].board[2][1] = '.';
    assert(find_solution(cases, 0, 0) == 2);
    
    test_clean_case(&cases[0]);
    cases[0].height = 7;
    cases[0].width  = 6; 
    cases[0].board[0][0] = 'C';
    cases[0].board[1][0] = 'B';
    cases[0].board[2][0] = 'K';
    cases[0].board[3][0] = 'Y';
    cases[0].board[4][0] = 'W';
    cases[0].board[5][0] = 'W';
    assert(find_solution(cases, 0, 0) == 29);

    for (i = 0; i < 1000; i++) {
        test_clean_case(&cases[i]);
    }
    cases[0].height = 2;
    cases[0].width  = 2; 
    cases[0].board[0][0] = 'Y';
    cases[0].board[0][1] = '.';
    cases[0].board[1][0] = 'B';
    cases[0].board[1][1] = 'Y';

    assert(find_solution(cases, 0, 0) == 1);

    /*Test find_parents function*/
    test_clean_case(&cases[0]);
    cases[0].height = 2;
    cases[0].width  = 2; 
    cases[0].board[0][0] = 'Y';
    cases[0].board[0][1] = '.';
    cases[0].board[1][0] = 'B';
    cases[0].board[1][1] = 'Y';
    solution = find_solution(cases, 0, 0);
    assert(find_parents(cases, solution) == 2);

    test_clean_case(&cases[0]);
    cases[0].height = 3;
    cases[0].width  = 3; 
    cases[0].board[0][0] = 'Y';
    cases[0].board[1][0] = 'G';
    cases[0].board[2][0] = 'Y';
    cases[0].board[2][1] = '.';
    solution = find_solution(cases, 0, 0);
    assert(find_parents(cases, solution) == 2);

   
    for (i = 0; i < 1000; i++) {
        test_clean_case(&cases[i]);
    }
    cases[0].height = 5;
    cases[0].width  = 3; 
    cases[0].board[0][0] = 'C';
    cases[0].board[1][0] = 'B';
    cases[0].board[2][0] = 'K';
    cases[0].board[3][0] = 'Y';
    cases[0].board[4][0] = 'W';
    cases[0].board[4][1] = 'W';
    solution = find_solution(cases, 0, 0);
    assert(find_parents(cases, solution) == 1);



    free(cases);
}

void print_bookcases(Bookcase bkcs[MAXIMUM], int solution) {

    int y, x;
    int height = bkcs[0].height;
    int width = bkcs[0].width;
    int parent = solution;

    do {

        for (y = 0; y < height; y++) {
            printf("\n");
            for (x = 0; x < width; x++) {
                printf("%c", bkcs.board[y][x]);
            }
        }
        printf("\n");

    } while (parent != 0)

}

void print_bookcase(Bookcase bkcs){

    int y, x;
    int height = bkcs.height;
    int width = bkcs.width;

    for (y = 0; y < height; y++) {
        printf("\n");
        for (x = 0; x < width; x++) {

            printf("%c", bkcs.board[y][x]);
        }
    }
    printf("\n");
}

int find_parents(Bookcase array[MAXIMUM], int solution) {

    register int count = 1; 

    while (solution != 0) {
        solution = array[solution].parent;
        count++;
    }
    return count;

}

int find_solution(Bookcase array[MAXIMUM], int parent, int endpoint) {  

    if (find_happy_bookcase(array) == 0) {
        return 0;
    }

    do {
        /*No Solution Condition*/
        if (endpoint > 900000) {
            printf("No Solution?\n");
            return 0;
        }
        endpoint = make_children(array, &array[parent], endpoint);
        parent++;
    } while (find_happy_bookcase(array) == 0);

    return find_happy_bookcase(array);
}

int find_happy_bookcase(Bookcase array[MAXIMUM]) {

    int i = 0;
    int height = array[0].height;
    int width  = array[0].width;

    while (array[i].height != 0) {
        
        if (is_happy(array[i].board, height, width)) {
                return i;
            }      
        i++;
    }
    return -1; 
}

int make_children(Bookcase array[MAXIMUM], Bookcase *parent, int endcase) {

    int height = parent->height;
    int width = parent->width;
    int y, x, i = endcase;

    for (y = 0; y < height; y++) {
        for (x = 0; x < height; x++) {

            if (valid_move(parent->board, y, x, height, width)) {
                copy_bookcase(&array[++i], parent);
                make_move(&array[i], y, x, width);
                get_info(&array[i], parent);
            }
        }
    }
    return i;
}

void make_move(Bookcase *child, int start, int end, int width) {

    char book = find_book(child->board, start, width);

    if (add_book(child->board, end, book, width)) {
        remove_book(child->board, start, book, width);
    } 
}

void get_info(Bookcase *child, Bookcase *parent) {

    child->parent = parent->number;
    child->height = parent->height;
    child->width  = parent->width;
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

void test_clean_case(Bookcase *bkcs) {

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


bool valid_move(char array[MAX][MAX] ,int start, int end, int height, int width) {

    if (start == end) {
        return false;
    }

    if (is_row_empty(array, start, height, width)) {
        return false;
    }
    if (!is_space(array, end, height, width)){
        return false;
    }   

    return true;
}

bool remove_book(char array[MAX][MAX], int row, char book, int width) {

    int i;

    for (i = width-1; i >= 0; i--) {
        if (array[row][i] == book) {
            
            array[row][i] = '.';
            return true;
        }
    }
    return false;
}

bool add_book(char array[MAX][MAX], int row, char book, int width){

    int i;

    for (i = 0; i < width; i++) {
        if (array[row][i] == '.') {
            
            array[row][i] = book;
            return true;
        }
    }
    return false;
}

char find_book(char array[MAX][MAX], int row, int width) {

    char book = '.'; 
    int i;

    for (i = 0; i < width; i++) {
        if (is_valid_letter(array[row][i])) {
            book = array[row][i];
        }
    } 
    return book;
}


bool is_happy(char array[MAX][MAX], int height, int width) {

    int y = 0;

    while (y != height) {
        if (!is_row_happy(array, y, width)) {
            return false;
        }
        y++;
    }
    
    if (!books_in_rows(array, height)) {
        return false;
    }

    if (is_shelf_empty(array, height, width)){
        return false;
    }

    return true;
}

bool books_in_rows(char array[MAX][MAX], int height) {

    int x, y;
    
    for (y = 0; y < height; y++) {
        for (x = y+1; x < height; x++) {

            if (is_valid_letter(array[y][0]) && is_valid_letter(array[x][0])) {

                if (array[y][0] == array[x][0]) {
                    return false;
                }
            } 
        }
    }
    return true;
}

bool is_row_happy(char array[MAX][MAX], int row, int width) {

    int i, j;

    for (i = 0; i < width; i++) {
        for (j = i+1; j < width; j++) {

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

bool is_space(char array[MAX][MAX], int row, int height, int width) {

    if (row >= height || row < 0) {
        fprintf(stderr, "Row invalid, please pick another\n");
        exit(EXIT_FAILURE);
    }

    if (array[row][width-1] == '.') {
            return true;
    }
    return false;
}

bool is_shelf_empty(char array[MAX][MAX], int height, int width) {

    int x;
    for (x = 0; x < height; x++) {
        if (!is_row_empty(array, x, height, width)) {
            return false;
        }
    }
    return true;
}

bool is_row_empty(char array[MAX][MAX], int row, int height, int width) {

    int x;

    if (row >= height || row < 0) {
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

