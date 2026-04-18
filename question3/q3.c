#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s) {
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }

    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s) {
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) {
            return np;
        }
    }

    return NULL;
}

struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL) {
            return NULL;
        } 
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free((void *) np->defn);
    }
        
    if ((np->defn = strdup(defn)) == NULL) {
        return NULL;
    }
    
    return np;
}

int intersection(int output[], int array1[], int lenArr1, int array2[], int lenArr2) {
    char key[50];
    int count = 0;

    for (int i = 0; i < lenArr1; i++) {
        sprintf(key, "%d", array1[i]);
        install(key, "1");
    }

    for (int i = 0; i < lenArr2; i++) {
        sprintf(key, "%d", array2[i]);
        struct nlist *n = lookup(key);

        if (n != NULL && strcmp(n->defn, "1") == 0) {
            output[count++] = array2[i];
            install(key, "0"); // So no double count
        }
    }

    return count;
}

int main() {
    int n1, n2;

    scanf("%d", &n1);
    int *arr1 = malloc(n1 * sizeof(int));
    if (arr1 == NULL) {
        return 1;
    }

    for (int i = 0; i < n1; i++) {
        scanf("%d", &arr1[i]);
    }

    scanf("%d", &n2);
    int *arr2 = malloc(n2 * sizeof(int));
    if (arr2 == NULL) {
        free(arr1);
        return 1;
    }

    for (int i = 0; i < n2; i++) {
        scanf("%d", &arr2[i]);
    }

    int *result = malloc((n1 < n2 ? n1 : n2) * sizeof(int));
    if (result == NULL) {
        free(arr1);
        free(arr2);
        return 1;
    }

    int resultLength = intersection(result, arr1, n1, arr2, n2);

    for (int i = 0; i < resultLength; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(arr1);
    free(arr2);
    free(result);

    return 0;
}