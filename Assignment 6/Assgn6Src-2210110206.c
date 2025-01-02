#include <stdio.h>
#include <stdlib.h> 
#include <time.h>  
#include <math.h>

int main() {
    int process_size, logical_address_bits, page_size;
    int total_pages, total_frames;
    int choice;
    int logical_address; 
    int page_number; 

    srand(time(0)); 
    
    printf("Enter process size (bytes): ");
    scanf("%d", &process_size);
    printf("Enter logical address bits: ");
    scanf("%d", &logical_address_bits);
    printf("Enter page size (bytes): ");
    scanf("%d", &page_size);

    total_pages = process_size / page_size;

    total_frames = total_pages; 
    int *frame_allocation = (int *)malloc(total_frames * sizeof(int));
    for (int i = 0; i < total_frames; ++i) {
        frame_allocation[i] = rand() % total_frames; 
    }

    int page_number_bits = log2(process_size / page_size);
    int page_offset_bits = log2(page_size);
    int frame_number_bits = page_number_bits;
    int frame_offset_bits = page_offset_bits;
    total_pages = pow(2, page_number_bits);
    total_frames = process_size / page_size;

    printf("Logical address bits = %d\n", logical_address_bits);
    printf("Page Number Bits = %d\n", page_number_bits);
    printf("Page Offset bits = %d\n", page_offset_bits);
    printf("Physical Address Bits = %d\n", logical_address_bits);
    printf("Frame Number bits = %d\n", frame_number_bits);
    printf("Frame Offset bits = %d\n", frame_offset_bits);
    printf("Total number of pages in the Logical Address Space = %d\n", total_pages);
    printf("Total Number of frames can be allocated in Main memory = %d\n", total_frames);

    do {
        printf("\nInteractive Menu:\n");
        printf("1. Calculate number of pages for the process size\n");
        printf("2. Request address and get frame number in main memory\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Total number of pages for the process size: %d\n", total_pages);
                break;
            case 2:
                printf("Enter the logical address: ");
                scanf("%d", &logical_address);
                page_number = logical_address / page_size;
                if (page_number >= total_pages) {
                    printf("Error: Address out of range!\n");
                } else {
                    int frame_number = frame_allocation[page_number];
                    printf("Frame number in main memory: %d\n", frame_number);
                }
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);

    free(frame_allocation); 

    return 0;
}
