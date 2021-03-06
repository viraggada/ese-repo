#include <stdlib.h>
#include <stdio.h>

/*Declaring Function prototype*/
char reverse(char *str, int lenght);

int main()
{   /*Initialize variables*/
    int size,i;
    char value;

    char str1[17]= "This is a string.";
    int length1 = 17;
    
    printf("\nFirst String is: ");
    for(i=0;i<length1;i++)
       {
        printf("%x",*(str1+i));
       }
    /*This is a string.*/
    char value1 = reverse(str1,length1); 

    char str2[18]= "some NUMmbers12345";
    int length2 = 18;
    printf("\n\nSecond String is: ");
    for(i=0;i<length2;i++)
       {
        printf("%x",*(str2+i));
       }
    /*some NUMmbers12345*/
    char value2 = reverse(str2,length2);
    
    char str3[30] = "Does it reverse \n\0\t correctly?";
    int length3 = 30;
    printf("\n\nThird String is: ");

    for(i=0;i<length3;i++)
       {
        printf("%x",*(str3+i));
       }
    /*Does it reverse \n\0\t correctly?*/
    char value3 = reverse(str3,length3);
    printf("\n");

    /*Read array size*/
    /*/printf("Enter the length of the array: ");
    scanf("%d",&size);
    char str[size];

    for(i = 0; i<size;i++)
       { str[i]='\0';
       }
    */
    /*Read array*/
    /*printf("Enter the array: ");
    for(i = 0; i<=size;i++)
      {scanf("%x",&str[i]);}
    */
   /* value = reverse(str,size);

    if (value == '1')
       printf("\nArray is Empty");
    else if (value =='2')
             printf("\nLength is incorrect");
         else if (value == 0)
                 printf("\nArray is reversed correctly");*/

    return 1;
}

/*Function to reverse the array
  It receives the array pointer and length
  and returns some information about the array*/
char reverse(char *str, int length)
{
    int j=0;
    char temp;
    char *first = str;
    char *last = str + length-1;

    if(*first == '\0')/*Check for empty array*/
       return '1';
    else if (length <= 0) /*Check for incorrect length*/
           { return '2';}
         else {for(j=0;j<length/2;j++) /*Reverse if previous cases are false*/
                 {
                  temp = *first;
                  *first = *last;
                  *last = temp;
                  last--;
                  first++;
                 }

               printf("\nThe reverse array is as follows:");
               for(j=0;j<length;j++)
                 {
                  printf("%x",*(str+j));
                 }
               return 0;}
}
