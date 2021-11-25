/*
 * Basic string generation for brute-force attacks
 * Copyright (C) 2021 BIKRAM GHOSH

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* I chose to use an one way linked list data structure
 * to avoid restrictions on the generated string length.
 * The thing is, the list must be converted to string so
 * it could be used. This conversion have to happen in
 * each cycle and causes unnecessary slowdown.
 * 
 * Faster solution would be to implement the generation
 * directly on some staticaly allocated string with fixed
 * size (20 characters are more than enough).
 */
typedef struct charlist charlist_t;
struct charlist
{
    unsigned char character;
    charlist_t* next;
};

/* Return new initialized charlist_t element.
 *
 * Elements are initialized
 * @return charlist_t
 */
charlist_t* new_charlist_element()
{
    charlist_t* element;

    if ((element = malloc(sizeof(charlist_t))) != 0)
    {
        element->character = 0;
        element->next = NULL;
    }
    else
    {
        perror("malloc() failed.");
    }

    return element;
}

/* Free memory allocated by charlist.
 *
 * @param list Pointer at the first element.
 * @return void
 */
void free_charlist(charlist_t* list)
{
    charlist_t* current = list;
    charlist_t* next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

/* Print the charlist_t data structure.
 *
 * Iterates through the whole list and prints all characters
 * in the list including any '\0'.
 * 
 * @param list Input list of characters.
 * @return void
 */
void print_charlist(charlist_t* list)
{
    charlist_t* next = list;
    while (next != NULL)
    {
        printf("%d ", next->character);
        next = next->next;
    }
    printf("\n");
}

/* Get next character sequence.
 *
 * It treats characters as numbers (0-255). Function tries to increment
 * character in the first position. If it fails, new character is
 * added to the back of the list.
 *
 * It's basicaly a number with base = 256.
 *
 * @param list A pointer to charlist_t.
 * @return void
 */
void next(charlist_t* list)
{
    list->character++;
    if (list->character == 0)
    {
        if (list->next == NULL)
        {
            list->next = new_charlist_element();
        }
        else
        {
            next(list->next);
        }
    }
}

int main()
{
    charlist_t* sequence;
    sequence = new_charlist_element();

    while (1)
    {
        next(sequence);
        print_charlist(sequence);
    }

    free_charlist(sequence);
}

