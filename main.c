#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//Prototypes

int int_lenght(int num);
long double my_Pow(long double num, int power);
int digit_count(int num);
void print_line(char *symbol, int times);

struct characters
{
    char *characters;
    int lenght;

};


int main(int argc, char *argv[]) {
    int N = 10;
    int accuracy= 16;

    printf("Enter N (the number of values): ");
    scanf("%i", &N);

    printf("Enter accuracy (how many decimals to show [defaut is 5]): ");
    scanf("%i", &accuracy);
    if (accuracy <= 0)
    {
        accuracy = 10; //defaut
    } else if (accuracy > 16)
    {
        accuracy = 16;
    }

    
    const int Y = N;
    const int X = 3;
    long double k_arr[Y][X];


    for (int i = 0; i < N; i++)
    {
        printf("Enter k_%i: ", i + 1);
        scanf("%Lf", k_arr[i]);
    }
    
    
    /*
    Test values:
    k_arr[0][0] = 0.15;
    k_arr[1][0] = 0.13;
    k_arr[2][0] = 0.45;
    k_arr[3][0] = 0.40;
    k_arr[4][0] = 0.10;
    k_arr[5][0] = 0.20;
    k_arr[6][0] = 0.40;
    k_arr[7][0] = 0.37;
    k_arr[8][0] = 0.55;
    k_arr[9][0] = 0.57;
    */

    //k_avg
    long double k_avg;
    long double sum = 0;

    for (int i = 0; i < Y; i++)
    {
        sum += k_arr[i][0];
    }

    k_avg = sum / N;
    
    
    //Δk
    for (int i = 0; i < N; i++)
    {
        k_arr[i][1] = k_avg - k_arr[i][0];
    }
    

    //Δk² 
    for (int i = 0; i < N; i++)
    {
        k_arr[i][2] = my_Pow(k_arr[i][1], 2);
    }


    // ΣΔk² 
    long double Sum_delta_k_sq = 0;

    for (int i = 0; i < N; i++)
    {
        Sum_delta_k_sq += k_arr[i][2];
    }

    
    // σ
    long double sigma = sqrt(Sum_delta_k_sq / (N * (N - 1))); 

    
    // Output (idk)
    /*
    %10s, string - there will be 10-str_len spaces followed by the string.
    -%10s, string - there will be a string followed by 10-str_len times spaces.
    */

    /*
    N k Δk Δk² 
    N - 1
    k
    k - 1
    Δk - 3
    Δk² - 5

    */
    //char *characters[4][2] = {{"N", 1} , {"k", 1}, {"Δk", 2}, {"Δk²", 3}}; // X - displayed character lenght


    //OUTPUT:

    int Y_characters = 4;
    
    int spaces_l = 1;
    int spaces_r = 1;

    struct characters symbols [4] = {
        {"N", 1},
        {"k", 1},
        {"Δk", 2},
        {"Δk²", 3}
    };

    // N
    printf("|%*s%*s|", spaces_l + symbols[0].lenght, symbols[0].characters, spaces_r, "");

    // k, Δk, Δk²

    int max_int_lenght = 0;
    for (int i = 0; i < N; i++)
    {
        if (max_int_lenght < int_lenght((int)k_arr[i][0]))
        {
            max_int_lenght = int_lenght((int)k_arr[i][0]);
        }
        
    }

    accuracy += max_int_lenght;

    int space = accuracy + 4; 
    for (int i = 1; i < Y_characters; i++)
    {
        int free_space = space - symbols[i].lenght;
        spaces_r = (free_space) / 2;
        spaces_l = free_space - spaces_r;

        printf("%*s%*s|", spaces_l + (int)strlen(symbols[i].characters), symbols[i].characters, spaces_r, "");

    }

    printf("\n");
    print_line("-", (accuracy + 4 + 1) * 3 + 5);

    for (int i = 0; i < Y; i++) {

        // N
        spaces_l = 1;
        spaces_r = 1;
        printf("|%*i%*s|", spaces_l + digit_count(i + 1), i + 1, spaces_r - digit_count(i + 1) + 1, ""); 

        // k, Δk, Δk²
        for (int j = 0; j < X; j++)
        {   

            printf("%*.*Lf%*s|", spaces_l + accuracy + 2, accuracy - max_int_lenght, k_arr[i][j], spaces_r, ""); 

        }
        printf("\n");
        
    }
    print_line("-", (accuracy + 4 + 1) * 3 + 5);

    printf("k_avg is %.*Lf\n", accuracy, k_avg);
    printf("ΣΔk² is %.*Lf\n", accuracy, Sum_delta_k_sq);
    printf("σ is %.*Lf\n", accuracy, sigma);

    printf("k = %.*Lf ⨦ %.*Lf\n", accuracy, Sum_delta_k_sq, accuracy, sigma);
    return 0;
}

// prints this: -------------------------------
void print_line(char *symbol, int times)
{
    for (int i = 0; i < times; i++)
    {
        printf("%s", symbol);
    }
    printf("\n");

}


long double my_Pow(long double num, int power)
{
    long double result = 1;
    for (int i = 0; i < power; i++)
    {
        result = result * num;
    }

    return result;

}

int digit_count(int num) 
{
    int count = 0;
    while (num != 0)
    {
        num /= 10;
        ++count;
    }
    return count;
}

int int_lenght(int num)
{
    int counter = 0;
    while (num != 0)
    {
        num = (int)floor(num / 10);
        counter ++;
    }
    return counter;
}
