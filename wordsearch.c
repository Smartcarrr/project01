#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
int bSize;
// Main function, DO NOT MODIFY 	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;
    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }
    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));
    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);
    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    return 0;
}


void upperCase(char* str) {
    for (int i = 0; i < strlen(str); i++) {
        if (*(str+i) >= 'a' && *(str+i) <= 'z') {
            *(str+i) = *(str+i) - ('a' - 'A');
        }
    }
}
void showPath(int** path) {
    for (int i = 0; i < bSize; ++i) {
        for (int j = 0; j < bSize; ++j) {
            int value =*(*(path+i)+j); //pointer notation
            if (value != 0) {
                int reversed = 0;
                while (value > 0) {
                    reversed = reversed * 10 + value % 10;
                    value /= 10;
                }
                printf("%d\t", reversed);
            } else {
                printf("0\t");
            }
        }
        printf("\n");
    }
}
void printPuzzle(char** arr) {
	// This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...
    for(int i = 0; i < bSize; i++){
		for(int j = 0; j < bSize; j++){
			printf("%c ", *(*(arr+i)+j));
		}
		printf("\n");
	}
	printf("\n");
}
int findNeighbor(char** arr, int** temp, char* word, int x, int y, int index) {
    if (index == strlen(word) + 1) {
        return 1;
    }
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int row = x + i;
            int column = y + j;
            if (row >= 0 && row < bSize && column >= 0 && column < bSize && *(*(arr + row) + column) == *(word + (index - 1))) {
                if ((*(*(temp + row) + column) % 10 != index - 1 || *(*(temp + row) + column) == 0)) {
                    int original = *(*(temp + row) + column);
                    if (original == 0) {
                        *(*(temp + row) + column) = index;
                    } else {
                        *(*(temp + row) + column) = original * 10 + index;
                    }
                    
                    if (findNeighbor(arr, temp, word, row, column, index + 1)){
                        return 1;
                    }

                    if (original == 0) {
                        *(*(temp + row) + column) = 0;
                    } else {
                        *(*(temp + row) + column) = (original - index) / 10;
                    }
                }
            }
        }
    }
    
    return 0;
}
void searchPuzzle(char** arr, char* word) {
    int **temp = (int**)malloc(bSize * sizeof(int*));
    for (int i = 0; i < bSize; i++) {
        temp[i] = (int*)calloc(bSize, sizeof(int)); // Initialize to 0
    }
    upperCase(word);
    int found = 0;
    // Check for each cell if it can be the start of the word
    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            if (*(*(arr+i)+j) == *(word)) { // Check if first letter matches
                // Call findNeighbor and check if the word is found
                if (findNeighbor(arr, temp, word, i, j, 1)) {
                    found = 1; // Word found
                }
            }
        }
    }
    // If any path was found, print it
    if (found) {
        printf("\nWord found!\nPrinting the search path:\n");
        showPath(temp);
    } else {
        printf("Word not found!\n");
    }
    // Free allocated memory
    for (int i = 0; i < bSize; i++) {
        free(temp[i]);
    }
    free(temp);
}


