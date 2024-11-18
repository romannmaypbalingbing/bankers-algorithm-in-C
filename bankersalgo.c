/** OPERATING SYSTEMS - BANKER'S ALGORITHM
  *  @file  bankersalgo.c
  *  @author ROM-ANN MAY P. BALINGBING      BSCS - 3C
  * 
  *  @brief This program implements the banker's algorithm. 
  *  The banker's algorithm is a resource allocation and deadlock avoidance algorithm that tests for safety by simulating the allocation of predetermined maximum       *  possible amounts of all resources, and then makes an "s-state" check to test for possible activities, before deciding whether allocation should be allowed to    *  *  continue.
  */

#include <stdio.h>
#include <stdlib.h>


void define_alloc_matrix(int* num_resources, int* num_processes, int** total_resources, int*** alloc_matrix);
void define_max_matrix(int* num_resources, int* num_processes, int** total_resources, int*** max_matrix);
void compute_need_matrix(int* num_resources, int* num_processes, int** alloc_matrix, int** max_matrix, int** need_matrix);
void compute_avail_matrix(int* num_resources, int* num_processes, int** alloc_matrix, int** avail_matrix);
void check_safe_state(int* num_resources, int* num_processes, int** alloc_matrix, int** max_matrix, int** need_matrix, int** avail_matrix);
void print_matrix(int* num_resources, int* num_processes, int* total_resources);


int main(){
    //initializations and allocations
    int num_processes, num_resources;

    printf("\tOPERATING SYSTEMS\n\tBANKER'S ALGORITHM\n======================================\n");

    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);
    printf("Number of resources: %d\nNumber of processes: %d\n", num_resources, num_processes);

    //matrices
    int *total_resources = (int*)malloc(num_resources*sizeof(int));
    int **alloc_matrix = (int**)malloc(num_processes*sizeof(int*));
    int **max_matrix = (int**)malloc(num_processes*sizeof(int*));
    int **need_matrix = (int**)malloc(num_processes*sizeof(int*));
    int *avail_matrix = (int*)malloc(num_resources*sizeof(int));

    if(alloc_matrix == NULL || max_matrix == NULL || need_matrix == NULL || avail_matrix == NULL || total_resources == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    //define the total resources 
    for(int i = 0; i < num_processes; i++){
        alloc_matrix[i] = (int *)malloc(num_resources * sizeof(int));
        max_matrix[i] = (int *)malloc(num_resources * sizeof(int));
        need_matrix[i] = (int *)malloc(num_resources * sizeof(int));

        if(alloc_matrix[i] == NULL || max_matrix[i] == NULL || need_matrix[i] == NULL){
            printf("Memory allocation failed\n");
            exit(1);
        }

        if (i < num_resources) {  // Make sure you don't go beyond total_resources bounds
        printf("Enter the number of available resources for resource %c: ", 65+i);
        scanf(" %d", &total_resources[i]);
        }
    }   
    //define_alloc_matrix(&num_processes, &num_resources, &total_resources, &alloc_matrix);
    // define_max_matrix(&num_resources, &num_processes, &total_resources, &max_matrix);

    system("cls");
    print_matrix(&num_resources, &num_processes, total_resources);

    return 0;
}


void define_alloc_matrix(int* num_processes, int* num_resources, int** total_resources, int*** alloc_matrix){
    for(int i = 0; i < *num_processes; i++){
        for(int j = 0; j < *num_resources; j++){
            if(j == 0)
                printf("Enter the number of resources allocated for process %d for resource %c - %c: ", i, 65, 65+*num_resources);
                scanf(" %d", &(*alloc_matrix)[i][j]);
        }
    }
}

void define_max_matrix(int* num_resources, int* num_processes, int** total_resources, int*** max_matrix){
    printf("Enter the maximum number of resources required for each process and resource: \n");
    for(int i = 0; i < *num_processes; i++){
        for(int j = 0; j < *num_resources; j++){
            printf("process %d resource %c: ", i, 65+j);
            scanf(" %d", &(*max_matrix)[i][j]);
        }
    }
}

void print_matrix(int* num_resources, int* num_processes, int* total_resources){
    // RESOURCES TABLE
    printf("  RESOURCES\n");
    // Print row separator
    printf("  +");
    for (int j = 0; j < *num_resources; j++) {
        printf("-----+");
    }
    printf("\n");

    printf("  |");
    for (int j = 0; j < *num_resources; j++) {
        printf("  %c  |", 65+j); 
    }
    printf("\n");

    // Print top border
    printf("  +");
    for (int j = 0; j < *num_resources; j++) {
        printf("-----+");
    }
    printf("\n");

    // Print data rows
    printf("  |");
    for(int i = 0; i < *num_resources; i++){
        printf(" %3d |", total_resources[i]);
    }
    printf("\n");

    // Print row separator
    printf("  +");
    for (int j = 0; j < *num_resources; j++) {
        printf("-----+");
    }
    printf("\n\n\n");

    //
}
