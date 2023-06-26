#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 16382000
#include <stdio.h>
#include <alg.h>
#include <string.h>

long long find_transition(long long** arr, int y, int x, char* symbol) {
    int res = -1;
    for (int i = 1; i < x; ++i) {
        if (arr[y][i] != -1) {
            char val = arr[y][i] / 10000000000 - 100 + 33;
            if (val == *symbol) {
                res = i;
                return res;
            }
        }
    }
    return res;
}

long long find_state(long long** arr, int state, int y) {
    for (int i = 0; i < y; ++i) {
        if (arr[i][0] == state) {
            return i;
        }
    }
    return -1;
}

long long findX(long long** arr, int* state, int y, int x) {
    for (size_t j = 1; j < x; ++j) {
        if (arr[y][j] == -1) {
            return j;
        }
    }

    return -1;
}

int main() {
    short power;

    scanf("%d", &power);
    int* states = (int*)malloc(power * sizeof(int));
    for (size_t i = 0; i < power; i++)
    {
        scanf("%d", &states[i]);
    }

    int start, stop, power_transition;
    scanf("%d%d%d", &start, &stop, &power_transition);

    long long** transition_table = malloc(power * sizeof(long long*));
    for (int i = 0; i < power; ++i) {
        transition_table[i] = calloc(power_transition + 1, sizeof(long long));
        transition_table[i][0] = states[i];
    }

    for (size_t i = 0; i < power; ++i) {
        transition_table[i][0] = i;
        for (size_t j = 1; j < power_transition; ++j) {
            transition_table[i][j] = -1;
        }
    }

    for (int i = 0; i < power_transition; ++i) {
        int state;
        scanf("%d", &state);

        int pos_y = find_state(transition_table, state, power);
        int pos_x = findX(transition_table, &state, pos_y, power_transition);

        long long transition;
        scanf("%lld", &transition);

        transition_table[pos_y][pos_x] = transition;
    }
    char card[200000];
    for (int i = 0; i < 200000; ++i) {
        card[i] = '_';
    }

    char start_state[100000];
    scanf("%s", start_state);

    int pos = 0;
    while (start_state[pos] != '\0') {
        card[pos + 100000] = start_state[pos];
        ++pos;
    }

    int transition_counter = 0;
    int curr_state_name = start;
    int curr_tran_ind = 0;

    pos = 100000;

    while (transition_counter < 100000) {
        char symbol = card[pos];

        int curr_tran_ind = find_transition(transition_table, curr_state_name, power_transition + 1, &symbol);

        if (curr_tran_ind == -1) {
            printf("FAIL after %d transition\n", transition_counter);
            int pos_l = 0, pos_r = 0;
            for (int i = 0; i < 2000000; ++i) {
                if (card[i] != '_') {
                    pos_l = i;
                    break;
                }
            }

            for (int i = 200000 - 1; i >= pos_l; --i) {
                if (card[i] != '_') {
                    pos_r = i;
                    break;
                }
            }
            for (int i = pos_l; i <= pos_r; ++i) {
                printf("%c", card[i]);
            }
            printf("\n");

            printf("%d %d\n", pos - pos_l, transition_table[curr_state_name][0]);

            exit(0);
        }
        else {
            card[pos] = (transition_table[curr_state_name][curr_tran_ind] % 10000 / 10 + 33 - 100);
            if (transition_table[curr_state_name][curr_tran_ind] % 10 == 0) {
                --pos;
                curr_state_name = (transition_table[curr_state_name][curr_tran_ind]
                    % 10000000000) / 10000 - 100000;
                ++transition_counter;
            }
            else if (transition_table[curr_state_name][curr_tran_ind] % 10 == 1) {
                ++pos;
                curr_state_name = (transition_table[curr_state_name][curr_tran_ind]
                    % 10000000000) / 10000 - 100000;
                ++transition_counter;
            }
            else {
                if (transition_table[curr_state_name][curr_tran_ind] % 10000000000 / 10000 - 100000 == stop
                    && transition_table[curr_state_name][curr_tran_ind] % 10 == 2) {
                    ++transition_counter;
                    long long s = transition_table[curr_state_name][curr_tran_ind];
                    printf("%s", "STOP after ");
                    printf("%d%s\n", transition_counter, " transition");

                    int pos_l = 0;
                    for (int i = 0; i < 2000000; ++i) {
                        if (card[i] != '_') {
                            pos_l = i;
                            break;
                        }
                    }

                    int pos_r = 0;

                    for (int i = 200000 - 1; i >= pos_l; --i) {
                        if (card[i] != '_') {
                            pos_r = i;
                            break;
                        }
                    }
                    for (int i = pos_l; i <= pos_r; ++i) {
                        printf("%c", card[i]);
                    }
                    printf("\n");

                    printf("%i %i", (transition_table[curr_state_name][curr_tran_ind] % 10000000000) / 10000 - 100000, pos - pos_l);


                    exit(0);
                }
                else {
                    ++transition_counter;
                    curr_state_name = (transition_table[curr_state_name][curr_tran_ind]
                        % 10000000000) / 10000 - 100000;
                }
            }
        }
    }

    printf("%s\n", "MADE 1000000 transitions ");

    int pos_l = 0;
    for (int i = 0; i < 2000000; ++i) {
        if (card[i] != '_') {
            pos_l = i;
            break;
        }
    }

    int pos_r = 0;

    for (int i = 200000 - 1; i >= pos_l; --i) {
        if (card[i] != '_') {
            pos_r = i;
            break;
        }
    }
    for (int i = pos_l; i <= pos_r; ++i) {
        printf("%c", card[i]);
    }

    printf("\n");

    int val = transition_table[curr_state_name][0];

    printf("%i %i", val, pos - pos_l);
    exit(0);
    return 1;
}
