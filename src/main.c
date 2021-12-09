#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define FILE_NAME "data.dat"
#define STRING_MAX_LEN 50

typedef struct user
{
    char name[STRING_MAX_LEN];
    char phone_number[STRING_MAX_LEN];
    char email[STRING_MAX_LEN];
    struct user *next;
} User;

bool match(char* to_search, char* target) {
    return strstr(to_search, target) != NULL;
}

char* random_email(unsigned int length_greater_than_11) {
    const char* suffix = "@gmail.com";
    // 11 reserved, with \0
    
    const unsigned int random_part_length = length_greater_than_11 - strlen(suffix) - 1;
    
    char *random_part = malloc((random_part_length * sizeof(char)) + 1);
    char *output = malloc(length_greater_than_11 * sizeof(char));
    
    srand((unsigned int)(time(NULL)));

    const char random_char_list[] = "abcdefg";

    unsigned int i = 0;
    for(i = 0; i < random_part_length; i++)
	{
	    random_part[i] = random_char_list[rand() % (sizeof random_char_list - 1)];
	}
    random_part[random_part_length] = '\0';

    snprintf(output, length_greater_than_11, "%s%s", random_part, suffix);
	return output;
}

void print_linked_list(User* first_user_ptr) {
    User* ptr = first_user_ptr;
    while (ptr != NULL)
    {
        printf("address = %p, ", ptr);
        printf("name = \"%s\" ", ptr->name);
        printf("phone number = \"%s\" ", ptr->phone_number);
        printf("email = \"%s\" ", ptr->email);
        printf("next = %p\n", ptr->next);
        ptr = ptr->next;
    }
}

void save_linked_list_to_file(FILE* fp, User* first_user_ptr) {
    User* ptr = first_user_ptr;
    while (ptr != NULL)
    {
        fprintf(fp, "%s %s %s\n", ptr->name, ptr->phone_number, ptr->email);
        ptr = ptr->next;
    }
}

int main()
{
    FILE *fp = NULL;

    while ((fp = fopen(FILE_NAME, "r+")) == NULL)
    {
        printf("%s not exists, creating...\n", FILE_NAME);
        fp = fopen(FILE_NAME, "w+");
        if (fp != NULL)
        {
            printf("%s is created!\n", FILE_NAME);
            fclose(fp);
        }
    }
    printf("reading %s!\n", FILE_NAME);

    User *first_user_ptr = NULL;
    User *prev_user_ptr = NULL;
    User *current_user_ptr = NULL;

    while (
        (current_user_ptr = (User *)malloc(sizeof(User))) &&
        (fscanf(fp, "%s %s %s\n",
                current_user_ptr->name,
                current_user_ptr->phone_number,
                current_user_ptr->email) != EOF))
    {
        if (first_user_ptr == NULL)
        {
            first_user_ptr = current_user_ptr;
        }

        if (prev_user_ptr != NULL)
        {
            prev_user_ptr->next = current_user_ptr;
        }

        current_user_ptr->next = NULL;

        prev_user_ptr = current_user_ptr;
    }

    printf("file content is stored in linkedlist!\n");

    printf("\n");
    {
        printf("Now we print out our linkedlist as below!\n");
        print_linked_list(first_user_ptr);

    }

    printf("\n");
    {
        printf("Now we modify our linkedlist!\n");
        printf("Say, we search for the user name \"peter\" (case sensitive), then we modify his email!\n");

        User* ptr = first_user_ptr;

        while (ptr != NULL)
        {
            printf("address = %p, ", ptr);
            printf("name = \"%s\" ", ptr->name);
            printf("phone number = \"%s\" ", ptr->phone_number);
            printf("email = \"%s\" ", ptr->email);

            if (match(ptr->name, "peter")) {
                printf("(We find \"%s\" here!), generating new email... ", ptr->name);
                strcpy(ptr->email, random_email(20));
                printf("updated email = %s ", ptr->email);
            }

            printf("next = %p\n", ptr->next);
            ptr = ptr->next;
        }
    }

    printf("\n");
    {
        printf("Now we delete a record from our linkedlist!\n");
        printf("Say, we search for the user name \"billy\" (case sensitive), then we delete!\n");
        
        User **user_indirect = &first_user_ptr;
        while (strcmp((*user_indirect)->name, "billy")) {
            user_indirect = &(*user_indirect)->next;
        }
        *user_indirect = (*user_indirect)->next;
    }

    printf("\n");
    {
        printf("Now we check our linkedlist!\n");
        print_linked_list(first_user_ptr);
    }


    printf("\n");
    {
        printf("Now we save our linkedlist to %s!\n", FILE_NAME);
        fclose(fp);

        fp = fopen("data.dat", "w");
        save_linked_list_to_file(fp, first_user_ptr);
        fclose(fp);
    }

    printf("\n");
    printf("DONE! Bye bye!\n");

    system("pause");
    return 0;
}