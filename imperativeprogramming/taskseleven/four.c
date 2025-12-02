#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[31];
    int birthYear;
    char country[11];
} ActorBio;

typedef struct {
    char actorName[31];
    char movieName[21];
} ActorInMovie;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n, m;
    scanf("%d\n", &n);
    
    ActorBio *actors = (ActorBio*)malloc(n * sizeof(ActorBio));
    for (int i = 0; i < n; i++) {
        char name[100];
        scanf("\"%[^\"]\" %d \"%[^\"]\"\n", name, &actors[i].birthYear, actors[i].country);
        strcpy(actors[i].name, name);
    }
    
    scanf("%d\n", &m);
    
    ActorInMovie *movies = (ActorInMovie*)malloc(m * sizeof(ActorInMovie));
    for (int i = 0; i < m; i++) {
        char actorName[100], movieName[100];
        scanf("\"%[^\"]\" \"%[^\"]\"\n", actorName, movieName);
        strcpy(movies[i].actorName, actorName);
        strcpy(movies[i].movieName, movieName);
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (strcmp(actors[i].name, movies[j].actorName) == 0) {
                printf("\"%s\" %d \"%s\" \"%s\" \"%s\"\n", 
                       actors[i].name, actors[i].birthYear, actors[i].country,
                       movies[j].actorName, movies[j].movieName);
            }
        }
    }
    
    free(actors);
    free(movies);
    
    return 0;
}