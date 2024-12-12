#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

char** split_string(const char* str, int* word_count) {
    if (str == NULL) {
        *word_count = 0;
        return NULL;
    }

    char* temp_str = _strdup(str);
    if (temp_str == NULL) {
        *word_count = 0;
        return NULL;
    }

    int count = 0;
    char* token = strtok(temp_str, " \t\n");
    while (token != NULL) {
        count++;
        token = strtok(NULL, " \t\n");
    }

    char** words = (char**)malloc(count * sizeof(char*));
    if (words == NULL) {
        free(temp_str);
        *word_count = 0;
        return NULL;
    }

    strcpy(temp_str, str);
    token = strtok(temp_str, " \t\n");
    int index = 0;
    while (token != NULL && index < count) {
        words[index] = _strdup(token);
        if (words[index] == NULL) {

            for (int i = 0; i < index; i++) {
                free(words[i]);
            }
            free(words);
            free(temp_str);
            *word_count = 0;
            return NULL;
        }
        index++;
        token = strtok(NULL, " \t\n");
    }

    free(temp_str); 
    *word_count = count;
    return words;
}

void free_words(char** words, int word_count) {
    for (int i = 0; i < word_count; i++) {
        free(words[i]);
    }
    free(words);
}

int main() {
    setlocale(LC_ALL, "RU");
    const char* text = "Це приклад рядка для розбиття на слова.";
    int word_count = 0;

    char** words = split_string(text, &word_count);
    if (words == NULL) {
        printf("Помилка виділення пам'яті або вхідний рядок порожній.\n");
        return 1;
    }

    printf("Розбиття рядка на слова:\n");
    for (int i = 0; i < word_count; i++) {
        printf("%s\n", words[i]);
    }

    free_words(words, word_count);
    return 0;
}
