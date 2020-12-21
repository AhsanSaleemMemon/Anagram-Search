#include<iostream>
#include<cstdlib>
#include <cstring>
#include<string>
#include<cstdio>
#include <fstream>
#include <cctype>
#include <algorithm>
using namespace std;
const int TABLE_SIZE = 200000; // size of the hashTable
 
class HashNode  // HashNode for a single word anagrams
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

class HashMap // This will contain a 2d pointer of HashNode which will contain 
{             // multiple anagram pointers at each row
    private:
        HashNode** htable;
    public:
        HashMap() // Default Constructor
        {   
            htable = new HashNode*[TABLE_SIZE];
            for (int i = 0; i < TABLE_SIZE; i++)
                htable[i] = NULL;
        }
        ~HashMap() // Destructor
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

        string convertToLower(string word){ // for converting a word to Lower Case
          for (int i=0;i<word.length();i++){
              // cout<<i<<endl;
              word[i] = tolower(word[i]);
              // cout<<word[i];
          }
          return word;
        }
        string sortAlpha(string word){ // Sorting the word to make a hash Key
          	sort(word.begin(), word.end());
	          return word;
        }

        int HashFunc(string key) // Hash Function to generate index from the given key
        {
          // cout<<"Key: "<<key<<endl;
          int hashVal = 0;
          for (int i = 0; i<key.length(); i++)
            hashVal = 43 * hashVal + key[i];
          hashVal %= TABLE_SIZE;
          if (hashVal<0)
            hashVal += TABLE_SIZE;
          // cout<<"hashVal: "<<hashVal<<endl;
          return hashVal;
        }
        void insert(string key, string anagram) // inserting an anagram into the hashTable with the given key
        {
            int hash_val = HashFunc(key);
            HashNode* prev = NULL;
            HashNode* entry = htable[hash_val];
            while (entry!= NULL) {
                prev = entry;
                entry = entry->next;
            }
            if (entry == NULL) {
                entry = new HashNode(key, anagram);
                if (prev == NULL) {
                  htable[hash_val] = entry;
                } else {
                  prev->next = entry;
                }
            } else {
                entry->anagram = anagram;
            }
          }
      
        bool hasPunctuation(string word){
          for(int i=0;i<word.length();i++){
            if(ispunct(word[i]))
              return true;
          }
          return false;
        }
        void Search(string key,ofstream& fout, string word) // Search anagrams of a given word
        {   
          //  cout<<"Search function: "<<key<<endl;
            bool flag = false;
      
            int hash_val = HashFunc(key);
            // cout<<"Search: Key: "<<key<<", Index: "<<hash_val<<endl;
            HashNode* entry = htable[hash_val];
            int count = 0;
            string anagrams[50] = {""};
            while (entry != NULL)
	          {   
              if(entry->anagram!=word){  // all anagrams other than the input word
                anagrams[count] = entry->anagram;
                count++;
              }
             //   cout<<entry->anagram<<" ";
                entry = entry->next;
                flag = true;
            }
            if (!flag)
                cout<<"No Element Found at key: "<<hash_val<<endl;
            fout<<count<<" ";
            cout<<"Anagrams: ";
            for (int i=0;anagrams[i]!="";i++){
              
              cout<<anagrams[i]<<" ";
              fout<<anagrams[i]<<" ";
            }
            fout<<endl;
            cout<<"\n\n";
        }
};

int main()
{   
    HashMap hashTable;
    
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
    while(!fileReader.eof()){ // Reading the dictionary file
      word = "";
      fileReader>>word;
      if(hashTable.hasPunctuation(word)!=true){ // Punctuated words won't be inserted
        string loweredWord = hashTable.convertToLower(word);
        keyWord = hashTable.sortAlpha(loweredWord);
       
      
        hashTable.insert(keyWord, loweredWord);
      }
    }
    cout<<"Reading complete"<<endl;

    ifstream inputReader;
    inputReader.open("input.txt");
    ofstream outputWriter;
    outputWriter.open("output.txt");

    if(!inputReader){
      cout<<"File doesn't exist"<<endl;
    }
    cout<<"\n***Reading Input.txt***\n\n";
    while(!inputReader.eof()){

        inputReader>>inputWord;
        if(hashTable.hasPunctuation(inputWord)!=true){
          cout<<"Word: "<<inputWord<<endl;
          outputWriter << inputWord << ": ";
          string loweredInput = hashTable.convertToLower(inputWord);

          string inputKey = hashTable.sortAlpha(loweredInput);
          cout<<"Hash Key: "<<inputKey<<"\n";
          hashTable.Search(inputKey,outputWriter,loweredInput);
        }

    }
    cout<<"***All Anagrams searched, check the output.txt file***\n";
    outputWriter.close();
    inputReader.close();
    fileReader.close();

   
  
}
