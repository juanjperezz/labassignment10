#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
  struct Trie *children[26];
  int count;
};

// Inserts the word to the trie structure
void insert(struct Trie **pTrie, char *word)
{
  if(*pTrie == NULL){
    *pTrie = malloc(sizeof(struct Trie));
    memset((*pTrie)->children, 0, sizeof((*pTrie)->children));
    (*pTrie)->count = 0;
  }
  struct Trie *temp = *pTrie;
  for(int i = 0; i < strlen(word); i++){
    int index = word[i] - 'a';
    if(temp->children[index] == NULL){
      temp->children[index] = malloc(sizeof(struct Trie));
      memset(temp->children[index]->children, 0, sizeof(temp->children[index]->children));
      temp->children[index]->count = 0;
    }
    temp = temp->children[index];
  }
  temp->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
  for(int i = 0; i < strlen(word); i++){
    int index = word[i] - 'a';
    if(pTrie->children[index] == NULL){
      return 0;
    }
    pTrie = pTrie->children[index];
  }
  return pTrie->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
  if(pTrie != NULL){
    for(int i = 0; i < 26; i++){
      if(pTrie->children[i] != NULL){
        deallocateTrie(pTrie->children[i]);
      }
    }
    free(pTrie);
  }
  return NULL;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char* filename, char** pInWords)
{
  FILE* file = fopen(filename, "r");
  if (file == NULL) return -1;
  int wordCount = 0;

  fscanf(file, "%d\n", &wordCount);
  char word[100];
  for(int i = 0; i < wordCount; i++){
    fscanf(file, "%s\n", word);
    pInWords[i] = (char*)calloc(strlen(word) + 1, sizeof(char));
    strcpy(pInWords[i], word);
  }
  fclose(file);
  return wordCount;
  
}

struct Trie* createTrie(void){ 
    struct Trie* newTrie =  (struct Trie*)malloc(sizeof(struct Trie)); 
    for (int i=0;i<26;++i) 
        newTrie->children[i] = NULL;
    newTrie->count = 0; 
    return newTrie; 
} 

int main(void)
{
  char *inWords[256];

  //read the number of the words in the dictionary
  int numWords = readDictionary("dictionary.txt", inWords);
  for (int i=0;i<numWords;++i)
  {
    printf("%s\n",inWords[i]);
  }

  struct Trie *pTrie = createTrie();
  for (int i=0;i<numWords;i++)
  {
    insert(pTrie, inWords[i]);
  }
  // parse lineby line, and insert each word to the trie data structure
  char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
  for (int i=0;i<5;i++)
  {
    printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
  }
  pTrie = deallocateTrie(pTrie);
  if (pTrie != NULL)
    printf("There is an error in this program\n");
  return 0;
}