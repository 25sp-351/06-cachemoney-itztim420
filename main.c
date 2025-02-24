#include <stdio.h>
#include <string.h>
#include "cache.h"

// Define arrays for ones and tens words
const char *ones[] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", 
                      "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", 
                      "eighteen", "nineteen"};
const char *tens[] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

// Helper function to convert number to words
void num_to_words(int n, char *result) {
    if (n == 0) {
        strcat(result, "zero");
    } else if (n < 20) {
        strcat(result, ones[n]);
    } else if (n < 100) {
        strcat(result, tens[n / 10]);
        if (n % 10 != 0) {
            strcat(result, "-");
            strcat(result, ones[n % 10]);
        }
    } else if (n < 1000) {
        strcat(result, ones[n / 100]);
        strcat(result, " hundred");
        if (n % 100 != 0) {
            strcat(result, " ");
            num_to_words(n % 100, result);
        }
    } else {
        strcat(result, ones[n / 1000]);
        strcat(result, " thousand");
        if (n % 1000 != 0) {
            strcat(result, " ");
            num_to_words(n % 1000, result);
        }
    }
}

// Convert money to text and cache it
void money_to_text(int money, char *result) {
    int dollars = money / 100;
    int cents = money % 100;

    // Check if value is already cached
    if (get_cached_value(money, result)) {
        return;
    }

    char dollars_text[1024] = "";
    char cents_text[1024] = "";

    if (dollars > 0) {
        num_to_words(dollars, dollars_text);
        strcat(result, dollars_text);
        strcat(result, " dollars");
    }

    if (cents > 0) {
        num_to_words(cents, cents_text);
        if (dollars > 0) {
            strcat(result, " and ");
        }
        strcat(result, cents_text);
        strcat(result, " cents");
    }

    if (dollars == 0 && cents == 0) {
        strcpy(result, "zero dollars");
    }

    // Save computed value to cache
    save_cache(money, result);
}

// Main function
int main() {
    int money;

    printf("Welcome to the Money to Text Converter!\n");
    printf("Please enter a money value in cents (e.g., 4734 for $47.34) or a negative value to exit:\n");

    // Load cache before taking input
    load_cache();

    while (1) {
        printf("\nEnter a value in cents: ");
        int result = scanf("%d", &money);

        if (result != 1 || money < 0) {
            break;
        }

        char result_text[2048] = "";
        money_to_text(money, result_text);
        
        printf("\n%5d = %s\n", money, result_text);
    }

    printf("\nThank you for using the Money to Text Converter! Goodbye!\n");

    return 0;
}