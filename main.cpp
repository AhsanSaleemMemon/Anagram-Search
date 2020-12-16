#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;


int main() {
  ifstream fileReader;
  string word;
  int wordCount = 0;
  fileReader.open("words.txt"); 
  
  if(!fileReader){
    cout<<"File doesn't exist"<<endl;
    exit(1);
  }

  cout<<"*** Reading dictionary ***"<<endl;
  while(!fileReader.eof()){
    getline(fileReader,word);
    // cout<<word<<endl;
    wordCount++;
  }
  cout<<"Reading Complete\n";

  fileReader.close();

  cout<<"Total Words Read: "<<wordCount<<endl;
}