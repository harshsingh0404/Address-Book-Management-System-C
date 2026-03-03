#include "contact.h"
#include <string.h>
#include"validation.h"
#include<stdio.h>

// validation for the name is correct or not
int validateName(char *name)
{
    int i = 0;
    while (name[i] != '\0')
    {
        if (!((name[i] >= 'A' && name[i] <= 'Z') ||
              (name[i] >= 'a' && name[i] <= 'z') ||
              name[i] == ' '))
        {
            return 0;   // Failure
        }
        i++;
    }
    return 1; // Success
}

// validation for the mobile number is correct or not
int validateMobile(char *phone)
{
    int len = strlen(phone);

    // Must be exactly 10 digits
    if (len != 10)
        return 0;

    // Check digits only
    for (int i = 0; i < len; i++)
    {
        if (phone[i] < '0' || phone[i] > '9')
            return 0;
    }

    return 1; // Success
}

// validation for the gmail is correct or not
int validategmail(char *email)
{
    // 1. Check for spaces in email
    for (int i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == ' ')
        {
            //printf("Spaces are not allowed in email!\n");
            return 0;
        }
    }

    // 2. Find '@'
    char *at = strchr(email, '@');
    if (at == NULL)
        return 0;

    // 3. Username cannot be empty
    if (at == email)
        return 0;

    // 4. Check domain exactly "@gmail.com"
    if (strcmp(at, "@gmail.com") != 0)
        return 0;

    return 1; // valid
}



