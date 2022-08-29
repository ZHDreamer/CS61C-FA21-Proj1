/*
 * Include the provided hash table library.
 */
#include "hashtable.h"

/*
 * Include the header file.
 */
#include "philphix.h"

/*
 * Standard IO and file routines.
 */
#include <stdio.h>

/*
 * General utility routines (including malloc()).
 */
#include <stdlib.h>

/*
 * Character utility routines.
 */
#include <ctype.h>

/*
 * String utility routines.
 */
#include <string.h>

/*
 * This hash table stores the dictionary.
 */
HashTable *dictionary;

/*
 * The MAIN routine.  You can safely print debugging information
 * to standard error (stderr) as shown and it will be ignored in
 * the grading process.
 */
#ifndef _PHILPHIX_UNITTEST
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Specify a dictionary\n");
        return 1;
    }
    /*
     * Allocate a hash table to store the dictionary.
     */
    fprintf(stderr, "Creating hashtable\n");
    dictionary = createHashTable(0x61C, &stringHash, &stringEquals);

    fprintf(stderr, "Loading dictionary %s\n", argv[1]);
    readDictionary(argv[1]);
    fprintf(stderr, "Dictionary loaded\n");

    fprintf(stderr, "Processing stdin\n");
    processInput();

    /*
     * The MAIN function in C should always return 0 as a way of telling
     * whatever program invoked this that everything went OK.
     */
    return 0;
}
#endif /* _PHILPHIX_UNITTEST */

/* Task 3 */
int isValid(char c) {
    return (c != ' ' && c != '\f' && c != '\n' && c != '\r' && c != '\t'
            && c != '\v');
}

char *readWord(FILE **input) {
    unsigned int capacity = 64;
    unsigned int counter  = 0;

    char  c;
    char *str = (char *)malloc(sizeof(char) * capacity);

    while ((c = fgetc(*input)) != EOF) {
        int valid = isValid(c);
        if (!valid) {
            if (counter == 0) {
                continue;
            } else {
                break;
            }
        } else {
            str[counter] = c;
            counter++;
            if (counter >= capacity) {
                capacity *= 2;
                str = (char *)realloc(str, capacity * sizeof(char));
            }
        }
    }
    str[counter] = 0;
    return str;
}

void readDictionary(char *dictName) {
    // -- DONE --
    // fprintf(stderr, "You need to implement readDictionary\n");
    FILE *dict = fopen(dictName, "r");

    if (!dict) {
        fprintf(stderr, "File doesn't exit\n");
        exit(61);
    }

    while (1) {
        char *key = readWord(&dict);

        if (key[0] != 0) {
            char *data = readWord(&dict);
            insertData(dictionary, key, data);
        } else {
            break;
        }
    }
}

/* Task 4 */
int isAlnum(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
        || (c >= '0' && c <= '9');
}

char *toLower(char *word) {
    unsigned int capacity = 64;
    unsigned int counter;
    char        *res = (char *)malloc(sizeof(char) * capacity);

    res[0] = word[0];

    for (counter = 1; word[counter] != 0; counter++) {
        if (word[counter] >= 'A' && word[counter] <= 'Z') {
            res[counter] = word[counter] - 'A' + 'a';
        } else {
            res[counter] = word[counter];
        }
        if (counter == capacity) {
            capacity *= 2;
            res = (char *)realloc(res, capacity * sizeof(char));
        }
    }
    res[counter] = 0;
    return res;
}

char *replaceWord(char *key) {
    char *data = findData(dictionary, key);
    if (data) {
        return data;
    }

    key  = toLower(key);
    data = findData(dictionary, key);
    if (data) {
        return data;
    }

    if (key[0] >= 'A' && key[0] <= 'Z') {
        key[0] = key[0] - 'A' + 'a';
        data   = findData(dictionary, key);
    }

    return data;
}

void processInput() {
    // -- DONE --
    // fprintf(stderr, "You need to implement processInput\n");
    unsigned int counter = 0, capacity = 64;
    char         c;
    char        *key = (char *)malloc(sizeof(char) * capacity), *data;
    while (1) {
        c = fgetc(stdin);
        if (isAlnum(c)) {
            key[counter] = c;
            counter++;
            if (counter >= capacity) {
                capacity *= 2;
                key = (char *)realloc(key, capacity * sizeof(char));
            }
        } else {
            if (counter != 0) {
                key[counter] = 0;
                counter      = 0;
                data         = replaceWord(key);
                if (data) {
                    printf("%s", data);
                } else {
                    printf("%s", key);
                }
            }
            if (c == EOF) {
                break;
            } else {
                fputc(c, stdout);
            }
        }
    }
}
