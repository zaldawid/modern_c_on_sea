#include <stdio.h>
#include "include/word_counter.h"

void process_line(word_counter_s* counter, char* line) {

    const char* sep = "\t” (),.;:?!\"\n'";

    char* token = strtok(line, sep);

    while (token) {
        if (strlen(token))
            increment(counter, token);
        token = strtok(NULL, sep);
    }
}

word_counter_s process_file(const char* fileName) {

    word_counter_s counter = cnt_create();

    FILE* fp = fopen(fileName, "r");


    if (fp) {
        int count = 1;
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), fp)) {
            process_line(&counter, buffer);
//            printf("Line: %d, size: %d\n", count, counter.size);
            ++count;
        }
    }
    return counter;
}


int main() {
    printf("Hello, World!\n");
    word_counter_s counter = process_file("alice0.txt");
    const char* words[] = {"Alice", "the", "her", "have", "is", "of", "Rabbit", "rabbit"};
    for (int i = 0; i < (int)(sizeof(words)/sizeof(words[0])); ++i) {
        printf("%s: %ld\n", words[i], get_or_default(&counter, words[i], 0));
    }
    cnt_destroy(&counter);
    return 0;
}

