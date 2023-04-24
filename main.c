#include "hangman-io.h"
#include "words.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void print_asteriks(char word[], char asteriks[], int word_len) {
    for (int i = 0; i < word_len; i++) {
        printf("%c", asteriks[i]);
    }
    printf("\n");
}

void in_word(char letter, char word[], char asteriks[], int word_len, int *strike_count) {
    int check = 0;
    for (int i = 0; i < word_len; i++) {
        if (word[i] == letter) {
            asteriks[i] = letter;
            check++;
        }
    }
    if (check == 0) {
        printf(not_in_word, letter);
        *strike_count += 1;
        if (max_strikes - *strike_count != 0) {
            printf(not_last_guess, max_strikes - *strike_count);
        }
    }
}

bool victory(char asteriks[]) {
    for (int i = 0; asteriks[i] != '\0'; i++) {
        if (asteriks[i] == '*') {
            return false;
        }
    }
    return true;
}

void check_letter (char word[], char asteriks[], char guessed_aray[], int word_len, bool *win, int *strike_count) {
    bool valid_letter = false;
    char letter = 0;

    print_hangman(*strike_count);
    printf("%s", letter_prompt);
    print_asteriks(word, asteriks, word_len);

    while (!valid_letter) {
        scanf(" %c", &letter);
        if (65 <= letter && letter <= 90) {
            valid_letter = true;
            break;
        }
        else if (97 <= letter && letter <= 122) {
            letter = letter - 'a' + 'A';
            valid_letter = true;
            break;
        } 
        else{
            printf(not_a_letter, letter);
            print_hangman(*strike_count);
            printf("%s", letter_prompt);
            print_asteriks(word, asteriks, word_len);
        }
    }

    bool check = false;
    for (int i = 0; i < 27; i++) {
        if (guessed_aray[i] == letter) {
            check = true;
        }
    }
    guessed_aray[letter-65] = letter;
    
    if (check) {
        printf(already_guessed_letter, letter);
    }

    if (!check) {
        in_word(letter, word, asteriks, word_len, strike_count);
    }
    
    if (victory(asteriks)) {
        *win = true;
    }
}

int main(void) {
    char guessed_array[27];
    bool win = false;
    int strike_count = 0;   
    bool play = true;
    while (play) {
        strike_count = 0;
        win = false; 
        for (int i = 0; i < 27; i++) {
            guessed_array[i] = 0;
        }

        printf(enter_game_number, max_words);
        int word_num = 0;
        while (true) {
            scanf("%d", &word_num);
            if (1 <= word_num && word_num <= max_words) {
                break;
            }
            else {
                printf("%s", invalid_game_number);
                printf(enter_game_number, max_words);
                continue;
            }
        }

        char word[50] = {};
        for (int i = 0; i < strlen(get_word(word_num)); i++) {
            word[i] = get_word(word_num)[i];
        }
        char asteriks[50] = {};
        for (int i = 0; i < strlen(get_word(word_num)); i++) {
            if (word[i] == 32) {
                asteriks[i] = ' ';
            }
            else {
                asteriks[i] = '*';
            }
        }

        while (strike_count < max_strikes && !win) {
            check_letter(word, asteriks, guessed_array, strlen(get_word(word_num)), &win, &strike_count); 
            if (win) {
                printf(congratulations, get_word(word_num));
                printf("%s", play_again);
                char result = 0;
                while (true) {
                    scanf(" %c", &result);
                    if (result == 'y' || result == 'Y') {
                        play = true;
                        break;
                    }
                    else if (result == 'n' || result == 'N') {
                        play = false;
                        break;
                    }
                    else {
                        printf("%s", invalid_play_again_response);
                        printf("%s", play_again);
                    }
                }
            }
            if (strike_count == max_strikes) {
                print_hangman(strike_count);
                printf(game_over, get_word(word_num));
                printf("%s", play_again);
                char result = 0;
                while (true) {
                    scanf(" %c", &result);
                    if (result == 'y' || result == 'Y') {
                        play = true;
                        break;
                    }
                    else if (result == 'n' || result == 'N') {
                        play = false;
                        break;
                    }
                    else {
                        printf("%s", invalid_play_again_response);
                        printf("%s", play_again);
                    }
                }
            }
        }
    }

}
