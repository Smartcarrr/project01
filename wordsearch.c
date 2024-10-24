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

void findNeighbor(char** arr, char* word, int i, int j){
    if(*word == '\0'){
        printf("Found\n");
        return;
    }
    int iMax = i+1, jMax = j+1;
    int iMin = i-1, jMin = j-1;
    if(bSize < iMax){
        iMax = bSize-1;
    }
    if(iMin < 0){
        iMin = 0;
    }
    if(bSize <= jMax){
        jMax = bSize-1;
    }
    if(jMin < 0){
        jMin = 0;
    }
    for(int x = iMin; x <= iMax; x++){
        for(int z = jMin; z <= jMax; z++){
            printf("%c:%c  ", *word, *(*(arr + x) + z));
            if(*word == *(*(arr + x) + z)){
                printf("\n");
                findNeighbor(arr, word+1, x, z);
            }
        }
    }
}

void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...
    int z = 1;
    char **pathArr = (char**)malloc(bSize * sizeof(char*));
    for(int i = 0; i < bSize; i++){
        *(pathArr + i) = (char*)malloc(bSize * sizeof(char));
        for(int j = 0; j < bSize; j++){
            *(*(pathArr + i) + j) = '0';
        }
    }

    for(int i = 0; i < bSize; i++){
        for(int j = 0; j < bSize; j++){
            if(*word == *(*(arr + i) + j)){
                findNeighbor(arr, word+1, i, j);
            }
        }
    }

    
    printPuzzle(pathArr);
}


