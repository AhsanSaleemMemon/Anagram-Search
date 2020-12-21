#include<iostream>
#include<cstdlib>
#include <cstring>
#include<string>
#include<cstdio>
#include <fstream>
#include <cctype>
#include <algorithm>
using namespace std;
const int TABLE_SIZE = 200000;
 
/*
 * HashNode Class Declaration
 */
class HashNode
{
  public:
    string key;
    string anagram;
    HashNode* next;
    HashNode(string key, string anagram)
    {   
        this->key = key;
        this->anagram = anagram;
        this->next = NULL;
    }
};
 
/*
 * HashMap Class Declaration
 */
class HashMap1
{
    private:
        HashNode** htable;
    public:
        HashMap1()
        {   
            htable = new HashNode*[TABLE_SIZE];
            for (int i = 0; i < TABLE_SIZE; i++)
                htable[i] = NULL;
        }
        ~HashMap1()
        {
            for (int i = 0; i < TABLE_SIZE; ++i)
	    {
                HashNode* entry = htable[i];
                while (entry != NULL)
	        {
                    HashNode* prev = entry;
                    entry = entry->next;
                    delete prev;
                }
            }
            delete[] htable;
        }

        string convertToLower(string word){
          for (int i=0;i<word.length();i++){
              // cout<<i<<endl;
              word[i] = tolower(word[i]);
              // cout<<word[i];
          }
          return word;

        }

        
        string sortAlpha(string word){
          	sort(word.begin(), word.end());
	          return word;
        }

        /*
         * Hash Function
         */
        int HashFunc(string key)
        {
          // cout<<"Key: "<<key<<endl;
          int hashVal = 0;
          for (int i = 0; i<key.length(); i++)
            hashVal = 37 * hashVal + key[i];
          hashVal %= TABLE_SIZE;
          if (hashVal<0)
            hashVal += TABLE_SIZE;
          // cout<<"hashVal: "<<hashVal<<endl;
          return hashVal;
        }
          
          
        /*
         * insert Element at a key
         */
        void insert(string key, string anagram)
        {
            int hash_v = HashFunc(key);
            HashNode* p = NULL;
            HashNode* en = htable[hash_v];
            while (en!= NULL) {
                p = en;
                en = en->next;
            }
            if (en == NULL) {
                en = new HashNode(key, anagram);
                if (p == NULL) {
                  htable[hash_v] = en;
                } else {
                  p->next = en;
                }
            } else {
                en->anagram = anagram;
            }
          }
      
        void Search(string key)
        {   
          //  cout<<"Search function: "<<key<<endl;
            bool flag = false;
            cout<<key<<": ";
            int hash_val = HashFunc(key);
            // cout<<"Search: Key: "<<key<<", Index: "<<hash_val<<endl;
            HashNode* entry = htable[hash_val];
            while (entry != NULL)
	          {
                cout<<entry->anagram<<" ";
                entry = entry->next;
                flag = true;
            }
            if (!flag)
                cout<<"No Element Found at key: "<<hash_val<<endl;
            cout<<endl;
        }

};
/*
 * Main Contains Menu
 */
int main()
{   
    HashMap1 hashTable;
    
    ifstream fileReader;
    string word, keyWord;
    string inputWord;
    int wordCount = 0;
    fileReader.open("words.txt"); 
    
    if(!fileReader){
      cout<<"File doesn't exist"<<endl;
      exit(1);
    }

    cout<<"*** Reading dictionary ***"<<endl;
    while(!fileReader.eof()){
      word = "";
      fileReader>>word;
      // count++;
      // cout<<word<<endl;
      // cout<<"Word: "<<word<<endl;
      keyWord = hashTable.sortAlpha(word);
      string loweredWord = hashTable.convertToLower(word);
      // loweredWord = hashTable.removeTrailingSpaces(loweredWord);
      // cout<<"Without Spaces: "<<loweredWord.length()<<endl;
      hashTable.insert(keyWord, loweredWord);

     
    }

    ifstream inputReader;
    inputReader.open("input.txt");
    ofstream outputWriter;
    outputWriter.open("output.txt");

    if(!inputReader){
      cout<<"File doesn't exist"<<endl;
    }
    while(!inputReader.eof()){

        inputReader>>inputWord;
        outputWriter << inputWord << ": "<<endl;
        string inputKey = hashTable.sortAlpha(inputWord);
        hashTable.Search(inputKey);

    }
    outputWriter.close();
    inputReader.close();
    fileReader.close();

   
  
}
