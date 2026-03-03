#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.csv", "w");

    if (fp == NULL)
    {
        printf("File not opening\n");
        return;
    }

    // Write contact count
    fprintf(fp, "%d\n", addressBook->contactCount);

    // Write CSV rows
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fp);
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr;
    fptr = fopen("contacts.csv", "r");

    if (fptr == NULL)
    {
        printf("Failed to open file\n");
        return;
    }

    // Read contact count
    fscanf(fptr, "%d\n", &addressBook->contactCount);

    // Read each contact line
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fptr, "%49[^,],%19[^,],%49[^\n]\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    fclose(fptr);
}
