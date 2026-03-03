#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include"validation.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    if(addressBook->contactCount == 0)
    {
        printf("NO CONTACT FOUND.\n");
        return;
    }
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        printf("%-20s %-15s %-30s\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
}

void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);

}
void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
void createContact(AddressBook *addressBook)
{	
    /* Define the logic to create a Contacts */
    char name[50];
    char phone[15];
    char email[50];
    int res=0;
// ------------------------ add BY NAME ------------------------
do 
    {
        printf("Enter Name: ");
        scanf(" %[^\n]", name); // read the value from the user
        // call the function
        res = validateName(name);
        if (res == 0)
        printf("Invalid Name! Try again.\n"); // this is for the print the invalide after the function call
    } 
    while (res == 0);

    // ------------------------ add BY number ------------------------ 
while(1) //loop until a valid and unique mobile number is entered
{
    printf("Enter Mobile Number: ");
    scanf("%s", phone);
    if (!validateMobile(phone)) //check if number is 10 digits or not
    {
        printf("Invalid Mobile! Must be 10 digits.\n");
        continue; //ask again if invalid
    }

    
// DUPLICATE CHECK HERE
    int duplicate = 0; //flag to track if number already exists
    for (int i = 0; i < addressBook->contactCount; i++) // loop through all saved contacts
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0) //compare entered number with exiting
        {
            duplicate = 1; //mark as duplicate
            break; //exit loop after finding duplicate
        }
    }
    if(duplicate) // if number already exists
    {
        printf("Duplicate Phone! Enter a different number.\n");
        continue; // ask again
    }
    break; //number is valid + unique → exit loop
}


// ------------------------ add BY email ------------------------
while(1) //repeat until a valid and unique email is entered
{
    printf("Enter email: ");
    scanf(" %s", email);  //read full email including spaces

    if (!validategmail(email)) // validate format:
    {
        printf("Invalid email!\n");
        continue; // ask again if invalid
    }
    

    // DUPLICATE CHECK HERE
    int duplicate = 0; //flag for checking if email already exists
    for (int i = 0; i < addressBook->contactCount; i++) //loop through all saved contacts
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0) //compare with existing emails
        {
            duplicate = 1; //mark if duplicate found 
            break;        //stop checking further
        }
    }

    if (duplicate) //if email already exists
    {
        printf("\nDuplicate email! Enter a different email.\n");
        continue; // ask again
    }

    break;  // emailis valid and unique exit loop
}

// SAVE CONTACT
strcpy(addressBook->contacts[addressBook->contactCount].name, name);    // save name
strcpy(addressBook->contacts[addressBook->contactCount].phone, phone); // save phone
strcpy(addressBook->contacts[addressBook->contactCount].email, email);// save email

addressBook->contactCount++; //increase total contact count 

printf("\nContact saved successfully!\n"); //comfirmation message
}


void searchContact(AddressBook *addressBook)
{
    int choice;             //User choice for search category 
    char temp[100];        //Temporary input buffer
    int found = 0;        //Flag to track if contact found

    printf("\n--- Search Contact ---\n");
    printf("Search by:\n");
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        // ------------------------ SEARCH BY NAME ------------------------
        case 1:
            do {
                printf("Enter Name: ");
                scanf(" %[^\n]", temp); //Read full name with spaces

                if (validateName(temp) == 0)
                    printf("Invalid Name! Try again.\n"); //Name validation check

            } while (validateName(temp) == 0); //repeat until valid name 

            for (int i = 0; i < addressBook->contactCount; i++) // loop through contact 
            {
                if (strcmp(addressBook->contacts[i].name, temp) == 0) //Match name
                {
                    printf("\nContact Found:\n");
                    printf("Name  : %s\n", addressBook->contacts[i].name);
                    printf("Phone : %s\n", addressBook->contacts[i].phone);
                    printf("Email : %s\n", addressBook->contacts[i].email);
                    found = 1; //Mark contact as found
                    break; // Exit name search loop
                }
            }
            
            if (!found)
                printf("Contact Not Found!\n"); //Display if no contact matched 
                break;                         //Exite switch after case 1

        // ------------------------ SEARCH BY PHONE ------------------------
        case 2:
            do {
                printf("Enter Phone Number: ");
                scanf("%s", temp); //read phone number input

                if (validateMobile(temp) == 0)
                    printf("Invalid Phone! Must be 10 digits.\n"); 

            } while (validateMobile(temp) == 0); //Loop through contact 

            for (int i = 0; i < addressBook->contactCount; i++) //Match phone 
            {
                if (strcmp(addressBook->contacts[i].phone, temp) == 0)
                {
                    printf("\nContact Found:\n");
                    printf("Name  : %s\n", addressBook->contacts[i].name);
                    printf("Phone : %s\n", addressBook->contacts[i].phone);
                    printf("Email : %s\n", addressBook->contacts[i].email);
                    found = 1; //Mark contact as found
                    break;    //Exit phone search loop
                }
            }

            if (!found)
                printf("Contact Not Found!\n"); //Display if no contact matched
            break;                             //Exit switch after case 2

        // ------------------------ SEARCH BY EMAIL ------------------------
        case 3:
            do 
            {
                printf("Enter Email: ");
                scanf("%s", temp);          //Read email input

                if (validategmail(temp) == 0) 
                    printf("Invalid Email! Must contain @ and .com\n");

            } while (validategmail(temp) == 0);

            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].email, temp) == 0)
                {
                    printf("\nContact Found:\n");
                    printf("Name  : %s\n", addressBook->contacts[i].name);
                    printf("Phone : %s\n", addressBook->contacts[i].phone);
                    printf("Email : %s\n", addressBook->contacts[i].email);
                    found = 1;
                    break;
                }
            }

            if (!found)
                printf("Contact Not Found!\n");
            break;

        case 4:
            return;

        default:
            printf("Invalid Choice! Try Again.\n");
    }
}
void editContact(AddressBook *addressBook)
{
	 //Define the logic for Editcontact 

    int choice;
    char temp[100];
    int found = 0, index = -1;

    printf("\n--- Search Contact ---\n");
    printf("Search by:\n");
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    switch (choice)
    {
        // ------------------------ SEARCH BY NAME ------------------------
        case 1:
        {
            printf("Enter Name: ");
            scanf(" %[^\n]", temp);

            int matchIndexes[100];
            int matchCount = 0;

            // find all matches
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].name, temp) == 0)
                {
                    matchIndexes[matchCount++] = i;
                }
            }

            if (matchCount == 0)
            {
                printf("Contact Not Found!\n");
                return;
            }

            if (matchCount == 1)
            {
                index = matchIndexes[0];
                found = 1;
            }
            else
            {
                // multiple contacts found — show list
                printf("\nMultiple contacts found with name '%s':\n", temp);
                for (int i = 0; i < matchCount; i++)
                {
                    int idx = matchIndexes[i];
                    printf("%d. Phone: %s | Email: %s\n",
                           i + 1,
                           addressBook->contacts[idx].phone,
                           addressBook->contacts[idx].email);
                }

                int sel;
                printf("Select which contact to edit (1-%d): ", matchCount);
                scanf("%d", &sel);

                if (sel < 1 || sel > matchCount)
                {
                    printf("Invalid Selection!\n");
                    return;
                }

                index = matchIndexes[sel - 1];
                found = 1;
            }
        }
        break;
        // ------------------------ SEARCH BY PHONE ------------------------
        case 2:
                printf("Enter Phone Number: ");
                scanf("%s", temp);
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].phone, temp) == 0)
                {
                    found = 1;
                    index = i;
                    break;
                }
            }
            break;

        // ------------------------ SEARCH BY EMAIL ------------------------
        case 3:
                printf("Enter Email: ");
                scanf("%s", temp);
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].email, temp) == 0)
                {
                    found = 1;
                    index = i;
                    break;
                }
            }
            break;

        case 4:
            return;

        default:
            printf("Invalid Choice!\n");
            return;
    }
    if (!found)
    {
        printf("Contact Not Found!\n");
        return;
    }
  // ----------------------------------- EDIT MENU -----------------------------------
    printf("\nContact Found:\n");
    printf("1. Edit Name\n");
    printf("2. Edit Phone\n");
    printf("3. Edit Email\n");
    printf("4. Cancel\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    char newValue[100];
    int res;
    switch(choice)
    {
        case 1:
        // ------------------------ Edit BY NAME ------------------------
        do 
        {
            printf("Enter New Name: ");
            scanf(" %[^\n]", newValue);
            res = validateName(newValue);
                if (res == 0)
                {
                    printf("Invalid Name! Try again.\n");
                    continue;
                } }
        while (res == 0);

            strcpy(addressBook->contacts[index].name, newValue);
            printf("Name Updated Successfully!\n");
            break;

        
            // ------------------------ Edit BY Phone ------------------------

         case 2:
            do 
            {
                printf("Enter New Phone: ");
                scanf(" %[^\n]", newValue);

                res = validateMobile(newValue);
                if (res == 0)
                {
                    printf("Invalid Phone! Try again.\n");
                    continue;
                }

                // Duplicate check
                int duplicate = 0;
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (i == index) continue;  
                    if (strcmp(addressBook->contacts[i].phone, newValue) == 0)
                    {
                        duplicate = 1;
                        break;
                    }
                }

                if (duplicate)
                {
                    printf("Phone already exists! Enter a different number.\n");
                    res = 0;
                }

            } while (res == 0);

            strcpy(addressBook->contacts[index].phone, newValue);
            printf("Phone Updated Successfully!\n");
            break;

            // ------------------------ Edit BY email ------------------------
                case 3:
            do 
            {
                printf("Enter New Email: ");
                scanf(" %[^\n]", newValue);

                res = validategmail(newValue);
                if (res == 0)
                {
                    printf("Invalid Email! Try again.\n");
                    continue;
                }

                // Duplicate check
                int duplicate = 0;
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (i == index) continue;  
                    if (strcmp(addressBook->contacts[i].email, newValue) == 0)
                    {
                        duplicate = 1;
                        break;
                    }
                }

                if (duplicate)
                {
                    printf("Email already exists! Enter a different email.\n");
                    res = 0;
                }
        } while (res == 0);

            strcpy(addressBook->contacts[index].email, newValue);
            printf("email Updated Successfully!\n");
            break;
        case 4:
        return;

        default:
        {
            printf("Invalid Choice!\n");
        }
    }
}
void deleteContact(AddressBook *addressBook)
{
    int choice;
    char temp[100];
    int found = 0, index = -1;

    printf("\n--- Delete Contact ---\n");
    printf("Search contact to delete by:\n");
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        // ------------------------ DELETE BY NAME (supports duplicates) ------------------------
        case 1:
        {
            printf("Enter Name: ");
            scanf(" %[^\n]", temp);

            int matchIndexes[100];
            int matchCount = 0;

            // Find all contacts with this name
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].name, temp) == 0)
                {
                    matchIndexes[matchCount] = i; // store index of matched contact
                    matchCount++;
                }
            }

            if (matchCount == 0)
            {
                printf("Contact Not Found!\n");
                return;
            }

            if (matchCount == 1)
            {
                index = matchIndexes[0]; // Direct delete if only 1 match
                found = 1;
                break;
            }

            // Multiple contacts found → ask user to select exact one
            printf("\nMultiple contacts found with name '%s':\n", temp);
            for (int i = 0; i < matchCount; i++)
            {
                int idx = matchIndexes[i];
                printf("%d. Phone: %s | Email: %s\n",
                       i + 1,
                       addressBook->contacts[idx].phone,
                       addressBook->contacts[idx].email);
            }

            int sel;
            printf("Enter which one to delete (1-%d): ", matchCount);
            scanf("%d", &sel);

            if (sel < 1 || sel > matchCount)
            {
                printf("Invalid Selection!\n");
                return;   //user selected wrong option
            }

            index = matchIndexes[sel - 1]; // select correct contact
            found = 1;
            break;
        }

        // ------------------------ DELETE BY PHONE ------------------------
        case 2:
            printf("Enter Phone Number: ");
            scanf("%s", temp);
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].phone, temp) == 0)
                {
                    found = 1;
                    index = i;  // save index of contact
                    break;
                }
            }
            break;

        // ------------------------ DELETE BY EMAIL ------------------------
        case 3:
            printf("Enter Email: ");
            scanf("%s", temp);
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].email, temp) == 0)
                {
                    found = 1;
                    index = i; //save index of matched contant
                    break;
                }
            }
            break;

        case 4:
            return; //exit delete menu

        default:
            printf("Invalid Choice!\n");
            return; 
    }

    if (!found)
    {
        printf("Contact Not Found!\n");
        return; //Nothing Matched
    }

    // ------------------------ SHOW CONTACT + CONFIRM ------------------------
    printf("\nContact Found:\n");
    printf("Name  : %s\n", addressBook->contacts[index].name);
    printf("Phone : %s\n", addressBook->contacts[index].phone);
    printf("Email : %s\n", addressBook->contacts[index].email);

    printf("\nAre you sure you want to delete this contact? (y/n): ");
    char confirm;
    scanf(" %c", &confirm);

    if (confirm != 'y' && confirm != 'Y')
    {
        printf("Delete Cancelled.\n");
        return; //user cancelled deletion
    }

    // ------------------------ DELETE (SHIFT LEFT) ------------------------
    for (int i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1]; // shift left
    }

    addressBook->contactCount--; //reduce total count

    printf("Contact Deleted Successfully!\n");
}

