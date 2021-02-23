//required pre-processor directives
#include<stdio.h>
#include<stdlib.h>

//implementing Trie as a data structure
typedef struct Node {
	char data;
	struct Node* child[26]; //26 - ary tree implemented to hold the next child character
	int word_end; //denotes the count of word present in the dictionary of words
} TrieNode;

//initialising a Trie Data structure
TrieNode* init() {
	TrieNode* root = (TrieNode*)malloc(sizeof(TrieNode));
	root->data = '$';
	for (int i = 0; i < 26; i++)	(*root).child[i] = NULL;
	root->word_end = 0;
	return root;
}

//function to insert a new word in the dictionary
void insert_word(TrieNode** root, char word[], int len) {
	TrieNode* head = *root;
	for(int i = 0; i < len; i++) {
		if(head->child[(int)(word[i] - 'a')] == NULL){
		//	printf("%d\n", (int)word[i] - 'a');
			TrieNode* ptr = (TrieNode*)malloc(sizeof(TrieNode));
			ptr->word_end = 0;
			ptr->data = word[i];
			head->child[(int)(word[i] - 'a')] = ptr; 
			head = ptr;
		}	
		else {
		    //printf("Hello\n");   
		    head = head->child[(int)(word[i] - 'a')];
		}
	}
	head->word_end += 1; // incrementing the word end value to support multiple inserion of the same string 
}

//function to search the presence of word in a dictionary
int search_word (TrieNode* root, char word[], int len) {
    
	TrieNode* head = root;
	for(int i = 0; i < len; i++) {
		if(head->child[(int)(word[i] - 'a')] == NULL)
			return 0;
		head = head->child[(int)word[i] - 'a'];
	}
	return head->word_end > 0;
}

//function to delete a word from the dictionary
void delete_word (TrieNode** root, char word[], int len) {
    int present = search_word(*root, word, len); //check if the word exists or not
    if(present){
        TrieNode* head = *root;
        for(int i = 0; i < len; i++) {
            head = head->child[(int)(word[i] - 'a')];
        }
        head->word_end -= 1;
    }
    else {
        printf("Word doesn't exist !\n");
        return;
    }
}

//driver funcion to check the utility
int main() {
    TrieNode* root = init();
    insert_word(&root, "abba", 4);
    insert_word(&root, "abcd", 4);
    insert_word(&root, "aba", 3);
    insert_word(&root, "aba", 3);
    insert_word(&root, "ab", 2);
    
    printf("%d\n", search_word(root, "abcd", 4));
    printf("%d", search_word(root, "ab", 2));
    
    delete_word(&root, "aba", 3);
    delete_word(&root, "aba", 3);
    printf("%d", search_word(root, "aba", 3));
	return 0;
}

