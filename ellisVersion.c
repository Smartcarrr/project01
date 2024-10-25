#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
void helperValue(int** temp, int x_axis, int y_axis, int index);
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

char* upperCase(const char* str) {
    if (str == NULL) return NULL;

    int len = strlen(str);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) return NULL;

    for (int i = 0; i < len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            result[i] = str[i] - ('a' - 'A');
        } else {
            result[i] = str[i];
        }
    }
    result[len] = '\0'; // Null-terminate the string

    return result;
}


void showPath(int** path, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int value = path[i][j];
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
    if (index >= strlen(word) + 1) {
        helperValue(temp, x, y, index - 1);
        return 1;
    }

    printf("finding neighbor of %d\n", index);
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int x_axis = x + i;
            int y_axis = y + j;

            //printf("x: %d, y: %d\n", x_axis, y_axis);

            if ((x_axis >= 0 && x_axis < bSize) && (y_axis >= 0 && y_axis < bSize) && !(i == 0 && j == 0)){
                //printf("works!!\n");
                if(*(*(arr + x_axis) + y_axis) == *(word + (index - 1))) {
                    if (findNeighbor(arr, temp, word, x_axis, y_axis, index + 1)) {
                        helperValue(temp, x_axis, y_axis, index - 1);
                        return 1;
                    }
                }
            }
        }
    }
    
    return 0;
}

//helper value should replace the 0 with index, OR if there is already a # there
// multiply it by 10 and add the index

void searchPuzzle(char** arr, char* word) {
    int **temp = (int**)malloc(bSize * sizeof(int*));
    for (int i = 0; i < bSize; i++) {
        temp[i] = (int*)calloc(bSize, sizeof(int)); // Initialize to 0
    }

    word = upperCase(word);
    int found = 0;

    // Check for each cell if it can be the start of the word
    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            if (arr[i][j] == word[0]) { // Check if first letter matches
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
        showPath(temp, bSize);
    } else {
        printf("Word not found!\n");
    }

    // Free allocated memory
    for (int i = 0; i < bSize; i++) {
        free(temp[i]);
    }
    free(temp);
}

void helperValue(int** temp, int x_axis, int y_axis, int index){
    int tempValue = *(*(temp + x_axis) + y_axis);

    if(tempValue == 0){
        *(*(temp + x_axis) + y_axis) = index;
    } else {
        *(*(temp + x_axis) + y_axis) *= 10;
        *(*(temp + x_axis) + y_axis) += index;
    }
}
