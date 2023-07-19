#include<stdio.h>
#include<ctype.h>
# define MAX 26
char circularQueue[MAX];
int front = -1;
int rear = -1;


// Inserting Alphabets into the queue
void queueinsert(char item) {
  if((front == 0 && rear == MAX-1) || (front == rear+1))
  {
    printf("\nQueue Overflow ");
    return;
  }
  if(front == -1)
  {
    front = 0;
    rear = 0;
  }
  else
  {
    if(rear == MAX-1)
      rear = 0;
  else
    rear = rear+1;
  }
  circularQueue[rear] = item;
}


// Encrypting each letter
char encrypt(char letter) {
  int encryptedLetterAscii;
  char encryptedLetter;
  int queueLetter =(int) circularQueue[front];
  int letter1 = (int) letter;
  int first = (queueLetter%65)+1;
  int second = (letter1%65)+1;
  encryptedLetterAscii = ((((queueLetter%65)+1) + ((letter1%65)+1) )%26);
  if(encryptedLetterAscii == 0) {
    encryptedLetterAscii = 90;
  } 
  else {
    encryptedLetterAscii+= 64;
  }
  encryptedLetter = (char) encryptedLetterAscii;
  return encryptedLetter;
}

// Text Encryption
char* encryption(char key, char *message) {
  char encryptedLetter;
  char* encryptedMessage;
  int i = 0;
  front = key-1;
  if(front == 0) {
    rear = 25;
  }
  else {
    rear = key-2;
  }
  
  while(message[i]!='\0') {
    if(!isspace(message[i])) {
      encryptedLetter = encrypt(message[i]);
      encryptedMessage[i] = encryptedLetter;
      front++;
    }
    else {
      encryptedMessage[i] = message[i];
    }
    i++;
  }
  encryptedMessage[i] = '\0';
  return encryptedMessage;
}

// Decrypting each letter
char decrypt(char letter) 
{
  int decryptedLetterAscii;
  char decryptedLetter;
  int queueLetter =(int) circularQueue[front];
  int letter1 = (int) letter;
  int first = (queueLetter%65)+1;
  int second = (letter1%65)+1;
  decryptedLetterAscii =  (((letter1%65)+1)-((queueLetter%65)+1) ) ;
  if(decryptedLetterAscii < 0) {
    decryptedLetterAscii +=26;
  }
  decryptedLetterAscii +=64;
  decryptedLetter = (char) decryptedLetterAscii;
  return decryptedLetter;
}



//Text decryption
char* decryption(char key, char *message)
 {
  char decryptedLetter;
  char* decryptedMessage;
  int i = 0;
  front = key-1;
  if(front == 0) {
    rear = 25;
  }
  else
   {
    rear = key-2;
  }
  
  while(message[i]!='\0') {
    if(!isspace(message[i])) {
      decryptedLetter = decrypt(message[i]);
      decryptedMessage[i] = decryptedLetter;
      front++;
    }
    else {
      decryptedMessage[i] = message[i];
    }
    i++;
  }
  decryptedMessage[i] = '\0';
  return decryptedMessage;
}

int main() {
  FILE *fptr1;
  FILE *fptr2;
    int ch;
    int choice;
    int key;
    int queueIndex = 0;
    char queueElement;
    char inputMessage1[300];
    char* encryptedMessage;
    char* decryptedMessage;

    for(int queueIndex = 65; queueIndex <= 90; queueIndex++) {
      queueElement = (char) queueIndex;
      queueinsert(queueElement);
    }

    printf("\n Select the operation you want to perform");
    printf("\n 1. Encryption");
    printf("\n 2. Decryption\n");
    scanf("%d",&ch);

    if(ch==1) {
      printf("\n Press \n1.To encrypt message from standard input\n2.To encrypt from file\n");
      scanf("%d",&choice);
      if(choice==1)
      {
      printf("\n Select a secret key between 1 to 26 and Enter the message to be encrypted:");
      scanf("%d\n", &key);
      fgets(inputMessage1, sizeof(inputMessage1), stdin);
      encryptedMessage = encryption(key, inputMessage1);
      printf("\nEncrypted Message: %s", encryptedMessage);
      printf("\nWriting to file.....\n");
      fptr1=fopen("file1","w");
      fprintf(fptr1,"%s",encryptedMessage);
      printf("\nContents written to file1");
      fclose(fptr1);
      }
      else if(choice==2)
      {
        printf("Enter the secret key :");
        scanf("%d",&key);
          FILE *fptr2=fopen("message.txt","r");
          fgets(inputMessage1, sizeof(inputMessage1),fptr2);
          printf("Contents of Original file\n");
          puts(inputMessage1);
          fclose(fptr2);
          encryptedMessage = encryption(key,inputMessage1); 
          printf("\nEncrypted Message: %s", encryptedMessage);
          printf("\nWriting to file.....\n");
          fptr1=fopen("encrypted.txt","w");
          fprintf(fptr1,"%s",encryptedMessage);
          printf("\nContents written to encrypted.txt");
          fclose(fptr1); 
      }    
    }
    else if(ch==2) 
    {  
      printf("\n Press \n1.To decrypt message from standard input\n2.To decrypt from file\n");
      scanf("%d",&choice);
      if(choice==1)
      {
        printf("\n Select a secret key between 1 to 26 and Enter the message to be decrypted:");
        scanf("%d\n", &key);
        fgets(inputMessage1, sizeof(inputMessage1), stdin);
        decryptedMessage = decryption(key, inputMessage1);
        printf("\nDecrypted Message: %s", decryptedMessage);
        printf("\nWriting to file.....\n");
        fptr2=fopen("file2","w");
        fprintf(fptr2,"%s",decryptedMessage);
        printf("\nContents written to file2");
        fclose(fptr2);
      }
      else if(choice==2)
      {
        printf("Enter the secret key :");
        scanf("%d",&key);
          FILE *fptr1=fopen("encrypted.txt","r");
          fgets(inputMessage1, sizeof(inputMessage1),fptr1);
          printf("Contents of file\n");
          puts(inputMessage1);
          fclose(fptr1);
          decryptedMessage = decryption(key,inputMessage1);
          printf("\nDecrypted Message:%s", decryptedMessage);  
          printf("\nWriting to file.....\n");
          fptr2=fopen("decrypted.txt","w");
          fprintf(fptr2,"%s",decryptedMessage);
          printf("\nContents written to decrypted.txt");
          fclose(fptr2); 
      }
    }
  return 0;
}
