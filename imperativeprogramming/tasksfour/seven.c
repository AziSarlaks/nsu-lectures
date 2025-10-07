#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* gup(char* word, char* words[], int index, int word_count) {
    int len = strlen(word);
    char* prefix = malloc(len + 1); 
    
    for (int i = 1; i <= len; i++) {
        strncpy(prefix, word, i);
        prefix[i] = '\0';
        
        int is_unique = 1;
        for (int j = 0; j < word_count; j++) {
            if (j != index && strncmp(words[j], prefix, i) == 0) {
                is_unique = 0;
                break;
            }
        }
        if (is_unique) {
            return prefix;
        }
    }
    
    strcpy(prefix, word);
    return prefix;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    char* words[100];
    char buffer[101];
    int word_count = 0;
    
    
    if (fgets(buffer, 101, stdin) != NULL) {
        
        int len = strlen(buffer);
        while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
            buffer[len - 1] = '\0';
            len--;
        }
        
        
        if (buffer[0] == '\0') {
            printf("\n");
            return 0; 
        }
        
        
        int has_spaces = (strchr(buffer, ' ') != NULL);
        
        if (has_spaces) {
            
            char* token = strtok(buffer, " ");
            while (token != NULL && word_count < 100) {
                words[word_count] = malloc(strlen(token) + 1);
                strcpy(words[word_count], token);
                word_count++;
                token = strtok(NULL, " ");
            }
        } else {
            
            words[word_count] = malloc(strlen(buffer) + 1);
            strcpy(words[word_count], buffer);
            word_count++;
            
            
            while (fgets(buffer, 101, stdin) != NULL) {
                int len = strlen(buffer);
                while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
                    buffer[len - 1] = '\0';
                    len--;
                }
                if (buffer[0] == '\0') break; 
                
                words[word_count] = malloc(strlen(buffer) + 1);
                strcpy(words[word_count], buffer);
                word_count++;
            }
        }
    }
    
    
    char* prefixes[100];
    for (int i = 0; i < word_count; i++) {
        prefixes[i] = gup(words[i], words, i, word_count);
    }
    
    
    for (int i = word_count - 1; i >= 0; i--) {
        printf("%s", prefixes[i]);
        if (i > 0) printf("#");
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}