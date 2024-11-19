/** OPERATING SYSTEMS - BANKER'S ALGORITHM
  *  @file  bankersalgo.c
  *  @author ROM-ANN MAY P. BALINGBING      BSCS - 3C
  * 
  *  @brief This program implements the banker's algorithm. 
  *  The banker's algorithm is a resource allocation and deadlock avoidance algorithm that tests for safety by simulating the allocation of predetermined maximum       
  *  possible amounts of all resources, and then makes an "s-state" check to test for possible activities, before deciding whether allocation should be allowed to continue.
  */

#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void define_alloc_matrix(int* num_resources, int* num_processes, int** total_resources, int*** alloc_matrix);
void define_max_matrix(int* num_resources, int* num_processes, int** total_resources, int*** max_matrix);
void compute_need_matrix(int* num_resources, int* num_processes, int** alloc_matrix, int** max_matrix, int** need_matrix);
void compute_avail_matrix(int* num_resources, int* num_processes, int* total_resources, int** alloc_matrix, int* avail_matrix, int* total_alloc);
void check_safe_state(int* num_resources, int* num_processes, int** alloc_matrix, int** max_matrix, int** need_matrix, int** avail_matrix);
void print_matrix(int* num_resources, int* num_processes, int* total_resources, int** alloc_matrix, int** max_matrix, int** need_matrix, int* avail_matrix);


int main(){
    //initializations and allocations
    int num_processes, num_resources;

    printf("\tOPERATING SYSTEMS\n\tBANKER'S ALGORITHM\n======================================\n");

    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    //matrices
    int *total_resources = (int*)malloc(num_resources*sizeof(int));
    int **alloc_matrix = (int**)malloc(num_processes*sizeof(int*));
    int **max_matrix = (int**)malloc(num_processes*sizeof(int*));
    int **need_matrix = (int**)malloc(num_processes*sizeof(int*));
    int *avail_matrix = (int*)malloc(num_resources*sizeof(int));
    int *total_alloc = (int*)malloc(num_resources*sizeof(int));

    if(alloc_matrix == NULL || max_matrix == NULL || need_matrix == NULL || avail_matrix == NULL || total_resources == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    //define the total resources 
    for(int i = 0; i < num_processes; i++){
        //allocate memory for each row of the matrices
        alloc_matrix[i] = (int *)malloc(num_resources * sizeof(int));
        max_matrix[i] = (int *)malloc(num_resources * sizeof(int));
        need_matrix[i] = (int *)malloc(num_resources * sizeof(int));

        if(alloc_matrix[i] == NULL || max_matrix[i] == NULL || need_matrix[i] == NULL){
            printf("Memory allocation failed\n");
            exit(1);
        }

        if (i < num_resources) { 
        printf("Enter the number of available resources for resource %c: ", 65+i);
        scanf(" %d", &total_resources[i]);
        }
    }   
    define_alloc_matrix(&num_processes, &num_resources, &total_resources, &alloc_matrix);
    define_max_matrix(&num_resources, &num_processes, &total_resources, &max_matrix);
    compute_need_matrix(&num_resources, &num_processes, alloc_matrix, max_matrix, need_matrix);
    compute_avail_matrix(&num_resources, &num_processes, total_resources, alloc_matrix, avail_matrix, total_alloc);
    print_matrix(&num_resources, &num_processes, total_resources, alloc_matrix, max_matrix, need_matrix, avail_matrix);
    check_safe_state(&num_resources, &num_processes, alloc_matrix, max_matrix, need_matrix, &avail_matrix);

    free(alloc_matrix);
    free(max_matrix);
    free(need_matrix);
    free(avail_matrix);
    free(total_resources);
    free(total_alloc);

    return 0;
}

/** @brief This function asks for user input for the allocation matrix */
void define_alloc_matrix(int* num_processes, int* num_resources, int** total_resources, int*** alloc_matrix){
    printf("\nALLOCATION MATRIX\n");
    printf("Enter the allocation matrix each process and resource: (e.g. \"1 2 3 4\")\n");
    for(int i = 0; i < *num_processes; i++){
        for(int j = 0; j < *num_resources; j++){
            if(j == 0)
                printf("process %d resource %c - %c: ", i, 65, 65+(*num_resources-1));
            scanf(" %d", &(*alloc_matrix)[i][j]);
        }
    }
}

/** @brief This function asks for user input for the maximum matrix */
void define_max_matrix(int* num_resources, int* num_processes, int** total_resources, int*** max_matrix){
    printf("\nMAXIMUM MATRIX\n");
    printf("Enter the maximum number of resources required for each process and resource: (e.g. \"1 2 3 4\")\n");
    for(int i = 0; i < *num_processes; i++){
        for(int j = 0; j < *num_resources; j++){
            if(j==0)
                printf("process %d resource %c - %c: ", i, 65, 65+(*num_resources-1));
            scanf(" %d", &(*max_matrix)[i][j]);
        }
    }
}

/** @brief This function computes the need matrix */
void compute_need_matrix(int* num_resources, int* num_processes, int** alloc_matrix, int** max_matrix, int** need_matrix){
    for(int i = 0; i < *num_processes; i++){
        for(int j = 0; j < *num_resources; j++){
            need_matrix[i][j] = max_matrix[i][j] - alloc_matrix[i][j];
        }
    }
}

/** @brief This function computes the available matrix */
void compute_avail_matrix(int* num_resources, int* num_processes, int* total_resources, int** alloc_matrix, int* avail_matrix, int* total_alloc){
    
    for(int i = 0; i < *num_resources; i++){
        total_alloc[i] = 0;  // Initialize total_alloc[i] to 0 for each resource
        for(int j = 0; j < *num_processes; j++){
            total_alloc[i] += alloc_matrix[j][i];
        }
    }

    for(int i = 0; i < *num_resources; i++){
        avail_matrix[i] = total_resources[i] - total_alloc[i];
    }
}

/** @brief This function prints the matrices */
void print_matrix(int* num_resources, int* num_processes, int* total_resources, int** alloc_matrix, int** max_matrix, int** need_matrix, int* avail_matrix){
    // RESOURCES TABLE
    printf("\n  RESOURCES\n");
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


    //ALLOCATION MATRIX
    printf("   ALLOCATION MATRIX\n");
    printf("   +");
    for (int j = 0; j < *num_resources; j++) {
        printf("-----+");
    }
    printf("\n");

    printf("   |");
    for (int j = 0; j < *num_resources; j++) {
        printf("  %c  |", 65+j); 
    }
    printf("\n");

    // Print top border
    printf("   +");
    for (int j = 0; j < *num_resources; j++) {
        printf("-----+");
    }
    printf("\n");

    // Print data rows
    for(int i = 0; i < *num_processes; i++){
        printf("P%d |", i);
        for(int j = 0; j < *num_resources; j++){
            printf(" %3d |", alloc_matrix[i][j]);
        }
        printf("\n");

        // Print row separator
        printf("   +");
        for (int j = 0; j < *num_resources; j++) {
            printf("-----+");
        }
        printf("\n");
        
    }
    printf("\n\n");


    //MAX MATRIX
    printf("   MAX NEED MATRIX\n");
    printf("   +");
    for (int j = 0; j < *num_resources; j++) {
        printf("-----+");
    }
    printf("\n");

    printf("   |");
    for (int j = 0; j < *num_resources; j++) {
        printf("  %c  |", 65+j); 
    }
    printf("\n");

    // Print top border
    printf("   +");
    for (int j = 0; j < *num_resources; j++) {
        printf("-----+");
    }
    printf("\n");

    // Print data rows
    for(int i = 0; i < *num_processes; i++){
        printf("P%d |", i);
        for(int j = 0; j < *num_resources; j++){
            printf(" %3d |", max_matrix[i][j]);
        }
        printf("\n");

        // Print row separator
        printf("   +");
        for (int j = 0; j < *num_resources; j++) {
            printf("-----+");
        }
        printf("\n");
        
    }
    printf("\n\n");


    //NEED MATRIX
    printf("   NEED MATRIX\n");
    printf("   +");
    for (int j = 0; j < *num_resources; j++) {
        printf("-----+");
    }
    printf("\n");

    printf("   |");
    for (int j = 0; j < *num_resources; j++) {
        printf("  %c  |", 65+j); 
    }
    printf("\n");

    // Print top border
    printf("   +");
    for (int j = 0; j < *num_resources; j++) {
        printf("-----+");
    }
    printf("\n");

    // Print data rows
    for(int i = 0; i < *num_processes; i++){
        printf("P%d |", i);
        for(int j = 0; j < *num_resources; j++){
            printf(" %3d |", need_matrix[i][j]);
        }
        printf("\n");

        // Print row separator
        printf("   +");
        for (int j = 0; j < *num_resources; j++) {
            printf("-----+");
        }
        printf("\n");
        
    }
    printf("\n\n");

    //AVAILABLE MATRIX
    printf("  AVAILABLE MATRIX\n");
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
        printf(" %3d |", avail_matrix[i]);
    }
    printf("\n");

    // Print row separator
    printf("  +");
    for (int j = 0; j < *num_resources; j++) {
        printf("-----+");
    }
    printf("\n\n\n");

}

/** @brief This function checks if the system is in a safe state */
void check_safe_state(int* num_resources, int* num_processes, int** alloc_matrix, int** max_matrix, int** need_matrix, int** avail_matrix) {
    int* work = (int*)malloc(*num_resources * sizeof(int));
    int* finish = (int*)malloc(*num_processes * sizeof(int));
    int* safe_sequence = (int*)malloc(*num_processes * sizeof(int));
    int index = 0;

    // Initialize work = avail_matrix and finish[i] = 0 for all i
    for (int i = 0; i < *num_resources; i++) {
        work[i] = (*avail_matrix)[i];
    }
    for (int i = 0; i < *num_processes; i++) {
        finish[i] = 0; // 0 means not finished
    }

    printf("\nChecking for Safe State...\n");

    while (index < *num_processes) {
        int found = 0; // To check if a process is found in this pass

        for (int i = 0; i < *num_processes; i++) {
            // Check if process `i` is not finished and its need is less than or equal to work
            if (finish[i] == 0) {
                int can_allocate = 1; // Assume the process can be allocated

                for (int j = 0; j < *num_resources; j++) {
                    if (need_matrix[i][j] > work[j]) {
                        can_allocate = 0; // Process cannot proceed
                        break;
                    }
                }

                // If the process can proceed
                if (can_allocate) {
                    // Update work: add allocated resources of this process to work
                    for (int j = 0; j < *num_resources; j++) {
                        work[j] += alloc_matrix[i][j];
                    }

                    // Mark this process as finished
                    finish[i] = 1;
                    safe_sequence[index++] = i; // Add process to safe sequence

                    found = 1;
                }
            }
        }

        // If no process was found in this pass, break the loop (unsafe state)
        if (!found) {
            break;
        }
    }

    // Check if all processes are finished
    int is_safe = 1;
    for (int i = 0; i < *num_processes; i++) {
        if (finish[i] == 0) {
            is_safe = 0; // System is not in a safe state
            break;
        }
    }

    if (is_safe) {
        printf("The system is in a SAFE STATE.\n");
        printf("Safe Sequence: ");
        for (int i = 0; i < *num_processes; i++) {
            printf("P%d ", safe_sequence[i]);
        }
        printf("\n");
    } else {
        printf("The system is in an UNSAFE STATE. No safe sequence exists.\n");
    }

    // Free allocated memory
    free(work);
    free(finish);
    free(safe_sequence);
}
