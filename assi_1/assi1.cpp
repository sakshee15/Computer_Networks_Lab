#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char binaryInput[100];
int xPos, yPos;

void up(float length) {
   line(xPos, yPos, xPos, yPos - 2 * length * 10); // Draw vertical line from current position up
   yPos -= 2 * length * 10;
}

void down(float length) {
   line(xPos, yPos, xPos, yPos + 2 * length * 10); // Draw vertical line from current position down
   yPos += 2 * length * 10;
}

void horizontal(float length) {
   line(xPos, yPos, xPos + 2 * length * 10, yPos); // Draw horizontal line from current position
   xPos += 2 * length * 10;
}

void uniPolar() {
   int length = strlen(binaryInput);
   for (int i = 0; i < length; i++) {
      if (i == 0) {                               
         if (binaryInput[i] == '1') {
            up(1);
            horizontal(1);
         } else if (binaryInput[i] == '0') {
            horizontal(1);
         }
      } else {
         if (binaryInput[i] == '1' && binaryInput[i - 1] != '1') {
            up(1);
            horizontal(1);
         } else if (binaryInput[i] == '0' && binaryInput[i - 1] != '0') {
            down(1);
            horizontal(1);
         } else if (binaryInput[i] == '1' && binaryInput[i - 1] == '1') {
            horizontal(1);
         } else if (binaryInput[i] == '0' && binaryInput[i - 1] == '0') {
            horizontal(1);
         }
      }
   }
}

void NRZ_L() {
   int length = strlen(binaryInput);
   for (int i = 0; i < length; i++) {
      if (i == 0) {
         if (binaryInput[i] == '1') {
            down(1);
            horizontal(1);
         } else if (binaryInput[i] == '0'){
            up(1);
            horizontal(1);

         }

      } else {

         if (binaryInput[i] == '1' && binaryInput[i - 1] != '1') {
            down(2);
            horizontal(1);
         } else if (binaryInput[i] == '0' && binaryInput[i - 1] != '0') {
            up(2);
            horizontal(1);

         } else if (binaryInput[i] == '1' && binaryInput[i - 1] == '1') {

            horizontal(1);
         } else if (binaryInput[i] == '0' && binaryInput[i - 1] == '0') {
            horizontal(1);

         }

      }
   }
}

void NRZ_I() {
   int flag = 0;
   int length = strlen(binaryInput);
   for (int i = 0; i < length; i++) {
      if (i == 0) {
         if (binaryInput[i] == '1') {
            down(1);
            horizontal(1);
         } else if (binaryInput[i] == '0')

         {
            up(1);
            horizontal(1);
            flag = 1;
         }

      } else {
         if (binaryInput[i] == '0') {
            horizontal(1);
         } else if (binaryInput[i] == '1' && flag == 1) {
            down(2);
            horizontal(1);
            flag = 0;
         } else if (binaryInput[i] == '1' && flag == 0) {
            up(2);
            horizontal(1);
            flag = 1;
         }

      }
   }
}

void RZ() {
   int length = strlen(binaryInput);
   for (int i = 0; i < length; i++) {
      if (binaryInput[i] == '0') {
         down(1);
         horizontal(0.5);
         up(1);
         horizontal(0.5);

      } else if (binaryInput[i] == '1')
      {
         up(1);
         horizontal(0.5);
         down(1);
         horizontal(0.5);
      }
   }
}

void manchester() {
   int length = strlen(binaryInput);
   for (int i = 0; i < length; i++) {
      if (i == 0) {
         if (binaryInput[i] == '1') {
            down(1);
            horizontal(0.5);
            up(2);
            horizontal(0.5);
         } else if (binaryInput[i] == '0') {
            up(1);
            horizontal(0.5);
            down(2);
            horizontal(0.5);
         }
      } else {

         if (binaryInput[i] == '1' && binaryInput[i - 1] != '1') {
            horizontal(0.5);
            up(2);
            horizontal(0.5);
         } else if (binaryInput[i] == '0' && binaryInput[i - 1] != '0') {
            horizontal(0.5);
            down(2);
            horizontal(0.5);

         } else if (binaryInput[i] == '1' && binaryInput[i - 1] == '1') {
            down(2);
            horizontal(0.5);
            up(2);
            horizontal(0.5);
         } else if (binaryInput[i] == '0' && binaryInput[i - 1] == '0') {
            up(2);
            horizontal(0.5);
            down(2);
            horizontal(0.5);

         }

      }
   }
}

void diff_manchester() {
   int length = strlen(binaryInput);
   int flag = 0;
   for (int i = 0; i < length; i++) {
      if (i == 0) {
         if (binaryInput[i] == '1') {
            up(1);
            horizontal(0.5);
            down(2);
            horizontal(0.5);
            flag=1;
         } else if (binaryInput[i] == '0') {
            down(1);
            horizontal(0.5);
            up(2);
            horizontal(0.5);
            flag = 0;
         }
      } else {
         if (binaryInput[i] == '1' && flag == 1) {
            horizontal(0.5);
            up(2);
            horizontal(0.5);
            flag=0;
         } else if (binaryInput[i] == '0' && flag == 1) {
            up(2);
            horizontal(0.5);
            down(2);
            horizontal(0.5);
         } else if (binaryInput[i] == '1' && flag == 0) {
            horizontal(0.5);
            down(2);
            horizontal(0.5);
            flag=1;
         } else if (binaryInput[i] == '0' && flag == 0) {
            down(2);
            horizontal(0.5);
            up(2);
            horizontal(0.5);
         }
      }
   }
}

int main() {
   int gdriver = DETECT;
   int gmode;
   int err;
   int c;

   initgraph( & gdriver, & gmode, "C:\\Turboc3\\BGI");

   err = graphresult();
   if (err != grOk) {
      printf("Graphics Error: %s\n", grapherrormsg(err));
      return 0;
   }
   //take input
   printf("Enter binary input: ");
   scanf("%s", binaryInput);
   //choose encoding technique
   printf("1.UniPolar Encoding\n2.NRZ-L Encoding\n3.NRZ-I Encoding\n4.RZ Encoding\n5.Manchester Encoding\n6.Differential Manchester Encoding");
   printf("\nEnter your choice: ");
   scanf("%d",&c);
   clrscr();
   printf("Given input - %s ",binaryInput);
   
   // Draw x-axis
   line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);

   // Draw y-axis
   line(getmaxx() / 2, 0, getmaxx() / 2, getmaxy());
   
   // determine origin position
   xPos = getmaxx() / 2;
   yPos = getmaxy() / 2;
   
   //set color for encoding 
   setcolor(RED);
   switch (c) {
   case 1:
      printf("\t\t\tUniPolar encoding\t\t\t");
      uniPolar();
      break;
   case 2:
      printf("\t\t\tNRZ-L encoding\t\t\t\t");
      NRZ_L();
      break;
   case 3:
      printf("\t\t\tNRZ-I encoding\t\t\t\t");
      NRZ_I();
      break;
   case 4:
      printf("\t\t\tRZ encoding\t\t\t\t");
      RZ();
      break;
   case 5:
      printf("\t\t\tManchester encoding\t\t\t");
      manchester();
      break;
   case 6:
   	printf("\t\tDifferential Manchester encoding\t\t");
      diff_manchester();
      break;
   default:
      printf("Invalid choice!!!");
      exit(0);
   }
   getch();
   closegraph();
   return 0;
}
