#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

int phi_insertion(int size, int occupied_space);
int phi_deletion(int size, int occupied_space);

int main()
{
    //All parameters are initialized to 0.
    int i, size = 0, occupied_space = 0;
    int amo_cost = 0, cost_i = 0, phi_i = 0, phi_i_minus_1 = 0;
    char ops[MAX];
    FILE *fptr;

    //Get the sequence of operations from the user:
    printf("Enter the sequence of operations:\n");
      scanf("%s", ops);

    //Open a file to store the data for each operation:
    fptr = fopen("D:\\Professional\\Projects\\Data Structures in C\\Amortized Analysis for Dynamic Table\\Data.txt", "w");
    if(!fptr) //If there's a file error...
    {
        printf("FILE_ERROR: File does not exist!\n");
        exit(1);
    }
    //Give the column names:
    fprintf(fptr, "i\tOperation\tSize_i\tNum_i\tC_i\tPhi_i\tC_i'");

    //Print the column names:
    printf("IND.\tOPER.\tSIZE\tNUM\tCOST_I\tPHI_I\tAMORTIZED COST");

    for(i = 0; i < strlen(ops); i++)
    {
        //For insertion operation:
        if(ops[i] == 'I')
        {
            if(!size) //In case the table is empty.
                size = 1;

            //Expansion condition:
            if(size == occupied_space)
            {
                cost_i = occupied_space + 1;
                size *= 2;
            }
            else
                cost_i = 1;

            occupied_space += 1;

            phi_i = phi_insertion(size, occupied_space);
        }

        //For deletion operation:
        else if(ops[i] == 'D')
        {
            if(!size) //In case the table is empty.
            {
                printf("ERROR: Table empty!\n");
                break;
            }

            occupied_space -= 1;

            //Contraction condition:
            if(occupied_space / (float)size <= 0.25)
            {
                cost_i = occupied_space + 1;
                size /= 2;
            }
            else
                cost_i = 1;

            phi_i = phi_deletion(size, occupied_space);
        }

        //Get the amortized cost:
        amo_cost = cost_i + phi_i - phi_i_minus_1;

        phi_i_minus_1 = phi_i;

        //Print the output:
        printf("\n%d\t%c\t%d\t%d\t%d\t%d\t%d",
                i+1, ops[i],size, occupied_space, cost_i, phi_i, amo_cost);

        //Store the output:
        fprintf(fptr, "\n%d\t%c\t%d\t%d\t%d\t%d\t%d",
                i+1, ops[i],size, occupied_space, cost_i, phi_i, amo_cost);
    }
    //Close the file:
    fclose(fptr);

    return 0;
}

int phi_insertion(int size, int occupied_space)
/**
* Brief: Utility function. Calculates the potential for a
*        single insertion operation.
*
* Argument(s):
*   size - Current capacity of the table.
*   occupied_space - Total number of elements in the table.
*/
{
    return 2 * occupied_space - size;
}

int phi_deletion(int size, int occupied_space)
/**
* Brief: Utility function. Calculates the potential for a
*        single deletion operation.
*
* Argument(s):
*   size - Current capacity of the table.
*   occupied_space - Total number of elements in the table.
*/
{
    float alpha = occupied_space / (float) size;
    if(alpha >= 0.5)
        return 2 * occupied_space - size;
    else
        return size / 2 - occupied_space;
}
