#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

void print_set(unsigned char* st, long int elem, long int start, long int stop) {
    unsigned long int length = stop - start;
    for (unsigned long int i=0; i<length;i++) {
        if (st[i]) {
            printf("%4d", start+i);
        }
    };
    printf("\n");
};

long int elem_by_position_in_set(unsigned long int i, long int start) {
    return start + i;
};

unsigned char* prepare_set(long int start, long int stop) {
    return (unsigned char *)calloc(stop - start, sizeof(long int));
};

void add_to_set(unsigned char* st, long int elem, long int start) {
    st[elem - start] = 1;
};

unsigned long int input_set(unsigned char* st, long int start, long int stop) {
    unsigned long int n;
    long int temp;
    printf("Vvedit kilkist elementiv:");
    scanf("%d", &n);
    printf("Vvedit elementy:");
    for (unsigned long int i = 0; i<n; i++) {
        scanf("%d", &temp);
        add_to_set(st, temp, start);
    };
    return n;
};

unsigned char** prepare_relation(unsigned long int n, unsigned long int m) {
    unsigned char** new_relation = (unsigned char**)calloc(n, sizeof(unsigned char*));
    for (unsigned long int i=0; i<n; i++){
        new_relation[i] = (unsigned char*)calloc(m, sizeof(unsigned char));
    };
    return new_relation;
};

void make_relation(unsigned char** relation, unsigned long int n, unsigned long int m, unsigned char* set1,
        unsigned char* set2, long int start, long int stop, unsigned char (*condition)(long int, long int)) {
    unsigned long j;
    for (unsigned long int i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            if ((set1[i] == 1) && (set2[j] == 1)) {
                relation[i][j] = condition(elem_by_position_in_set(i, start), elem_by_position_in_set(j, start));
            };
        };
    };
};

void print_matrix(unsigned char** matrix, unsigned long int n, unsigned long int m) {
    unsigned long int j;
    for (unsigned long int i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            printf("%d ", (int)matrix[i][j]);
        };
        printf("\n");
    };
    printf("\n");
};

unsigned char my_condition(long int a, long int b) {
    return b < (a*a);
};

int main() {
    unsigned long int s_begin, s_end;

    printf("Enter minimum of universum: ");
    scanf("%d", &s_begin);

    printf("Enter maximum of universum: ");
    scanf("%d", &s_end);

    unsigned long int n = (s_end + 1) - s_begin;
    unsigned long int m = (s_end + 1) - s_begin;

    printf("Enter Set1:\n");
    unsigned char* set1 = prepare_set(s_begin, s_end + 1);
    unsigned long int set1_length = input_set(set1, s_begin, s_end + 1);

    for (int i=0; i<n; i++) {
        printf("%i ", set1[i]);
    };
    printf("\n\n");

    printf("Enter Set2:\n");
    unsigned char* set2 = prepare_set(s_begin, s_end + 1);
    unsigned long int set2_length = input_set(set2, s_begin, s_end + 1);

    for (int i=0; i<m; i++) {
        printf("%i ", set2[i]);
    };
    printf("\n\n");

    unsigned char** relation = prepare_relation(n, m);
    make_relation(relation, n, m, set1, set2, s_begin, s_end + 1, my_condition);

    print_matrix(relation, n, m);

    unsigned long int j;
    for (unsigned long int i=0; i < n; i++) {
        if (set1[i] == 1) {
            for (j=0; j < m; j++) {
                if (set2[j] == 1) {
                    printf("%d ", (int)relation[i][j]);
                };
            };
            printf("\n");
        };
    };
};