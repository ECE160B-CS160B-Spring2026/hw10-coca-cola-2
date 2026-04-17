#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 1000
#define BUFSIZE 1000 

typedef struct node {
	char* data;
	int count;
	struct node *left_child; 
	struct node *right_child;
} node;

typedef struct {
	char *text;
	int count;
} Word;

void makearray(node *p, node **list, int *i);
void sortarray(node **list, int n);
void arrayprint(node **list, int n);
int getword(char *word, int lim);
int getch(void);
void ungetch(int c);

node* makespacefortree(){
	return (node*)malloc(sizeof(node));
}

node* add_node(node* n, char* word){

	if (n == NULL) {
		n = makespacefortree();
		n->data = strdup(word);
		n->left_child = NULL; 
		n->right_child = NULL;
		n->count = 1;
	} else if(strcmp(word, n->data) < 0) {
		n->left_child = add_node(n->left_child, word);
	} else if(strcmp(word, n->data) > 0){
		n->right_child = add_node(n->right_child, word);
	} else if (strcmp(word, n->data) == 0) {
		n->count++;
	}

	return n; 

}

int main(int argc, char*argv[]) {
	
	char word[MAXLINE];
	node* tree = NULL;
	

	node *list[10000];
	int n = 0;

	while(getword(word, MAXLINE) != EOF) {
		tree = add_node(tree, word);
	}

	makearray(tree, list, &n);
	sortarray(list, n); 
	arrayprint(list, n);

	return 0; 
}


void makearray(node *p, node **list, int *i){

	if (p == NULL) {
		return;
	}

	makearray(p->left_child, list, i); 
	list[*i] = p; 
	(*i)++;
	makearray(p->right_child, list, i);
}


void sortarray(node **list, int n){

	for(int i = 0; i < n - 1; i++){
		for(int j = i + 1; j < n; j++){
			if(list[i]->count < list[j]->count){
				node *tnode = list[i];
				list[i] = list[j];
				list[j] = tnode; 
			}
		}
	}
}

void arrayprint(node **list, int n) {
	for (int i = 0; i < n; i++){
		printf("%s: %d\n", list[i]->data, list[i]->count);
	}
}

int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;

    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for ( ; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }

    *w = '\0';

    return c;
}

char buf[BUFSIZE]; 
int bufp = 1; 

int getch(void) 
{
    return (bufp > 1) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many caracters\n");
    else
        buf[bufp++] = c;
}	
