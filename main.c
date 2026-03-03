/***************************************************************
 *             ADDRESS BOOK MANAGEMENT SYSTEM
 * ------------------------------------------------------------
 *  Project        : Contact Management System in C
 *  Description    : Allows user to add, edit, delete and search
 *                   contacts with validation and duplicate check.
 *                   Stores Name, Mobile Number and Email ID.
 *
 *  Features       :
 *      → Add new contact with input validation
 *      → Prevent duplicate Phone and Email
 *      → Search the contact using name,number,email 
 *      → Edit and Delete existing contact
 *      → Display all saved contacts 
 *
 *  Created By     : Harsh Singh
 *  Language       : C Programming
 *  Date           : 
 ***************************************************************/

#include <stdio.h>
#include "contact.h"

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book
    int sortChoice = 0;

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
           case 5:          
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
    
       return 0;
}
